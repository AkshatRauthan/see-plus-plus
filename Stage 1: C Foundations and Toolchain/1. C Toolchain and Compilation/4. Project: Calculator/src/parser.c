
#include <stdio.h>
#include <stdlib.h>

#include "../include/parser.h"

static int getPrecedence(OperatorType op) {
	switch (op) {
	case OP_ADD:
	case OP_SUBTRACT:
		return 1;

	case OP_MULTIPLY:
	case OP_DIVIDE:
	case OP_FLOOR:
	case OP_MODULO:
		return 2;

	case OP_POWER:
		return 3;

	case OP_FACTORIAL:
		return 4;

	default:
		return -1;
	}
}

static int isOpeningBracket(BracketType type) {
	return type == ROUND_BRACKETS_OPEN || type == CURLY_BRACKETS_OPEN ||
		   type == SQUARE_BRACKETS_OPEN;
}

static int isClosingBracket(BracketType type) {
	return type == ROUND_BRACKETS_CLOSE || type == CURLY_BRACKETS_CLOSE ||
		   type == SQUARE_BRACKETS_CLOSE;
}

static int bracketsMatch(BracketType open, BracketType close) {
	return (open == ROUND_BRACKETS_OPEN && close == ROUND_BRACKETS_CLOSE) ||
		   (open == CURLY_BRACKETS_OPEN && close == CURLY_BRACKETS_CLOSE) ||
		   (open == SQUARE_BRACKETS_OPEN && close == SQUARE_BRACKETS_CLOSE);
}

static int isRightAssociative(OperatorType op) { return op == OP_POWER; }

static int shouldPop(OperatorType stackOp, OperatorType currentOp) {
	int stackPrecedence = getPrecedence(stackOp);
	int currentPrecedence = getPrecedence(currentOp);

	return stackPrecedence > currentPrecedence ||
		   (stackPrecedence == currentPrecedence &&
			!isRightAssociative(currentOp));
}

int ValidateInfix(const Token *infix, int tokenCount) {
	if (infix == NULL || tokenCount <= 0) {
		return EXIT_FAILURE;
	}

	enum { EXPECT_OPERAND, EXPECT_OPERATOR } state = EXPECT_OPERAND;

	Stack brackets = createStack(tokenCount);
	int foundOperand = 0;

	for (int i = 0; i < tokenCount; i++) {
		Token curr = infix[i];

		if (curr.type == TOKEN_END) {
			if (i != tokenCount - 1 || state != EXPECT_OPERATOR) {
				fprintf(stderr, "Syntax Error: Unexpected end of expression\n");
				goto validation_error;
			}

			break;
		}

		switch (curr.type) {
		case TOKEN_OPERAND:
			if (state != EXPECT_OPERAND) {
				fprintf(stderr, "Syntax Error: Unexpected operand '%s'\n",
						curr.symbol);
				goto validation_error;
			}

			state = EXPECT_OPERATOR;
			foundOperand = 1;
			break;

		case TOKEN_OPERATOR:
			if (getPrecedence(curr.operatorType) < 0) {
				fprintf(stderr, "Syntax Error: Invalid operator\n");
				goto validation_error;
			}

			if (curr.operatorType == OP_FACTORIAL) {
				if (state != EXPECT_OPERATOR) {
					fprintf(stderr, "Syntax Error: Misplaced factorial\n");
					goto validation_error;
				}

				break;
			}

			if (state != EXPECT_OPERATOR) {
				fprintf(stderr,
						"Syntax Error: Unexpected binary operator '%s'\n",
						curr.symbol);
				goto validation_error;
			}

			state = EXPECT_OPERAND;
			break;

		case TOKEN_BRACKET:
			if (isOpeningBracket(curr.bracketType)) {
				if (state != EXPECT_OPERAND) {
					fprintf(stderr,
							"Syntax Error: Unexpected opening bracket\n");
					goto validation_error;
				}

				push(&brackets, curr);
				break;
			}

			if (!isClosingBracket(curr.bracketType)) {
				fprintf(stderr, "Syntax Error: Invalid bracket\n");
				goto validation_error;
			}

			if (state != EXPECT_OPERATOR || isEmpty(&brackets)) {
				fprintf(stderr,
						"Syntax Error: Unexpected closing bracket '%s'\n",
						curr.symbol);
				goto validation_error;
			}

			if (!bracketsMatch(top(&brackets).bracketType, curr.bracketType)) {
				fprintf(stderr, "Syntax Error: Mismatched brackets\n");
				goto validation_error;
			}

			pop(&brackets);
			break;

		default:
			fprintf(stderr, "Syntax Error: Unknown token encountered\n");
			goto validation_error;
		}
	}

	if (!foundOperand || state != EXPECT_OPERATOR || !isEmpty(&brackets)) {
		fprintf(stderr, "Syntax Error: Incomplete expression\n");
		goto validation_error;
	}

	freeStack(&brackets);
	return EXIT_SUCCESS;

validation_error:
	freeStack(&brackets);
	return EXIT_FAILURE;
}

