#include <stdio.h>
#include <stdlib.h>

// Receives a copy of the caller's pointer.
// Reassigning this local copy does not affect the caller.
static void ReassignLocalPointer(int *pointer, int *replacement) {
    pointer = replacement;
}

// Receives the address of the caller's pointer.
// Reassigning *pointer modifies the caller's pointer.
static void ReassignCallerPointer(int **pointer, int *replacement) {
    *pointer = replacement;
}

int main(void) {
    // --------------------------------------------------
    // 1. Incorrect indirection level
    // --------------------------------------------------

    int value = 100;
    int *ptr = &value;
    int **doublePtr = &ptr;

    printf("1. Correct Indirection:\n");
    printf("value: %d\n", **doublePtr);

    // Incorrect: *doublePtr is an int pointer, not an int.
    // printf("%d\n", *doublePtr);


    // --------------------------------------------------
    // 2. Modifying a local pointer instead of the caller's
    // --------------------------------------------------

    int first = 10;
    int second = 20;

    int *original = &first;

    // This function receives a copy of the pointer.
    ReassignLocalPointer(original, &second);

    printf("\n2. Local Pointer Reassignment:\n");
    printf("original still points to: %d\n", *original);


    // --------------------------------------------------
    // 3. Correctly modifying the caller's pointer
    // --------------------------------------------------

    // Pass the address of original so the function can
    // modify the actual pointer variable belonging to main.
    ReassignCallerPointer(&original, &second);

    printf("\n3. Caller Pointer Reassignment:\n");
    printf("original now points to: %d\n", *original);


    // --------------------------------------------------
    // 4. Dereferencing an uninitialized double pointer
    // --------------------------------------------------

    int **uninitialized;

    // Incorrect: uninitialized contains an indeterminate value.
    // *uninitialized = &value;

    // Initialize it before dereferencing.
    uninitialized = &ptr;

    printf("\n4. Initialized Double Pointer:\n");
    printf("Value: %d\n", **uninitialized);


    // --------------------------------------------------
    // 5. Dereferencing a NULL double pointer
    // --------------------------------------------------

    int **nullPtr = NULL;

    // Incorrect: dereferencing NULL causes undefined behavior.
    // **nullPtr = 500;

    // Check before dereferencing.
    if (nullPtr != NULL) {
        **nullPtr = 500;
    }

    printf("\n5. NULL Pointer Check:\n");
    printf("nullPtr is NULL: %s\n", nullPtr == NULL ? "Yes" : "No");


    // --------------------------------------------------
    // 6. Losing an allocation through incorrect assignment
    // --------------------------------------------------

    int *allocated = malloc(sizeof *allocated);

    if (allocated == NULL) {
        fprintf(stderr, "Allocation failed.\n");
        return 1;
    }

    *allocated = 500;

    // Incorrect: directly overwriting the only owning pointer
    // can lose the allocation address and cause a memory leak.
    //
    // allocated = malloc(sizeof *allocated);

    // Correct: use a temporary pointer when replacing an allocation.
    int *replacement = malloc(sizeof *replacement);

    if (replacement == NULL) {
        free(allocated);
        return 1;
    }

    *replacement = 900;

    free(allocated);
    allocated = replacement;
    replacement = NULL;

    printf("\n6. Safe Allocation Replacement:\n");
    printf("Value: %d\n", *allocated);


    // --------------------------------------------------
    // 7. Incorrectly freeing only the outer pointer array
    // --------------------------------------------------

    size_t rows = 2;
    size_t cols = 3;

    int **matrix = calloc(rows, sizeof *matrix);

    if (matrix == NULL) {
        free(allocated);
        return 1;
    }

    // Allocate each row independently.
    for (size_t i = 0; i < rows; i++) {
        matrix[i] = calloc(cols, sizeof *matrix[i]);

        if (matrix[i] == NULL) {
            // Release previously allocated rows.
            for (size_t j = 0; j < i; j++) {
                free(matrix[j]);
            }

            free(matrix);
            free(allocated);
            return 1;
        }
    }

    // Incorrect: free(matrix) alone would leak the row allocations.
    // Correct cleanup requires freeing each row first.
    for (size_t i = 0; i < rows; i++) {
        free(matrix[i]);
    }

    free(matrix);
    matrix = NULL;

    printf("\n7. Dynamic Matrix Cleanup:\n");
    printf("All row allocations released.\n");

	
    // --------------------------------------------------
    // 8. Using a pointer after freeing its allocation
    // --------------------------------------------------

    int *dangling = malloc(sizeof *dangling);

    if (dangling == NULL) {
        free(allocated);
        return 1;
    }

    *dangling = 700;

    printf("\n8. Before Deallocation:\n");
    printf("Value: %d\n", *dangling);

    free(dangling);
    dangling = NULL;

    // The allocation has been released.
    // Never dereference dangling after free().
    printf("Pointer reset to NULL: %s\n",
           dangling == NULL ? "Yes" : "No");

    // --------------------------------------------------
    // Final cleanup
    // --------------------------------------------------

    free(allocated);
    allocated = NULL;

    return 0;
}
