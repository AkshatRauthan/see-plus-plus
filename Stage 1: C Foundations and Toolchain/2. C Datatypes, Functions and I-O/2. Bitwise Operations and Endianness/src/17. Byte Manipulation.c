
#include <limits.h>
#include <stdint.h>
#include <stdio.h>

/*
 * Extract a byte from a 32-bit integer.
 *
 * Position 0 represents the least significant byte.
 * Position 3 represents the most significant byte.
 */
uint8_t extractByte(uint32_t value, unsigned int position) {
	return (uint8_t)(value >> (position * CHAR_BIT));
}

/*
 * Combine four bytes into a 32-bit integer.
 *
 * The first argument becomes the most significant byte.
 */
uint32_t combineBytes(uint8_t b0, uint8_t b1, uint8_t b2, uint8_t b3) {
	return ((uint32_t)b0 << 24) | ((uint32_t)b1 << 16) | ((uint32_t)b2 << 8) |
		   (uint32_t)b3;
}

/* Reverse the byte order of a 32-bit integer. */
uint32_t swapBytes(uint32_t value) {
	return ((value & 0x000000FFU) << 24) | ((value & 0x0000FF00U) << 8) |
		   ((value & 0x00FF0000U) >> 8) | ((value & 0xFF000000U) >> 24);
}

int main(void) {
	uint32_t value = 0x12345678U;

	printf("Byte Manipulation\n");
	printf("-----------------\n");

	printf("Original value: 0x%08X\n", value);

	/* Extract individual bytes. */
	printf("\nExtracted bytes:\n");

	for (unsigned int i = 0; i < 4; i++) {
		printf("Byte %u: 0x%02X\n", i, (unsigned int)extractByte(value, i));
	}

	/* Combine four bytes into a 32-bit integer. */
	uint32_t combined = combineBytes(0x12, 0x34, 0x56, 0x78);

	printf("\nCombined value: 0x%08X\n", combined);

	/* Reverse the byte order. */
	uint32_t swapped = swapBytes(value);

	printf("Swapped value:  0x%08X\n", swapped);

	return 0;
}
