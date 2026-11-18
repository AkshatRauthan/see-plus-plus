
#include <limits.h>
#include <stdio.h>

int main(void) {
    /*
     * Unsigned integers:
     *
     * All value bits represent a non-negative magnitude.
     *
     * For an N-bit unsigned integer:
     * Range = 0 to (2^N - 1)
     *
     * Signed integers:
     *
     * C11/C17 permit multiple signed representations:
     * sign-and-magnitude, ones' complement, and two's complement.
     *
     * Two's complement is used by modern mainstream systems.
     * This experiment assumes two's complement when interpreting
     * the displayed signed values as bit patterns.
     */

    unsigned char unsigned_value = 13;
    signed char signed_value = 13;

    printf("Unsigned and Signed Integer Representation\n");
    printf("-------------------------------------------\n");

    printf("CHAR_BIT: %d\n", CHAR_BIT);
    printf("unsigned char size: %zu byte(s)\n", sizeof(unsigned_value));
    printf("signed char size:   %zu byte(s)\n\n", sizeof(signed_value));

    /*
     * Display the object representation of each value.
     *
     * Accessing an object's representation through unsigned char
     * is permitted by the C standard.
     */
    printf("Unsigned char value: %u\n", (unsigned int)unsigned_value);
    printf("Unsigned representation: ");

    for (int i = CHAR_BIT - 1; i >= 0; i--) {
        printf("%u", (unsigned int)((unsigned_value >> i) & 1U));
    }

    printf("\n\n");

    printf("Signed char value: %d\n", (int)signed_value);
    printf("Signed representation: ");

    const unsigned char *bytes =
        (const unsigned char *)&signed_value;

    for (int i = CHAR_BIT - 1; i >= 0; i--) {
        printf("%u", (unsigned int)((bytes[0] >> i) & 1U));
    }

    printf("\n");

    return 0;
}
