
#include <stdint.h>
#include <stdio.h>

#define BYTE_COUNT 4

/*
 * Serialize a 32-bit integer into four bytes.
 *
 * The most significant byte is stored first,
 * producing a big-endian byte sequence.
 */
void serializeUint32(uint32_t value, uint8_t buffer[BYTE_COUNT]) {
    buffer[0] = (uint8_t)(value >> 24);
    buffer[1] = (uint8_t)(value >> 16);
    buffer[2] = (uint8_t)(value >> 8);
    buffer[3] = (uint8_t)value;
}

/*
 * Deserialize four big-endian bytes into a 32-bit integer.
 */
uint32_t deserializeUint32(const uint8_t buffer[BYTE_COUNT]) {
    return ((uint32_t)buffer[0] << 24) |
           ((uint32_t)buffer[1] << 16) |
           ((uint32_t)buffer[2] << 8) |
           (uint32_t)buffer[3];
}

int main(void) {
    uint32_t original = 0x12345678U;
    uint8_t buffer[BYTE_COUNT];

    printf("Serialization and Deserialization\n");
    printf("---------------------------------\n");

    printf("Original value: 0x%08X\n", original);

    /* Convert the integer into a byte sequence. */
    serializeUint32(original, buffer);

    printf("\nSerialized bytes:\n");

    for (size_t i = 0; i < BYTE_COUNT; i++) {
        printf("Byte %zu: 0x%02X\n",
               i, (unsigned int)buffer[i]);
    }

    /* Reconstruct the integer from the byte sequence. */
    uint32_t restored = deserializeUint32(buffer);

    printf("\nDeserialized value: 0x%08X\n", restored);

    printf("Values match: %s\n",
           original == restored ? "Yes" : "No");

    return 0;
}
