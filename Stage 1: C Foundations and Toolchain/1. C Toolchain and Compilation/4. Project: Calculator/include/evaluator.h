#ifndef EVALUATOR_H
#define EVALUATOR_H

#include "./stack.h"

// Returns EXIT_SUCCESS on success, EXIT_FAILURE on evaluation error.
// Stores the final result in *result.
int EvaluatePostfix(const Token *postfix, int tokenCount, double *result);

#endif
