
#include "../include/cli.h"

#include <ctype.h>
#include <inttypes.h>
#include <stdio.h>
#include <string.h>

/*
 * Displays the application version.
 */
void cli_print_version(void) {
    printf("ccli 1.0.0\n");
}

/*
 * Displays the application usage information.
 */
void cli_print_usage(const char *program) {
    printf(
        "Usage:\n"
        "  %s <command> [options] [arguments]\n\n"
        "Commands:\n"
        "  greet       Display a greeting\n"
        "  calc        Perform arithmetic operations\n"
        "  inspect     Inspect a signed integer\n\n"
        "Global options:\n"
        "  -h, --help       Display help\n"
        "  -V, --version    Display version\n\n"
        "Examples:\n"
        "  %s greet --name Akshat\n"
        "  %s greet -n Akshat -u\n"
        "  %s calc add 10 20\n"
        "  %s inspect -42\n",
        program, program, program, program, program
    );
}

/*
 * Greet command.
 *
 * Supported options:
 *   -n, --name NAME
 *   -u, --uppercase
 */
int cli_run_greet(int argc, char *argv[]) {
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
    size_t positional_count = 0;

    if (cli_parse_options(
        argc,
        argv,
        options,
        sizeof(options) / sizeof(options[0]),
        positionals,
        1,
        &positional_count
    ) != 0 || positional_count != 0) {
        fprintf(stderr, "greet: invalid arguments\n");
        fprintf(stderr, "Usage: ccli greet [--name NAME] [--uppercase]\n");
        return 1;
    }

    const char *name = "World";

    if (options[0].seen) {
        name = options[0].value;
    }

    char message[256];

    int length = snprintf(
        message,
        sizeof(message),
        "Hello, %s!",
        name
    );

    if (length < 0 || (size_t)length >= sizeof(message)) {
        fprintf(stderr, "greet: name is too long\n");
        return 1;
    }

    // Apply uppercase formatting when requested.
    if (options[1].seen) {
        for (size_t i = 0; message[i] != '\0'; i++) {
            message[i] = (char)toupper((unsigned char)message[i]);
        }
    }

    puts(message);

    return 0;
}

/*
 * Calculator command.
 *
 * Usage:
 *   ccli calc add LEFT RIGHT
 */
int cli_run_calc(int argc, char *argv[]) {
    if (argc != 3 || strcmp(argv[0], "add") != 0) {
        fprintf(stderr, "Usage: ccli calc add LEFT RIGHT\n");
        return 1;
    }

    int64_t left;
    int64_t right;

    if (cli_parse_i64(argv[1], 10, &left) != 0) {
        fprintf(stderr, "calc: invalid left operand: %s\n", argv[1]);
        return 1;
    }

    if (cli_parse_i64(argv[2], 10, &right) != 0) {
        fprintf(stderr, "calc: invalid right operand: %s\n", argv[2]);
        return 1;
    }

    // Check for signed overflow before performing addition.
    if ((right > 0 && left > INT64_MAX - right) ||
        (right < 0 && left < INT64_MIN - right)) {
        fprintf(stderr, "calc: integer overflow\n");
        return 1;
    }

    int64_t result = left + right;

    printf(
        "%" PRId64 " + %" PRId64 " = %" PRId64 "\n",
        left,
        right,
        result
    );

    return 0;
}

/*
 * Inspects the binary representation of a signed 64-bit integer.
 *
 * Usage:
 *   ccli inspect NUMBER
 */
int cli_run_inspect(int argc, char *argv[]) {
    if (argc != 1) {
        fprintf(stderr, "Usage: ccli inspect NUMBER\n");
        return 1;
    }

    int64_t value;

    if (cli_parse_i64(argv[0], 0, &value) != 0) {
        fprintf(stderr, "inspect: invalid integer: %s\n", argv[0]);
        return 1;
    }

    // Conversion to uint64_t gives the corresponding modulo-2^64 bit pattern.
    uint64_t bits = (uint64_t)value;

    printf("Decimal: %" PRId64 "\n", value);
    printf("Hex:     0x%016" PRIX64 "\n", bits);
    printf("Binary:  ");

    // Print all 64 bits, from most significant to least significant.
    for (int i = 63; i >= 0; i--) {
        putchar((bits >> i) & UINT64_C(1) ? '1' : '0');

        // Group bits into bytes for readability.
        if (i % 8 == 0 && i != 0) {
            putchar(' ');
        }
    }

    putchar('\n');

    return 0;
}

/*
 * Dispatches a command to its corresponding handler.
 */
int cli_dispatch(int argc, char *argv[]) {
    if (argc < 1 || argv == NULL) {
        fprintf(stderr, "No command supplied.\n");
        return 1;
    }

    const char *command = argv[0];

    if (strcmp(command, "greet") == 0) {
        return cli_run_greet(argc - 1, argv + 1);
    }

    if (strcmp(command, "calc") == 0) {
        return cli_run_calc(argc - 1, argv + 1);
    }

    if (strcmp(command, "inspect") == 0) {
        return cli_run_inspect(argc - 1, argv + 1);
    }

    fprintf(stderr, "Unknown command: %s\n", command);

    return 1;
}
