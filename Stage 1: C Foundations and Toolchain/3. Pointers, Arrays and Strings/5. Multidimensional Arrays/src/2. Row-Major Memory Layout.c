#include <stdio.h>

int main(void) {
    int matrix[3][4] = {
        {10, 20, 30, 40},
        {50, 60, 70, 80},
        {90, 100, 110, 120}
    };

    size_t rows = sizeof(matrix) / sizeof(matrix[0]);
    size_t columns = sizeof(matrix[0]) / sizeof(matrix[0][0]);

    unsigned char *base = (unsigned char *)&matrix;

    printf("=== Row-Major Layout ===\n\n");

    for (size_t row = 0; row < rows; row++) {
        for (size_t col = 0; col < columns; col++) {
            size_t element_index = row * columns + col;
            size_t byte_offset = element_index * sizeof(int);

            printf("matrix[%zu][%zu] = %3d | "
                   "element #%2zu | offset %2zu bytes | address %p\n",
                   row, col,
                   matrix[row][col],
                   element_index,
                   byte_offset,
                   (void *)&matrix[row][col]);
        }
    }

    printf("\n=== Element-Start Addresses ===\n");

    for (size_t offset = 0; offset < sizeof(matrix);
         offset += sizeof(int)) {
        printf("Offset %2zu: address %p\n",
               offset, (void *)(base + offset));
    }

    printf("\n=== Row Boundaries ===\n");

    for (size_t row = 0; row < rows; row++) {
        printf("Row %zu starts: %p\n",
               row, (void *)&matrix[row][0]);
    }

    printf("\n=== Size Information ===\n");
    printf("Row size:   %zu bytes\n", sizeof(matrix[0]));
    printf("Total size: %zu bytes\n", sizeof(matrix));

    return 0;
}
