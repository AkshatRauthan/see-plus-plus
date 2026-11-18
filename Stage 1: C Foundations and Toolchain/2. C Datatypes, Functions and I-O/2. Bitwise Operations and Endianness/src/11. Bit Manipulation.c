
#include <stdio.h>

/*
 * Set a bit:
 * Uses OR to force the selected bit to 1.
 */
unsigned int setBit(unsigned int value, unsigned int position) {
	return value | (1U << position);
}

/*
 * Clear a bit:
 * Uses AND with an inverted mask to force the selected bit to 0.
 */
unsigned int clearBit(unsigned int value, unsigned int position) {
	return value & ~(1U << position);
}

/*
 * Toggle a bit:
 * Uses XOR to invert the selected bit.
 */
unsigned int toggleBit(unsigned int value, unsigned int position) {
	return value ^ (1U << position);
}

/*
 * Test a bit:
 * Uses AND to determine whether the selected bit is set.
 */
int testBit(unsigned int value, unsigned int position) {
	return (value & (1U << position)) != 0;
}

/*
 * Display the lowest 8 bits of an unsigned integer.
 */
void printBinary(unsigned int value) {
	for (int i = 7; i >= 0; i--) {
		printf("%u", (value >> i) & 1U);
	}

	printf("\n");
}

int main(void) {
	unsigned int value = 12U; // 00001100
	unsigned int position = 1U;

	printf("Bit Manipulation\n");
	printf("----------------\n");

	printf("Original value: ");
	printBinary(value);

	/* Set bit 1. */
	unsigned int set_result = setBit(value, position);

	printf("\nAfter setting bit %u: ", position);
	printBinary(set_result);

	/* Clear bit 2. */
	unsigned int clear_result = clearBit(value, 2U);

	printf("After clearing bit 2: ");
	printBinary(clear_result);

	/* Toggle bit 0. */
	unsigned int toggle_result = toggleBit(value, 0U);

	printf("After toggling bit 0: ");
	printBinary(toggle_result);

	/* Test bit 2. */
	printf("\nIs bit 2 set? %s\n", testBit(value, 2U) ? "Yes" : "No");

	/* Test bit 0. */
	printf("Is bit 0 set? %s\n", testBit(value, 0U) ? "Yes" : "No");

	return 0;
}
