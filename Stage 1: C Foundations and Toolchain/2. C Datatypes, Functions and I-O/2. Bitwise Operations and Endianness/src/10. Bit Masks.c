
#include <stdio.h>

int main(void) {
	/*
	 * Bit Masks:
	 *
	 * A mask selects specific bit positions.
	 *
	 * Example:
	 *
	 *     value = 11001100
	 *     mask  = 00001111
	 *     ----------------
	 * value & mask = 00001100
	 *
	 * Only the bits selected by the mask remain.
	 */

	unsigned int value = 0xCCU;   /* 0b11001100 */
	unsigned int mask  = 0x0FU;   /* 0b00001111 */

	printf("Bit Masks\n");
	printf("---------\n");

	printf("Value: %u\n", value);
	printf("Mask:  %u\n", mask);
	printf("Value & mask: %u\n\n", value & mask);

	/*
	 * Display the lowest 8 bits.
	 */
	printf("Binary representation:\n");

	printf("Value       = ");
	for (int i = 7; i >= 0; i--)
		printf("%u", (value >> i) & 1U);

	printf("\nMask        = ");
	for (int i = 7; i >= 0; i--)
		printf("%u", (mask >> i) & 1U);

	printf("\nValue & mask = ");
	for (int i = 7; i >= 0; i--)
		printf("%u", ((value & mask) >> i) & 1U);

	printf("\n");

	return 0;
}
