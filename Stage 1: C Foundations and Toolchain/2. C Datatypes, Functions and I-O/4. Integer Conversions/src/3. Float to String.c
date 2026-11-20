
#include <errno.h>
#include <float.h>
#include <stdio.h>

#include "../include/conversion.h"

/*
 * Convert float into a decimal string.
 *
 * %.9g prints up to nine significant decimal digits.
 *
 * Nine significant digits are sufficient to distinguish every
 * binary32 float value when parsed back into a float.
 *
 * A float argument is promoted to double when passed through
 * a variadic function such as snprintf().
 */
int format_f32(float value, char *buffer, size_t capacity) {

    if (buffer == NULL || capacity == 0) {
        errno = EINVAL;
        return -1;
    }

    int written = snprintf(buffer, capacity, "%.9g", (double)value);

    if (written < 0) {
        return -1;
    }

    // Detect output truncation.
    if ((size_t)written >= capacity) {
        errno = ERANGE;
        return -1;
    }

    return written;
}

/*
 * Convert double into a decimal string.
 *
 * %.17g provides enough significant decimal digits to round-trip
 * every finite binary64 double value.
 *
 * The %g conversion automatically selects between fixed-point
 * and scientific notation depending on the value and precision.
 */
int format_f64(double value, char *buffer, size_t capacity) {

    if (buffer == NULL || capacity == 0) {
        errno = EINVAL;
        return -1;
    }

    int written = snprintf(buffer, capacity, "%.17g", value);

    if (written < 0) {
        return -1;
    }

    if ((size_t)written >= capacity) {
        errno = ERANGE;
        return -1;
    }

    return written;
}

/*
 * Convert long double into a decimal string.
 *
 * LDBL_DECIMAL_DIG specifies the number of decimal digits required
 * to distinguish long double values when converted to decimal text
 * and parsed back into long double.
 *
 * Its value depends on the implementation.
 */
int format_fld(long double value, char *buffer, size_t capacity) {

    if (buffer == NULL || capacity == 0) {
        errno = EINVAL;
        return -1;
    }

#ifdef LDBL_DECIMAL_DIG

    int written = snprintf(
        buffer,
        capacity,
        "%.*Lg",
        LDBL_DECIMAL_DIG,
        value
    );

#else

    // Fallback precision provided by the C implementation.
    int written = snprintf(
        buffer,
        capacity,
        "%.*Lg",
        DECIMAL_DIG,
        value
    );

#endif

    if (written < 0) {
        return -1;
    }

    if ((size_t)written >= capacity) {
        errno = ERANGE;
        return -1;
    }

    return written;
}
