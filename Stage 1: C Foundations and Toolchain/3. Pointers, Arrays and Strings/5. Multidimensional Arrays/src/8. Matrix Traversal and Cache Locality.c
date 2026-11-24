#include <stdio.h>
#include <stdint.h>
#include <time.h>

#define ROWS 2048
#define COLS 2048
#define REPETITIONS 5

static int matrix[ROWS][COLS];

void InitializeMatrix(void) {
    for (size_t row = 0; row < ROWS; row++) {
        for (size_t col = 0; col < COLS; col++) {
            matrix[row][col] = (int)((row + col) % 100);
        }
    }
}

int64_t SumRowWise(void) {
    int64_t sum = 0;

    for (size_t row = 0; row < ROWS; row++) {
        for (size_t col = 0; col < COLS; col++) {
            sum += matrix[row][col];
        }
    }

    return sum;
}

int64_t SumColumnWise(void) {
    int64_t sum = 0;

    for (size_t col = 0; col < COLS; col++) {
        for (size_t row = 0; row < ROWS; row++) {
            sum += matrix[row][col];
        }
    }

    return sum;
}

double BenchmarkRowWise(void) {
    int64_t checksum = 0;

    clock_t start = clock();

    for (size_t repetition = 0; repetition < REPETITIONS; repetition++) {
        checksum += SumRowWise();
    }

    clock_t end = clock();

    printf("Row-wise checksum: %lld\n", (long long)checksum);

    return (double)(end - start) / CLOCKS_PER_SEC;
}

double BenchmarkColumnWise(void) {
    int64_t checksum = 0;

    clock_t start = clock();

    for (size_t repetition = 0; repetition < REPETITIONS; repetition++) {
        checksum += SumColumnWise();
    }

    clock_t end = clock();

    printf("Column-wise checksum: %lld\n", (long long)checksum);

    return (double)(end - start) / CLOCKS_PER_SEC;
}

int main(void) {
    InitializeMatrix();

    printf("=== Matrix Information ===\n");
    printf("Dimensions: %d x %d\n", ROWS, COLS);
    printf("Total elements: %d\n", ROWS * COLS);
    printf("Element size: %zu bytes\n", sizeof(matrix[0][0]));
    printf("Total memory: %.2f MiB\n",
           (double)sizeof(matrix) / (1024.0 * 1024.0));
    printf("Repetitions: %d\n", REPETITIONS);

    printf("\n=== Row-wise Traversal ===\n");
    double rowTime = BenchmarkRowWise();
    printf("Time: %.6f seconds\n", rowTime);

    printf("\n=== Column-wise Traversal ===\n");
    double columnTime = BenchmarkColumnWise();
    printf("Time: %.6f seconds\n", columnTime);

    printf("\n=== Comparison ===\n");

    if (rowTime > 0.0 && columnTime > 0.0) {
        printf("Row-wise:    %.6f seconds\n", rowTime);
        printf("Column-wise: %.6f seconds\n", columnTime);
        printf("Column-wise / Row-wise: %.2fx\n",
               columnTime / rowTime);
    } else {
        printf("Measured time was too small for a meaningful comparison.\n");
    }

    return 0;
}
