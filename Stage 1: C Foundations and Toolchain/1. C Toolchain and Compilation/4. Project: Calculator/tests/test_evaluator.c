#include "../include/evaluator.h"
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

static int evaluate(const Token *postfix, int count, double expected) {
	double result;

	CHECK(EvaluatePostfix(postfix, count, &result) == EXIT_SUCCESS);
	CHECK_NEAR(result, expected, 1e-9);

	return EXIT_SUCCESS;
}

static int testAddition(void) {
	Token postfix[] = {operand(5), operand(3), op(OP_ADD)};

	return evaluate(postfix, 3, 8);
}

static int testSubtraction(void) {
	Token postfix[] = {operand(5), operand(3), op(OP_SUBTRACT)};

	return evaluate(postfix, 3, 2);
}

static int testMultiplication(void) {
	Token postfix[] = {operand(5), operand(3), op(OP_MULTIPLY)};

	return evaluate(postfix, 3, 15);
}

static int testDivision(void) {
	Token postfix[] = {operand(5), operand(2), op(OP_DIVIDE)};

	return evaluate(postfix, 3, 2.5);
}

static int testFloorDivision(void) {
	Token postfix[] = {operand(7), operand(2), op(OP_FLOOR)};

	return evaluate(postfix, 3, 3);
}

static int testModulo(void) {
	Token postfix[] = {operand(10), operand(3), op(OP_MODULO)};

	return evaluate(postfix, 3, 1);
}

static int testExponentiation(void) {
	Token postfix[] = {operand(2), operand(3), op(OP_POWER)};

	return evaluate(postfix, 3, 8);
}

static int testFactorial(void) {
	Token postfix[] = {operand(5), op(OP_FACTORIAL)};

	return evaluate(postfix, 2, 120);
}

static int testCompoundExpression(void) {
	Token postfix[] = {operand(5), operand(3), operand(2), op(OP_MULTIPLY),
					   op(OP_ADD)};

	return evaluate(postfix, 5, 11);
}

static int testDivisionByZero(void) {
	Token postfix[] = {operand(5), operand(0), op(OP_DIVIDE)};

	double result;

	CHECK(EvaluatePostfix(postfix, 3, &result) == EXIT_FAILURE);

	return EXIT_SUCCESS;
}

static int testModuloByZero(void) {
	Token postfix[] = {operand(5), operand(0), op(OP_MODULO)};

	double result;

	CHECK(EvaluatePostfix(postfix, 3, &result) == EXIT_FAILURE);

	return EXIT_SUCCESS;
}

static int testInvalidFactorial(void) {
	Token postfix[] = {operand(-5), op(OP_FACTORIAL)};

	double result;

	CHECK(EvaluatePostfix(postfix, 2, &result) == EXIT_FAILURE);

	return EXIT_SUCCESS;
}

static int testFractionalFactorial(void) {
	Token postfix[] = {operand(5.5), op(OP_FACTORIAL)};

	double result;

	CHECK(EvaluatePostfix(postfix, 2, &result) == EXIT_FAILURE);

	return EXIT_SUCCESS;
}

static int testFactorialOverflow(void) {
	Token postfix[] = {operand(171), op(OP_FACTORIAL)};

	double result;

	CHECK(EvaluatePostfix(postfix, 2, &result) == EXIT_FAILURE);

	return EXIT_SUCCESS;
}

static int testInsufficientOperands(void) {
	Token postfix[] = {operand(5), op(OP_ADD)};

	double result;

	CHECK(EvaluatePostfix(postfix, 2, &result) == EXIT_FAILURE);

	return EXIT_SUCCESS;
}

static int testExcessOperands(void) {
	Token postfix[] = {operand(5), operand(3)};

	double result;

	CHECK(EvaluatePostfix(postfix, 2, &result) == EXIT_FAILURE);

	return EXIT_SUCCESS;
}

static int testInvalidToken(void) {
	Token postfix[] = {
		operand(5),
		{.type = TOKEN_BRACKET, .bracketType = ROUND_BRACKETS_OPEN}};

	double result;

	CHECK(EvaluatePostfix(postfix, 2, &result) == EXIT_FAILURE);

	return EXIT_SUCCESS;
}

int main(void) {
	RUN_TEST(testAddition);
	RUN_TEST(testSubtraction);
	RUN_TEST(testMultiplication);
	RUN_TEST(testDivision);
	RUN_TEST(testFloorDivision);
	RUN_TEST(testModulo);
	RUN_TEST(testExponentiation);
	RUN_TEST(testFactorial);
	RUN_TEST(testCompoundExpression);
	RUN_TEST(testDivisionByZero);
	RUN_TEST(testModuloByZero);
	RUN_TEST(testInvalidFactorial);
	RUN_TEST(testFractionalFactorial);
	RUN_TEST(testFactorialOverflow);
	RUN_TEST(testInsufficientOperands);
	RUN_TEST(testExcessOperands);
	RUN_TEST(testInvalidToken);

	return EXIT_SUCCESS;
}
