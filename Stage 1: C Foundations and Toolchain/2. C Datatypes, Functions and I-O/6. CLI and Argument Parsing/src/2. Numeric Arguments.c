
#include "../include/cli.h"

#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdlib.h>

/*
 * Converts a string into a signed 64-bit integer.
 *
 * endptr detects incomplete parsing.
 * errno detects range errors.
 *
 * The result is assigned only after all validation succeeds.
 */
int cli_parse_i64(const char *text, int base, int64_t *result) {
    if (text == NULL || result == NULL ||
        text[0] == '\0' || base < 0 || base == 1 || base > 36) {
        errno = EINVAL;
        return -1;
    }

    // Reset errno before conversion.
    errno = 0;

    char *endptr;

    intmax_t value = strtoimax(text, &endptr, base);

    // Detect overflow and underflow.
    if (errno == ERANGE) {
        return -1;
    }

    // Detect input that contains no valid number.
    if (endptr == text) {
        errno = EINVAL;
        return -1;
    }

    // Reject trailing characters and incomplete conversions.
    if (*endptr != '\0') {
        errno = EINVAL;
        return -1;
    }

    // Validate the destination type's range.
    if (value < INT64_MIN || value > INT64_MAX) {
        errno = ERANGE;
        return -1;
    }

    *result = (int64_t)value;

    return 0;
}

/*
 * Converts a string into an unsigned 64-bit integer.
 *
 * Negative input is rejected explicitly, even though
 * strtoumax() itself accepts a leading minus sign.
 */
int cli_parse_u64(const char *text, int base, uint64_t *result) {
    if (text == NULL || result == NULL ||
        text[0] == '\0' || text[0] == '-' ||
        base < 0 || base == 1 || base > 36) {
        errno = EINVAL;
        return -1;
    }

    errno = 0;

    char *endptr;

    uintmax_t value = strtoumax(text, &endptr, base);

    if (errno == ERANGE) {
        return -1;
    }

    if (endptr == text || *endptr != '\0') {
        errno = EINVAL;
        return -1;
    }

    if (value > UINT64_MAX) {
        errno = ERANGE;
        return -1;
    }

    *result = (uint64_t)value;

    return 0;
}
