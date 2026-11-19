#include "../include/integers.h"

#include <stddef.h>

uint64_t GetBits(const Integer *n) {
	if (n == NULL)
		return 0;

	switch (n->type) {
	case INT_8:
		return (uint8_t)n->value.i8;
	case INT_16:
		return (uint16_t)n->value.i16;
	case INT_32:
		return (uint32_t)n->value.i32;
	case INT_64:
		return (uint64_t)n->value.i64;
	case UINT_8:
		return n->value.u8;
	case UINT_16:
		return n->value.u16;
	case UINT_32:
		return n->value.u32;
	case UINT_64:
		return n->value.u64;
	}

	return 0;
}

unsigned CountSetBits(uint64_t bits) {
	unsigned count = 0;

	while (bits) {
		bits &= bits - 1; /* Clears the lowest set bit. */
		count++;
	}

	return count;
}

static const char *const TYPE_NAMES[] = {"int8_t",	 "int16_t", "int32_t",
										 "int64_t",	 "uint8_t", "uint16_t",
										 "uint32_t", "uint64_t"};

const char *IntegerTypeName(IntegerType type) {
	if ((unsigned)type >= sizeof TYPE_NAMES / sizeof TYPE_NAMES[0])
		return "unknown";

	return TYPE_NAMES[type];
}
