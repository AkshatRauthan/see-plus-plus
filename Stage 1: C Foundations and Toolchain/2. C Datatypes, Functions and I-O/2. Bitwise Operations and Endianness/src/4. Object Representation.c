
#include <limits.h>
#include <stdio.h>

int main(void) {
	/*
	 * Object representation:
	 *
	 * Every object in C has an object representation consisting
	 * of sizeof(object) bytes.
	 *
	 * An object's representation can be inspected through
	 * a pointer to unsigned char.
	 *
	 * Note:
	 * Object representation may contain padding bits or bytes.
	 * Not every bit necessarily contributes to the value.
	 */

	unsigned int number = 0x12345678U;

	const unsigned char *bytes = (const unsigned char *)&number;

	printf("Object Representation\n");
	printf("---------------------\n");

	printf("Value: 0x%X\n", number);
	printf("Size: %zu byte(s)\n", sizeof(number));
	printf("Bits per byte: %d\n\n", CHAR_BIT);

	/*
	 * Display each byte in hexadecimal.
	 *
	 * The order in which bytes appear depends on the
	 * system's endianness.
	 */
	printf("Memory representation:\n");

	for (size_t i = 0; i < sizeof(number); i++) {
		printf("Byte %zu: 0x%02X\n", i, (unsigned int)bytes[i]);
	}

	return 0;
}
