#include <stdio.h>

int main(void) {
    int numbers[] = {10, 20, 30, 40, 50};
    int *ptr = numbers;

    printf("Array information:\n");
    printf("sizeof(numbers): %zu bytes\n", sizeof(numbers));
    printf("sizeof(numbers[0]): %zu bytes\n", sizeof(numbers[0]));
    printf("Array elements: %zu\n", sizeof(numbers) / sizeof(numbers[0]));

    printf("\nPointer information:\n");
    printf("sizeof(ptr): %zu bytes\n", sizeof(ptr));
    printf("sizeof(*ptr): %zu bytes\n", sizeof(*ptr));

    printf("\nAddress information:\n");
    printf("numbers: %p\n", (void *)numbers);
    printf("&numbers: %p\n", (void *)&numbers);
    printf("ptr: %p\n", (void *)ptr);
    printf("&ptr: %p\n", (void *)&ptr);

    return 0;
}
