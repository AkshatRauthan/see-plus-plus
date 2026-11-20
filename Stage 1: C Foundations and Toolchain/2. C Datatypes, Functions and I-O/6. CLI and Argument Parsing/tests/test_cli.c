#include "../include/cli.h"

#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

/*
 * Tests long options using the manual parser.
 *
 * Covers:
 *   --name=Akshat
 *   --uppercase
 */
static void TestLongOptions(void) {
    char *argv[] = {
        "--name=Akshat",
        "--uppercase"
    };

    CliOption options[] = {
        {
            .long_name = "name",
            .short_name = 'n',
            .requires_value = true
        },
        {
            .long_name = "uppercase",
            .short_name = 'u',
            .requires_value = false
        }
    };

    const char *positionals[2];
    size_t count = 0;

    assert(cli_parse_options(
        2, argv, options, 2,
        positionals, 2, &count
    ) == 0);

    assert(options[0].seen);
    assert(strcmp(options[0].value, "Akshat") == 0);

    assert(options[1].seen);
    assert(options[1].value == NULL);

    assert(count == 0);
}

/*
 * Tests short options using the manual parser.
 *
 * Covers:
 *   -n Akshat
 *   -u
 */
static void TestShortOptions(void) {
    char *argv[] = {
        "-n",
        "Akshat",
        "-u"
    };

    CliOption options[] = {
        {
            .long_name = "name",
            .short_name = 'n',
            .requires_value = true
        },
        {
            .long_name = "uppercase",
            .short_name = 'u',
            .requires_value = false
        }
    };

    const char *positionals[1];
    size_t count = 0;

    assert(cli_parse_options(
        3, argv, options, 2,
        positionals, 1, &count
    ) == 0);

    assert(options[0].seen);
    assert(strcmp(options[0].value, "Akshat") == 0);

    assert(options[1].seen);
    assert(count == 0);
}

/*
 * Tests short options with attached values.
 *
 * Covers:
 *   -n=Akshat
 */
static void TestShortOptionAttachedValue(void) {
    char *argv[] = {
        "-n=Akshat"
    };

    CliOption options[] = {
        {
            .long_name = "name",
            .short_name = 'n',
            .requires_value = true
        }
    };

    const char *positionals[1];
    size_t count = 0;

    assert(cli_parse_options(
        1, argv, options, 1,
        positionals, 1, &count
    ) == 0);

    assert(options[0].seen);
    assert(strcmp(options[0].value, "Akshat") == 0);
}

/*
 * Tests positional argument collection.
 */
static void TestPositionalArguments(void) {
    char *argv[] = {
        "add",
        "10",
        "20"
    };

    const char *positionals[3];
    size_t count = 0;

    assert(cli_parse_options(
        3, argv, NULL, 0,
        positionals, 3, &count
    ) == 0);

    assert(count == 3);
    assert(strcmp(positionals[0], "add") == 0);
    assert(strcmp(positionals[1], "10") == 0);
    assert(strcmp(positionals[2], "20") == 0);
}

/*
 * Tests the end-of-options marker.
 *
 * Arguments following "--" are treated as positional,
 * even when they begin with a hyphen.
 */
static void TestEndOfOptions(void) {
    char *argv[] = {
        "--",
        "-42"
    };

    const char *positionals[2];
    size_t count = 0;

    assert(cli_parse_options(
        2, argv, NULL, 0,
        positionals, 2, &count
    ) == 0);

    assert(count == 1);
    assert(strcmp(positionals[0], "-42") == 0);
}

/*
 * Tests duplicate option detection.
 */
static void TestDuplicateOption(void) {
    char *argv[] = {
        "--name",
        "First",
        "--name",
        "Second"
    };

    CliOption options[] = {
        {
            .long_name = "name",
            .short_name = 'n',
            .requires_value = true
        }
    };

    const char *positionals[1];
    size_t count = 0;

    assert(cli_parse_options(
        4, argv, options, 1,
        positionals, 1, &count
    ) == -1);
}

/*
 * Tests invalid option definitions.
 *
 * Long names and short names must be unique.
 */
