#include <stdio.h>

int main(void) {
    int matrix[3][4] = {
        {10, 20, 30, 40},
        {50, 60, 70, 80},
        {90, 100, 110, 120}
    };

    size_t rows = sizeof(matrix) / sizeof(matrix[0]);
    size_t columns = sizeof(matrix[0]) / sizeof(matrix[0][0]);

    int (*rowPtr)[4] = matrix;

    printf("=== Row Pointer Traversal ===\n");

    for (size_t row = 0; row < rows; row++) {
        printf("Row %zu at %p: ",
               row, (void *)(rowPtr + row));

        for (size_t col = 0; col < columns; col++) {
            printf("%d ", (* (rowPtr + row))[col]);
        }

        printf("\n");
    }

    printf("\n=== Element Pointer Traversal Within a Row ===\n");

    int *elementPtr = matrix[0];

    for (size_t col = 0; col < columns; col++) {
        printf("elementPtr + %zu = %p | value = %d\n",
               col,
               (void *)(elementPtr + col),
               *(elementPtr + col));
    }

    printf("\n=== Advancing Across Rows ===\n");

    for (size_t row = 0; row < rows; row++) {
        int (*currentRow)[4] = rowPtr + row;

        printf("Row %zu | first = %d | last = %d\n",
               row,
               (*currentRow)[0],
               (*currentRow)[3]);
    }

    printf("\n=== Row and Element Offsets ===\n");

    printf("rowPtr + 0: %p\n", (void *)(rowPtr + 0));
    printf("rowPtr + 1: %p\n", (void *)(rowPtr + 1));
    printf("rowPtr + 2: %p\n", (void *)(rowPtr + 2));
    printf("rowPtr + 3: %p (one-past)\n", (void *)(rowPtr + 3));

    printf("\n=== Accessing Elements Through Row Pointer ===\n");

    printf("rowPtr[0][0] = %d\n", rowPtr[0][0]);
    printf("rowPtr[0][3] = %d\n", rowPtr[0][3]);
    printf("rowPtr[1][0] = %d\n", rowPtr[1][0]);
    printf("rowPtr[1][3] = %d\n", rowPtr[1][3]);
    printf("rowPtr[2][0] = %d\n", rowPtr[2][0]);
    printf("rowPtr[2][3] = %d\n", rowPtr[2][3]);

    return 0;
}
