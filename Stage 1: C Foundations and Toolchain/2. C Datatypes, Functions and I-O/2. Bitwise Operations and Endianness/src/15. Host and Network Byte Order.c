
#include <arpa/inet.h>
#include <stdint.h>
#include <stdio.h>

/* Print the bytes of an object in memory order. */
void printBytes(const void *object, size_t size) {
	const unsigned char *bytes = object;

	for (size_t i = 0; i < size; i++) {
		printf("%02X ", (unsigned int)bytes[i]);
	}

	printf("\n");
}

int main(void) {
	uint16_t host16 = 0x1234U;
	uint32_t host32 = 0x12345678U;

	/* Convert host byte order to network byte order. */
	uint16_t network16 = htons(host16);
	uint32_t network32 = htonl(host32);

	/* Convert network byte order back to host byte order. */
	uint16_t restored16 = ntohs(network16);
	uint32_t restored32 = ntohl(network32);

	printf("Host and Network Byte Order\n");
	printf("---------------------------\n");

	printf("Original 16-bit value: 0x%04X\n", host16);
	printf("Network 16-bit value:  0x%04X\n", network16);
	printf("Restored 16-bit value: 0x%04X\n", restored16);

	printf("\nOriginal 32-bit value: 0x%08X\n", host32);
	printf("Network 32-bit value:  0x%08X\n", network32);
	printf("Restored 32-bit value: 0x%08X\n", restored32);

	printf("\nNetwork 16-bit bytes: ");
	printBytes(&network16, sizeof(network16));

	printf("Network 32-bit bytes: ");
	printBytes(&network32, sizeof(network32));

	return 0;
}
