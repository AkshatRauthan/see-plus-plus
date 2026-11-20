#ifndef _POSIX_C_SOURCE
#define _POSIX_C_SOURCE 200809L
#endif

#include "../include/cli.h"

#include <errno.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/*
 * Validates option definitions before passing them to getopt().
 *
 * getopt() represents short options as characters in an option
 * string, so short names must be printable and must not conflict
 * with its special characters.
 */
static int ValidateOptions(CliOption options[], size_t option_count) {
	for (size_t i = 0; i < option_count; i++) {
		if (options[i].long_name == NULL || options[i].long_name[0] == '\0' ||
			strchr(options[i].long_name, '=') != NULL) {
			errno = EINVAL;
			return -1;
		}

		if (options[i].short_name != '\0') {
			unsigned char name = (unsigned char)options[i].short_name;

			if (name < 33 || name > 126 || name == ':' || name == '?' ||
				name == '-') {
				errno = EINVAL;
				return -1;
			}
		}

		for (size_t j = 0; j < i; j++) {
			if (strcmp(options[i].long_name, options[j].long_name) == 0) {
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
 * Assigns the value returned by getopt().
 *
 * Duplicate options are rejected.
 * Options requiring values must receive non-empty values.
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
 * Parses short command-line options using POSIX getopt().
 *
 * getopt() normally expects argv[0] to contain the program name.
 * This project's parser interface receives only the arguments,
 * so a temporary argv array is created with a dummy program name.
 *
 * The temporary array also prevents getopt() implementations
 * that reorder argv elements from modifying the caller's array.
 *
 * Long options are not supported by POSIX getopt().
 *
 * Returns:
 *     0  on success.
 *    -1  on invalid, unknown, duplicate, or missing arguments.
 */
int cli_parse_options_getopt(int argc, char *argv[], CliOption options[],
							 size_t option_count, const char *positionals[],
							 size_t positional_capacity,
							 size_t *positional_count) {
	if (positional_count == NULL) {
		errno = EINVAL;
		return -1;
	}

	*positional_count = 0;

	if (argc < 0 || argc == INT_MAX || argv == NULL ||
		(option_count > 0 && options == NULL) ||
		(positional_capacity > 0 && positionals == NULL)) {
		errno = EINVAL;
		return -1;
	}

	if (ValidateOptions(options, option_count) != 0) {
		return -1;
	}

	// Reset option state before parsing.
	for (size_t i = 0; i < option_count; i++) {
		options[i].seen = false;
		options[i].value = NULL;
	}

	/*
	 * Build the option string expected by getopt().
	 *
	 * A leading ':' tells getopt() to return ':' when a required
	 * option argument is missing instead of printing an error.
	 *
	 * Each option requiring a value is followed by ':'.
	 */
	char option_string[256];
	size_t option_length = 0;

	option_string[option_length++] = ':';

	for (size_t i = 0; i < option_count; i++) {
		if (options[i].short_name == '\0') {
			// POSIX getopt() cannot parse long-only options.
			continue;
		}

		if (option_length + 2 >= sizeof(option_string)) {
			errno = E2BIG;
			return -1;
		}

		option_string[option_length++] = options[i].short_name;

		if (options[i].requires_value) {
			option_string[option_length++] = ':';
		}
	}

	option_string[option_length] = '\0';

	// Allocate a temporary argument vector.
	size_t vector_count = (size_t)argc + 1;

	if (vector_count > SIZE_MAX / sizeof(char *)) {
		errno = EOVERFLOW;
		return -1;
	}

	char **getopt_argv = malloc(vector_count * sizeof(char *));

	if (getopt_argv == NULL) {
		return -1;
	}

	// getopt() expects the program name at argv[0].
	char program_name[] = "cli";

	getopt_argv[0] = program_name;

	for (int i = 0; i < argc; i++) {
		if (argv[i] == NULL) {
			free(getopt_argv);
			errno = EINVAL;
			return -1;
		}

		getopt_argv[i + 1] = argv[i];
	}

	/*
	 * getopt() uses global variables.
	 *
	 * Disable its automatic error messages because this parser
	 * returns errors through its own return value and errno.
	 */
	int previous_opterr = opterr;

	opterr = 0;

/*
 * Reset getopt's internal state.
 *
 * glibc requires optind = 0 to fully reinitialize
 * its internal parsing state between argument vectors.
 * Other POSIX implementations use optind = 1.
 */
#ifdef __GLIBC__
	optind = 0;
#else
	optind = 1;
#endif

	int status = 0;

	while (1) {
		int option_character = getopt(argc + 1, getopt_argv, option_string);

		if (option_character == -1) {
			break;
		}

		// ':' means a required value was missing.
		// '?' means an unknown option was encountered.
		if (option_character == ':' || option_character == '?') {
			status = -1;
			errno = EINVAL;
			break;
		}

		// Find the corresponding option definition.
		size_t index = option_count;

		for (size_t i = 0; i < option_count; i++) {
			if (options[i].short_name == option_character) {
				index = i;
				break;
			}
		}

		if (index == option_count) {
			status = -1;
			errno = EINVAL;
			break;
		}

		const char *value = options[index].requires_value ? optarg : NULL;

		if (SetOption(&options[index], value) != 0) {
			status = -1;
			break;
		}
	}

	/*
	 * getopt() updates optind to indicate where positional
	 * arguments begin.
	 *
	 * Some implementations reorder options and operands;
	 * therefore, use the temporary argument vector here.
	 */
	if (status == 0) {
		for (int i = optind; i < argc + 1; i++) {
			if (*positional_count >= positional_capacity) {
				status = -1;
				errno = E2BIG;
				break;
			}

			positionals[*positional_count] = getopt_argv[i];
			(*positional_count)++;
		}
	}

	// Restore the previous error-reporting setting.
	opterr = previous_opterr;

	// Reset getopt state for a future invocation.
	optind = 1;

	free(getopt_argv);

	return status;
}
