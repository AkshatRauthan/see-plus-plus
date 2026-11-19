#ifndef INTEGER_H
#define INTEGER_H

#include "floats.h"
#include "integers.h"

int ParseInteger(const char *ch, Integer *number, int isSigned);
int ParseFloat(const char *input, Floating *number);
int ParseDouble(const char *input, Floating *number);

#endif
