
#include <ctype.h>
#include <errno.h>
#include <stdlib.h>

#include "../include/conversion.h"

/*
 * Validate the floating-point input.
 *
 * The standard strto* functions accept leading whitespace.
 * We reject null, empty, and whitespace-only strings.
 */
static int ValidFloatText(const char *text) {

    if (text == NULL) {
        return 0;
    }

    // Skip leading whitespace.
    while (isspace((unsigned char)*text)) {
        ++text;
    }

    return *text != '\0';
}

/*
 * Ensure that the entire input string was consumed.
 *
 * end points to the first character that was not part of the number.
 *
 * For example:
 *
 *   "12.5"    -> valid
 *   "12.5abc" -> invalid
 *
 * This implementation rejects trailing whitespace as well.
 */
static int CompleteFloatParse(const char *text, char *end) {
    return end != text && end != NULL && *end == '\0';
}

/*
 * Convert a string into float.
 *
 * strtof() parses a floating-point string and returns a float.
 *
 * It also supports:
 *   - Decimal notation
 *   - Scientific notation
 *   - Hexadecimal floating-point notation
 *   - Infinity
 *   - NaN
 *
 * errno is checked for range errors.
 */
int parse_f32(const char *text, float *result) {

    if (result == NULL || !ValidFloatText(text)) {
        errno = EINVAL;
        return -1;
    }

    // Reset errno before parsing.
    errno = 0;

    char *end = NULL;

    // Convert the string into a float.
    float value = strtof(text, &end);

    // Detect overflow or underflow.
    if (errno == ERANGE) {
        return -1;
    }

    // Reject invalid or partially converted input.
    if (!CompleteFloatParse(text, end)) {
        errno = EINVAL;
        return -1;
    }

    // Store the converted value.
    *result = value;

    return 0;
}

/*
 * Convert a string into double.
 *
 * strtod() performs the same general conversion as strtof(),
 * but returns a double value.
 */
int parse_f64(const char *text, double *result) {

    if (result == NULL || !ValidFloatText(text)) {
        errno = EINVAL;
        return -1;
    }

    errno = 0;

    char *end = NULL;

    // Convert the string into a double.
    double value = strtod(text, &end);

    if (errno == ERANGE) {
        return -1;
    }

    if (!CompleteFloatParse(text, end)) {
        errno = EINVAL;
        return -1;
    }

    *result = value;

    return 0;
}

/*
 * Convert a string into long double.
 *
 * strtold() provides the widest standard floating-point conversion
 * interface available through the strto* family.
 *
 * The actual precision of long double is implementation-dependent.
 */
int parse_fld(const char *text, long double *result) {

    if (result == NULL || !ValidFloatText(text)) {
        errno = EINVAL;
        return -1;
    }

    errno = 0;

    char *end = NULL;

    // Convert the string into a long double.
    long double value = strtold(text, &end);

    if (errno == ERANGE) {
        return -1;
    }

    if (!CompleteFloatParse(text, end)) {
        errno = EINVAL;
        return -1;
    }

    *result = value;

    return 0;
}
