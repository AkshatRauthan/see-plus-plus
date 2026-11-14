#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/calculator.h"

int parseFloat(const char *ch, float *num) {
	char *end;

	errno = 0;
	*num = strtof(ch, &end);

	if (ch == end || *end != '\0' || errno == ERANGE) {
		fprintf(stderr, "Invalid Operand Provided: %s\n", ch);
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

int main(int argc, char *argv[]) {
	if (argc != 4) {
		fprintf(stderr,
				"Invalid Number Of Command Line Arguments Given. Expected 4, "
				"Recieved %d\n",
				argc - 1);
		return EXIT_FAILURE;
	} else {
		float ans, num1, num2;

		if (parseFloat(argv[1], &num1) != EXIT_SUCCESS) {
			return EXIT_FAILURE;
		}

		if (parseFloat(argv[3], &num2) != EXIT_SUCCESS) {
			return EXIT_FAILURE;
		}

		if (strcmp(argv[2], "+") == 0) {
			ans = sum(num1, num2);

		} else if (strcmp(argv[2], "-") == 0) {
			ans = subtraction(num1, num2);

		} else if (strcmp(argv[2], "*") == 0) {
			ans = product(num1, num2);

		} else if (strcmp(argv[2], "/") == 0) {
			if (num2 == 0) {
				fprintf(stderr, "Division By Zero...\n");
				return EXIT_FAILURE;
			}
			ans = divison(num1, num2);

		} else if (strcmp(argv[2], "^") == 0) {
			if (num2 < 0) {
				fprintf(stderr, "Negative Powers Are Not Handled...\n");
				return EXIT_FAILURE;
			}
			ans = power(num1, num2);

		} else {
			printf("Invalid Operator %s Entered\n", argv[2]);
			return EXIT_FAILURE;
		}

		printf("Result Of %s %s %s = %.4f\n", argv[1], argv[2], argv[3], ans);
	}
	return EXIT_SUCCESS;
}
