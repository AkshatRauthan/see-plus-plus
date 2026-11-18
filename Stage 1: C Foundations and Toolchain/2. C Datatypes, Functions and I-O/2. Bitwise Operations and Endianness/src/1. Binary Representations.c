
#include <limits.h>
#include <stdio.h>

int main(void) {
	/*
	 * Binary representation:
	 *
	 * Computers represent integer values using bits (0 and 1).
	 *
	 * Each binary digit represents a power of 2.
	 *
	 * Example:
	 * 13 = 8 + 4 + 1
	 *    = 1101 in binary
	 */

	unsigned int number = 13U;

	printf("Binary Representation\n");
	printf("---------------------\n");

	/* Display the decimal value. */
	printf("Decimal value: %u\n", number);

	/*
	 * CHAR_BIT specifies the number of bits in one C byte.
	 *
	 * sizeof returns the number of C bytes occupied by an object.
	 */
	printf("Bits per byte: %d\n", CHAR_BIT);
	printf("Size of unsigned int: %zu byte(s)\n", sizeof(number));
	printf("Total object bits: %zu\n\n", sizeof(number) * CHAR_BIT);

	/*
	 * Display the binary representation.
	 *
	 * Start from the most significant bit and inspect each bit
	 * using a right shift and bitwise AND.
	 */
	printf("Binary representation: ");

	for (int i = (int)(sizeof(number) * CHAR_BIT) - 1; i >= 0; i--) {
		printf("%u", (number >> i) & 1U);

		/* Separate groups of 8 bits for readability. */
		if (i > 0 && i % 8 == 0) {
			printf(" ");
		}
	}

	printf("\n");

	return 0;
}
