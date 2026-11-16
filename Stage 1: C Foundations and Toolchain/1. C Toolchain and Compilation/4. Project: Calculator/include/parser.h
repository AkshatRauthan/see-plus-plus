#ifndef PARSER_H
#define PARSER_H

#include "./stack.h"

int ValidateInfix(const Token *infix, int tokenCount);
int InfixToPostfix(const Token *infix, Token *postfix, int tokenCount);

#endif
