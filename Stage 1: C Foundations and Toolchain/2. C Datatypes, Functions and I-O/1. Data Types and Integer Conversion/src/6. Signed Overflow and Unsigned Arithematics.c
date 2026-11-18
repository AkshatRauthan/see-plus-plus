
#include <limits.h>
#include <stdio.h>

int main(void) {
	/*
	 * Signed integer overflow:
	 *
	 * If an arithmetic operation produces a value outside the
	 * representable range of a signed integer type, its behavior
	 * is undefined (UB).
	 *
	 * Do not execute the overflowing operation directly in this
	 * demonstration. Use UBSan separately to investigate it.
	 */

	printf("Signed integer limits\n");
	printf("INT_MIN = %d\n", INT_MIN);
	printf("INT_MAX = %d\n\n", INT_MAX);

	/*
	 * Example 1: Signed overflow boundary
	 *
	 * INT_MAX + 1 would cause signed integer overflow.
	 * Instead, demonstrate the boundary without overflowing.
	 */
	int signed_value = INT_MAX;

	printf("Example 1: signed integer boundary\n");
	printf("Value at maximum = %d\n", signed_value);
	printf("Adding 1 would cause signed overflow.\n\n");

	/*
	 * Example 2: Unsigned integer wraparound
	 *
	 * Unsigned arithmetic is performed modulo UINT_MAX + 1.
	 * Therefore, UINT_MAX + 1 produces 0.
	 */
	unsigned int unsigned_value = UINT_MAX;

	printf("Example 2: unsigned overflow\n");
	printf("UINT_MAX = %u\n", unsigned_value);

	unsigned_value += 1U;

	printf("UINT_MAX + 1 = %u\n\n", unsigned_value);

	/*
	 * Example 3: Unsigned underflow
	 *
	 * Subtracting 1 from 0 wraps around to UINT_MAX.
	 */
	unsigned int zero = 0U;

	printf("Example 3: unsigned underflow\n");
	printf("0 - 1 = %u\n\n", zero - 1U);

	/*
	 * Example 4: Unsigned modular arithmetic
	 *
	 * Unsigned arithmetic wraps modulo UINT_MAX + 1.
	 */
	unsigned int a = UINT_MAX - 2U;
	unsigned int b = 5U;

	printf("Example 4: unsigned modular arithmetic\n");
	printf("a = %u\n", a);
	printf("b = %u\n", b);
	printf("a + b = %u\n", a + b);

	return 0;
}
