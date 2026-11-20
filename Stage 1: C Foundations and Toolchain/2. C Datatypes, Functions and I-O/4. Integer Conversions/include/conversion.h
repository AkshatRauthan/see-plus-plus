
#ifndef CONVERSION_H
#define CONVERSION_H

#include <stddef.h>
#include <stdint.h>

/*
 * Integer-to-string conversion.
 *
 * Each function writes the formatted number into the supplied buffer.
 *
 * Returns:
 *   >= 0 : Number of characters written, excluding '\0'.
 *   -1   : Conversion error or insufficient buffer capacity.
 */
int format_i32(int32_t value, char *buffer, size_t capacity);
int format_u32(uint32_t value, char *buffer, size_t capacity);
int format_i64(int64_t value, char *buffer, size_t capacity);
int format_u64(uint64_t value, char *buffer, size_t capacity);

/*
 * Floating-point-to-string conversion.
 *
 * The formatting precision is selected to support round-trip conversion
 * for finite values of the corresponding floating-point type.
 */
int format_f32(float value, char *buffer, size_t capacity);
int format_f64(double value, char *buffer, size_t capacity);
int format_fld(long double value, char *buffer, size_t capacity);

/*
 * String-to-integer conversion.
 *
 * The base determines the number system:
 *   0       : Automatically detect the base from prefixes.
 *   2..36   : Explicit conversion base.
 *
 * Returns:
 *    0 : Successful conversion.
 *   -1 : Invalid input, overflow, or invalid arguments.
 *
 * The converted value is written through the result pointer.
 */
int parse_i32(const char *text, int base, int32_t *result);
int parse_u32(const char *text, int base, uint32_t *result);
int parse_i64(const char *text, int base, int64_t *result);
int parse_u64(const char *text, int base, uint64_t *result);

/*
 * String-to-floating-point conversion.
 *
 * Returns:
 *    0 : Successful conversion.
 *   -1 : Invalid input, range error, or invalid arguments.
 */
int parse_f32(const char *text, float *result);
int parse_f64(const char *text, double *result);
int parse_fld(const char *text, long double *result);

/*
 * Manually converts a signed 64-bit integer into a decimal string.
 *
 * This implementation handles INT64_MIN without signed overflow.
 *
 * Returns:
 *   >= 0 : Number of characters written, excluding '\0'.
 *   -1   : Error or insufficient buffer capacity.
 */
int manual_i64_to_string(int64_t value, char *buffer, size_t capacity);

#endif
