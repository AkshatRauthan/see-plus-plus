
#include "../include/cli.h"
#include "../include/commands.h"

#include <errno.h>
#include <inttypes.h>
#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Prints the available commands. */
static void PrintUsage(const char *program) {
    fprintf(stderr,
        "Usage: %s <command> [arguments]\n\n"
        "Integer Inspection:\n"
        "  int [--signed | --unsigned] [--width 8|16|32|64] <value>\n"
        "\n"
        "Bitwise Operations:\n"
        "  and <a> <b>\n"
        "  or <a> <b>\n"
        "  xor <a> <b>\n"
        "  not <value>\n"
        "  shl <value> <count>\n"
        "  shr <value> <count>\n"
        "\n"
        "Bit Manipulation:\n"
        "  set <value> <position>\n"
        "  clear <value> <position>\n"
        "  toggle <value> <position>\n"
        "  test <value> <position>\n"
        "  extract <value> <position> <length>\n"
        "  insert <value> <source> <position> <length>\n"
        "\n"
        "Bit Analysis:\n"
        "  popcount <value>\n"
        "  leading-zeros <value>\n"
        "  trailing-zeros <value>\n"
        "  power-of-two <value>\n"
        "\n"
        "Memory and Endianness:\n"
        "  memory <value>\n"
        "  bytes <value>\n"
        "  byteswap <value>\n"
        "  endian\n"
        "\n"
        "Floating-Point:\n"
        "  float <value>\n"
        "  double <value>\n",
        program
    );
}

/* Changes an integer to the requested width after validating its range. */
static int SetIntegerWidth(Integer *number, unsigned width) {
    if (number == NULL)
        return -1;

    if (width != 8 && width != 16 && width != 32 && width != 64) {
        fprintf(stderr, "Invalid width. Use 8, 16, 32, or 64.\n");
        return -1;
    }

    if (number->isSigned) {
        intmax_t value;

        switch (number->type) {
        case INT_8:
            value = number->value.i8;
            break;
        case INT_16:
            value = number->value.i16;
            break;
        case INT_32:
            value = number->value.i32;
            break;
        case INT_64:
            value = number->value.i64;
            break;
        default:
            return -1;
        }

        if ((width == 8 && (value < INT8_MIN || value > INT8_MAX)) ||
            (width == 16 && (value < INT16_MIN || value > INT16_MAX)) ||
            (width == 32 && (value < INT32_MIN || value > INT32_MAX)) ||
            (width == 64 && (value < INT64_MIN || value > INT64_MAX))) {
            fprintf(stderr,
                    "Value does not fit in signed %u-bit integer.\n", width);
            return -1;
        }

        switch (width) {
        case 8:
            number->type = INT_8;
            number->value.i8 = (int8_t)value;
            break;
        case 16:
            number->type = INT_16;
            number->value.i16 = (int16_t)value;
            break;
        case 32:
            number->type = INT_32;
            number->value.i32 = (int32_t)value;
            break;
        case 64:
            number->type = INT_64;
            number->value.i64 = (int64_t)value;
            break;
        }
    } else {
        uintmax_t value;

        switch (number->type) {
        case UINT_8:
            value = number->value.u8;
            break;
        case UINT_16:
            value = number->value.u16;
            break;
        case UINT_32:
            value = number->value.u32;
            break;
        case UINT_64:
            value = number->value.u64;
            break;
        default:
            return -1;
        }

        if ((width == 8 && value > UINT8_MAX) ||
            (width == 16 && value > UINT16_MAX) ||
            (width == 32 && value > UINT32_MAX) ||
            (width == 64 && value > UINT64_MAX)) {
            fprintf(stderr,
                    "Value does not fit in unsigned %u-bit integer.\n", width);
            return -1;
        }

        switch (width) {
        case 8:
            number->type = UINT_8;
            number->value.u8 = (uint8_t)value;
            break;
        case 16:
            number->type = UINT_16;
            number->value.u16 = (uint16_t)value;
            break;
        case 32:
            number->type = UINT_32;
            number->value.u32 = (uint32_t)value;
            break;
        case 64:
            number->type = UINT_64;
            number->value.u64 = (uint64_t)value;
            break;
        }
    }

    number->width = (int)width;
    return 0;
}

/* Parses an integer using the project's integer parser. */
static int ParseIntegerArg(const char *input, Integer *number, int isSigned) {
    return ParseInteger(input, number, isSigned);
}

/* Parses a non-negative integer argument. */
static int ParseUnsignedArg(const char *input, unsigned *value) {
    if (input == NULL || value == NULL ||
        input[0] == '\0' || input[0] == '-')
        return -1;

    char *end;
    errno = 0;

    uintmax_t parsed = strtoumax(input, &end, 10);

    if (errno == ERANGE || end == input || *end != '\0' ||
        parsed > UINT_MAX)
        return -1;

    *value = (unsigned)parsed;
    return 0;
}

