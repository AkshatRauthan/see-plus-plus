
#include "../include/cli.h"
#include "../include/commands.h"
#include "../include/floats.h"
#include "../include/integers.h"
#include "../include/parser.h"

#include <assert.h>
#include <inttypes.h>
#include <limits.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static unsigned checks;
static int saved_stderr = -1;

#define CHECK(expr)                                                            \
	do {                                                                       \
		checks++;                                                              \
		if (!(expr)) {                                                         \
			fprintf(stderr, "FAIL %s:%d: %s\n", __FILE__, __LINE__, #expr);    \
			exit(EXIT_FAILURE);                                                \
		}                                                                      \
	} while (0)

static void silence_output(void) {
	static int redirected;
	if (redirected)
		return;
	fflush(stdout);
	fflush(stderr);
	saved_stderr = dup(STDERR_FILENO);
	CHECK(saved_stderr >= 0);
	FILE *nullout = freopen("/dev/null", "w", stdout);
	FILE *nullerr = freopen("/dev/null", "w", stderr);
	CHECK(nullout != NULL);
	CHECK(nullerr != NULL);
	redirected = 1;
}

static int cli(int argc, const char **args) {
	char *argv[8];
	CHECK(argc <= (int)(sizeof argv / sizeof argv[0]));
	for (int i = 0; i < argc; ++i)
		argv[i] = (char *)args[i];
	return RunCLI(argc, argv);
}

static void test_integer_parser(void) {
	Integer n;
	CHECK(ParseInteger("0", &n, 1) == 0 && n.width == 8 && n.type == INT_8 &&
		  n.value.i8 == 0);
	CHECK(ParseInteger("127", &n, 1) == 0 && n.width == 8 && n.value.i8 == 127);
	CHECK(ParseInteger("-128", &n, 1) == 0 && n.width == 8 &&
		  n.value.i8 == -128);
	CHECK(ParseInteger("128", &n, 1) == 0 && n.width == 16 &&
		  n.value.i16 == 128);
	CHECK(ParseInteger("-129", &n, 1) == 0 && n.width == 16 &&
		  n.value.i16 == -129);
	CHECK(ParseInteger("32767", &n, 1) == 0 && n.width == 16);
	CHECK(ParseInteger("32768", &n, 1) == 0 && n.width == 32);
	CHECK(ParseInteger("-32769", &n, 1) == 0 && n.width == 32);
	CHECK(ParseInteger("2147483647", &n, 1) == 0 && n.width == 32);
	CHECK(ParseInteger("2147483648", &n, 1) == 0 && n.width == 64);
	CHECK(ParseInteger("-2147483649", &n, 1) == 0 && n.width == 64);
	CHECK(ParseInteger("9223372036854775807", &n, 1) == 0 &&
		  n.value.i64 == INT64_MAX);
	CHECK(ParseInteger("-9223372036854775808", &n, 1) == 0 &&
		  n.value.i64 == INT64_MIN);
	CHECK(ParseInteger("", &n, 1) != 0);
	CHECK(ParseInteger("12x", &n, 1) != 0);
	CHECK(ParseInteger("1.0", &n, 1) != 0);
	CHECK(ParseInteger("999999999999999999999999999999999999999", &n, 1) != 0);
	CHECK(ParseInteger("-999999999999999999999999999999999999999", &n, 1) != 0);
	CHECK(ParseInteger(NULL, &n, 1) != 0);
	CHECK(ParseInteger("1", NULL, 1) != 0);
	CHECK(ParseInteger("1", &n, 2) != 0);

	CHECK(ParseInteger("0", &n, 0) == 0 && n.width == 8 && n.type == UINT_8 &&
		  n.value.u8 == 0);
	CHECK(ParseInteger("255", &n, 0) == 0 && n.width == 8 &&
		  n.value.u8 == UINT8_MAX);
	CHECK(ParseInteger("256", &n, 0) == 0 && n.width == 16);
	CHECK(ParseInteger("65535", &n, 0) == 0 && n.width == 16);
	CHECK(ParseInteger("65536", &n, 0) == 0 && n.width == 32);
	CHECK(ParseInteger("4294967295", &n, 0) == 0 && n.width == 32);
	CHECK(ParseInteger("4294967296", &n, 0) == 0 && n.width == 64);
	CHECK(ParseInteger("18446744073709551615", &n, 0) == 0 &&
		  n.value.u64 == UINT64_MAX);
	CHECK(ParseInteger("-1", &n, 0) != 0);
	CHECK(ParseInteger("", &n, 0) != 0);
	CHECK(ParseInteger("12z", &n, 0) != 0);
	CHECK(ParseInteger("18446744073709551616", &n, 0) != 0);
	CHECK(ParseInteger(NULL, &n, 0) != 0);
	CHECK(ParseInteger("1", NULL, 0) != 0);
	CHECK(ParseInteger("1", &n, -1) != 0);
}

static void test_float_parser(void) {
	Floating f;
	CHECK(ParseFloat("0", &f) == 0 && f.width == 32 && f.type == FLOAT_32 &&
		  f.value.f32 == 0.0f);
	CHECK(ParseFloat("-0", &f) == 0 && signbit(f.value.f32));
	CHECK(ParseFloat("1.25", &f) == 0 && f.value.f32 == 1.25f);
	CHECK(ParseFloat("-3.5e2", &f) == 0 && f.value.f32 == -350.0f);
	CHECK(ParseFloat("1e999", &f) != 0);
	CHECK(ParseFloat("1e-999", &f) != 0);
	CHECK(ParseFloat("nan", &f) != 0);
	CHECK(ParseFloat("inf", &f) != 0);
	CHECK(ParseFloat("1.2x", &f) != 0);
	CHECK(ParseFloat("", &f) != 0);
	CHECK(ParseFloat(NULL, &f) != 0);
	CHECK(ParseFloat("1", NULL) != 0);

	CHECK(ParseDouble("0", &f) == 0 && f.width == 64 && f.type == FLOAT_64);
	CHECK(ParseDouble("-0", &f) == 0 && signbit(f.value.f64));
	CHECK(ParseDouble("1.2345678901234567", &f) == 0);
	CHECK(ParseDouble("-2.5e100", &f) == 0);
	CHECK(ParseDouble("1e9999", &f) != 0);
	CHECK(ParseDouble("1e-9999", &f) != 0);
	CHECK(ParseDouble("nan", &f) != 0);
	CHECK(ParseDouble("-inf", &f) != 0);
	CHECK(ParseDouble("2.0x", &f) != 0);
	CHECK(ParseDouble("", &f) != 0);
	CHECK(ParseDouble(NULL, &f) != 0);
	CHECK(ParseDouble("1", NULL) != 0);
}

static void test_integer_helpers(void) {
	Integer n;
	CHECK(GetBits(NULL) == 0);
	CHECK(ParseInteger("-1", &n, 1) == 0 && GetBits(&n) == UINT8_MAX);
	CHECK(ParseInteger("256", &n, 0) == 0 && GetBits(&n) == 256);
	CHECK(ParseInteger("4294967296", &n, 0) == 0 &&
		  GetBits(&n) == UINT64_C(4294967296));
	CHECK(CountSetBits(0) == 0);
	CHECK(CountSetBits(1) == 1);
	CHECK(CountSetBits(UINT64_MAX) == 64);
	CHECK(CountSetBits(UINT64_C(0xF0F0)) == 8);
	CHECK(strcmp(IntegerTypeName(INT_8), "int8_t") == 0);
	CHECK(strcmp(IntegerTypeName(UINT_64), "uint64_t") == 0);
	CHECK(strcmp(IntegerTypeName((IntegerType)99), "unknown") == 0);
	CHECK(strcmp(FloatingTypeName(FLOAT_32), "float") == 0);
	CHECK(strcmp(FloatingTypeName(FLOAT_64), "double") == 0);
	CHECK(strcmp(FloatingTypeName((FloatingType)99), "unknown") == 0);
	CHECK(GetFloatingBits(NULL) == 0);
	Floating f;
	CHECK(ParseFloat("1.0", &f) == 0);
	CHECK(GetFloatingBits(&f) == UINT32_C(0x3F800000));
	CHECK(ParseDouble("-0", &f) == 0);
	CHECK(GetFloatingBits(&f) == UINT64_C(0x8000000000000000));
}

static void test_bitwise(void) {
	Integer a, b;
	CHECK(ParseInteger("12", &a, 1) == 0);
	CHECK(ParseInteger("10", &b, 1) == 0);
	CHECK(BitwiseBinary(OP_AND, &a, &b) == 0);
	CHECK(BitwiseBinary(OP_OR, &a, &b) == 0);
	CHECK(BitwiseBinary(OP_XOR, &a, &b) == 0);
	CHECK(BitwiseBinary((BitOp)99, &a, &b) != 0);
	CHECK(BitwiseBinary(
			  OP_AND, &a,
			  &(Integer){.width = 16, .isSigned = 1, .type = INT_16}) != 0);
	CHECK(ParseInteger("-1", &a, 1) == 0);
	CHECK(BitwiseNot(&a) == 0);
	CHECK(ParseInteger("1", &a, 1) == 0);
	CHECK(BitwiseShift(OP_SHL, &a, 0) == 0);
	CHECK(BitwiseShift(OP_SHL, &a, 1) == 0);
	CHECK(BitwiseShift(OP_SHR, &a, 0) == 0);
	CHECK(BitwiseShift(OP_SHR, &a, 1) == 0);
	CHECK(ParseInteger("-8", &a, 1) == 0);
	CHECK(BitwiseShift(OP_SHR, &a, 1) == 0);
	CHECK(BitwiseShift(OP_SHL, &a, 8) != 0);
	CHECK(BitwiseShift((BitOp)OP_AND, &a, 1) != 0);
	CHECK(ParseInteger("9223372036854775807", &a, 1) == 0);
	CHECK(BitwiseShift(OP_SHL, &a, 63) == 0);
}

static void test_bit_manipulation(void) {
	Integer a, v;
	CHECK(ParseInteger("0", &a, 0) == 0);
	CHECK(BitSingle(BM_SET, &a, 0) == 0);
	CHECK(BitSingle(BM_CLEAR, &a, 0) == 0);
	CHECK(BitSingle(BM_TOGGLE, &a, 7) == 0);
	CHECK(BitSingle(BM_TEST, &a, 7) == 0);
	CHECK(BitSingle(BM_TEST, &a, 0) == 0);
	CHECK(BitSingle((BitManipOp)99, &a, 0) != 0);
	CHECK(BitSingle(BM_SET, &a, 8) != 0);
	CHECK(BitSingle(BM_SET, NULL, 0) != 0);
	CHECK(BitExtract(&a, 0, 8) == 0);
	CHECK(BitExtract(&a, 7, 1) == 0);
	CHECK(BitExtract(&a, 0, 0) != 0);
	CHECK(BitExtract(&a, 0, 9) != 0);
	CHECK(BitExtract(&a, UINT_MAX, 1) != 0);
	CHECK(BitExtract(NULL, 0, 1) != 0);
	CHECK(ParseInteger("5", &v, 0) == 0);
	CHECK(BitInsert(&a, &v, 0, 3) == 0);
	CHECK(BitInsert(&a, &v, 6, 2) != 0);
	CHECK(BitInsert(&a, &v, 0, 0) != 0);
	CHECK(BitInsert(&a, &v, 0, 9) != 0);
	CHECK(BitInsert(&a, &v, UINT_MAX, UINT_MAX) != 0);
	CHECK(BitInsert(&a, NULL, 0, 1) != 0);
	Integer bad = {.width = 0};
	CHECK(BitSingle(BM_SET, &bad, 0) != 0);
	CHECK(BitExtract(&bad, 0, 1) != 0);
	CHECK(BitInsert(&a, &bad, 0, 1) != 0);
}

static void test_analysis(void) {
	Integer n;
	CHECK(ParseInteger("0", &n, 0) == 0);
	CHECK(BitPopcount(&n) == 0);
	CHECK(BitLeadingZeros(&n) == 0);
	CHECK(BitTrailingZeros(&n) == 0);
	CHECK(BitPowerOfTwo(&n) == 0);
	CHECK(ParseInteger("1", &n, 0) == 0);
	CHECK(BitPopcount(&n) == 0);
	CHECK(BitLeadingZeros(&n) == 0);
	CHECK(BitTrailingZeros(&n) == 0);
	CHECK(BitPowerOfTwo(&n) == 0);
	CHECK(ParseInteger("128", &n, 0) == 0);
	CHECK(BitPowerOfTwo(&n) == 0);
	CHECK(ParseInteger("3", &n, 0) == 0);
	CHECK(BitPowerOfTwo(&n) == 0);
	CHECK(ParseInteger("-128", &n, 1) == 0);
	CHECK(BitPowerOfTwo(&n) == 0);
	CHECK(ParseInteger("-1", &n, 1) == 0);
	CHECK(BitPowerOfTwo(&n) == 0);
	CHECK(BitPopcount(NULL) != 0);
	CHECK(BitLeadingZeros(NULL) != 0);
	CHECK(BitTrailingZeros(NULL) != 0);
	CHECK(BitPowerOfTwo(NULL) != 0);
}

static void test_memory(void) {
	Integer n;
	CHECK(ParseInteger("305419896", &n, 0) == 0); /* 0x12345678 */
	CHECK(MemoryInspection(&n) == 0);
	CHECK(ByteInspection(&n) == 0);
	CHECK(ByteSwap(&n) == 0);
	CHECK(ParseInteger("1", &n, 0) == 0);
	CHECK(ByteSwap(&n) == 0);
	CHECK(ParseInteger("1", &n, 1) == 0);
	CHECK(MemoryInspection(NULL) != 0);
	CHECK(ByteInspection(NULL) != 0);
	CHECK(ByteSwap(NULL) != 0);
	CHECK(EndianInspection() == 0);
}

static void test_float_inspection(void) {
	Floating f;
	CHECK(ParseFloat("1.5", &f) == 0);
	CHECK(FloatInspection(&f) == 0);
	CHECK(DoubleInspection(&f) != 0);
	CHECK(ParseDouble("-0", &f) == 0);
	CHECK(DoubleInspection(&f) == 0);
	CHECK(FloatInspection(&f) != 0);
	CHECK(FloatInspection(NULL) != 0);
	CHECK(DoubleInspection(NULL) != 0);
}

static void test_cli(void) {
	const char *a0[] = {"bitview"};
	const char *bad[] = {"bitview", "unknown"};
	const char *integer[] = {"bitview", "int", "-128"};
	const char *integer_u[] = {"bitview", "int", "--unsigned", "255"};
	const char *integer_width[] = {"bitview", "int", "--width", "16", "128"};
	const char *integer_width_eq[] = {"bitview", "int", "--width=8", "127"};
	const char *integer_width_bad[] = {"bitview", "int", "--width", "7", "1"};
	const char *integer_range_bad[] = {"bitview", "int", "--width=8", "128"};
	const char *integer_no_value[] = {"bitview", "int", "--signed"};
	const char *integer_extra[] = {"bitview", "int", "1", "2"};
	const char *integer_dup[] = {"bitview", "int", "--width=8", "--width=16",
								 "1"};
	const char *integer_conflict[] = {"bitview", "int", "--signed",
									  "--unsigned", "1"};
	const char *integer_unknown[] = {"bitview", "int", "--bad", "1"};
	const char *integer_bad_parse[] = {"bitview", "int", "1x"};
	const char *andv[] = {"bitview", "and", "3", "1"};
	const char *orv[] = {"bitview", "or", "3", "1"};
	const char *xorv[] = {"bitview", "xor", "3", "1"};
	const char *notv[] = {"bitview", "not", "3"};
	const char *shl[] = {"bitview", "shl", "3", "1"};
	const char *shr[] = {"bitview", "shr", "-8", "1"};
	const char *setv[] = {"bitview", "set", "0", "1"};
	const char *clearv[] = {"bitview", "clear", "3", "1"};
	const char *togglev[] = {"bitview", "toggle", "3", "1"};
	const char *testv[] = {"bitview", "test", "3", "1"};
	const char *extract[] = {"bitview", "extract", "255", "0", "4"};
	const char *insert[] = {"bitview", "insert", "0", "3", "0", "2"};
	const char *pop[] = {"bitview", "popcount", "3"};
	const char *lz[] = {"bitview", "leading-zeros", "1"};
	const char *tz[] = {"bitview", "trailing-zeros", "8"};
	const char *pow[] = {"bitview", "power-of-two", "8"};
	const char *memory[] = {"bitview", "memory", "1"};
	const char *bytes[] = {"bitview", "bytes", "1"};
	const char *swap[] = {"bitview", "byteswap", "1"};
	const char *endian[] = {"bitview", "endian"};
	const char *floatv[] = {"bitview", "float", "1.5"};
	const char *doublev[] = {"bitview", "double", "1.5"};
	const char *bad_arity[] = {"bitview", "and", "1"};
	const char *bad_not[] = {"bitview", "not"};
	const char *bad_shift[] = {"bitview", "shl", "1", "-1"};
	const char *bad_single[] = {"bitview", "set", "1", "8"};
	const char *bad_extract[] = {"bitview", "extract", "1", "0"};
	const char *bad_insert[] = {"bitview", "insert", "1", "2", "0"};
	const char *bad_analysis[] = {"bitview", "popcount"};
	const char *bad_memory[] = {"bitview", "memory"};
	const char *bad_endian[] = {"bitview", "endian", "1"};
	const char *bad_float[] = {"bitview", "float", "nan"};

#define RUN_OK(x) CHECK(cli((int)(sizeof(x) / sizeof((x)[0])), x) == 0)
#define RUN_FAIL(x) CHECK(cli((int)(sizeof(x) / sizeof((x)[0])), x) != 0)
	CHECK(cli(1, a0) != 0);
	CHECK(cli(2, bad) != 0);
	RUN_OK(integer);
	RUN_OK(integer_u);
	RUN_OK(integer_width);
	RUN_OK(integer_width_eq);
	RUN_FAIL(integer_width_bad);
	RUN_FAIL(integer_range_bad);
	RUN_FAIL(integer_no_value);
	RUN_FAIL(integer_extra);
	RUN_FAIL(integer_dup);
	RUN_FAIL(integer_conflict);
	RUN_FAIL(integer_unknown);
	RUN_FAIL(integer_bad_parse);
	RUN_OK(andv);
	RUN_OK(orv);
	RUN_OK(xorv);
	RUN_OK(notv);
	RUN_OK(shl);
	RUN_OK(shr);
	RUN_OK(setv);
	RUN_OK(clearv);
	RUN_OK(togglev);
	RUN_OK(testv);
	RUN_OK(extract);
	RUN_OK(insert);
	RUN_OK(pop);
	RUN_OK(lz);
	RUN_OK(tz);
	RUN_OK(pow);
	RUN_OK(memory);
	RUN_OK(bytes);
	RUN_OK(swap);
	RUN_OK(endian);
	RUN_OK(floatv);
	RUN_OK(doublev);
	RUN_FAIL(bad_arity);
	RUN_FAIL(bad_not);
	RUN_FAIL(bad_shift);
	RUN_FAIL(bad_single);
	RUN_FAIL(bad_extract);
	RUN_FAIL(bad_insert);
	RUN_FAIL(bad_analysis);
	RUN_FAIL(bad_memory);
	RUN_FAIL(bad_endian);
	RUN_FAIL(bad_float);
#undef RUN_OK
#undef RUN_FAIL
}

int main(void) {
	silence_output();
	test_integer_parser();
	test_float_parser();
	test_integer_helpers();
	test_bitwise();
	test_bit_manipulation();
	test_analysis();
	test_memory();
	test_float_inspection();
	test_cli();
	fflush(stderr);
	CHECK(dup2(saved_stderr, STDERR_FILENO) >= 0);
	close(saved_stderr);
	fprintf(stderr, "PASS: %u checks\n", checks);
	return EXIT_SUCCESS;
}