static void TestInvalidOptionDefinitions(void) {
    char *argv[] = {
        "--name",
        "Akshat"
    };

    const char *positionals[1];
    size_t count = 0;

    // Duplicate long names.
    CliOption duplicate_long[] = {
        {
            .long_name = "name",
            .short_name = 'n',
            .requires_value = true
        },
        {
            .long_name = "name",
            .short_name = 'm',
            .requires_value = true
        }
    };

    assert(cli_parse_options(
        2, argv, duplicate_long, 2,
        positionals, 1, &count
    ) == -1);

    // Duplicate short names.
    CliOption duplicate_short[] = {
        {
            .long_name = "name",
            .short_name = 'n',
            .requires_value = true
        },
        {
            .long_name = "number",
            .short_name = 'n',
            .requires_value = true
        }
    };

    assert(cli_parse_options(
        2, argv, duplicate_short, 2,
        positionals, 1, &count
    ) == -1);

    // Empty long name.
    CliOption empty_name[] = {
        {
            .long_name = "",
            .short_name = 'n',
            .requires_value = true
        }
    };

    assert(cli_parse_options(
        2, argv, empty_name, 1,
        positionals, 1, &count
    ) == -1);

    // Long names cannot contain '='.
    CliOption invalid_name[] = {
        {
            .long_name = "na=me",
            .short_name = 'n',
            .requires_value = true
        }
    };

    assert(cli_parse_options(
        2, argv, invalid_name, 1,
        positionals, 1, &count
    ) == -1);
}

/*
 * Tests manual parser error handling.
 */
static void TestManualParserErrors(void) {
    const char *positionals[2];
    size_t count = 0;

    CliOption name_option[] = {
        {
            .long_name = "name",
            .short_name = 'n',
            .requires_value = true
        }
    };

    // Missing long-option value.
    char *missing_value[] = {
        "--name"
    };

    assert(cli_parse_options(
        1, missing_value, name_option, 1,
        positionals, 2, &count
    ) == -1);

    // Explicitly empty long-option value.
    char *empty_value[] = {
        "--name="
    };

    assert(cli_parse_options(
        1, empty_value, name_option, 1,
        positionals, 2, &count
    ) == -1);

    // Unknown long option.
    char *unknown_long[] = {
        "--unknown"
    };

    assert(cli_parse_options(
        1, unknown_long, name_option, 1,
        positionals, 2, &count
    ) == -1);

    // Unknown short option.
    char *unknown_short[] = {
        "-x"
    };

    assert(cli_parse_options(
        1, unknown_short, name_option, 1,
        positionals, 2, &count
    ) == -1);

    // Short-option clustering is not supported.
    char *clustered[] = {
        "-nu"
    };

    assert(cli_parse_options(
        1, clustered, name_option, 1,
        positionals, 2, &count
    ) == -1);

    // A boolean flag must not receive a value.
    CliOption flag_option[] = {
        {
            .long_name = "verbose",
            .short_name = 'v',
            .requires_value = false
        }
    };

    char *flag_value[] = {
        "--verbose=true"
    };

    assert(cli_parse_options(
        1, flag_value, flag_option, 1,
        positionals, 2, &count
    ) == -1);

    // Positional argument capacity exceeded.
    char *too_many[] = {
        "first",
        "second"
    };

    assert(cli_parse_options(
        2, too_many, NULL, 0,
        positionals, 1, &count
    ) == -1);

    // Invalid parser arguments.
    assert(cli_parse_options(
        1, too_many, NULL, 0,
        positionals, 1, NULL
    ) == -1);
}

/*
 * Tests POSIX getopt() with clustered short options.
 *
 * -unAkshat means:
 *   -u          Boolean flag.
 *   -n Akshat   Option requiring a value.
 *
 * The remaining argument is positional.
 */
static void TestGetoptOptions(void) {
    char *argv[] = {
        "-unAkshat",
        "input.txt"
    };

    CliOption options[] = {
        {
            .long_name = "name",
            .short_name = 'n',
            .requires_value = true
        },
        {
            .long_name = "uppercase",
            .short_name = 'u',
            .requires_value = false
        }
    };

    const char *positionals[2];
    size_t count = 0;

    assert(cli_parse_options_getopt(
        2, argv, options, 2,
        positionals, 2, &count
    ) == 0);

    assert(options[0].seen);
    assert(strcmp(options[0].value, "Akshat") == 0);

    assert(options[1].seen);

    assert(count == 1);
    assert(strcmp(positionals[0], "input.txt") == 0);
}