/* Parses one signed integer argument. */
static int GetInteger(const char *input, Integer *number) {
    return ParseIntegerArg(input, number, 1);
}

/* Dispatches integer inspection and processes its flags. */
static int HandleInteger(int argc, char *argv[]) {
    int isSigned = 1;
    int signedSeen = 0;
    int unsignedSeen = 0;
    int widthSeen = 0;

    unsigned width = 0;
    const char *input = NULL;

    for (int i = 2; i < argc; i++) {
        if (strcmp(argv[i], "--signed") == 0) {
            if (signedSeen || unsignedSeen)
                goto invalid_arguments;

            signedSeen = 1;
            isSigned = 1;
        } else if (strcmp(argv[i], "--unsigned") == 0) {
            if (unsignedSeen || signedSeen)
                goto invalid_arguments;

            unsignedSeen = 1;
            isSigned = 0;
        } else if (strcmp(argv[i], "--width") == 0) {
            if (widthSeen || i + 1 >= argc)
                goto invalid_arguments;

            if (ParseUnsignedArg(argv[++i], &width) != 0)
                goto invalid_arguments;

            widthSeen = 1;
        } else if (strncmp(argv[i], "--width=", 8) == 0) {
            if (widthSeen)
                goto invalid_arguments;

            if (ParseUnsignedArg(argv[i] + 8, &width) != 0)
                goto invalid_arguments;

            widthSeen = 1;
        } else if (strncmp(argv[i], "--", 2) == 0) {
            goto invalid_arguments;
        } else {
            if (input != NULL)
                goto invalid_arguments;

            input = argv[i];
        }
    }

    if (input == NULL)
        goto invalid_arguments;

    Integer number;

    if (ParseIntegerArg(input, &number, isSigned) != 0)
        return EXIT_FAILURE;

    if (widthSeen && SetIntegerWidth(&number, width) != 0)
        return EXIT_FAILURE;

    return IntegerInspection(&number);

invalid_arguments:
    fprintf(stderr, "Invalid integer arguments.\n\n");
    PrintUsage(argv[0]);
    return EXIT_FAILURE;
}

/* Dispatches binary bitwise operations. */
static int HandleBitwiseBinary(const char *command, const char *left,
                               const char *right) {
    Integer a, b;
    BitOp op;

    if (strcmp(command, "and") == 0)
        op = OP_AND;
    else if (strcmp(command, "or") == 0)
        op = OP_OR;
    else if (strcmp(command, "xor") == 0)
        op = OP_XOR;
    else
        return EXIT_FAILURE;

    if (GetInteger(left, &a) != 0 || GetInteger(right, &b) != 0)
        return EXIT_FAILURE;

    return BitwiseBinary(op, &a, &b);
}

/* Dispatches unary and shift bitwise operations. */
static int HandleBitwiseUnary(int argc, char *argv[]) {
    Integer number;

    if (strcmp(argv[1], "not") == 0) {
        if (argc != 3 || GetInteger(argv[2], &number) != 0)
            return EXIT_FAILURE;

        return BitwiseNot(&number);
    }

    if (strcmp(argv[1], "shl") == 0 || strcmp(argv[1], "shr") == 0) {
        unsigned count;

        if (argc != 4 || GetInteger(argv[2], &number) != 0 ||
            ParseUnsignedArg(argv[3], &count) != 0)
            return EXIT_FAILURE;

        BitOp op = strcmp(argv[1], "shl") == 0 ? OP_SHL : OP_SHR;

        return BitwiseShift(op, &number, count);
    }

    return EXIT_FAILURE;
}

/* Dispatches single-bit manipulation operations. */
static int HandleBitSingle(const char *command, const char *input,
                           const char *position) {
    Integer number;
    unsigned pos;
    BitManipOp op;

    if (GetInteger(input, &number) != 0 ||
        ParseUnsignedArg(position, &pos) != 0)
        return EXIT_FAILURE;

    if (strcmp(command, "set") == 0)
        op = BM_SET;
    else if (strcmp(command, "clear") == 0)
        op = BM_CLEAR;
    else if (strcmp(command, "toggle") == 0)
        op = BM_TOGGLE;
    else if (strcmp(command, "test") == 0)
        op = BM_TEST;
    else
        return EXIT_FAILURE;

    return BitSingle(op, &number, pos);
}

/* Dispatches bit extraction. */
static int HandleExtract(const char *input, const char *position,
                         const char *length) {
    Integer number;
    unsigned pos, len;

    if (GetInteger(input, &number) != 0 ||
        ParseUnsignedArg(position, &pos) != 0 ||
        ParseUnsignedArg(length, &len) != 0)
        return EXIT_FAILURE;

    return BitExtract(&number, pos, len);
}

