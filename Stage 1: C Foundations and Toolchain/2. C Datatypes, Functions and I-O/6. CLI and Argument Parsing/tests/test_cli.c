
#include "../include/cli.h"

#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

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
        2,
        argv,
        options,
        2,
        positionals,
        2,
        &count
    ) == 0);

    assert(options[0].seen);
    assert(strcmp(options[0].value, "Akshat") == 0);
    assert(options[1].seen);
    assert(count == 0);
}

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
        3,
        argv,
        options,
        2,
        positionals,
        1,
        &count
    ) == 0);

    assert(options[0].seen);
    assert(strcmp(options[0].value, "Akshat") == 0);
    assert(options[1].seen);
}

static void TestPositionalArguments(void) {
    char *argv[] = {
        "add",
        "10",
        "20"
    };

    const char *positionals[3];
    size_t count = 0;

    assert(cli_parse_options(
        3,
        argv,
        NULL,
        0,
        positionals,
        3,
        &count
    ) == 0);

    assert(count == 3);
    assert(strcmp(positionals[0], "add") == 0);
    assert(strcmp(positionals[1], "10") == 0);
    assert(strcmp(positionals[2], "20") == 0);
}

static void TestEndOfOptions(void) {
    char *argv[] = {
        "--",
        "-42"
    };

    const char *positionals[2];
    size_t count = 0;

    assert(cli_parse_options(
        2,
        argv,
        NULL,
        0,
        positionals,
        2,
        &count
    ) == 0);

    assert(count == 1);
    assert(strcmp(positionals[0], "-42") == 0);
}

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
        4,
        argv,
        options,
        1,
        positionals,
        1,
        &count
    ) == -1);
}

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
}

static void TestInvalidNumbers(void) {
    int64_t signed_value;
    uint64_t unsigned_value;

    assert(cli_parse_i64("123abc", 10, &signed_value) == -1);
    assert(cli_parse_i64("", 10, &signed_value) == -1);
    assert(cli_parse_u64("-123", 10, &unsigned_value) == -1);
    assert(cli_parse_u64("invalid", 10, &unsigned_value) == -1);
}

static void TestIntegerBoundaries(void) {
    int64_t signed_value;
    uint64_t unsigned_value;

    assert(cli_parse_i64("9223372036854775807", 10, &signed_value) == 0);
    assert(signed_value == INT64_MAX);

    assert(cli_parse_i64("-9223372036854775808", 10, &signed_value) == 0);
    assert(signed_value == INT64_MIN);

    assert(cli_parse_i64("9223372036854775808", 10, &signed_value) == -1);

    assert(cli_parse_u64("18446744073709551615", 10, &unsigned_value) == 0);
    assert(unsigned_value == UINT64_MAX);

    assert(cli_parse_u64("18446744073709551616", 10, &unsigned_value) == -1);
}

int main(void) {
    TestLongOptions();
    TestShortOptions();
    TestPositionalArguments();
    TestEndOfOptions();
    TestDuplicateOption();
    TestNumericParsing();
    TestInvalidNumbers();
    TestIntegerBoundaries();

    puts("All CLI tests passed.");

    return 0;
}
