#include "../../include/commands.h"

#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

// Generate a mask containing the requested number of set bits.
static uint64_t WidthMask(unsigned width) {
	return width == 64 ? UINT64_MAX : (UINT64_C(1) << width) - 1;
}

// Print an integer using its original signedness.
static void PrintValue(uint64_t bits, unsigned width, int isSigned) {
	if (isSigned && ((bits >> (width - 1)) & 1)) {
		uint64_t extended = bits | ~WidthMask(width);
		int64_t value;

		memcpy(&value, &extended, sizeof value);
		printf("%" PRId64, value);
	} else {
		printf("%" PRIu64, bits);
	}
}

// Print a width-padded binary representation.
static void PrintBinary(uint64_t bits, unsigned width) {
	for (int i = (int)width - 1; i >= 0; i--) {
		putchar(((bits >> i) & 1) ? '1' : '0');

		if (i % 8 == 0 && i != 0)
			putchar(' ');
	}
}

// Print a value and its binary representation.
static void PrintRow(const char *label, uint64_t bits, unsigned width,
					 int isSigned) {
	printf("%-10s: ", label);
	PrintValue(bits, width, isSigned);

	printf("  (");
	PrintBinary(bits, width);
	printf(")\n");
}

// Validate a bit position.
static int CheckPos(const Integer *number, unsigned pos) {
	if (number == NULL || number->width < 1 || number->width > 64) {
		fprintf(stderr, "Invalid integer argument\n");
		return -1;
	}

	if (pos >= (unsigned)number->width) {
		fprintf(stderr, "Bit position %u out of range (0-%u for %s)\n", pos,
				(unsigned)number->width - 1, IntegerTypeName(number->type));
		return -1;
	}

	return 0;
}

// Validate a bit range without risking unsigned overflow.
static int CheckRange(const Integer *number, unsigned pos, unsigned len) {
	if (number == NULL || number->width < 1 || number->width > 64) {
		fprintf(stderr, "Invalid integer argument\n");
		return -1;
	}

	unsigned width = (unsigned)number->width;

	if (len == 0 || len > width || pos > width - len) {
		fprintf(stderr, "Range pos=%u len=%u does not fit in %u bits\n", pos,
				len, width);
		return -1;
	}

	return 0;
}

// Return the operation's display title.
static const char *OpTitle(BitManipOp op) {
	switch (op) {
		case BM_SET:
			return "SET BIT";
		case BM_CLEAR:
			return "CLEAR BIT";
		case BM_TOGGLE:
			return "TOGGLE BIT";
		case BM_TEST:
			return "TEST BIT";
		}

	return "UNKNOWN";
}

// Set, clear, toggle or test an individual bit.
int BitSingle(BitManipOp op, const Integer *a, unsigned pos) {
	if (op < BM_SET || op > BM_TEST) {
		fprintf(stderr, "Invalid bit manipulation operation\n");
		return -1;
	}

	if (CheckPos(a, pos) != 0)
		return -1;

	uint64_t bits = GetBits(a);
	uint64_t mask = UINT64_C(1) << pos;
	uint64_t result = bits;

	switch (op) {
	case BM_SET:
		result = bits | mask;
		break;

	case BM_CLEAR:
		result = bits & ~mask;
		break;

	case BM_TOGGLE:
		result = bits ^ mask;
		break;

	case BM_TEST:
		break;
	}

	printf("========== %s ==========\n\n", OpTitle(op));

	PrintRow("Operand", bits, a->width, a->isSigned);
	printf("%-10s: %u\n", "Position", pos);
	PrintRow("Mask", mask, a->width, 0);

	putchar('\n');

	if (op == BM_TEST) {
		int isSet = (bits & mask) != 0;

		printf("%-10s: %d (%s)\n", "Bit", isSet, isSet ? "set" : "clear");
	} else {
		PrintRow("Result", result, a->width, a->isSigned);
	}

	printf("\n================================\n");

	return 0;
}

// Extract a range of bits from an integer.
int BitExtract(const Integer *a, unsigned pos, unsigned len) {
	if (CheckRange(a, pos, len) != 0)
		return -1;

	uint64_t bits = GetBits(a);
	uint64_t mask = WidthMask(len) << pos;
	uint64_t result = (bits & mask) >> pos;

	printf("========== EXTRACT BITS ==========\n\n");

	PrintRow("Operand", bits, a->width, a->isSigned);

	printf("%-10s: bits %u..%u (%u bits)\n", "Range", pos + len - 1, pos, len);

	PrintRow("Mask", mask, a->width, 0);

	putchar('\n');

	// Extracted fields are displayed as unsigned bit patterns.
	PrintRow("Result", result, len, 0);

	printf("\n==================================\n");

	return 0;
}

// Insert a value into a specified bit range.
int BitInsert(const Integer *a, const Integer *value, unsigned pos,
			  unsigned len) {
	if (value == NULL) {
		fprintf(stderr, "Invalid value argument\n");
		return -1;
	}

	if (CheckRange(a, pos, len) != 0)
		return -1;

	if (value->width < 1 || value->width > 64) {
		fprintf(stderr, "Invalid value width\n");
		return -1;
	}

	uint64_t bits = GetBits(a);
	uint64_t insertValue = GetBits(value);

	// Ensure the inserted value fits within the selected range.
	if ((insertValue & ~WidthMask(len)) != 0) {
		fprintf(stderr, "Value does not fit in %u bits\n", len);
		return -1;
	}

	uint64_t mask = WidthMask(len) << pos;

	// Clear the target range and insert the new bit pattern.
	uint64_t result = (bits & ~mask) | (insertValue << pos);

	printf("========== INSERT BITS ==========\n\n");

	PrintRow("Operand", bits, a->width, a->isSigned);
	PrintRow("Value", insertValue, len, 0);

	printf("%-10s: bits %u..%u (%u bits)\n", "Range", pos + len - 1, pos, len);

	PrintRow("Mask", mask, a->width, 0);

	putchar('\n');

	PrintRow("Result", result, a->width, a->isSigned);

	printf("\n=================================\n");

	return 0;
}
