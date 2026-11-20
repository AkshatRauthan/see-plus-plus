#include <assert.h>
#include <errno.h>
#include <inttypes.h>
#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "../include/conversion.h"

/*
 * Test integer-to-string conversions.
 *
 * Boundary values are particularly important because they expose
 * incorrect handling of signed limits and unsigned ranges.
 */
static void TestIntegerFormatting(void) {

	char buffer[128];

	// Signed 32-bit minimum.
	assert(format_i32(INT32_MIN, buffer, sizeof buffer) > 0);
	assert(strcmp(buffer, "-2147483648") == 0);

	// Unsigned 32-bit maximum.
	assert(format_u32(UINT32_MAX, buffer, sizeof buffer) > 0);
	assert(strcmp(buffer, "4294967295") == 0);

	// Signed 64-bit minimum.
	assert(format_i64(INT64_MIN, buffer, sizeof buffer) > 0);
	assert(strcmp(buffer, "-9223372036854775808") == 0);

	// Unsigned 64-bit maximum.
	assert(format_u64(UINT64_MAX, buffer, sizeof buffer) > 0);
	assert(strcmp(buffer, "18446744073709551615") == 0);

	// Verify the manual conversion of INT64_MIN.
	assert(manual_i64_to_string(INT64_MIN, buffer, sizeof buffer) > 0);
	assert(strcmp(buffer, "-9223372036854775808") == 0);

	// Zero must produce the string "0".
	assert(manual_i64_to_string(0, buffer, sizeof buffer) == 1);
	assert(strcmp(buffer, "0") == 0);
}

/*
 * Test string-to-integer conversions.
 *
 * These tests verify successful parsing, automatic base detection,
 * invalid input handling, and destination-type range checks.
 */
static void TestIntegerParsing(void) {

	int32_t i32 = 0;
	uint32_t u32 = 0;
	int64_t i64 = 0;
	uint64_t u64 = 0;

	// Parse the minimum signed 32-bit value.
	assert(parse_i32("-2147483648", 10, &i32) == 0);
	assert(i32 == INT32_MIN);

	// Parse the maximum unsigned 32-bit value.
	assert(parse_u32("4294967295", 10, &u32) == 0);
	assert(u32 == UINT32_MAX);

	// Parse the minimum signed 64-bit value.
	assert(parse_i64("-9223372036854775808", 10, &i64) == 0);
	assert(i64 == INT64_MIN);

	// Parse the maximum unsigned 64-bit value.
	assert(parse_u64("18446744073709551615", 10, &u64) == 0);
	assert(u64 == UINT64_MAX);

	/*
	 * Base 0 enables automatic base detection.
	 *
	 * The 0x prefix identifies hexadecimal input.
	 */
	assert(parse_i32("0x7f", 0, &i32) == 0);
	assert(i32 == 127);

	// Reject characters that are not part of the integer.
	assert(parse_i32("12abc", 10, &i32) == -1);

	// Reject empty input.
	assert(parse_i32("", 10, &i32) == -1);

	// Reject values outside the int32_t range.
	assert(parse_i32("2147483648", 10, &i32) == -1);
	assert(errno == ERANGE);

	// Reject negative input for an unsigned destination.
	assert(parse_u32("-1", 10, &u32) == -1);

	// Reject values outside the uint32_t range.
	assert(parse_u32("4294967296", 10, &u32) == -1);
	assert(errno == ERANGE);
}

/*
 * Test floating-point conversions in both directions.
 *
 * We format each value into a string and parse it back.
 * Equality is appropriate here because the formatting precision
 * is selected to support round-trip conversion.
 */
static void TestFloatConversion(void) {

	char buffer[128];

	float f = 0.0f;
	double d = 0.0;
	long double ld = 0.0L;

	// float round trip.
	assert(format_f32(0.1f, buffer, sizeof buffer) > 0);
	assert(parse_f32(buffer, &f) == 0);
	assert(f == 0.1f);

	// double round trip.
	assert(format_f64(0.1, buffer, sizeof buffer) > 0);
	assert(parse_f64(buffer, &d) == 0);
	assert(d == 0.1);

	// long double round trip.
	assert(format_fld(0.1L, buffer, sizeof buffer) > 0);
	assert(parse_fld(buffer, &ld) == 0);
	assert(ld == 0.1L);

	// Test ordinary decimal input.
	assert(parse_f64("12.5", &d) == 0);
	assert(d == 12.5);

	// Reject trailing invalid characters.
	assert(parse_f64("12.5xyz", &d) == -1);

	// Reject empty input.
	assert(parse_f64("", &d) == -1);
}

int main(void) {

	TestIntegerFormatting();
	TestIntegerParsing();
	TestFloatConversion();

	puts("All conversion tests passed.");

	return 0;
}
