#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>

/*
 * Exact-width integer types
 *
 * These types provide integers with exactly the specified
 * number of bits, without padding bits.
 *
 * They are optional: an implementation only provides them
 * if it supports the corresponding width and representation.
 */

int main(void) {
	printf("Fixed-Width Integer Types\n");
	printf("=========================\n\n");

	/*
	 * 8-bit integers
	 *
	 * int8_t:
	 *   Range: -128 to 127
	 *
	 * uint8_t:
	 *   Range: 0 to 255
	 */
	printf("8-bit integers:\n");
	printf("  int8_t:\n");
	printf("    Size: %zu bytes\n", sizeof(int8_t));
	printf("    Min:  %" PRId8 "\n", INT8_MIN);
	printf("    Max:  %" PRId8 "\n", INT8_MAX);

	printf("  uint8_t:\n");
	printf("    Size: %zu bytes\n", sizeof(uint8_t));
	printf("    Min:  0\n");
	printf("    Max:  %" PRIu8 "\n\n", UINT8_MAX);

	/*
	 * 16-bit integers
	 *
	 * int16_t:
	 *   Range: -32768 to 32767
	 *
	 * uint16_t:
	 *   Range: 0 to 65535
	 */
	printf("16-bit integers:\n");
	printf("  int16_t:\n");
	printf("    Size: %zu bytes\n", sizeof(int16_t));
	printf("    Min:  %" PRId16 "\n", INT16_MIN);
	printf("    Max:  %" PRId16 "\n", INT16_MAX);

	printf("  uint16_t:\n");
	printf("    Size: %zu bytes\n", sizeof(uint16_t));
	printf("    Min:  0\n");
	printf("    Max:  %" PRIu16 "\n\n", UINT16_MAX);

	/*
	 * 32-bit integers
	 *
	 * int32_t:
	 *   Range: -2147483648 to 2147483647
	 *
	 * uint32_t:
	 *   Range: 0 to 4294967295
	 */
	printf("32-bit integers:\n");
	printf("  int32_t:\n");
	printf("    Size: %zu bytes\n", sizeof(int32_t));
	printf("    Min:  %" PRId32 "\n", INT32_MIN);
	printf("    Max:  %" PRId32 "\n", INT32_MAX);

	printf("  uint32_t:\n");
	printf("    Size: %zu bytes\n", sizeof(uint32_t));
	printf("    Min:  0\n");
	printf("    Max:  %" PRIu32 "\n\n", UINT32_MAX);

	/*
	 * 64-bit integers
	 *
	 * int64_t:
	 *   Range: -9223372036854775808 to 9223372036854775807
	 *
	 * uint64_t:
	 *   Range: 0 to 18446744073709551615
	 */
	printf("64-bit integers:\n");
	printf("  int64_t:\n");
	printf("    Size: %zu bytes\n", sizeof(int64_t));
	printf("    Min:  %" PRId64 "\n", INT64_MIN);
	printf("    Max:  %" PRId64 "\n", INT64_MAX);

	printf("  uint64_t:\n");
	printf("    Size: %zu bytes\n", sizeof(uint64_t));
	printf("    Min:  0\n");
	printf("    Max:  %" PRIu64 "\n\n", UINT64_MAX);

	/*
	 * Minimum-width integer types
	 *
	 * These guarantee at least the requested number of bits.
	 * The implementation chooses the smallest available integer type that
	 * satisfies the requirement.
	 */
	printf("Minimum-width integer types:\n");
	printf("  int_least8_t:  %zu bytes\n", sizeof(int_least8_t));
	printf("  int_least16_t: %zu bytes\n", sizeof(int_least16_t));
	printf("  int_least32_t: %zu bytes\n", sizeof(int_least32_t));
	printf("  int_least64_t: %zu bytes\n\n", sizeof(int_least64_t));

	/*
	 * Fastest-width integer types
	 *
	 * These provide integer types with at least the requested
	 * width, selected by the implementation for fast operations.
	 * Provides a type with at least N bits, selected by the implementation to
	 * provide efficient operations.
	 */
	printf("Fast-width integer types:\n");
	printf("  int_fast8_t:  %zu bytes\n", sizeof(int_fast8_t));
	printf("  int_fast16_t: %zu bytes\n", sizeof(int_fast16_t));
	printf("  int_fast32_t: %zu bytes\n", sizeof(int_fast32_t));
	printf("  int_fast64_t: %zu bytes\n\n", sizeof(int_fast64_t));

	/*
	 * Pointer-sized integer types
	 *
	 * intptr_t:
	 *   Signed integer type capable of holding a converted void pointer.
	 *
	 * uintptr_t:
	 *   Unsigned integer type capable of holding a converted void pointer.
	 *
	 * Both types are optional.
	 */
	printf("Pointer-sized integer types:\n");
	printf("  intptr_t:  %zu bytes\n", sizeof(intptr_t));
	printf("  uintptr_t: %zu bytes\n", sizeof(uintptr_t));

	/*
	 * Diff B/w Least and Fast variables:
	 *
	 * int_leastN_t: chooses the smallest available type that satisfies the minimum width.
	 * int_fastN_t: chooses a type intended to provide efficient operations.
	 */
	return 0;
}
