
#include <limits.h>
#include <stdio.h>

int main(void) {
	/*
	 * Bitwise Shift Operators:
	 *
	 * Left shift (<<):
	 * Moves bits towards the left.
	 * Vacated lower-order bits are filled with zeros.
	 *
	 * Right shift (>>):
	 * Moves bits towards the right.
	 * For unsigned operands, vacated higher-order bits
	 * are filled with zeros.
	 *
	 * This experiment uses unsigned int to avoid the
	 * complications of shifting negative signed values.
	 */

	unsigned int value = 12U;

	unsigned int left_shift = value << 2;
	unsigned int right_shift = value >> 2;

	printf("Bitwise Shift Operators\n");
	printf("-----------------------\n");

	printf("Original value: %u\n", value);
	printf("Left shift by 2: %u\n", left_shift);
	printf("Right shift by 2: %u\n\n", right_shift);

	/*
	 * Display the lowest 8 bits.
	 */
	printf("Binary representation (lowest 8 bits):\n");

	printf("Original: ");
	for (int i = 7; i >= 0; i--) {
		printf("%u", (value >> i) & 1U);
	}

	printf("\nLeft:     ");
	for (int i = 7; i >= 0; i--) {
		printf("%u", (left_shift >> i) & 1U);
	}

	printf("\nRight:    ");
	for (int i = 7; i >= 0; i--) {
		printf("%u", (right_shift >> i) & 1U);
	}

	printf("\n");

	return 0;
}
