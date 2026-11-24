#include <stdio.h>

int main(void) {
    int matrix[3][4] = {
        {10, 20, 30, 40},
        {50, 60, 70, 80},
        {90, 100, 110, 120}
    };

    printf("=== 2D Array ===\n");
    for (size_t row = 0; row < 3; row++) {
        for (size_t col = 0; col < 4; col++) {
            printf("%4d ", matrix[row][col]);
        }
        printf("\n");
    }

    printf("\n=== Array Dimensions ===\n");
    printf("Rows: %zu\n", sizeof(matrix) / sizeof(matrix[0]));
    printf("Columns: %zu\n", sizeof(matrix[0]) / sizeof(matrix[0][0]));
    printf("Total elements: %zu\n", sizeof(matrix) / sizeof(matrix[0][0]));

    printf("\n=== Sizes ===\n");
    printf("sizeof(matrix): %zu bytes\n", sizeof(matrix));
    printf("sizeof(matrix[0]): %zu bytes\n", sizeof(matrix[0]));
    printf("sizeof(matrix[0][0]): %zu bytes\n", sizeof(matrix[0][0]));

    printf("\n=== Memory Addresses ===\n");
    printf("matrix:         %p\n", (void *)matrix);
    printf("matrix[0]:     %p\n", (void *)matrix[0]);
    printf("&matrix[0][0]: %p\n", (void *)&matrix[0][0]);

    printf("\n=== Row Addresses ===\n");
    for (size_t row = 0; row < 3; row++) {
        printf("matrix[%zu]: %p\n", row, (void *)matrix[row]);
    }

    printf("\n=== Element Addresses ===\n");
    for (size_t row = 0; row < 3; row++) {
        for (size_t col = 0; col < 4; col++) {
            printf("&matrix[%zu][%zu] = %p\n",
                   row, col, (void *)&matrix[row][col]);
        }
    }

    return 0;
}
