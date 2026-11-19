#ifndef COMMANDS_H
#define COMMANDS_H

#include "parser.h"
#include "floats.h"
#include "integers.h"

// Integer Inspections
int IntegerInspection(Integer *number);


// Bitwise Operations
typedef enum { OP_AND, OP_OR, OP_XOR, OP_NOT, OP_SHL, OP_SHR } BitOp;

int BitwiseBinary(BitOp op, const Integer *a, const Integer *b);
int BitwiseNot(const Integer *a);
int BitwiseShift(BitOp op, const Integer *a, unsigned count);


// Bit Manipulation Operations
typedef enum { BM_SET, BM_CLEAR, BM_TOGGLE, BM_TEST } BitManipOp;

int BitSingle(BitManipOp op, const Integer *a, unsigned pos);
int BitExtract(const Integer *a, unsigned pos, unsigned len);
int BitInsert(const Integer *a, const Integer *value, unsigned pos, unsigned len);


// Bit Analysis Operations
int BitPopcount(const Integer *number);
int BitLeadingZeros(const Integer *number);
int BitTrailingZeros(const Integer *number);
int BitPowerOfTwo(const Integer *number);


// Memory and Endianness Operations
int MemoryInspection(const Integer *number);
int ByteInspection(const Integer *number);
int ByteSwap(const Integer *number);
int EndianInspection(void);


// Floating-Point Operations
int FloatInspection(const Floating *number);
int DoubleInspection(const Floating *number);

#endif
