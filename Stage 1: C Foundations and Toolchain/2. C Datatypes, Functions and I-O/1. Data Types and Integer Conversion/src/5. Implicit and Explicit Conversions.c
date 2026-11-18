
#include <limits.h>
#include <stdio.h>

int main(void) {
	/*
	 * Type conversions:
	 *
	 * Implicit conversions happen automatically according to C's
	 * conversion rules.
	 *
	 * Explicit conversions are requested using cast operators.
	 */

	/* Example 1: implicit integer conversion */
	int integer = 100;
	double floating = integer;

	/*
	 * int is automatically converted to double.
	 * No information is lost for this value.
	 */
	printf("Example 1: implicit integer conversion\n");
	printf("integer = %d\n", integer);
	printf("floating = %f\n\n", floating);

	/* Example 2: implicit narrowing conversion */
	int large_value = 300;
	unsigned char small_value = large_value;

	/*
	 * Conversion to unsigned char reduces the value modulo
	 * UCHAR_MAX + 1.
	 *
	 * On an implementation with 8-bit bytes and 8-bit
	 * unsigned char, the result is 44.
	 */
	printf("Example 2: implicit narrowing conversion\n");
	printf("large_value = %d\n", large_value);
	printf("small_value = %u\n\n", (unsigned int)small_value);

	/* Example 3: explicit conversion using a cast */
	double decimal = 9.75;
	int truncated = (int)decimal;

	/*
	 * Conversion from floating-point to integer discards
	 * the fractional part (truncates toward zero).
	 */
	printf("Example 3: explicit conversion\n");
	printf("decimal = %f\n", decimal);
	printf("truncated = %d\n\n", truncated);

	/* Example 4: signed integer to unsigned integer */
	int negative = -1;
	unsigned int converted = (unsigned int)negative;

	/*
	 * Conversion to unsigned int is defined modulo UINT_MAX + 1.
	 * Therefore, -1 becomes UINT_MAX.
	 */
	printf("Example 4: signed to unsigned conversion\n");
	printf("negative = %d\n", negative);
	printf("converted = %u\n\n", converted);

	/* Example 5: unsigned integer to signed integer */
	unsigned int unsigned_value = UINT_MAX;

	/*
	 * If the unsigned value cannot be represented by int,
	 * the result of conversion to int is implementation-defined
	 * in C11 and C17.
	 *
	 * Avoid relying on a particular result.
	 */
	printf("Example 5: unsigned to signed conversion\n");
	printf("unsigned_value = %u\n", unsigned_value);

	/*
	 * Example 6: floating-point to integer conversion
	 */
	double positive = 12.99;
	double negative_decimal = -12.99;

	int positive_integer = (int)positive;
	int negative_integer = (int)negative_decimal;

	/*
	 * Fractional parts are discarded toward zero:
	 * 12.99  -> 12
	 * -12.99 -> -12
	 */
	printf("\nExample 6: floating-point to integer conversion\n");
	printf("12.99 -> %d\n", positive_integer);
	printf("-12.99 -> %d\n", negative_integer);

	return 0;
}
