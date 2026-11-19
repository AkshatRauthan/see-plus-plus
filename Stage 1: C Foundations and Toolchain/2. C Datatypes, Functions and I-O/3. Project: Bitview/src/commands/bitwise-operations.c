#include "../../include/commands.h"

#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

static uint64_t WidthMask(unsigned width) {
	return width == 64 ? UINT64_MAX : (UINT64_C(1) << width) - 1;
}

static const char *OpTitle(BitOp op) {
	switch (op) {
	case OP_AND:
		return "AND";
	case OP_OR:
		return "OR";
	case OP_XOR:
		return "XOR";
	case OP_NOT:
		return "NOT";
	case OP_SHL:
		return "LEFT SHIFT";
	case OP_SHR:
		return "RIGHT SHIFT";
	}
	return "?";
}

static void PrintValue(uint64_t bits, unsigned width, int isSigned) {
	if (isSigned && ((bits >> (width - 1)) & 1)) {
		uint64_t extended = bits | ~WidthMask(width); /* sign-extend */
		int64_t value;
		memcpy(&value, &extended, sizeof value); /* reinterpret, no UB */
		printf("%" PRId64, value);
	} else {
		printf("%" PRIu64, bits);
	}
}

static void PrintBinary(uint64_t bits, unsigned width) {
	for (int i = (int)width - 1; i >= 0; i--) {
		putchar(((bits >> i) & 1) ? '1' : '0');
		if (i % 8 == 0 && i != 0)
			putchar(' ');
	}
}

static void PrintRow(const char *label, uint64_t bits, unsigned width,
					 int isSigned) {
	printf("%-10s: ", label);
	PrintValue(bits, width, isSigned);
	printf("  (");
	PrintBinary(bits, width);
	printf(")\n");
}

static void PrintHeader(BitOp op) {
	printf("========== BITWISE %s ==========\n\n", OpTitle(op));
}

static void PrintFooter(void) {
	printf("\n================================\n");
}

int BitwiseBinary(BitOp op, const Integer *a, const Integer *b) {
	if (a->width != b->width || a->isSigned != b->isSigned) {
		fprintf(stderr, "Operands must have the same type (%s vs %s)\n",
				IntegerTypeName(a->type), IntegerTypeName(b->type));
		return -1;
	}

	uint64_t x = GetBits(a);
	uint64_t y = GetBits(b);
	uint64_t result;

	switch (op) {
	case OP_AND:
		result = x & y;
		break;
	case OP_OR:
		result = x | y;
		break;
	case OP_XOR:
		result = x ^ y;
		break;
	default:
		fprintf(stderr, "Not a binary bitwise operation\n");
		return -1;
	}

	PrintHeader(op);
	PrintRow("Operand 1", x, a->width, a->isSigned);
	PrintRow("Operand 2", y, a->width, a->isSigned);
	putchar('\n');
	PrintRow("Result", result, a->width, a->isSigned);
	PrintFooter();
	return 0;
}

int BitwiseNot(const Integer *a) {
	uint64_t x = GetBits(a);
	uint64_t result = ~x & WidthMask(a->width); /* ~ flips all 64 bits; trim */

	PrintHeader(OP_NOT);
	PrintRow("Operand", x, a->width, a->isSigned);
	putchar('\n');
	PrintRow("Result", result, a->width, a->isSigned);
	PrintFooter();
	return 0;
}

int BitwiseShift(BitOp op, const Integer *a, unsigned count) {
	if (op != OP_SHL && op != OP_SHR) {
		fprintf(stderr, "Not a shift operation\n");
		return -1;
	}
	if (count >= (unsigned)a->width) {
		fprintf(stderr, "Shift count %u must be less than width %u\n", count,
				a->width);
		return -1;
	}

	uint64_t mask = WidthMask(a->width);
	uint64_t x = GetBits(a);
	uint64_t result;

	if (op == OP_SHL) {
		result = (x << count) & mask;
	} else {
		result = x >> count; /* logical shift on the unsigned pattern */
		if (a->isSigned && ((x >> (a->width - 1)) & 1))
			result |=
				mask & ~(mask >> count); /* arithmetic: refill sign bits */
	}

	PrintHeader(op);
	PrintRow("Operand", x, a->width, a->isSigned);
	printf("%-10s: %u\n", "Shift by", count);
	putchar('\n');
	PrintRow("Result", result, a->width, a->isSigned);
	PrintFooter();
	return 0;
}
