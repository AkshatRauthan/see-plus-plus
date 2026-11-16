#include "../include/parser.h"
#include "test_common.h"

static Token operand(double value) {
	Token token = {0};

	token.type = TOKEN_OPERAND;
	token.value = value;
	token.operatorType = OP_INVALID;
	token.bracketType = BRACKET_INVALID;

	return token;
}

static Token op(OperatorType type) {
	Token token = {0};

	token.type = TOKEN_OPERATOR;
	token.operatorType = type;
	token.bracketType = BRACKET_INVALID;

	return token;
}

static Token bracket(BracketType type) {
	Token token = {0};

	token.type = TOKEN_BRACKET;
	token.bracketType = type;
	token.operatorType = OP_INVALID;

	return token;
}

static int testSimpleExpression(void) {
	Token infix[] = {operand(5), op(OP_ADD), operand(3)};

	CHECK(ValidateInfix(infix, 3) == EXIT_SUCCESS);

	return EXIT_SUCCESS;
}

static int testOperatorPrecedence(void) {
	Token infix[] = {operand(5), op(OP_ADD), operand(3), op(OP_MULTIPLY),
					 operand(2)};

	Token postfix[6];

	CHECK(ValidateInfix(infix, 5) == EXIT_SUCCESS);
	CHECK(InfixToPostfix(infix, postfix, 5) == 5);

	CHECK(postfix[0].type == TOKEN_OPERAND);
	CHECK_NEAR(postfix[0].value, 5, 1e-9);

	CHECK(postfix[1].type == TOKEN_OPERAND);
	CHECK_NEAR(postfix[1].value, 3, 1e-9);

	CHECK(postfix[2].type == TOKEN_OPERAND);
	CHECK_NEAR(postfix[2].value, 2, 1e-9);

	CHECK(postfix[3].operatorType == OP_MULTIPLY);
	CHECK(postfix[4].operatorType == OP_ADD);

	return EXIT_SUCCESS;
}

static int testRightAssociativity(void) {
	Token infix[] = {operand(2), op(OP_POWER), operand(3), op(OP_POWER),
					 operand(2)};

	Token postfix[6];

	CHECK(ValidateInfix(infix, 5) == EXIT_SUCCESS);
	CHECK(InfixToPostfix(infix, postfix, 5) == 5);

	CHECK(postfix[3].operatorType == OP_POWER);
	CHECK(postfix[4].operatorType == OP_POWER);

	return EXIT_SUCCESS;
}

static int testNestedBrackets(void) {
	Token infix[] = {bracket(ROUND_BRACKETS_OPEN),
					 operand(5),
					 op(OP_ADD),
					 bracket(SQUARE_BRACKETS_OPEN),
					 operand(3),
					 op(OP_MULTIPLY),
					 operand(2),
					 bracket(SQUARE_BRACKETS_CLOSE),
					 bracket(ROUND_BRACKETS_CLOSE)};

	Token postfix[10];

	CHECK(ValidateInfix(infix, 9) == EXIT_SUCCESS);
	CHECK(InfixToPostfix(infix, postfix, 9) == 5);

	CHECK(postfix[3].operatorType == OP_MULTIPLY);
	CHECK(postfix[4].operatorType == OP_ADD);

	return EXIT_SUCCESS;
}

static int testFactorial(void) {
	Token infix[] = {operand(5), op(OP_FACTORIAL), op(OP_FACTORIAL)};

	Token postfix[4];

	CHECK(ValidateInfix(infix, 3) == EXIT_SUCCESS);
	CHECK(InfixToPostfix(infix, postfix, 3) == 3);

	CHECK(postfix[1].operatorType == OP_FACTORIAL);
	CHECK(postfix[2].operatorType == OP_FACTORIAL);

	return EXIT_SUCCESS;
}

static int testMissingOperand(void) {
	Token infix[] = {operand(5), op(OP_ADD)};

	CHECK(ValidateInfix(infix, 2) == EXIT_FAILURE);

	return EXIT_SUCCESS;
}

static int testConsecutiveOperators(void) {
	Token infix[] = {operand(5), op(OP_ADD), op(OP_MULTIPLY), operand(3)};

	CHECK(ValidateInfix(infix, 4) == EXIT_FAILURE);

	return EXIT_SUCCESS;
}

static int testAdjacentOperands(void) {
	Token infix[] = {operand(5), operand(3)};

	CHECK(ValidateInfix(infix, 2) == EXIT_FAILURE);

	return EXIT_SUCCESS;
}

static int testEmptyBrackets(void) {
	Token infix[] = {bracket(ROUND_BRACKETS_OPEN),
					 bracket(ROUND_BRACKETS_CLOSE)};

	CHECK(ValidateInfix(infix, 2) == EXIT_FAILURE);

	return EXIT_SUCCESS;
}

static int testMismatchedBrackets(void) {
	Token infix[] = {bracket(ROUND_BRACKETS_OPEN), operand(5),
					 bracket(SQUARE_BRACKETS_CLOSE)};

	CHECK(ValidateInfix(infix, 3) == EXIT_FAILURE);

	return EXIT_SUCCESS;
}

static int testUnclosedBracket(void) {
	Token infix[] = {bracket(ROUND_BRACKETS_OPEN), operand(5)};

	CHECK(ValidateInfix(infix, 2) == EXIT_FAILURE);

	return EXIT_SUCCESS;
}

int main(void) {
	RUN_TEST(testSimpleExpression);
	RUN_TEST(testOperatorPrecedence);
	RUN_TEST(testRightAssociativity);
	RUN_TEST(testNestedBrackets);
	RUN_TEST(testFactorial);
	RUN_TEST(testMissingOperand);
	RUN_TEST(testConsecutiveOperators);
	RUN_TEST(testAdjacentOperands);
	RUN_TEST(testEmptyBrackets);
	RUN_TEST(testMismatchedBrackets);
	RUN_TEST(testUnclosedBracket);

	return EXIT_SUCCESS;
}
