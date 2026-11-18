
#include <limits.h>
#include <stdio.h>

/*
 * Extract a group of bits.
 *
 * value:     Source integer.
 * position:  Starting bit position (LSB = 0).
 * width:     Number of bits to extract.
 *
 * The extracted bits are returned right-aligned.
 */
unsigned int extractBits(unsigned int value, unsigned int position,
						 unsigned int width) {
	unsigned int mask = (1U << width) - 1U;

	return (value >> position) & mask;
}

/*
 * Insert a group of bits.
 *
 * value:     Original integer.
 * new_bits:  Bits to insert.
 * position:  Starting bit position.
 * width:     Number of bits to replace.
 *
 * Bits outside the selected range remain unchanged.
 */
unsigned int insertBits(unsigned int value, unsigned int new_bits,
						unsigned int position, unsigned int width) {
	unsigned int mask = (1U << width) - 1U;

	/* Clear the destination bit range. */
	value &= ~(mask << position);

	/* Insert the new bits into the cleared range. */
	value |= (new_bits & mask) << position;

	return value;
}

/* Display the lowest 8 bits. */
void printBinary(unsigned int value) {
	for (int i = 7; i >= 0; i--) {
		printf("%u", (value >> i) & 1U);
	}

	printf("\n");
}

int main(void) {
	/*
	 * Original value:
	 *
	 * 11010110
	 *
	 * Extract 3 bits starting at position 2:
	 *
	 *       11010110
	 *          ^^^
	 *
	 * Extracted value = 101 = 5
	 */

	unsigned int value = 0b11010110U;

	unsigned int position = 2U;
	unsigned int width = 3U;

	printf("Bit Extraction and Insertion\n");
	printf("----------------------------\n");

	printf("Original value: ");
	printBinary(value);

	/* Extract three bits starting at position 2. */
	unsigned int extracted = extractBits(value, position, width);

	printf("\nExtracted bits: ");
	printBinary(extracted);

	printf("Extracted decimal value: %u\n", extracted);

	/*
	 * Replace those three bits with 011.
	 *
	 * Original:  11010110
	 * New bits:      011
	 * Result:    11001110
	 */

	unsigned int new_bits = 0b011U;

	unsigned int modified = insertBits(value, new_bits, position, width);

	printf("\nAfter insertion: ");
	printBinary(modified);

	return 0;
}
