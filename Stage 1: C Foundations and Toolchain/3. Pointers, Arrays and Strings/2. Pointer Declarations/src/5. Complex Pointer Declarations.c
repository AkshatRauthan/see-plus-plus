#include <stdio.h>

/* A function returning a pointer to char */
char *get_text(void) {
    return "Hello from get_text";
}

/* A function returning an int */
int calculate(int a, int b) {
    return a + b;
}

int main(void) {
    int value = 100;

    /* 1. Pointer to pointer */
    int **pointer_to_pointer = NULL;
    int *pointer = &value;
    pointer_to_pointer = &pointer;

    /* 2. Array of pointers */
    int first = 10, second = 20, third = 30;
    int *pointer_array[3] = {&first, &second, &third};

    /* 3. Pointer to an array */
    int numbers[5] = {10, 20, 30, 40, 50};
    int (*array_pointer)[5] = &numbers;

    /* 4. Single function pointer */
    int (*function_pointer)(int, int) = calculate;

    /* 5. Array of function pointers */
    int (*function_array[3])(int, int) = {
        calculate,
        NULL,
        NULL
    };

    /* 6. Function returning a pointer */
    char *(*text_function)(void) = get_text;

    printf("Pointer to pointer:\n");
    printf("  **pointer_to_pointer = %d\n", **pointer_to_pointer);

    printf("\nArray of pointers:\n");
    for (size_t i = 0; i < 3; i++) {
        printf("  *pointer_array[%zu] = %d\n", i, *pointer_array[i]);
    }

    printf("\nPointer to array:\n");
    for (size_t i = 0; i < 5; i++) {
        printf("  (*array_pointer)[%zu] = %d\n", i, (*array_pointer)[i]);
    }

    printf("\nSingle function pointer:\n");
    printf("  function_pointer(5, 3) = %d\n", function_pointer(5, 3));

    printf("\nArray of function pointers:\n");
    if (function_array[0] != NULL) {
        printf("  function_array[0](5, 3) = %d\n",
               function_array[0](5, 3));
    }

    printf("\nFunction returning a pointer:\n");
    printf("  text_function() = %s\n", text_function());

    return 0;
}
