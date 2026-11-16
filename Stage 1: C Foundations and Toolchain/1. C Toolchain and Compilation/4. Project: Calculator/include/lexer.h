#ifndef LEXER_H
#define LEXER_H

typedef enum {
	TOKEN_END,
	TOKEN_OPERAND,
	TOKEN_BRACKET,
	TOKEN_OPERATOR,
} TokenType;

typedef enum {
	BRACKET_INVALID = -1,
	ROUND_BRACKETS_OPEN,
	CURLY_BRACKETS_OPEN,
	SQUARE_BRACKETS_OPEN,
	ROUND_BRACKETS_CLOSE,
	CURLY_BRACKETS_CLOSE,
	SQUARE_BRACKETS_CLOSE,
} BracketType;

typedef enum {
	OP_INVALID = -1,
	OP_ADD,
	OP_SUBTRACT,
	OP_MULTIPLY,
	OP_DIVIDE,
	OP_FLOOR,
	OP_MODULO,
	OP_POWER,
	OP_FACTORIAL
} OperatorType;

typedef struct {
	char symbol[4]; // Used when type == TOKEN_OPERATOR or TOKEN_BRACKET
	double value;	// Used when type == TOKEN_OPERAND
	TokenType type;
	BracketType bracketType;
	OperatorType operatorType;
} Token;

int ParseTokens(const int len, const char *ch[], Token *tokenArray);

#endif
