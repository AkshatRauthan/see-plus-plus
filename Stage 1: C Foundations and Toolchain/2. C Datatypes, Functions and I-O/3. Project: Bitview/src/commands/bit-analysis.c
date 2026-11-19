#include "../../include/commands.h"

#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>

static void PrintBinary(uint64_t bits, unsigned width) {
	for (int i = (int)width - 1; i >= 0; i--) {
		putchar(((bits >> i) & 1) ? '1' : '0');

		if (i % 8 == 0 && i != 0)
			putchar(' ');
	}
}

static void PrintHeader(const char *title) {
	printf("========== BIT ANALYSIS: %s ==========\n\n", title);
}

static void PrintFooter(void) {
	printf("\n======================================\n");
}

static void PrintInput(const Integer *number) {
	uint64_t bits = GetBits(number);

	printf("Value     : %" PRIu64 "\n", bits);
	printf("Binary    : ");
	PrintBinary(bits, number->width);
	putchar('\n');
}

// Count the number of set bits.
int BitPopcount(const Integer *number) {
	if (number == NULL)
		return -1;

	uint64_t bits = GetBits(number);
	unsigned count = CountSetBits(bits);

	PrintHeader("POPCOUNT");
	PrintInput(number);
	printf("\nSet Bits  : %u\n", count);
	PrintFooter();

	return 0;
}

// Count consecutive zero bits starting from the most significant bit.
int BitLeadingZeros(const Integer *number) {
	if (number == NULL)
		return -1;

	uint64_t bits = GetBits(number);
	unsigned count = 0;

	for (int i = (int)number->width - 1; i >= 0; i--) {
		if ((bits >> i) & 1)
			break;

		count++;
	}

	PrintHeader("LEADING ZEROS");
	PrintInput(number);
	printf("\nLeading Zeros : %u\n", count);
	PrintFooter();

	return 0;
}

// Count consecutive zero bits starting from the least significant bit.
int BitTrailingZeros(const Integer *number) {
	if (number == NULL)
		return -1;

	uint64_t bits = GetBits(number);
	unsigned count = 0;

	while (count < (unsigned)number->width && ((bits >> count) & 1) == 0)
		count++;

	PrintHeader("TRAILING ZEROS");
	PrintInput(number);
	printf("\nTrailing Zeros : %u\n", count);
	PrintFooter();

	return 0;
}

// Check whether the value is a positive power of two.
int BitPowerOfTwo(const Integer *number) {
	if (number == NULL)
		return -1;

	uint64_t bits = GetBits(number);

	int result = bits != 0 && (bits & (bits - 1)) == 0;

	// Negative signed integers are not positive powers of two.
	if (number->isSigned && (bits >> (number->width - 1)))
		result = 0;

	PrintHeader("POWER OF TWO");
	PrintInput(number);
	printf("\nPower of Two : %s\n", result ? "Yes" : "No");
	PrintFooter();

	return 0;
}
