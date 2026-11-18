
#include <stdio.h>

/*
 * Detect the host system's byte order.
 *
 * Inspecting an object's representation through
 * unsigned char is permitted by the C standard.
 */
int main(void) {
	unsigned int value = 0x12345678U;

	/* Access the individual bytes of the integer. */
	const unsigned char *bytes = (const unsigned char *)&value;

	printf("Endianness Detection\n");
	printf("--------------------\n");

	printf("Original value: 0x%X\n", value);

	printf("\nMemory representation:\n");

	for (size_t i = 0; i < sizeof(value); i++) {
		printf("Byte %zu: 0x%02X\n", i, (unsigned int)bytes[i]);
	}

	printf("\nHost byte order: ");

	if (bytes[0] == 0x78U) {
		printf("Little-endian\n");
	} else if (bytes[0] == 0x12U) {
		printf("Big-endian\n");
	} else {
		printf("Other or unrecognized byte order\n");
	}

	return 0;
}
