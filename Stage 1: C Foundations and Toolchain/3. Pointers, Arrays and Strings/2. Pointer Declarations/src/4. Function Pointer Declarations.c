#include <stdio.h>

// Function accepting two integers and returning their sum.
static int add(int first, int second) {
    return first + second;
}

// Function accepting two integers and returning their difference.
static int subtract(int first, int second) {
    return first - second;
}

// Function accepting two integers and returning their product.
static int multiply(int first, int second) {
    return first * second;
}

// Function accepting two integers and returning their quotient.
static int divide(int first, int second) {
    if (second == 0) {
        fprintf(stderr, "Division by zero is not allowed.\n");
        return 0;
    }

    return first / second;
}

int main(void) {
    /*
     * Declare a pointer to a function that:
     * - Accepts two integers.
     * - Returns an integer.
     */
    int (*operation)(int, int);

    int first = 20;
    int second = 5;

    // Assign the address of add to the function pointer.
    operation = add;

    printf("Addition:\n");
    printf("%d + %d = %d\n",
           first, second, operation(first, second));

    // Reassign the pointer to subtract.
    operation = subtract;

    printf("\nSubtraction:\n");
    printf("%d - %d = %d\n",
           first, second, operation(first, second));

    // Reassign the pointer to multiply.
    operation = multiply;

    printf("\nMultiplication:\n");
    printf("%d * %d = %d\n",
           first, second, operation(first, second));

    // Reassign the pointer to divide.
    operation = divide;

    printf("\nDivision:\n");
    printf("%d / %d = %d\n",
           first, second, operation(first, second));

    // Explicitly dereference the function pointer.
    printf("\nExplicit Dereferencing:\n");
    printf("Result: %d\n", (*operation)(100, 10));

    return 0;
}
