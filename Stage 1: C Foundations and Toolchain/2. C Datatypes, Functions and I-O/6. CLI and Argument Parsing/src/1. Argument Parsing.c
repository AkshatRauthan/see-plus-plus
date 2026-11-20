#include "../include/cli.h"

#include <errno.h>
#include <stdbool.h>
#include <string.h>

/*
 * Validates option definitions.
 *
 * Rejects:
 * - Missing or empty long names.
 * - Long names containing '='.
 * - Duplicate long names.
 * - Duplicate short names.
 * - Short names that cannot be represented safely in an option string.
 */
static int ValidateOptions(
    CliOption options[],
    size_t option_count
) {
    for (size_t i = 0; i < option_count; i++) {
        if (options[i].long_name == NULL ||
            options[i].long_name[0] == '\0' ||
            strchr(options[i].long_name, '=') != NULL) {
            errno = EINVAL;
            return -1;
        }

        if (options[i].short_name != '\0') {
            unsigned char short_name =
                (unsigned char)options[i].short_name;

            if (short_name < 33 || short_name > 126 ||
                short_name == ':' ||
                short_name == '?' ||
                short_name == '-') {
                errno = EINVAL;
                return -1;
            }
        }

        for (size_t j = 0; j < i; j++) {
            if (strcmp(
                options[i].long_name,
                options[j].long_name
            ) == 0) {
                errno = EINVAL;
                return -1;
            }

            if (options[i].short_name != '\0' &&
                options[i].short_name == options[j].short_name) {
                errno = EINVAL;
                return -1;
            }
        }
    }

    return 0;
}

/*
 * Finds an option using its long name.
 *
 * Returns the matching index or option_count if it does not exist.
 */
static size_t FindLongOption(
    const char *name,
    size_t length,
    CliOption options[],
    size_t option_count
) {
    for (size_t i = 0; i < option_count; i++) {
        if (strlen(options[i].long_name) == length &&
            strncmp(options[i].long_name, name, length) == 0) {
            return i;
        }
    }

    return option_count;
}

/*
 * Finds an option using its short character.
 *
 * Returns the matching index or option_count if it does not exist.
 */
static size_t FindShortOption(
    char name,
    CliOption options[],
    size_t option_count
) {
    for (size_t i = 0; i < option_count; i++) {
        if (options[i].short_name == name && name != '\0') {
            return i;
        }
    }

    return option_count;
}

/*
 * Assigns a parsed option value.
 *
 * Boolean flags must not receive values.
 * Value-taking options must receive a non-empty value.
 * Duplicate options are rejected.
 */
static int SetOption(CliOption *option, const char *value) {
    if (option->seen) {
        errno = EINVAL;
        return -1;
    }

    if (option->requires_value) {
        if (value == NULL || value[0] == '\0') {
            errno = EINVAL;
            return -1;
        }

        option->value = value;
    } else {
        if (value != NULL) {
            errno = EINVAL;
            return -1;
        }
    }

    option->seen = true;

    return 0;
}

/*
 * Parses command-line options.
 *
 * argv[0] is the first argument to parse.
 * The caller passes argc - 1 and argv + 1 when parsing
 * arguments belonging to a subcommand.
 */
int cli_parse_options(
    int argc,
    char *argv[],
    CliOption options[],
    size_t option_count,
    const char *positionals[],
    size_t positional_capacity,
    size_t *positional_count
) {
    if (positional_count == NULL) {
        errno = EINVAL;
        return -1;
    }

    *positional_count = 0;

    if (argc < 0 ||
        argv == NULL ||
        (option_count > 0 && options == NULL) ||
        (positional_capacity > 0 && positionals == NULL)) {
        errno = EINVAL;
        return -1;
    }

    if (ValidateOptions(options, option_count) != 0) {
        return -1;
    }

    // Reset parser state so option definitions can be reused.
    for (size_t i = 0; i < option_count; i++) {
        options[i].seen = false;
        options[i].value = NULL;
    }

    bool options_enabled = true;

    for (int i = 0; i < argc; i++) {
        const char *argument = argv[i];

        if (argument == NULL) {
            errno = EINVAL;
            return -1;
        }

        // Everything after "--" is positional input.
        if (options_enabled && strcmp(argument, "--") == 0) {
            options_enabled = false;
            continue;
        }

        // Parse long options: --name or --name=value.
        if (options_enabled &&
            argument[0] == '-' &&
            argument[1] == '-') {

            const char *name = argument + 2;
            const char *equals = strchr(name, '=');

            size_t name_length = equals != NULL
                ? (size_t)(equals - name)
                : strlen(name);

            if (name_length == 0) {
                errno = EINVAL;
                return -1;
            }

            size_t index = FindLongOption(
                name,
                name_length,
                options,
                option_count
            );

            if (index == option_count) {
                errno = EINVAL;
                return -1;
            }

            const char *value = equals != NULL
                ? equals + 1
                : NULL;

            if (options[index].requires_value && value == NULL) {
                if (i + 1 >= argc) {
                    errno = EINVAL;
                    return -1;
                }

                value = argv[++i];
            }

            if (SetOption(&options[index], value) != 0) {
                return -1;
            }

            continue;
        }

        // Parse short options: -n or -n=value.
        if (options_enabled &&
            argument[0] == '-' &&
            argument[1] != '\0') {

            const char *name = argument + 1;

            // Short-option clustering is not supported.
            if (name[1] != '\0' && name[1] != '=') {
                errno = EINVAL;
                return -1;
            }

            size_t index = FindShortOption(
                name[0],
                options,
                option_count
            );

            if (index == option_count) {
                errno = EINVAL;
                return -1;
            }

            const char *value = name[1] == '='
                ? name + 2
                : NULL;

            if (options[index].requires_value && value == NULL) {
                if (i + 1 >= argc) {
                    errno = EINVAL;
                    return -1;
                }

                value = argv[++i];
            }

            if (SetOption(&options[index], value) != 0) {
                return -1;
            }

            continue;
        }

        // Collect positional arguments.
        if (*positional_count >= positional_capacity) {
            errno = E2BIG;
            return -1;
        }

        positionals[*positional_count] = argument;
        (*positional_count)++;
    }

    return 0;
}
