#include <stdio.h>
#include <stdlib.h>

#include "../include/stack.h"

Stack createStack(int capacity) {
	if (capacity <= 0) {
		fprintf(stderr, "Invalid Stack Capacity\n");
		exit(EXIT_FAILURE);
	}

	Stack st;
	st.top = -1;
	st.capacity = capacity;
	st.tokens = malloc(sizeof(Token) * capacity);

	if (st.tokens == NULL) {
		perror("Failed To Allocate Stack");
		exit(EXIT_FAILURE);
	}

	return st;
}

void push(Stack *st, Token token) {
	if (st->top + 1 >= st->capacity) {
		fprintf(stderr, "Stack Overflow\n");
		exit(EXIT_FAILURE);
	}

	st->tokens[++st->top] = token;
}

Token pop(Stack *st) {
	if (isEmpty(st)) {
		fprintf(stderr, "Stack Underflow\n");
		exit(EXIT_FAILURE);
	}

	return st->tokens[st->top--];
}

Token top(Stack *st) {
	if (isEmpty(st)) {
		fprintf(stderr, "Stack Is Empty\n");
		exit(EXIT_FAILURE);
	}

	return st->tokens[st->top];
}

int isEmpty(const Stack *st) { return st->top == -1; }

void freeStack(Stack *st) {
	if (st != NULL && st->tokens != NULL) {
		free(st->tokens);
		st->tokens = NULL; // Good practice to avoid dangling pointers
		st->top = -1;
		st->capacity = 0;
	}
}
