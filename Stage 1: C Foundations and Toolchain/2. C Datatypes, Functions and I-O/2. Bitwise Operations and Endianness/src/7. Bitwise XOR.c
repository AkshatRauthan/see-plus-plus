
#include <stdio.h>

int main(void) {
	/*
	 * Bitwise XOR (^):
	 *
	 * Performs XOR on each corresponding bit.
	 *
	 * Example:
	 *
	 *     12 = 1100
	 *      10 = 1010
	 *     --------
	 * 12 ^ 10 = 0110 = 6
	 */

	unsigned int a = 12U;
	unsigned int b = 10U;

	unsigned int result = a ^ b;

	printf("Bitwise XOR\n");
	printf("-----------\n");

	printf("a = %u\n", a);
	printf("b = %u\n", b);
	printf("a ^ b = %u\n\n", result);

	/*
	 * Display operands and result in binary.
	 */
	printf("Binary representation:\n");

	printf("a      = ");
	for (int i = 7; i >= 0; i--) {
		printf("%u", (a >> i) & 1U);
	}

	printf("\nb      = ");
	for (int i = 7; i >= 0; i--) {
		printf("%u", (b >> i) & 1U);
	}

	printf("\n----------------\n");

	printf("a ^ b  = ");
	for (int i = 7; i >= 0; i--) {
		printf("%u", (result >> i) & 1U);
	}

	printf("\n");

	return 0;
}
