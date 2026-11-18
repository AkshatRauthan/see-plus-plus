
#include <stdio.h>

int main(void) {
    /*
     * Arithmetic conversions:
     *
     * When arithmetic operators or comparison operators receive
     * operands of different arithmetic types, C converts them
     * to a common type before performing the operation.
     */

    /* Example 1: int and long */
    int a = 10;
    long b = 20L;

    /*
     * int is converted to long.
     * The addition is performed using long.
     */
    printf("Example 1: int and long\n");
    printf("a + b = %ld\n", a + b);
    printf("sizeof(a + b) = %zu byte(s)\n\n", sizeof(a + b));

    /* Example 2: signed int and unsigned int */
    int signed_value = -1;
    unsigned int unsigned_value = 1U;

    /*
     * int and unsigned int have the same rank.
     * The signed operand is converted to unsigned int.
     *
     * -1 becomes UINT_MAX (modulo UINT_MAX + 1).
     */
    printf("Example 2: int and unsigned int\n");
    printf("signed_value < unsigned_value: %s\n",
           signed_value < unsigned_value ? "true" : "false");

    printf("signed_value + unsigned_value = %u\n\n",
           signed_value + unsigned_value);

    /* Example 3: signed long and unsigned int */
    long signed_long = -1L;
    unsigned int unsigned_int = 1U;

    /*
     * If long can represent every unsigned int value,
     * unsigned int is converted to long.
     *
     * Otherwise, both operands are converted to unsigned long.
     *
     * On common 32-bit and 64-bit systems, long can represent
     * every unsigned int value.
     */
    printf("Example 3: long and unsigned int\n");
    printf("signed_long < unsigned_int: %s\n\n",
           signed_long < unsigned_int ? "true" : "false");

    /* Example 4: float and double */
    float f = 3.5f;
    double d = 2.5;

    /*
     * float is converted to double.
     * The addition is performed using double.
     */
    printf("Example 4: float and double\n");
    printf("f + d = %f\n", f + d);
    printf("sizeof(f + d) = %zu byte(s)\n\n", sizeof(f + d));

    /* Example 5: integer and floating-point */
    int integer = 10;
    double floating = 2.5;

    /*
     * The integer is converted to double.
     * The addition is performed using double.
     */
    printf("Example 5: integer and floating-point\n");
    printf("integer + floating = %f\n", integer + floating);
    printf("sizeof(integer + floating) = %zu byte(s)\n",
           sizeof(integer + floating));

    return 0;
}
