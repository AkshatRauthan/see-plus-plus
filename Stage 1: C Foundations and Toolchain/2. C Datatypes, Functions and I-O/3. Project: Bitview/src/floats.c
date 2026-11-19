#include "../include//floats.h"

#include <stdint.h>
#include <string.h>

static const char *const FLOAT_TYPE_NAMES[] = {
    "float",
    "double"
};

const char *FloatingTypeName(FloatingType type) {
    if ((unsigned)type >=
        sizeof FLOAT_TYPE_NAMES / sizeof FLOAT_TYPE_NAMES[0])
        return "unknown";

    return FLOAT_TYPE_NAMES[type];
}

uint64_t GetFloatingBits(const Floating *number) {
    if (number == NULL)
        return 0;

    uint64_t bits = 0;

    switch (number->type) {
        case FLOAT_32: {
            uint32_t temp;
            memcpy(&temp, &number->value.f32, sizeof temp);
            bits = temp;
            break;
        }

        case FLOAT_64:
            memcpy(&bits, &number->value.f64, sizeof bits);
            break;
    }

    return bits;
}