/*
 * Tests getopt() with a separate option argument.
 *
 * Covers:
 *   -n Akshat -u
 */
static void TestGetoptSeparateValue(void) {
    char *argv[] = {
        "-n",
        "Akshat",
        "-u"
    };

    CliOption options[] = {
        {
            .long_name = "name",
            .short_name = 'n',
            .requires_value = true
        },
        {
            .long_name = "uppercase",
            .short_name = 'u',
            .requires_value = false
        }
    };

    const char *positionals[1];
    size_t count = 0;

    assert(cli_parse_options_getopt(
        3, argv, options, 2,
        positionals, 1, &count
    ) == 0);

    assert(options[0].seen);
    assert(strcmp(options[0].value, "Akshat") == 0);

    assert(options[1].seen);
    assert(count == 0);
}

/*
 * Tests getopt() with an attached option value.
 *
 * POSIX getopt() interprets "-n=Akshat" as an argument
 * whose value is "=Akshat", not "Akshat".
 */
static void TestGetoptAttachedEqualsValue(void) {
    char *argv[] = {
        "-n=Akshat"
    };

    CliOption options[] = {
        {
            .long_name = "name",
            .short_name = 'n',
            .requires_value = true
        }
    };

    const char *positionals[1];
    size_t count = 0;

    assert(cli_parse_options_getopt(
        1, argv, options, 1,
        positionals, 1, &count
    ) == 0);

    assert(options[0].seen);
    assert(strcmp(options[0].value, "=Akshat") == 0);
}

/*
 * Tests the getopt() end-of-options marker.
 */
static void TestGetoptEndOfOptions(void) {
    char *argv[] = {
        "--",
        "-42"
    };

    const char *positionals[2];
    size_t count = 0;

    assert(cli_parse_options_getopt(
        2, argv, NULL, 0,
        positionals, 2, &count
    ) == 0);

    assert(count == 1);
    assert(strcmp(positionals[0], "-42") == 0);
}

/*
 * Tests getopt() error handling.
 */
static void TestGetoptErrors(void) {
    const char *positionals[2];
    size_t count = 0;

    CliOption options[] = {
        {
            .long_name = "name",
            .short_name = 'n',
            .requires_value = true
        }
    };

    // Missing required value.
    char *missing_value[] = {
        "-n"
    };

    assert(cli_parse_options_getopt(
        1, missing_value, options, 1,
        positionals, 2, &count
    ) == -1);

    // Explicitly empty option value.
    char *empty_value[] = {
        "-n",
        ""
    };

    assert(cli_parse_options_getopt(
        2, empty_value, options, 1,
        positionals, 2, &count
    ) == -1);

    // Unknown short option.
    char *unknown_option[] = {
        "-x"
    };

    assert(cli_parse_options_getopt(
        1, unknown_option, options, 1,
        positionals, 2, &count
    ) == -1);

    // Long options are not supported by POSIX getopt().
    char *long_option[] = {
        "--name",
        "Akshat"
    };

    assert(cli_parse_options_getopt(
        2, long_option, options, 1,
        positionals, 2, &count
    ) == -1);

    // Duplicate boolean options.
    CliOption flags[] = {
        {
            .long_name = "verbose",
            .short_name = 'v',
            .requires_value = false
        }
    };

    char *duplicate[] = {
        "-v",
        "-v"
    };

    assert(cli_parse_options_getopt(
        2, duplicate, flags, 1,
        positionals, 2, &count
    ) == -1);

    // Positional capacity exceeded.
    char *too_many[] = {
        "first",
        "second"
    };

    assert(cli_parse_options_getopt(
        2, too_many, NULL, 0,
        positionals, 1, &count
    ) == -1);
}

/*
 * Tests getopt() with repeated parser invocations.
 *
 * This verifies that the parser correctly resets getopt's
 * internal state between independent argument vectors.
 */
static void TestGetoptStateReset(void) {
    CliOption options[] = {
        {
            .long_name = "verbose",
            .short_name = 'v',
            .requires_value = false
        }
    };

    const char *positionals[1];
    size_t count = 0;

    char *first_argv[] = {
        "-v"
    };

    assert(cli_parse_options_getopt(
        1, first_argv, options, 1,
        positionals, 1, &count
    ) == 0);

    assert(options[0].seen);

    char *second_argv[] = {
        "input.txt"
    };

    assert(cli_parse_options_getopt(
        1, second_argv, options, 1,
        positionals, 1, &count
    ) == 0);

    // The option state must be reset between parser calls.
    assert(!options[0].seen);

    assert(count == 1);
    assert(strcmp(positionals[0], "input.txt") == 0);
}

