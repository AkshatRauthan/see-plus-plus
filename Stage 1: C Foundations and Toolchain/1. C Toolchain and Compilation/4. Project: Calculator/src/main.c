#include <stdio.h>
#include <stdlib.h>

#include "../include/evaluator.h"
#include "../include/lexer.h"
#include "../include/parser.h"

int main(int argc, const char *argv[]) {
	if (argc < 2) {
		fprintf(stderr, "Usage: %s <expression>\n", argv[0]);
		return EXIT_FAILURE;
	}

	int tokenCount = argc - 1;

	Token tokens[tokenCount];
	Token postfix[tokenCount + 1];

	int res = ParseTokens(argc, argv, tokens);

	if (res != EXIT_SUCCESS) {
		fprintf(stderr, "Invalid command-line argument at index %d: %s\n", res,
				argv[res]);
		return EXIT_FAILURE;
	}

	if (ValidateInfix(tokens, tokenCount) != EXIT_SUCCESS) {
		return EXIT_FAILURE;
	}

	int postfixCount = InfixToPostfix(tokens, postfix, tokenCount);

	if (postfixCount < 0) {
		return EXIT_FAILURE;
	}

	double result;

	if (EvaluatePostfix(postfix, postfixCount, &result) != EXIT_SUCCESS) {
		return EXIT_FAILURE;
	}

	printf("%.15g\n", result);

	return EXIT_SUCCESS;
}
