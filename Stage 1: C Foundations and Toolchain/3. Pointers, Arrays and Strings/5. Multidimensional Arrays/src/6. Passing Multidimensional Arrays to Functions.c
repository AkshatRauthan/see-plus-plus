#include <stdio.h>

#define ROWS 3
#define COLS 4

void PrintMatrix(int matrix[][COLS], size_t rows);
void PrintMatrixUsingPointer(int (*matrix)[COLS], size_t rows);
void ModifyMatrix(int matrix[][COLS], size_t rows);
void PrintMatrixSizes(int matrix[][COLS]);

int main(void) {
    int matrix[ROWS][COLS] = {
        {10, 20, 30, 40},
        {50, 60, 70, 80},
        {90, 100, 110, 120}
    };

    printf("=== Original Matrix ===\n");
    PrintMatrix(matrix, ROWS);

    printf("\n=== Pointer Parameter ===\n");
    PrintMatrixUsingPointer(matrix, ROWS);

    printf("\n=== Modify Matrix in Function ===\n");
    ModifyMatrix(matrix, ROWS);
    PrintMatrix(matrix, ROWS);

    printf("\n=== sizeof Inside Function ===\n");
    PrintMatrixSizes(matrix);

    printf("\n=== sizeof in Main ===\n");
    printf("sizeof(matrix): %zu bytes\n", sizeof(matrix));
    printf("Total elements: %zu\n",
           sizeof(matrix) / sizeof(matrix[0][0]));

    return 0;
}

void PrintMatrix(int matrix[][COLS], size_t rows) {
    for (size_t row = 0; row < rows; row++) {
        for (size_t col = 0; col < COLS; col++) {
            printf("%4d ", matrix[row][col]);
        }
        printf("\n");
    }
}

void PrintMatrixUsingPointer(int (*matrix)[COLS], size_t rows) {
    for (size_t row = 0; row < rows; row++) {
        for (size_t col = 0; col < COLS; col++) {
            printf("%4d ", *(*(matrix + row) + col));
        }
        printf("\n");
    }
}

void ModifyMatrix(int matrix[][COLS], size_t rows) {
    for (size_t row = 0; row < rows; row++) {
        for (size_t col = 0; col < COLS; col++) {
            matrix[row][col] += 5;
        }
    }
}

void PrintMatrixSizes(int matrix[][COLS]) {
    printf("sizeof(matrix): %zu bytes\n", sizeof(matrix));
    printf("sizeof(matrix[0]): %zu bytes\n", sizeof(matrix[0]));
    printf("sizeof(matrix[0][0]): %zu bytes\n", sizeof(matrix[0][0]));
}
