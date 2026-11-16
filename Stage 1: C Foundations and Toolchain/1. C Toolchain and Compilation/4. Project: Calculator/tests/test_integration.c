#include "../include/evaluator.h"
#include "../include/lexer.h"
#include "../include/parser.h"
#include "test_common.h"

static int evaluateExpression(int argc, const char *argv[], double *result) {
	int tokenCount = argc - 1;

	Token tokens[tokenCount];
	Token postfix[tokenCount + 1];

	if (ParseTokens(argc, argv, tokens) != EXIT_SUCCESS) {
		return EXIT_FAILURE;
	}

	if (ValidateInfix(tokens, tokenCount) != EXIT_SUCCESS) {
		return EXIT_FAILURE;
	}

	int postfixCount = InfixToPostfix(tokens, postfix, tokenCount);

	if (postfixCount < 0) {
		return EXIT_FAILURE;
	}

	return EvaluatePostfix(postfix, postfixCount, result);
}

static int testSimpleExpression(void) {
	const char *argv[] = {"calc", "5", "+", "3"};

	double result;

	CHECK(evaluateExpression(4, argv, &result) == EXIT_SUCCESS);
	CHECK_NEAR(result, 8, 1e-9);

	return EXIT_SUCCESS;
}

static int testOperatorPrecedence(void) {
	const char *argv[] = {"calc", "5", "+", "3", "*", "2"};

	double result;

	CHECK(evaluateExpression(6, argv, &result) == EXIT_SUCCESS);
	CHECK_NEAR(result, 11, 1e-9);

	return EXIT_SUCCESS;
}

static int testNestedBrackets(void) {
	const char *argv[] = {"calc", "(", "5", "+", "3", ")", "*", "2"};

	double result;

	CHECK(evaluateExpression(8, argv, &result) == EXIT_SUCCESS);
	CHECK_NEAR(result, 16, 1e-9);

	return EXIT_SUCCESS;
}

static int testRightAssociativePower(void) {
	const char *argv[] = {"calc", "2", "^", "3", "^", "2"};

	double result;

	CHECK(evaluateExpression(6, argv, &result) == EXIT_SUCCESS);
	CHECK_NEAR(result, 512, 1e-9);

	return EXIT_SUCCESS;
}

static int testFactorialExpression(void) {
	const char *argv[] = {"calc", "5", "!", "+", "3"};

	double result;

	CHECK(evaluateExpression(5, argv, &result) == EXIT_SUCCESS);
	CHECK_NEAR(result, 123, 1e-9);

	return EXIT_SUCCESS;
}

static int testFloorDivision(void) {
	const char *argv[] = {"calc", "10", "//", "3"};

	double result;

	CHECK(evaluateExpression(4, argv, &result) == EXIT_SUCCESS);
	CHECK_NEAR(result, 3, 1e-9);

	return EXIT_SUCCESS;
}

static int testModulo(void) {
	const char *argv[] = {"calc", "10", "%", "3"};

	double result;

	CHECK(evaluateExpression(4, argv, &result) == EXIT_SUCCESS);
	CHECK_NEAR(result, 1, 1e-9);

	return EXIT_SUCCESS;
}

static int testInvalidExpression(void) {
	const char *argv[] = {"calc", "5", "+", "*", "3"};

	double result;

	CHECK(evaluateExpression(5, argv, &result) == EXIT_FAILURE);

	return EXIT_SUCCESS;
}

static int testMismatchedBrackets(void) {
	const char *argv[] = {"calc", "(", "5", "+", "3", "]"};

	double result;

	CHECK(evaluateExpression(6, argv, &result) == EXIT_FAILURE);

	return EXIT_SUCCESS;
}

int main(void) {
	RUN_TEST(testSimpleExpression);
	RUN_TEST(testOperatorPrecedence);
	RUN_TEST(testNestedBrackets);
	RUN_TEST(testRightAssociativePower);
	RUN_TEST(testFactorialExpression);
	RUN_TEST(testFloorDivision);
	RUN_TEST(testModulo);
	RUN_TEST(testInvalidExpression);
	RUN_TEST(testMismatchedBrackets);

	return EXIT_SUCCESS;
}
