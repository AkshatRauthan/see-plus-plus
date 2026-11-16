#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "../include/evaluator.h"

static int calculateFactorial(double operand, double *result) {
	if (!isfinite(operand) || operand < 0.0 || floor(operand) != operand) {
		fprintf(stderr, "Invalid factorial operand\n");
		return EXIT_FAILURE;
	}

	double factorial = 1.0;

	for (double i = 2.0; i <= operand; i += 1.0) {
		factorial *= i;

		if (!isfinite(factorial)) {
			fprintf(stderr, "Factorial overflow\n");
			return EXIT_FAILURE;
		}
	}

	*result = factorial;
	return EXIT_SUCCESS;
}

static int calculateBinary(OperatorType op, double lhs, double rhs,
						   double *result) {
	switch (op) {
	case OP_ADD:
		*result = lhs + rhs;
		break;

	case OP_SUBTRACT:
		*result = lhs - rhs;
		break;

	case OP_MULTIPLY:
		*result = lhs * rhs;
		break;

	case OP_DIVIDE:
		if (rhs == 0.0) {
			fprintf(stderr, "Division by zero\n");
			return EXIT_FAILURE;
		}

		*result = lhs / rhs;
		break;

	case OP_FLOOR:
		if (rhs == 0.0) {
			fprintf(stderr, "Floor division by zero\n");
			return EXIT_FAILURE;
		}

		*result = floor(lhs / rhs);
		break;

	case OP_MODULO:
		if (rhs == 0.0) {
			fprintf(stderr, "Modulo by zero\n");
			return EXIT_FAILURE;
		}

		*result = fmod(lhs, rhs);
		break;

	case OP_POWER:
		*result = pow(lhs, rhs);
		break;

	default:
		fprintf(stderr, "Invalid binary operator\n");
		return EXIT_FAILURE;
	}

	if (!isfinite(*result)) {
		fprintf(stderr, "Invalid or out-of-range operation\n");
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

int EvaluatePostfix(const Token *postfix, int tokenCount, double *result) {
	if (postfix == NULL || result == NULL || tokenCount <= 0) {
		fprintf(stderr, "Invalid evaluator arguments\n");
		return EXIT_FAILURE;
	}

	Stack values = createStack(tokenCount);

	for (int i = 0; i < tokenCount; i++) {
		Token curr = postfix[i];

		if (curr.type == TOKEN_END) {
			break;
		}

		if (curr.type == TOKEN_OPERAND) {
			push(&values, curr);
			continue;
		}

		if (curr.type != TOKEN_OPERATOR) {
			fprintf(stderr, "Invalid token in postfix expression\n");
			goto evaluation_error;
		}

		double operationResult;

		if (curr.operatorType == OP_FACTORIAL) {
			if (isEmpty(&values)) {
				fprintf(stderr, "Missing operand for factorial\n");
				goto evaluation_error;
			}

			double operand = pop(&values).value;

			if (calculateFactorial(operand, &operationResult) != EXIT_SUCCESS) {
				goto evaluation_error;
			}
		} else {
			if (values.top < 1) {
				fprintf(stderr, "Insufficient operands for binary operator\n");
				goto evaluation_error;
			}

			double rhs = pop(&values).value;
			double lhs = pop(&values).value;

			if (calculateBinary(curr.operatorType, lhs, rhs,
								&operationResult) != EXIT_SUCCESS) {
				goto evaluation_error;
			}
		}

		Token output = {0};
		output.type = TOKEN_OPERAND;
		output.value = operationResult;
		output.operatorType = OP_INVALID;
		output.bracketType = BRACKET_INVALID;

		push(&values, output);
	}

	if (values.top != 0) {
		fprintf(stderr, "Invalid postfix expression\n");
		goto evaluation_error;
	}

	*result = pop(&values).value;
	freeStack(&values);

	return EXIT_SUCCESS;

evaluation_error:
	freeStack(&values);
	return EXIT_FAILURE;
}
