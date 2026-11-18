
#include <limits.h>
#include <stdio.h>

int main(void) {
    /*
     * Two's complement representation:
     *
     * To obtain the two's complement of a binary number:
     *
     * 1. Invert every bit.
     * 2. Add 1.
     *
     * Example using 8 bits:
     *
     *  13 = 00001101
     * ~13 = 11110010
     * + 1 = 11110011
     *
     * Therefore, -13 is represented as 11110011.
     *
     * This experiment assumes an implementation using
     * two's complement signed integer representation.
     */

    signed char positive = 13;
    signed char negative = -13;

    printf("Two's Complement Representation\n");
    printf("--------------------------------\n");

    printf("Positive value: %d\n", (int)positive);
    printf("Negative value: %d\n\n", (int)negative);

    /*
     * Inspect the object representation through unsigned char.
     * This is permitted by the C standard.
     */
    const unsigned char *positive_bytes =
        (const unsigned char *)&positive;

    const unsigned char *negative_bytes =
        (const unsigned char *)&negative;

    printf("Positive representation: ");

    for (int i = CHAR_BIT - 1; i >= 0; i--) {
        printf("%u", (unsigned int)((positive_bytes[0] >> i) & 1U));
    }

    printf("\nNegative representation: ");

    for (int i = CHAR_BIT - 1; i >= 0; i--) {
        printf("%u", (unsigned int)((negative_bytes[0] >> i) & 1U));
    }

    printf("\n");

    return 0;
}