int InfixToPostfix(const Token *infix, Token *postfix, int tokenCount) {
	if (infix == NULL || postfix == NULL || tokenCount <= 0) {
		return -1;
	}

	if (ValidateInfix(infix, tokenCount) != EXIT_SUCCESS) {
		return -1;
	}

	Stack operators = createStack(tokenCount);
	int outIdx = 0;
	int foundEnd = 0;

	for (int i = 0; i < tokenCount; i++) {
		Token curr = infix[i];

		if (curr.type == TOKEN_END) {
			foundEnd = 1;
			break;
		}

		switch (curr.type) {
		case TOKEN_OPERAND:
			postfix[outIdx++] = curr;
			break;

		case TOKEN_OPERATOR:
			if (getPrecedence(curr.operatorType) < 0) {
				fprintf(stderr, "Syntax Error: Invalid operator\n");
				goto syntax_error;
			}

			// Factorial is a postfix unary operator.
			if (curr.operatorType == OP_FACTORIAL) {
				postfix[outIdx++] = curr;
				break;
			}

			while (!isEmpty(&operators)) {
				Token stackTop = top(&operators);

				if (stackTop.type != TOKEN_OPERATOR ||
					!shouldPop(stackTop.operatorType, curr.operatorType)) {
					break;
				}

				postfix[outIdx++] = pop(&operators);
			}

			push(&operators, curr);
			break;

		case TOKEN_BRACKET:
			if (isOpeningBracket(curr.bracketType)) {
				push(&operators, curr);
				break;
			}

			if (!isClosingBracket(curr.bracketType)) {
				fprintf(stderr, "Syntax Error: Invalid bracket\n");
				goto syntax_error;
			}

			int foundMatchingOpen = 0;

			while (!isEmpty(&operators)) {
				Token stackTop = pop(&operators);

				if (stackTop.type == TOKEN_BRACKET) {
					if (bracketsMatch(stackTop.bracketType, curr.bracketType)) {
						foundMatchingOpen = 1;
						break;
					}

					fprintf(stderr,
							"Syntax Error: Mismatched brackets '%s' and '%s'\n",
							stackTop.symbol, curr.symbol);
					goto syntax_error;
				}

				if (stackTop.type != TOKEN_OPERATOR) {
					fprintf(stderr, "Syntax Error: Invalid stack token\n");
					goto syntax_error;
				}

				postfix[outIdx++] = stackTop;
			}

			if (!foundMatchingOpen) {
				fprintf(stderr,
						"Syntax Error: Unmatched closing bracket '%s'\n",
						curr.symbol);
				goto syntax_error;
			}
			break;

		default:
			fprintf(stderr, "Syntax Error: Unknown token encountered\n");
			goto syntax_error;
		}
	}

	// Pop remaining operators.
	while (!isEmpty(&operators)) {
		Token stackTop = pop(&operators);

		if (stackTop.type == TOKEN_BRACKET) {
			fprintf(stderr, "Syntax Error: Unclosed opening bracket '%s'\n",
					stackTop.symbol);
			goto syntax_error;
		}

		if (stackTop.type != TOKEN_OPERATOR) {
			fprintf(stderr, "Syntax Error: Invalid stack token\n");
			goto syntax_error;
		}

		postfix[outIdx++] = stackTop;
	}

	// Append TOKEN_END if the input uses a terminator.
	if (foundEnd) {
		Token endToken = {0};
		endToken.type = TOKEN_END;
		endToken.operatorType = OP_INVALID;
		endToken.bracketType = BRACKET_INVALID;

		postfix[outIdx] = endToken;
	}

	freeStack(&operators);
	return outIdx;

syntax_error:
	freeStack(&operators);
	return -1;
}
