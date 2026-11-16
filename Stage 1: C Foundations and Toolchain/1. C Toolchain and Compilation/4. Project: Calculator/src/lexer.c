#include "../include/lexer.h"

#include <errno.h>
#include <stdlib.h>
#include <string.h>

int isOperator(const char *ch) {
	if (strcmp(ch, "+") == 0)
		return OP_ADD;
	else if (strcmp(ch, "-") == 0)
		return OP_SUBTRACT;
	else if (strcmp(ch, "*") == 0)
		return OP_MULTIPLY;
	else if (strcmp(ch, "!") == 0)
		return OP_FACTORIAL;
	else if (strcmp(ch, "/") == 0)
		return OP_DIVIDE;
	else if (strcmp(ch, "^") == 0)
		return OP_POWER;
	else if (strcmp(ch, "%") == 0)
		return OP_MODULO;
	else if (strcmp(ch, "//") == 0)
		return OP_FLOOR;
	else
		return OP_INVALID;
}

BracketType isBracket(const char *ch) {
	if (strcmp(ch, "(") == 0)
		return ROUND_BRACKETS_OPEN;
	else if (strcmp(ch, "{") == 0)
		return CURLY_BRACKETS_OPEN;
	else if (strcmp(ch, "[") == 0)
		return SQUARE_BRACKETS_OPEN;
	else if (strcmp(ch, ")") == 0)
		return ROUND_BRACKETS_CLOSE;
	else if (strcmp(ch, "}") == 0)
		return CURLY_BRACKETS_CLOSE;
	else if (strcmp(ch, "]") == 0)
		return SQUARE_BRACKETS_CLOSE;
	else
		return BRACKET_INVALID;
}

int parseDouble(const char *ch, double *num) {
	char *end;
	errno = 0;
	*num = strtod(ch, &end);
	if (ch == end || *end != '\0' || errno == ERANGE) {
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

int parseSingleToken(const char *ch, Token *t) {
	OperatorType operator= isOperator(ch);
	if (operator!= OP_INVALID) {
		t->value = 0.0;
		t->type = TOKEN_OPERATOR;
		t->operatorType = operator;
		strcpy(t->symbol, ch);
		t->bracketType = BRACKET_INVALID;
		return EXIT_SUCCESS;
	}

	BracketType bracket = isBracket(ch);
	if (bracket != BRACKET_INVALID) {
		t->value = 0.0;
		t->type = TOKEN_BRACKET;
		t->bracketType = bracket;
		t->operatorType = OP_INVALID;
		strcpy(t->symbol, ch);
		return EXIT_SUCCESS;
	}

	double num;
	if (parseDouble(ch, &num) == EXIT_SUCCESS) {
		t->value = num;
		t->symbol[0] = '\0';
		t->type = TOKEN_OPERAND;
		t->operatorType = OP_INVALID;
		t->bracketType = BRACKET_INVALID;
		return EXIT_SUCCESS;
	}

	return EXIT_FAILURE;
}

int ParseTokens(int len, const char *ch[], Token *tokens) {
	for (int i = 1; i < len; i++) {
		if (parseSingleToken(ch[i], &tokens[i - 1]) == EXIT_FAILURE) {
			return i;
		}
	}
	return EXIT_SUCCESS;
}
