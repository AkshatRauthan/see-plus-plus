#include <limits.h>
#include <stdio.h>

int main(void) {
	printf("Fundamental Integer Types\n");
	printf("=========================\n\n");

	/*
	 * char
	 * Size: 1 byte
	 * Range: -128 to 127 (assuming signed char behaviour)
	 *
	 * NOTE: Plain char can be either signed or unsigned,
	 * depending on the implementation.
	 */
	printf("char:\n");
	printf("  Size:      %zu bytes\n", sizeof(char));
	printf("  Min:       %d\n", CHAR_MIN);
	printf("  Max:       %d\n\n", CHAR_MAX);

	/*
	 * signed char
	 * Size: 1 byte
	 * Range: -128 to 127
	 *
	 * Uses one bit for the sign and seven bits for the value
	 * on systems using the conventional 8-bit representation.
	 */
	printf("signed char:\n");
	printf("  Size:      %zu bytes\n", sizeof(signed char));
	printf("  Min:       %d\n", SCHAR_MIN);
	printf("  Max:       %d\n\n", SCHAR_MAX);

	/*
	 * unsigned char
	 * Size: 1 byte
	 * Range: 0 to 255
	 *
	 * All 8 bits are used for the value.
	 */
	printf("unsigned char:\n");
	printf("  Size:      %zu bytes\n", sizeof(unsigned char));
	printf("  Min:       0\n");
	printf("  Max:       %u\n\n", UCHAR_MAX);

	/*
	 * short
	 * Size: 2 bytes
	 * Range: -32768 to 32767
	 */
	printf("short:\n");
	printf("  Size:      %zu bytes\n", sizeof(short));
	printf("  Min:       %d\n", SHRT_MIN);
	printf("  Max:       %d\n\n", SHRT_MAX);

	/*
	 * unsigned short
	 * Size: 2 bytes
	 * Range: 0 to 65535
	 */
	printf("unsigned short:\n");
	printf("  Size:      %zu bytes\n", sizeof(unsigned short));
	printf("  Min:       0\n");
	printf("  Max:       %u\n\n", USHRT_MAX);

	/*
	 * int
	 * Size: 4 bytes
	 * Range: -2147483648 to 2147483647
	 */
	printf("int:\n");
	printf("  Size:      %zu bytes\n", sizeof(int));
	printf("  Min:       %d\n", INT_MIN);
	printf("  Max:       %d\n\n", INT_MAX);

	/*
	 * unsigned int
	 * Size: 4 bytes
	 * Range: 0 to 4294967295
	 */
	printf("unsigned int:\n");
	printf("  Size:      %zu bytes\n", sizeof(unsigned int));
	printf("  Min:       0\n");
	printf("  Max:       %u\n\n", UINT_MAX);

	/*
	 * long
	 * Size: 8 bytes
	 * Range: -9223372036854775808 to 9223372036854775807
	 *
	 * On Linux x86-64 (LP64), long is 64 bits.
	 */
	printf("long:\n");
	printf("  Size:      %zu bytes\n", sizeof(long));
	printf("  Min:       %ld\n", LONG_MIN);
	printf("  Max:       %ld\n\n", LONG_MAX);

	/*
	 * unsigned long
	 * Size: 8 bytes
	 * Range: 0 to 18446744073709551615
	 */
	printf("unsigned long:\n");
	printf("  Size:      %zu bytes\n", sizeof(unsigned long));
	printf("  Min:       0\n");
	printf("  Max:       %lu\n\n", ULONG_MAX);

	/*
	 * long long
	 * Size: 8 bytes
	 * Range: -9223372036854775808 to 9223372036854775807
	 *
	 * Guaranteed to have at least 64 bits of precision.
	 */
	printf("long long:\n");
	printf("  Size:      %zu bytes\n", sizeof(long long));
	printf("  Min:       %lld\n", LLONG_MIN);
	printf("  Max:       %lld\n\n", LLONG_MAX);

	/*
	 * unsigned long long
	 * Size: 8 bytes
	 * Range: 0 to 18446744073709551615
	 */
	printf("unsigned long long:\n");
	printf("  Size:      %zu bytes\n", sizeof(unsigned long long));
	printf("  Min:       0\n");
	printf("  Max:       %llu\n", ULLONG_MAX);

	return 0;
}
