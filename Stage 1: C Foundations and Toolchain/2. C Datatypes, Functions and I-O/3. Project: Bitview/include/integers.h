#ifndef INTEGERS_H
#define INTEGERS_H

#include <stdint.h>

typedef union {
	int8_t i8;
	int16_t i16;
	int32_t i32;
	int64_t i64;

	uint8_t u8;
	uint16_t u16;
	uint32_t u32;
	uint64_t u64;
} IntegerValue;

typedef enum {
	INT_8,
	INT_16,
	INT_32,
	INT_64,

	UINT_8,
	UINT_16,
	UINT_32,
	UINT_64
} IntegerType;


typedef struct {
	int width;
	int isSigned;
	char input[32];
	IntegerType type;
	IntegerValue value;
} Integer;

const char *IntegerTypeName(IntegerType type);

uint64_t GetBits(const Integer *n);
unsigned CountSetBits(uint64_t bits);

#endif
