
#include <stdio.h>
#include <string.h>

struct Example {
    char character;
    int number;
    char flag;
};

/* Print an object's representation byte by byte. */
void inspectObject(const void *object, size_t size) {
    const unsigned char *bytes = object;

    for (size_t i = 0; i < size; i++) {
        printf("Byte %zu: 0x%02X\n",
               i, (unsigned int)bytes[i]);
    }
}

int main(void) {
    int original = 0x12345678;
    unsigned char representation[sizeof(original)];

    printf("Object Representation Inspection\n");
    printf("---------------------------------\n");

    printf("Original integer: 0x%X\n\n", original);

    printf("Inspecting original object:\n");
    inspectObject(&original, sizeof(original));

    /*
     * Copy the object's representation into an unsigned
     * char array using memcpy().
     *
     * This avoids accessing the integer through an
     * incompatible pointer type.
     */
    memcpy(representation, &original, sizeof(original));

    printf("\nCopied object representation:\n");
    inspectObject(representation, sizeof(representation));

    struct Example example = {
        .character = 'A',
        .number = 42,
        .flag = 1
    };

    printf("\nStructure inspection:\n");
    printf("Character size: %zu byte(s)\n", sizeof(example.character));
    printf("Integer size:   %zu byte(s)\n", sizeof(example.number));
    printf("Flag size:      %zu byte(s)\n", sizeof(example.flag));

    printf("Structure size: %zu byte(s)\n", sizeof(example));

    printf("\nStructure object representation:\n");
    inspectObject(&example, sizeof(example));

    return 0;
}
