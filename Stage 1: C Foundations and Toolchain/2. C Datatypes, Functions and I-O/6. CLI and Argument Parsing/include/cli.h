
#ifndef CLI_H
#define CLI_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

/*
 * Describes a command-line option.
 *
 * long_name:
 *     Long option name, such as "name".
 *
 * short_name:
 *     Short option character, such as 'n'.
 *
 * requires_value:
 *     true  -> option expects a value.
 *     false -> option is a boolean flag.
 *
 * seen:
 *     Set to true when the option appears.
 *
 * value:
 *     Stores the value supplied to an option.
 */
typedef struct {
	const char *long_name;
	char short_name;
	bool requires_value;
	bool seen;
	const char *value;
} CliOption;

/*
 * Parses options and collects positional arguments.
 *
 * Supports:
 *     --name value
 *     --name=value
 *     -n value
 *     -n=value
 *     -- to mark the end of options
 *
 * Short-option clustering, such as -abc, is not supported.
 *
 * Returns:
 *     0  on success.
 *    -1  on invalid, unknown, duplicate, or missing arguments.
 */
int cli_parse_options(int argc, char *argv[], CliOption options[],
					  size_t option_count, const char *positionals[],
					  size_t positional_capacity, size_t *positional_count);

/*
 * Parses a signed 64-bit integer.
 *
 * Supports bases accepted by strtoimax():
 *     0  -> automatic base detection.
 *     2  -> binary.
 *     8  -> octal.
 *     10 -> decimal.
 *     16 -> hexadecimal.
 *
 * Returns:
 *     0  on success.
 *    -1  on invalid input or range error.
 */
int cli_parse_i64(const char *text, int base, int64_t *result);

/*
 * Parses an unsigned 64-bit integer.
 *
 * Negative input is explicitly rejected.
 *
 * Returns:
 *     0  on success.
 *    -1  on invalid input or range error.
 */
int cli_parse_u64(const char *text, int base, uint64_t *result);

/* Command handlers. */
int cli_run_greet(int argc, char *argv[]);
int cli_run_calc(int argc, char *argv[]);
int cli_run_inspect(int argc, char *argv[]);

/* Displays application usage and version information. */
void cli_print_usage(const char *program);
void cli_print_version(void);

#endif
