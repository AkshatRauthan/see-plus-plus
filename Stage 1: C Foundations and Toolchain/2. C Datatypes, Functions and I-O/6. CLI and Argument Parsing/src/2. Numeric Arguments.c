
#include "../include/cli.h"

#include <ctype.h>
#include <errno.h>
#include <stdlib.h>

/*
 * Converts a string into a signed 64-bit integer.
 *
 * strtoll() performs the conversion.
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

    errno = 0;

    char *endptr;

    long long value = strtoll(text, &endptr, base);

    if (errno == ERANGE) {
        return -1;
    }

    if (endptr == text || *endptr != '\0') {
        errno = EINVAL;
        return -1;
    }

    // Ensure the value fits in int64_t.
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
 * Negative input is explicitly rejected, including input
 * containing leading whitespace before the minus sign.
 *
 * strtoull() itself accepts a leading minus sign, so this
 * validation must happen before conversion.
 */
int cli_parse_u64(const char *text, int base, uint64_t *result) {
    if (text == NULL || result == NULL ||
        text[0] == '\0' || base < 0 || base == 1 || base > 36) {
        errno = EINVAL;
        return -1;
    }

    // Reject negative values, including whitespace-prefixed input.
    const unsigned char *start = (const unsigned char *)text;

    while (isspace(*start)) {
        start++;
    }

    if (*start == '-') {
        errno = EINVAL;
        return -1;
    }

    errno = 0;

    char *endptr;

    unsigned long long value = strtoull(text, &endptr, base);

    if (errno == ERANGE) {
        return -1;
    }

    if (endptr == text || *endptr != '\0') {
        errno = EINVAL;
        return -1;
    }

    // Ensure the value fits in uint64_t.
    if (value > UINT64_MAX) {
        errno = ERANGE;
        return -1;
    }

    *result = (uint64_t)value;

    return 0;
}
