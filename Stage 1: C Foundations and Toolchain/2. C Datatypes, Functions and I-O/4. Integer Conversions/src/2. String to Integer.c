
#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdlib.h>

#include "../include/conversion.h"

/*
 * Validate the input string and conversion base.
 *
 * strtoimax() and strtoumax() accept leading whitespace,
 * so we skip it when checking whether the input contains anything.
 *
 * The actual conversion functions will handle the whitespace themselves.
 */
static int ValidIntegerText(const char *text, int base) {

	// Reject null input and unsupported conversion bases.
	if (text == NULL || (base != 0 && (base < 2 || base > 36))) {
		return 0;
	}

	// Skip leading whitespace.
	while (isspace((unsigned char)*text)) {
		++text;
	}

	// Reject empty or whitespace-only strings.
	return *text != '\0';
}

/*
 * Check whether the conversion stopped before the end of the string.
 *
 * endptr points to the first character that was not converted.
 *
 * We require the entire string to represent the number.
 */
static int HasTrailingCharacters(const char *end) {
	return end == NULL || *end != '\0';
}

/*
 * Convert a string into a signed 64-bit integer.
 *
 * strtoimax() converts a string into intmax_t, the widest standard
 * signed integer type provided by the implementation.
 *
 * We subsequently verify that the result fits inside int64_t.
 */
int parse_i64(const char *text, int base, int64_t *result) {

	// Validate arguments.
	if (result == NULL || !ValidIntegerText(text, base)) {
		errno = EINVAL;
		return -1;
	}

	/*
	 * Reset errno before conversion.
	 *
	 * Conversion functions do not necessarily clear errno on success.
	 * Resetting it allows us to identify a range error from this call.
	 */
	errno = 0;

	// end will point to the first unconverted character.
	char *end = NULL;

	// Convert the string into the widest signed integer type.
	intmax_t value = strtoimax(text, &end, base);

	// Detect integer overflow or underflow.
	if (errno == ERANGE) {
		return -1;
	}

	// Reject strings containing no valid number or trailing characters.
	if (end == text || HasTrailingCharacters(end)) {
		errno = EINVAL;
		return -1;
	}

	// Ensure the result fits inside int64_t.
	if (value < INT64_MIN || value > INT64_MAX) {
		errno = ERANGE;
		return -1;
	}

	// Store the validated result.
	*result = (int64_t)value;

	return 0;
}

/*
 * Convert a string into an unsigned 64-bit integer.
 *
 * strtoumax() converts a string into uintmax_t.
 *
 * Note that strtoumax() accepts a leading minus sign and applies
 * unsigned arithmetic. This implementation deliberately rejects
 * negative input for unsigned destination types.
 */
int parse_u64(const char *text, int base, uint64_t *result) {

	// Validate arguments.
	if (result == NULL || !ValidIntegerText(text, base)) {
		errno = EINVAL;
		return -1;
	}

	// Find the first non-whitespace character.
	const char *first = text;

	while (isspace((unsigned char)*first)) {
		++first;
	}

	// Reject negative input for unsigned integer types.
	if (*first == '-') {
		errno = EINVAL;
		return -1;
	}

	// Reset errno before conversion.
	errno = 0;

	char *end = NULL;

	// Convert the string into the widest unsigned integer type.
	uintmax_t value = strtoumax(text, &end, base);

	// Detect overflow.
	if (errno == ERANGE) {
		return -1;
	}

	// Reject invalid or partially converted strings.
	if (end == text || HasTrailingCharacters(end)) {
		errno = EINVAL;
		return -1;
	}

	// Ensure the result fits inside uint64_t.
	if (value > UINT64_MAX) {
		errno = ERANGE;
		return -1;
	}

	// Store the validated result.
	*result = (uint64_t)value;

	return 0;
}

/*
 * Convert a string into a signed 32-bit integer.
 *
 * Reuse parse_i64() instead of duplicating the parsing algorithm.
 *
 * This separates:
 *   1. Parsing the textual representation.
 *   2. Checking whether the result fits the requested type.
 */
int parse_i32(const char *text, int base, int32_t *result) {

	if (result == NULL) {
		errno = EINVAL;
		return -1;
	}

	int64_t value;

	// First parse the string as a signed 64-bit integer.
	if (parse_i64(text, base, &value) != 0) {
		return -1;
	}

	// Verify the value is within the int32_t range.
	if (value < INT32_MIN || value > INT32_MAX) {
		errno = ERANGE;
		return -1;
	}

	// Narrow only after verifying the range.
	*result = (int32_t)value;

	return 0;
}

/*
 * Convert a string into an unsigned 32-bit integer.
 *
 * Parse using the wider uint64_t type before checking the
 * destination type's limits.
 */
int parse_u32(const char *text, int base, uint32_t *result) {

	if (result == NULL) {
		errno = EINVAL;
		return -1;
	}

	uint64_t value;

	// Parse the string as an unsigned 64-bit integer.
	if (parse_u64(text, base, &value) != 0) {
		return -1;
	}

	// Verify the value is within the uint32_t range.
	if (value > UINT32_MAX) {
		errno = ERANGE;
		return -1;
	}

	// Narrow only after verifying the range.
	*result = (uint32_t)value;

	return 0;
}
