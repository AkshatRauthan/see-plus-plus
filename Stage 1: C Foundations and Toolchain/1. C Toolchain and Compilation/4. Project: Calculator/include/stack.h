#ifndef STACK_H
#define STACK_H

#include "./lexer.h"

typedef struct {
	int top;
	int capacity;
	Token *tokens;
} Stack;

Token pop(Stack *st);
Token top(Stack *st);
void freeStack(Stack *st);
int isEmpty(const Stack *st);
void push(Stack *st, Token token);

Stack createStack(int capacity);

#endif
