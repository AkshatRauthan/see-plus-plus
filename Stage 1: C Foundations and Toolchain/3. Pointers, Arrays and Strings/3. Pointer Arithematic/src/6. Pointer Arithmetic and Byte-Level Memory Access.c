#include <limits.h>
#include <stddef.h>
#include <stdio.h>
#include <stdint.h>

int main(void) {
    uint32_t number = UINT32_C(0x12345678);

    // 1. Accessing an object's representation through unsigned char.
    unsigned char *bytes = (unsigned char *)&number;

    // sizeof returns the object's size in bytes.
    size_t size = sizeof(number);

    printf("Number: 0x%08X\n", (unsigned int)number);
    printf("Size: %zu bytes\n", size);
    printf("Bits per byte: %d\n", CHAR_BIT);

    // 2. Inspecting individual bytes.
    printf("\nIndividual bytes:\n");

    for (size_t i = 0; i < size; i++) {
        printf("Byte %zu: 0x%02X\n", i, (unsigned int)bytes[i]);
    }

    // 3. Pointer arithmetic using byte offsets.
    printf("\nByte traversal using pointer arithmetic:\n");

    for (unsigned char *current = bytes;
         current < bytes + size;
         current++) {

        ptrdiff_t offset = current - bytes;

        printf("Offset %td: 0x%02X\n",
               offset,
               (unsigned int)*current);
    }

    // 4. Modifying an object's representation through unsigned char.
    // Set the first byte of the object's representation to zero.
    bytes[0] = 0;

    printf("\nAfter modifying the first byte:\n");

    for (size_t i = 0; i < size; i++) {
        printf("Byte %zu: 0x%02X\n", i, (unsigned int)bytes[i]);
    }

    printf("Updated number: 0x%08X\n", (unsigned int)number);

    return 0;
}