/*
 * Tests signed and unsigned numeric parsing.
 */
static void TestNumericParsing(void) {
    int64_t signed_value;
    uint64_t unsigned_value;

    assert(cli_parse_i64("-12345", 10, &signed_value) == 0);
    assert(signed_value == -12345);

    assert(cli_parse_u64("255", 10, &unsigned_value) == 0);
    assert(unsigned_value == 255);

    // Automatic hexadecimal detection.
    assert(cli_parse_i64("0xFF", 0, &signed_value) == 0);
    assert(signed_value == 255);

    // Explicit octal parsing.
    assert(cli_parse_i64("77", 8, &signed_value) == 0);
    assert(signed_value == 63);

    // Explicit binary parsing.
    assert(cli_parse_u64("1010", 2, &unsigned_value) == 0);
    assert(unsigned_value == 10);
}

/*
 * Tests invalid numeric input.
 */
static void TestInvalidNumbers(void) {
    int64_t signed_value = 77;
    uint64_t unsigned_value = 88;

    assert(cli_parse_i64("123abc", 10, &signed_value) == -1);
    assert(cli_parse_i64("", 10, &signed_value) == -1);
    assert(cli_parse_i64(NULL, 10, &signed_value) == -1);

    assert(cli_parse_u64("-123", 10, &unsigned_value) == -1);
    assert(cli_parse_u64(" -123", 10, &unsigned_value) == -1);
    assert(cli_parse_u64("invalid", 10, &unsigned_value) == -1);
    assert(cli_parse_u64("", 10, &unsigned_value) == -1);
    assert(cli_parse_u64(NULL, 10, &unsigned_value) == -1);

    // Invalid numeric bases.
    assert(cli_parse_i64("10", 1, &signed_value) == -1);
    assert(cli_parse_i64("10", 37, &signed_value) == -1);

    assert(cli_parse_u64("10", 1, &unsigned_value) == -1);
    assert(cli_parse_u64("10", 37, &unsigned_value) == -1);

    // Failed conversions must not modify the output value.
    signed_value = 77;

    assert(cli_parse_i64("invalid", 10, &signed_value) == -1);
    assert(signed_value == 77);

    unsigned_value = 88;

    assert(cli_parse_u64("-1", 10, &unsigned_value) == -1);
    assert(unsigned_value == 88);
}

/*
 * Tests signed and unsigned integer boundaries.
 */
static void TestIntegerBoundaries(void) {
    int64_t signed_value;
    uint64_t unsigned_value;

    assert(cli_parse_i64(
        "9223372036854775807", 10, &signed_value
    ) == 0);

    assert(signed_value == INT64_MAX);

    assert(cli_parse_i64(
        "-9223372036854775808", 10, &signed_value
    ) == 0);

    assert(signed_value == INT64_MIN);

    assert(cli_parse_i64(
        "9223372036854775808", 10, &signed_value
    ) == -1);

    assert(cli_parse_i64(
        "-9223372036854775809", 10, &signed_value
    ) == -1);

    assert(cli_parse_u64(
        "18446744073709551615", 10, &unsigned_value
    ) == 0);

    assert(unsigned_value == UINT64_MAX);

    assert(cli_parse_u64(
        "18446744073709551616", 10, &unsigned_value
    ) == -1);
}

int main(void) {
    // Manual parser tests.
    TestLongOptions();
    TestShortOptions();
    TestShortOptionAttachedValue();
    TestPositionalArguments();
    TestEndOfOptions();
    TestDuplicateOption();
    TestInvalidOptionDefinitions();
    TestManualParserErrors();

    // POSIX getopt() tests.
    TestGetoptOptions();
    TestGetoptSeparateValue();
    TestGetoptAttachedEqualsValue();
    TestGetoptEndOfOptions();
    TestGetoptErrors();
    TestGetoptStateReset();

    // Numeric parsing tests.
    TestNumericParsing();
    TestInvalidNumbers();
    TestIntegerBoundaries();

    puts("All CLI tests passed.");

    return 0;
}
