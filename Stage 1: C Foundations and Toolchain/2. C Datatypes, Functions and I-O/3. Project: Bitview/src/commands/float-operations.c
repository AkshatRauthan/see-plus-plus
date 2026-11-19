
#include "../../include/floats.h"
#include "../../include/commands.h"

#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <float.h>

// Print the binary representation, grouped into bytes.
static void PrintBinary(uint64_t bits, unsigned width) {
    for (int i = (int)width - 1; i >= 0; i--) {
        putchar(((bits >> i) & 1) ? '1' : '0');

        if (i % 8 == 0 && i != 0)
            putchar(' ');
    }
}

// Print the IEEE 754 sign, exponent and mantissa fields.
static void PrintIEEE754(uint64_t bits, unsigned width,
                         unsigned exponentBits,
                         unsigned mantissaBits) {
    uint64_t exponentMask =
        (UINT64_C(1) << exponentBits) - 1;

    uint64_t mantissaMask =
        (UINT64_C(1) << mantissaBits) - 1;

    unsigned sign = (unsigned)(bits >> (width - 1)) & 1;

    uint64_t exponent =
        (bits >> mantissaBits) & exponentMask;

    uint64_t mantissa = bits & mantissaMask;

    printf("[ IEEE 754 Representation ]\n");

    printf("Sign        : %u\n", sign);

    printf("Exponent    : ");
    for (int i = (int)exponentBits - 1; i >= 0; i--)
        putchar(((exponent >> i) & 1) ? '1' : '0');

    putchar('\n');

    printf("Mantissa    : ");
    for (int i = (int)mantissaBits - 1; i >= 0; i--)
        putchar(((mantissa >> i) & 1) ? '1' : '0');

    putchar('\n');

    printf("\nBinary      : ");
    PrintBinary(bits, width);
    putchar('\n');
}

// Display common floating-point metadata.
static void PrintMetadata(const Floating *number) {
    printf("[ Metadata ]\n");
    printf("Type        : %s\n", FloatingTypeName(number->type));
    printf("Width       : %d bits\n", number->width);
    printf("Storage     : %d bytes\n", number->width / 8);
    printf("Input       : %s\n", number->input);
}

// Inspect a 32-bit floating-point value.
int FloatInspection(const Floating *number) {
    if (number == NULL || number->type != FLOAT_32)
        return -1;

    if (sizeof(float) != 4 || FLT_RADIX != 2 ||
        FLT_MANT_DIG != 24 || FLT_MAX_EXP != 128) {
        fprintf(stderr, "Platform does not support IEEE 754 binary32\n");
        return -1;
    }

    uint64_t bits = GetFloatingBits(number);

    printf("========== FLOAT INSPECTION ==========\n\n");

    PrintMetadata(number);

    printf("\n[ Numeric Representation ]\n");
    printf("Decimal     : %.6f\n", number->value.f32);
    printf("Hexadecimal : 0x%08" PRIX32 "\n", (uint32_t)bits);

    printf("\n");
    PrintIEEE754(bits, 32, 8, 23);

    printf("\n======================================\n");

    return 0;
}

// Inspect a 64-bit floating-point value.
int DoubleInspection(const Floating *number) {
    if (number == NULL || number->type != FLOAT_64)
        return -1;

    if (sizeof(double) != 8 || FLT_RADIX != 2 ||
        DBL_MANT_DIG != 53 || DBL_MAX_EXP != 1024) {
        fprintf(stderr, "Platform does not support IEEE 754 binary64\n");
        return -1;
    }

    uint64_t bits = GetFloatingBits(number);

    printf("========== DOUBLE INSPECTION ==========\n\n");

    PrintMetadata(number);

    printf("\n[ Numeric Representation ]\n");
    printf("Decimal     : %.17g\n", number->value.f64);
    printf("Hexadecimal : 0x%016" PRIX64 "\n", bits);

    printf("\n");
    PrintIEEE754(bits, 64, 11, 52);

    printf("\n========================================\n");

    return 0;
}
