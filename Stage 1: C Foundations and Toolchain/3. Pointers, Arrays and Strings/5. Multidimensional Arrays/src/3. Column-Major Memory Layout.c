#include <stdio.h>

#define ROWS 3
#define COLS 4

int main(void) {
    int matrix[ROWS][COLS] = {
        {10, 20, 30, 40},
        {50, 60, 70, 80},
        {90, 100, 110, 120}
    };

    int columnMajor[ROWS * COLS];

    printf("=== Original Matrix ===\n");

    for (size_t row = 0; row < ROWS; row++) {
        for (size_t col = 0; col < COLS; col++) {
            printf("%4d ", matrix[row][col]);
        }
        printf("\n");
    }

    /*
     * Store the matrix in column-major order.
     *
     * Column-major index:
     * index = col * ROWS + row
     */
    for (size_t col = 0; col < COLS; col++) {
        for (size_t row = 0; row < ROWS; row++) {
            size_t index = col * ROWS + row;

            columnMajor[index] = matrix[row][col];
        }
    }

    printf("\n=== Simulated Column-Major Storage ===\n");

    for (size_t col = 0; col < COLS; col++) {
        for (size_t row = 0; row < ROWS; row++) {
            size_t index = col * ROWS + row;
            size_t byte_offset = index * sizeof(int);

            printf("matrix[%zu][%zu] = %3d | "
                   "index %2zu | offset %2zu bytes\n",
                   row, col,
                   columnMajor[index],
                   index,
                   byte_offset);
        }
    }

    printf("\n=== Column-Major Linear Memory Order ===\n");

    for (size_t index = 0; index < ROWS * COLS; index++) {
        printf("%3d ", columnMajor[index]);
    }
    printf("\n");

    printf("\n=== Reconstructing the Matrix ===\n");

    for (size_t row = 0; row < ROWS; row++) {
        for (size_t col = 0; col < COLS; col++) {
            size_t index = col * ROWS + row;

            printf("%4d ", columnMajor[index]);
        }
        printf("\n");
    }

    printf("\n=== Size Information ===\n");
    printf("Number of elements: %d\n", ROWS * COLS);
    printf("Storage size: %zu bytes\n", sizeof(columnMajor));

    return 0;
}
