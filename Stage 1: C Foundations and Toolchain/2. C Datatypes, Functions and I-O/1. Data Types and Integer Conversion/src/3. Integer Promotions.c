
#include <limits.h>
#include <stdio.h>

int main(void) {
	/*
	 * Integer promotions:
	 *
	 * Integer types with rank lower than int are promoted before
	 * participating in most arithmetic and bitwise operations.
	 *
	 * If int can represent every value of the original type,
	 * the value is promoted to int.
	 *
	 * Otherwise, it is promoted to unsigned int.
	 */

	/* Example 1: unsigned char promotion */
	unsigned char a = 10;
	unsigned char b = 20;

	/*
	 * Both a and b are promoted to int before addition.
	 * The result of the addition is therefore int.
	 */
	int sum = a + b;

	printf("Example 1: unsigned char promotion\n");
	printf("a + b = %d\n", sum);
	printf("sizeof(a)       = %zu byte(s)\n", sizeof(a));
	printf("sizeof(a + b)   = %zu byte(s)\n\n", sizeof(a + b));

	/* Example 2: signed char promotion */
	signed char x = 100;
	signed char y = 20;

	/*
	 * x and y are promoted to int before subtraction.
	 */
	int difference = x - y;

	printf("Example 2: signed char promotion\n");
	printf("x - y = %d\n", difference);
	printf("sizeof(x)       = %zu byte(s)\n", sizeof(x));
	printf("sizeof(x - y)   = %zu byte(s)\n\n", sizeof(x - y));

	/* Example 3: short integer promotion */
	short p = 1000;
	short q = 2000;

	/*
	 * short operands are promoted to int if int can represent
	 * every value of short.
	 */
	int product = p * q;

	printf("Example 3: short promotion\n");
	printf("p * q = %d\n", product);
	printf("sizeof(p)       = %zu byte(s)\n", sizeof(p));
	printf("sizeof(p * q)   = %zu byte(s)\n\n", sizeof(p * q));

	/* Example 4: integer promotions in comparisons */
	unsigned char value = 255;
	int promoted_value = value;

	/*
	 * value is promoted to int on implementations where int
	 * can represent all unsigned char values.
	 */
	printf("Example 4: comparison\n");
	printf("value = %u\n", value);
	printf("promoted value = %d\n", promoted_value);
	printf("value < 256: %s\n", value < 256 ? "true" : "false");

	/*
	 * Example 5: integer promotions with sizeof
	 *
	 * sizeof returns size_t, an unsigned integer type.
	 * sizeof(a) is not subject to integer promotion.
	 */
	printf("\nExample 5: sizeof\n");
	printf("sizeof(a) = %zu\n", sizeof(a));
	printf("sizeof(a + b) = %zu\n", sizeof(a + b));

	return 0;
}
