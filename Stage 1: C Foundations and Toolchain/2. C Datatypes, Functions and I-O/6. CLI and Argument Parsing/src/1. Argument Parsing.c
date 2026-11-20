
#include "../include/cli.h"

#include <errno.h>
#include <stdbool.h>
#include <string.h>

/*
 * Finds an option using its long name.
 *
 * Returns the matching option index or -1 if it does not exist.
 */
static int FindLongOption(const char *name, size_t length, CliOption options[],
						  size_t option_count) {
	for (size_t i = 0; i < option_count; i++) {
		if (strlen(options[i].long_name) == length &&
			strncmp(options[i].long_name, name, length) == 0) {
			return (int)i;
		}
	}

	return -1;
}

/*
 * Finds an option using its short character.
 *
 * Returns the matching option index or -1 if it does not exist.
 */
static int FindShortOption(char name, CliOption options[],
						   size_t option_count) {
	for (size_t i = 0; i < option_count; i++) {
		if (options[i].short_name == name && name != '\0') {
			return (int)i;
		}
	}

	return -1;
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
 * argv[0] is expected to be the command name.
 * The caller passes argc - 1 and argv + 1 when parsing
 * arguments belonging to a subcommand.
 */
int cli_parse_options(int argc, char *argv[], CliOption options[],
					  size_t option_count, const char *positionals[],
					  size_t positional_capacity, size_t *positional_count) {
	if (argc < 0 || argv == NULL || (option_count > 0 && options == NULL) ||
		(positional_capacity > 0 && positionals == NULL) ||
		positional_count == NULL) {
		errno = EINVAL;
		return -1;
	}

	*positional_count = 0;

	// Reset parser state so the option definitions can be reused.
	for (size_t i = 0; i < option_count; i++) {
		options[i].seen = false;
		options[i].value = NULL;

		if (options[i].long_name == NULL) {
			errno = EINVAL;
			return -1;
		}
	}

	bool options_enabled = true;

	for (int i = 0; i < argc; i++) {
		const char *argument = argv[i];

		if (argument == NULL) {
			errno = EINVAL;
			return -1;
		}

		// Everything after "--" is treated as positional input.
		if (options_enabled && strcmp(argument, "--") == 0) {
			options_enabled = false;
			continue;
		}

		// Parse long options: --name or --name=value.
		if (options_enabled && argument[0] == '-' && argument[1] == '-') {

			const char *name = argument + 2;
			const char *equals = strchr(name, '=');

			size_t name_length =
				equals != NULL ? (size_t)(equals - name) : strlen(name);

			if (name_length == 0) {
				errno = EINVAL;
				return -1;
			}

			int index =
				FindLongOption(name, name_length, options, option_count);

			if (index < 0) {
				errno = EINVAL;
				return -1;
			}

			const char *value = equals != NULL ? equals + 1 : NULL;

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
		if (options_enabled && argument[0] == '-' && argument[1] != '\0') {

			const char *name = argument + 1;

			if (name[0] == '\0' || name[1] != '\0') {
				if (name[0] == '\0' || name[1] != '=') {
					errno = EINVAL;
					return -1;
				}
			}

			int index = FindShortOption(name[0], options, option_count);

			if (index < 0) {
				errno = EINVAL;
				return -1;
			}

			const char *value = NULL;

			if (name[1] == '=') {
				value = name + 2;
			}

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
