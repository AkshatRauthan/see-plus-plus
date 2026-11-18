
#include <stdio.h>

int main(void) {
	/*
	 * Bitwise NOT (~):
	 *
	 * Inverts every bit of its operand.
	 *
	 * Example using 8 bits:
	 *
	 *     12 = 00001100
	 *    ~12 = 11110011
	 *
	 * Note:
	 * The unsigned int operand undergoes integer promotions
	 * (if necessary) before the NOT operation.
	 */

	unsigned int value = 12U;
	unsigned int result = ~value;

	printf("Bitwise NOT\n");
	printf("-----------\n");

	printf("value = %u\n", value);
	printf("~value = %u\n\n", result);

	/*
	 * Display the lowest 8 bits of the operand and result.
	 */
	printf("Lowest 8 bits:\n");

	printf("value  = ");
	for (int i = 7; i >= 0; i--) {
		printf("%u", (value >> i) & 1U);
	}

	printf("\n~value = ");
	for (int i = 7; i >= 0; i--) {
		printf("%u", (result >> i) & 1U);
	}

	printf("\n");

	return 0;
}
