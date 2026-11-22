#include <stdio.h>

int main(void) {
    // Declare variables of different types.
    int number = 42;
    char character = 'A';
    float decimal = 3.14f;
    double precise_decimal = 9.81;

    // Initialize pointers to their corresponding objects.
    int *integer_pointer = &number;
    char *character_pointer = &character;
    float *float_pointer = &decimal;
    double *double_pointer = &precise_decimal;
    void *generic_pointer = &number;

    // Display the sizes of different objects.
    printf("Object Sizes:\n");

    printf("int:    %zu bytes\n", sizeof(number));
    printf("char:   %zu bytes\n", sizeof(character));
    printf("float:  %zu bytes\n", sizeof(decimal));
    printf("double: %zu bytes\n", sizeof(precise_decimal));

    // Display the sizes of pointer variables.
    printf("\nPointer Sizes:\n");

    printf("int *:    %zu bytes\n", sizeof(integer_pointer));
    printf("char *:   %zu bytes\n", sizeof(character_pointer));
    printf("float *:  %zu bytes\n", sizeof(float_pointer));
    printf("double *: %zu bytes\n", sizeof(double_pointer));
    printf("void *:   %zu bytes\n", sizeof(generic_pointer));

    // Compare a pointer with the object it points to.
    printf("\nPointer vs Pointed Object:\n");

    printf("sizeof(integer_pointer): %zu bytes\n",
           sizeof(integer_pointer));

    printf("sizeof(*integer_pointer): %zu bytes\n",
           sizeof(*integer_pointer));

    return 0;
}
