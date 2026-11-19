#include "../../include/commands.h"

#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

static int IsLittleEndian(void) {
	uint16_t probe = 1;
	unsigned char first;
	memcpy(&first, &probe, 1);
	return first == 1;
}

int IntegerInspection(Integer *number) {
	uint64_t bits = GetBits(number);
	unsigned width = number->width;

	printf("========== INTEGER INSPECTION ==========\n");

	printf("\n[ Integer Metadata ]\n");
	printf("%-12s: %s\n", "Input", number->input);
	printf("%-12s: %s\n", "Type", IntegerTypeName(number->type));
	printf("%-12s: %u bits\n", "Width", width);
	printf("%-12s: %u bytes\n", "Storage", width / 8);
	printf("%-12s: %s\n", "Signedness",
		   number->isSigned ? "Signed" : "Unsigned");

	printf("\n[ Numeric Representation ]\n");
	printf("%-12s: %s\n", "Decimal", number->input);
	printf("%-12s: 0x%0*" PRIX64 "\n", "Hexadecimal", (int)(width / 4), bits);
	printf("%-12s: %#" PRIo64 "\n", "Octal", bits);
	printf("%-12s: ", "Binary");
	for (int i = (int)width - 1; i >= 0; i--) {
		putchar(((bits >> i) & 1) ? '1' : '0');
		if (i % 8 == 0 && i != 0)
			putchar(' ');
	}
	putchar('\n');

	printf("\n[ Bit Analysis ]\n");
	unsigned set = CountSetBits(bits);
	printf("%-12s: %u\n", "Set Bits", set);
	printf("%-12s: %u\n", "Unset Bits", width - set);

	int msb = -1;
	int lsb = -1;
	for (unsigned i = 0; i < width; i++) {
		if ((bits >> i) & 1) {
			if (lsb < 0)
				lsb = (int)i; /* first set bit from the bottom */
			msb = (int)i;	  /* last set bit seen is the highest */
		}
	}
	if (msb < 0) {
		printf("%-12s: N/A\n", "MSB");
		printf("%-12s: N/A\n", "LSB");
	} else {
		printf("%-12s: %d\n", "MSB", msb);
		printf("%-12s: %d\n", "LSB", lsb);
	}

	int negative = number->isSigned && ((bits >> (width - 1)) & 1);
	int isPow2 = !negative && bits != 0 && (bits & (bits - 1)) == 0;
	printf("%-12s: %s\n", "Power of 2", isPow2 ? "Yes" : "No");

	printf("\n[ Memory Representation ]\n");
	int little = IsLittleEndian();
	unsigned nbytes = width / 8;
	printf("%-12s: %s\n", "Host", little ? "Little Endian" : "Big Endian");
	for (unsigned i = 0; i < nbytes; i++) {
		unsigned shift = 8 * (little ? i : nbytes - 1 - i);
		printf("Byte %-7u: 0x%02" PRIX64 "\n", i, (bits >> shift) & 0xFF);
	}

	printf("\n========================================\n");
	return 0;
}
