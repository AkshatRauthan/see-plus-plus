
#include <limits.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

/* Count the number of set bits (1s) in an integer. */
unsigned int countSetBits(uint32_t value) {
    unsigned int count = 0;

    while (value != 0) {
        count += value & 1U;
        value >>= 1;
    }

    return count;
}

/* Check whether an integer is a power of two. */
bool isPowerOfTwo(uint32_t value) {
    return value != 0 && (value & (value - 1U)) == 0;
}

/* Reverse the byte order of a 32-bit integer. */
uint32_t byteSwap(uint32_t value) {
    return ((value & 0x000000FFU) << 24) |
           ((value & 0x0000FF00U) << 8)  |
           ((value & 0x00FF0000U) >> 8)  |
           ((value & 0xFF000000U) >> 24);
}

/* Extract a field of bits from an integer. */
uint32_t extractBits(uint32_t value,
                     unsigned int position,
                     unsigned int width) {
    uint32_t mask = (1U << width) - 1U;

    return (value >> position) & mask;
}

/* Insert a field of bits into an integer. */
uint32_t insertBits(uint32_t value,
                    uint32_t newBits,
                    unsigned int position,
                    unsigned int width) {
    uint32_t mask = (1U << width) - 1U;

    value &= ~(mask << position);
    value |= (newBits & mask) << position;

    return value;
}

/* Detect host endianness. */
void detectEndianness(void) {
    uint32_t value = 1U;
    const unsigned char *bytes = (const unsigned char *)&value;

    if (bytes[0] == 1U)
        printf("Little-endian\n");
    else if (bytes[0] == 0U)
        printf("Big-endian\n");
    else
        printf("Other byte order\n");
}

int main(void) {
    uint32_t value = 0x12345678U;

    printf("Practical Bit Manipulation Exercises\n");
    printf("-------------------------------------\n");

    /* Exercise 1: Count set bits. */
    printf("Set bits in 0x%08X: %u\n",
           value, countSetBits(value));

    /* Exercise 2: Check powers of two. */
    printf("\nPower-of-two checks:\n");
    printf("16: %s\n", isPowerOfTwo(16U) ? "Yes" : "No");
    printf("18: %s\n", isPowerOfTwo(18U) ? "Yes" : "No");

    /* Exercise 3: Extract a bit field. */
    printf("\nExtracted bits: %u\n",
           extractBits(0xD6U, 2U, 3U));

    /* Exercise 4: Insert a bit field. */
    printf("Inserted value: 0x%02X\n",
           insertBits(0xD6U, 3U, 2U, 3U));

    /* Exercise 5: Swap bytes. */
    printf("\nByte-swapped value: 0x%08X\n",
           byteSwap(value));

    /* Exercise 6: Detect host endianness. */
    printf("\nHost byte order: ");
    detectEndianness();

    return 0;
}
