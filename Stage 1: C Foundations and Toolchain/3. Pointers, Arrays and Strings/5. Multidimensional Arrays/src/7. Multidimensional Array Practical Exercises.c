#include <stdio.h>

#define ROWS 3
#define COLS 4

void PrintMatrix(const int matrix[][COLS], size_t rows);
void PrintMatrixUsingPointer(const int (*matrix)[COLS], size_t rows);
int SumMatrix(const int matrix[][COLS], size_t rows);
void SumRows(const int matrix[][COLS], size_t rows);
void SumColumns(const int matrix[][COLS], size_t rows);
void ModifyMatrix(int matrix[][COLS], size_t rows, int value);
int FindElement(const int matrix[][COLS], size_t rows, int target);
void TransposeMatrix(const int matrix[][COLS], int result[][ROWS], size_t rows);

int main(void) {
    int matrix[ROWS][COLS] = {
        {10, 20, 30, 40},
        {50, 60, 70, 80},
        {90, 100, 110, 120}
    };

    int transposed[COLS][ROWS];

    printf("=== 1. Original Matrix ===\n");
    PrintMatrix(matrix, ROWS);

    printf("\n=== 2. Pointer-Based Traversal ===\n");
    PrintMatrixUsingPointer(matrix, ROWS);

    printf("\n=== 3. Matrix Sum ===\n");
    printf("Total: %d\n", SumMatrix(matrix, ROWS));

    printf("\n=== 4. Row Sums ===\n");
    SumRows(matrix, ROWS);

    printf("\n=== 5. Column Sums ===\n");
    SumColumns(matrix, ROWS);

    printf("\n=== 6. Searching ===\n");
    int target = 70;
    int found = FindElement(matrix, ROWS, target);

    if (found) {
        printf("%d found in the matrix.\n", target);
    } else {
        printf("%d not found in the matrix.\n", target);
    }

    printf("\n=== 7. Modifying Matrix ===\n");
    ModifyMatrix(matrix, ROWS, 5);
    PrintMatrix(matrix, ROWS);

    printf("\n=== 8. Transposed Matrix ===\n");
    TransposeMatrix(matrix, transposed, ROWS);
    PrintMatrix(transposed, COLS);

    printf("\n=== 9. Pointer-to-Row Access ===\n");
    int (*rowPtr)[COLS] = matrix;

    printf("First element: %d\n", rowPtr[0][0]);
    printf("Last element of row 1: %d\n", rowPtr[1][COLS - 1]);
    printf("First element of row 2: %d\n", *(*(rowPtr + 2) + 0));

    printf("\n=== 10. Memory Layout ===\n");
    printf("Row size: %zu bytes\n", sizeof(matrix[0]));
    printf("Matrix size: %zu bytes\n", sizeof(matrix));

    return 0;
}

void PrintMatrix(const int matrix[][COLS], size_t rows) {
    for (size_t row = 0; row < rows; row++) {
        for (size_t col = 0; col < COLS; col++) {
            printf("%4d ", matrix[row][col]);
        }
        printf("\n");
    }
}

void PrintMatrixUsingPointer(const int (*matrix)[COLS], size_t rows) {
    for (size_t row = 0; row < rows; row++) {
        const int *elementPtr = *(matrix + row);

        for (size_t col = 0; col < COLS; col++) {
            printf("%4d ", *(elementPtr + col));
        }
        printf("\n");
    }
}

int SumMatrix(const int matrix[][COLS], size_t rows) {
    int sum = 0;

    for (size_t row = 0; row < rows; row++) {
        for (size_t col = 0; col < COLS; col++) {
            sum += matrix[row][col];
        }
    }

    return sum;
}

void SumRows(const int matrix[][COLS], size_t rows) {
    for (size_t row = 0; row < rows; row++) {
        int sum = 0;

        for (size_t col = 0; col < COLS; col++) {
            sum += matrix[row][col];
        }

        printf("Row %zu sum: %d\n", row, sum);
    }
}

void SumColumns(const int matrix[][COLS], size_t rows) {
    for (size_t col = 0; col < COLS; col++) {
        int sum = 0;

        for (size_t row = 0; row < rows; row++) {
            sum += matrix[row][col];
        }

        printf("Column %zu sum: %d\n", col, sum);
    }
}

void ModifyMatrix(int matrix[][COLS], size_t rows, int value) {
    for (size_t row = 0; row < rows; row++) {
        for (size_t col = 0; col < COLS; col++) {
            matrix[row][col] += value;
        }
    }
}

int FindElement(const int matrix[][COLS], size_t rows, int target) {
    for (size_t row = 0; row < rows; row++) {
        for (size_t col = 0; col < COLS; col++) {
            if (matrix[row][col] == target) {
                return 1;
            }
        }
    }

    return 0;
}

void TransposeMatrix(const int matrix[][COLS], int result[][ROWS], size_t rows) {
    for (size_t row = 0; row < rows; row++) {
        for (size_t col = 0; col < COLS; col++) {
            result[col][row] = matrix[row][col];
        }
    }
}