/* Dispatches bit insertion. */
static int HandleInsert(const char *input, const char *source,
                        const char *position, const char *length) {
    Integer number, value;
    unsigned pos, len;

    if (GetInteger(input, &number) != 0 ||
        GetInteger(source, &value) != 0 ||
        ParseUnsignedArg(position, &pos) != 0 ||
        ParseUnsignedArg(length, &len) != 0)
        return EXIT_FAILURE;

    return BitInsert(&number, &value, pos, len);
}

/* Dispatches bit analysis operations. */
static int HandleBitAnalysis(const char *command, const char *input) {
    Integer number;

    if (GetInteger(input, &number) != 0)
        return EXIT_FAILURE;

    if (strcmp(command, "popcount") == 0)
        return BitPopcount(&number);

    if (strcmp(command, "leading-zeros") == 0)
        return BitLeadingZeros(&number);

    if (strcmp(command, "trailing-zeros") == 0)
        return BitTrailingZeros(&number);

    if (strcmp(command, "power-of-two") == 0)
        return BitPowerOfTwo(&number);

    return EXIT_FAILURE;
}

/* Dispatches memory and endianness operations. */
static int HandleMemory(int argc, char *argv[]) {
    if (strcmp(argv[1], "endian") == 0) {
        if (argc != 2)
            return EXIT_FAILURE;

        return EndianInspection();
    }

    if (argc != 3)
        return EXIT_FAILURE;

    Integer number;

    if (GetInteger(argv[2], &number) != 0)
        return EXIT_FAILURE;

    if (strcmp(argv[1], "memory") == 0)
        return MemoryInspection(&number);

    if (strcmp(argv[1], "bytes") == 0)
        return ByteInspection(&number);

    if (strcmp(argv[1], "byteswap") == 0)
        return ByteSwap(&number);

    return EXIT_FAILURE;
}

/* Dispatches floating-point inspection. */
static int HandleFloating(int argc, char *argv[]) {
    if (argc != 3)
        return EXIT_FAILURE;

    Floating number;

    if (strcmp(argv[1], "float") == 0) {
        if (ParseFloat(argv[2], &number) != 0)
            return EXIT_FAILURE;

        return FloatInspection(&number);
    }

    if (strcmp(argv[1], "double") == 0) {
        if (ParseDouble(argv[2], &number) != 0)
            return EXIT_FAILURE;

        return DoubleInspection(&number);
    }

    return EXIT_FAILURE;
}

/* Main CLI dispatcher. */
int RunCLI(int argc, char *argv[]) {
    if (argc < 2) {
        PrintUsage(argv[0]);
        return EXIT_FAILURE;
    }

    const char *command = argv[1];

    if (strcmp(command, "int") == 0)
        return HandleInteger(argc, argv);

    if (strcmp(command, "and") == 0 ||
        strcmp(command, "or") == 0 ||
        strcmp(command, "xor") == 0) {
        if (argc != 4)
            goto invalid_arguments;

        return HandleBitwiseBinary(command, argv[2], argv[3]);
    }

    if (strcmp(command, "not") == 0 ||
        strcmp(command, "shl") == 0 ||
        strcmp(command, "shr") == 0)
        return HandleBitwiseUnary(argc, argv);

    if (strcmp(command, "set") == 0 ||
        strcmp(command, "clear") == 0 ||
        strcmp(command, "toggle") == 0 ||
        strcmp(command, "test") == 0) {
        if (argc != 4)
            goto invalid_arguments;

        return HandleBitSingle(command, argv[2], argv[3]);
    }

    if (strcmp(command, "extract") == 0) {
        if (argc != 5)
            goto invalid_arguments;

        return HandleExtract(argv[2], argv[3], argv[4]);
    }

    if (strcmp(command, "insert") == 0) {
        if (argc != 6)
            goto invalid_arguments;

        return HandleInsert(argv[2], argv[3], argv[4], argv[5]);
    }

    if (strcmp(command, "popcount") == 0 ||
        strcmp(command, "leading-zeros") == 0 ||
        strcmp(command, "trailing-zeros") == 0 ||
        strcmp(command, "power-of-two") == 0) {
        if (argc != 3)
            goto invalid_arguments;

        return HandleBitAnalysis(command, argv[2]);
    }

    if (strcmp(command, "memory") == 0 ||
        strcmp(command, "bytes") == 0 ||
        strcmp(command, "byteswap") == 0 ||
        strcmp(command, "endian") == 0)
        return HandleMemory(argc, argv);

    if (strcmp(command, "float") == 0 ||
        strcmp(command, "double") == 0)
        return HandleFloating(argc, argv);

invalid_arguments:
    fprintf(stderr, "Invalid arguments for command '%s'.\n\n", command);
    PrintUsage(argv[0]);
    return EXIT_FAILURE;
}
