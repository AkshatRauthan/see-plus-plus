#include "../include/lexer.h"
#include "test_common.h"

static int testIntegerOperand(void) {
	const char *argv[] = {"calc", "42"};
	Token tokens[1];

	CHECK(ParseTokens(2, argv, tokens) == EXIT_SUCCESS);
	CHECK(tokens[0].type == TOKEN_OPERAND);
	CHECK_NEAR(tokens[0].value, 42.0, 1e-9);

	return EXIT_SUCCESS;
}

static int testFloatOperand(void) {
	const char *argv[] = {"calc", "3.14"};
	Token tokens[1];

	CHECK(ParseTokens(2, argv, tokens) == EXIT_SUCCESS);
	CHECK(tokens[0].type == TOKEN_OPERAND);
	CHECK_NEAR(tokens[0].value, 3.14, 1e-9);

	return EXIT_SUCCESS;
}

static int testNegativeOperand(void) {
	const char *argv[] = {"calc", "-5.0"};
	Token tokens[1];

	CHECK(ParseTokens(2, argv, tokens) == EXIT_SUCCESS);
	CHECK(tokens[0].type == TOKEN_OPERAND);
	CHECK_NEAR(tokens[0].value, -5.0, 1e-9);

	return EXIT_SUCCESS;
}

static int testOperators(void) {
	const char *operators[] = {"+", "-", "*", "/", "//", "%", "^", "!"};

	const OperatorType expected[] = {OP_ADD,	OP_SUBTRACT, OP_MULTIPLY,
									 OP_DIVIDE, OP_FLOOR,	 OP_MODULO,
									 OP_POWER,	OP_FACTORIAL};

	for (int i = 0; i < 8; i++) {
		const char *argv[] = {"calc", operators[i]};
		Token tokens[1];

		CHECK(ParseTokens(2, argv, tokens) == EXIT_SUCCESS);
		CHECK(tokens[0].type == TOKEN_OPERATOR);
		CHECK(tokens[0].operatorType == expected[i]);
	}

	return EXIT_SUCCESS;
}

static int testBrackets(void) {
	const char *brackets[] = {"(", ")", "[", "]", "{", "}"};

	const BracketType expected[] = {ROUND_BRACKETS_OPEN,  ROUND_BRACKETS_CLOSE,
									SQUARE_BRACKETS_OPEN, SQUARE_BRACKETS_CLOSE,
									CURLY_BRACKETS_OPEN,  CURLY_BRACKETS_CLOSE};

	for (int i = 0; i < 6; i++) {
		const char *argv[] = {"calc", brackets[i]};
		Token tokens[1];

		CHECK(ParseTokens(2, argv, tokens) == EXIT_SUCCESS);
		CHECK(tokens[0].type == TOKEN_BRACKET);
		CHECK(tokens[0].bracketType == expected[i]);
	}

	return EXIT_SUCCESS;
}

static int testInvalidArgument(void) {
	const char *argv[] = {"calc", "@"};
	Token tokens[1];

	CHECK(ParseTokens(2, argv, tokens) == 1);

	return EXIT_SUCCESS;
}

int main(void) {
	RUN_TEST(testIntegerOperand);
	RUN_TEST(testFloatOperand);
	RUN_TEST(testNegativeOperand);
	RUN_TEST(testOperators);
	RUN_TEST(testBrackets);
	RUN_TEST(testInvalidArgument);

	return EXIT_SUCCESS;
}
