#ifndef FLOATING_H
#define FLOATING_H

#include <stdint.h>

typedef union {
    float f32;
    double f64;
} FloatingValue;

typedef enum {
    FLOAT_32,
    FLOAT_64
} FloatingType;

typedef struct {
    int width;
    char input[64];
    FloatingType type;
    FloatingValue value;
} Floating;

const char *FloatingTypeName(FloatingType type);
uint64_t GetFloatingBits(const Floating *number);

#endif
