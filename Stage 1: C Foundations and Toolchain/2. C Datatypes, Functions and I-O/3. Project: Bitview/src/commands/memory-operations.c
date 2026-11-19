#include "../../include/commands.h"

#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

static void PrintHeader(const char *title) {
	printf("========== %s ==========\n\n", title);
}

static void PrintFooter(void) {
	printf("\n========================================\n");
}

static const char *GetHostEndian(void) {
	uint32_t value = UINT32_C(1);
	const unsigned char *bytes = (const unsigned char *)&value;

	return bytes[0] == 1 ? "Little Endian" : "Big Endian";
}

// Inspect the actual memory representation of an integer.
int MemoryInspection(const Integer *number) {
	if (number == NULL)
		return -1;

	const unsigned char *bytes = (const unsigned char *)&number->value;

	unsigned width = number->width;
	unsigned byteCount = width / 8;

	PrintHeader("MEMORY INSPECTION");

	printf("Type        : %s\n", IntegerTypeName(number->type));
	printf("Width       : %u bits\n", width);
	printf("Storage     : %u bytes\n", byteCount);
	printf("Host        : %s\n", GetHostEndian());

	printf("\n[ Memory Layout ]\n");

	for (unsigned i = 0; i < byteCount; i++) {
		printf("Byte %-5u   : 0x%02X\n", i, bytes[i]);
	}

	PrintFooter();
	return 0;
}

// Display individual bytes in host memory order.
int ByteInspection(const Integer *number) {
	if (number == NULL)
		return -1;

	const unsigned char *bytes = (const unsigned char *)&number->value;

	unsigned byteCount = number->width / 8;

	PrintHeader("BYTE INSPECTION");

	printf("Width       : %u bits\n", number->width);
	printf("Host        : %s\n", GetHostEndian());

	for (unsigned i = 0; i < byteCount; i++) {
		printf("Byte %-5u   : 0x%02X\n", i, bytes[i]);
	}

	PrintFooter();
	return 0;
}

// Reverse the byte order of an integer.
int ByteSwap(const Integer *number) {
	if (number == NULL)
		return -1;

	uint64_t bits = GetBits(number);
	unsigned byteCount = number->width / 8;

	uint64_t result = 0;

	for (unsigned i = 0; i < byteCount; i++) {
		uint64_t byte = (bits >> (i * 8)) & UINT64_C(0xFF);

		result |= byte << ((byteCount - 1 - i) * 8);
	}

	PrintHeader("BYTE SWAP");

	printf("Original    : 0x%0*" PRIX64 "\n", (int)(byteCount * 2), bits);

	printf("Byte Swapped: 0x%0*" PRIX64 "\n", (int)(byteCount * 2), result);

	printf("Decimal     : %" PRIu64 "\n", result);

	PrintFooter();
	return 0;
}

// Detect and display host byte order.
int EndianInspection(void) {
	uint32_t value = UINT32_C(0x01020304);
	const unsigned char *bytes = (const unsigned char *)&value;

	PrintHeader("ENDIANNESS DETECTION");

	printf("Host Byte Order : %s\n", GetHostEndian());

	printf("\nByte Layout:\n");

	for (unsigned i = 0; i < sizeof(value); i++) {
		printf("0x%02X ", bytes[i]);
	}

	putchar('\n');

	PrintFooter();
	return 0;
}
