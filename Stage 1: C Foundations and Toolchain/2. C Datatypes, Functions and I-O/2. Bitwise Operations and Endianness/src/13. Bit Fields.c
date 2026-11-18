
#include <stdio.h>

/*
 * Bit-field structure:
 *
 * Each member specifies its width in bits.
 *
 * unsigned int state : 1;  -> 1-bit field
 * unsigned int mode  : 2;  -> 2-bit field
 * unsigned int flags : 4;  -> 4-bit field
 *
 * Bit-field allocation and ordering are implementation-defined.
 */
struct Status {
	unsigned int state : 1;
	unsigned int mode : 2;
	unsigned int flags : 4;
};

int main(void) {
	struct Status status = {0};

	printf("C Bit Fields\n");
	printf("------------\n");

	/* Assign values to individual bit fields. */
	status.state = 1;
	status.mode = 2;
	status.flags = 10;

	printf("State: %u\n", status.state);
	printf("Mode:  %u\n", status.mode);
	printf("Flags: %u\n\n", status.flags);

	/*
	 * Bit fields have limited ranges.
	 *
	 * A 1-bit unsigned field can represent 0 to 1.
	 * A 2-bit unsigned field can represent 0 to 3.
	 * A 4-bit unsigned field can represent 0 to 15.
	 */

	printf("Maximum representable values:\n");
	printf("State (1 bit): 1\n");
	printf("Mode  (2 bits): 3\n");
	printf("Flags (4 bits): 15\n\n");

	/*
	 * sizeof can be applied to the complete structure,
	 * but not to an individual bit-field member.
	 */
	printf("Structure size: %zu byte(s)\n", sizeof(status));

	return 0;
}
