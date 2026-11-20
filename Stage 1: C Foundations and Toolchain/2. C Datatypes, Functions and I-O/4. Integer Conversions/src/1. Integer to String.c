
#include <errno.h>
#include <inttypes.h>
#include <limits.h>
#include <stdarg.h>
#include <stdio.h>

#include "../include/conversion.h"

/*
 * Shared formatting helper.
 *
 * vsnprintf() is the variable-argument version of snprintf().
 *
 * It writes formatted output into a destination buffer while respecting
 * its capacity, preventing writes beyond the buffer's boundaries.
 *
 * Return value:
 *   >= 0 : Number of characters that would have been written.
 *   -1   : Formatting error.
 *
 * If the returned count is greater than or equal to the capacity,
 * the destination buffer was too small and the output was truncated.
 */
static int CheckedSnprintf(char *buffer, size_t capacity,
                           const char *format, ...) {

    // Validate the destination buffer and format string.
    if (buffer == NULL || capacity == 0 || format == NULL) {
        errno = EINVAL;
        return -1;
    }

    // Initialize the variable argument list.
    va_list args;
    va_start(args, format);

    // Perform the formatted output.
    int written = vsnprintf(buffer, capacity, format, args);

    // Release resources associated with the variable argument list.
    va_end(args);

    // A negative return value indicates a formatting error.
    if (written < 0) {
        return -1;
    }

    // Check whether the destination buffer was large enough.
    if ((size_t)written >= capacity) {
        errno = ERANGE;
        return -1;
    }

    return written;
}

/*
 * Convert int32_t into a decimal string.
 *
 * PRId32 is a portable format specifier for int32_t.
 *
 * We use it instead of assuming that int32_t is always represented
 * by the int type.
 */
int format_i32(int32_t value, char *buffer, size_t capacity) {
    return CheckedSnprintf(buffer, capacity, "%" PRId32, value);
}

/*
 * Convert uint32_t into a decimal string.
 *
 * PRIu32 is the corresponding unsigned integer format specifier.
 */
int format_u32(uint32_t value, char *buffer, size_t capacity) {
    return CheckedSnprintf(buffer, capacity, "%" PRIu32, value);
}

/*
 * Convert int64_t into a decimal string.
 *
 * PRId64 ensures that the correct format specifier is used
 * regardless of the underlying integer type.
 */
int format_i64(int64_t value, char *buffer, size_t capacity) {
    return CheckedSnprintf(buffer, capacity, "%" PRId64, value);
}

/*
 * Convert uint64_t into a decimal string.
 */
int format_u64(uint64_t value, char *buffer, size_t capacity) {
    return CheckedSnprintf(buffer, capacity, "%" PRIu64, value);
}

/*
 * Manually convert a signed 64-bit integer into a decimal string.
 *
 * Algorithm:
 *
 *   1. Extract the last digit using modulo 10.
 *   2. Convert the digit into its character representation.
 *   3. Remove the last digit using division by 10.
 *   4. Repeat until the number becomes zero.
 *   5. Reverse the extracted digits.
 *
 * Example:
 *
 *   Input: 1234
 *
 *   Extracted digits:
 *       4 -> 3 -> 2 -> 1
 *
 *   Reversed result:
 *       1234
 *
 * Special consideration:
 *
 *   INT64_MIN cannot be directly negated because its positive
 *   counterpart is outside the range of int64_t.
 *
 *   We therefore calculate its magnitude using uint64_t arithmetic.
 */
int manual_i64_to_string(int64_t value, char *buffer, size_t capacity) {

    // Validate the destination buffer.
    if (buffer == NULL || capacity == 0) {
        errno = EINVAL;
        return -1;
    }

    /*
     * Temporary storage for digits in reverse order.
     *
     * The maximum number of decimal digits in an int64_t value
     * is smaller than its number of binary bits.
     */
    char reversed[sizeof(int64_t) * CHAR_BIT + 1];

    size_t length = 0;

    // Store the absolute magnitude using an unsigned integer.
    uint64_t magnitude;

    if (value < 0) {

        /*
         * Avoid directly calculating -value.
         *
         * For INT64_MIN, that operation would overflow.
         *
         * Instead:
         *
         *   -(value + 1)
         *
         * is representable as int64_t.
         *
         * We then convert it to uint64_t and add one.
         */
        magnitude = (uint64_t)(-(value + 1)) + UINT64_C(1);

    } else {

        // Positive values can be converted directly.
        magnitude = (uint64_t)value;
    }

    /*
     * Extract decimal digits.
     *
     * The do-while loop is important because zero has one digit: "0".
     * A regular while loop would skip conversion when magnitude is zero.
     */
    do {

        // Obtain the final decimal digit.
        unsigned digit = (unsigned)(magnitude % UINT64_C(10));

        // Convert the numeric digit into its character representation.
        reversed[length++] = (char)('0' + digit);

        // Remove the final decimal digit.
        magnitude /= UINT64_C(10);

    } while (magnitude != 0);

    /*
     * Calculate the required buffer capacity:
     *
     *   Number of digits
     * + Optional minus sign
     * + Null terminator
     */
    size_t required = length + (value < 0 ? 1U : 0U) + 1U;

    if (capacity < required) {
        errno = ERANGE;
        return -1;
    }

    size_t output = 0;

    // Write the negative sign before the digits.
    if (value < 0) {
        buffer[output++] = '-';
    }

    /*
     * Copy the extracted digits in reverse order.
     *
     * Decrement length before accessing the array so that
     * the digits are written from most significant to least significant.
     */
    while (length > 0) {
        buffer[output++] = reversed[--length];
    }

    // Terminate the resulting C string.
    buffer[output] = '\0';

    // Return the number of characters, excluding '\0'.
    return (int)output;
}
