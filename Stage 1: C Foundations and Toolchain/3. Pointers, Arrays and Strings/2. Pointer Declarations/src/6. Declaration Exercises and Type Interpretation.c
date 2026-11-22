#include <stdio.h>

int add(int a, int b) {
    return a + b;
}

char *get_message(void) {
    return "Hello";
}

int main(void) {
    int value = 10;
    int numbers[5] = {1, 2, 3, 4, 5};

    int *pointer = &value;
    int **double_pointer = &pointer;

    int *pointer_array[3] = {&value, &numbers[0], &numbers[1]};
    int (*array_pointer)[5] = &numbers;

    int (*function_pointer)(int, int) = add;
    int (*function_array[2])(int, int) = {add, NULL};

    char *(*text_function)(void) = get_message;

    printf("value: %d\n", value);
    printf("*pointer: %d\n", *pointer);
    printf("**double_pointer: %d\n", **double_pointer);

    printf("\nPointer array:\n");
    for (size_t i = 0; i < 3; i++) {
        printf("  *pointer_array[%zu] = %d\n", i, *pointer_array[i]);
    }

    printf("\nPointer to array:\n");
    for (size_t i = 0; i < 5; i++) {
        printf("  (*array_pointer)[%zu] = %d\n", i, (*array_pointer)[i]);
    }

    printf("\nFunction pointer:\n");
    printf("  function_pointer(5, 7) = %d\n", function_pointer(5, 7));

    printf("\nFunction pointer array:\n");
    if (function_array[0] != NULL) {
        printf("  function_array[0](3, 4) = %d\n",
               function_array[0](3, 4));
    }

    printf("\nFunction returning pointer:\n");
    printf("  text_function() = %s\n", text_function());

    return 0;
}
