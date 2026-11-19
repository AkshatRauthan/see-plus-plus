#include "../include/parser.h"

#include <math.h>
#include <errno.h>
#include <float.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>

static int getRequiredWidth(intmax_t value) {
	if (value >= INT8_MIN && value <= INT8_MAX)
		return 8;

	if (value >= INT16_MIN && value <= INT16_MAX)
		return 16;

	if (value >= INT32_MIN && value <= INT32_MAX)
		return 32;

	return 64;
}

static int getRequiredUnsignedWidth(uintmax_t value) {
	if (value <= UINT8_MAX)
		return 8;

	if (value <= UINT16_MAX)
		return 16;

	if (value <= UINT32_MAX)
		return 32;

	return 64;
}

int ParseInteger(const char *ch, Integer *number, int isSigned) {
	if (ch == NULL || number == NULL) {
		fprintf(stderr, "Invalid argument: ch or number is NULL\n");
		return -1;
	}

	if (isSigned == 1) {
		char *end;
		errno = 0;
		intmax_t temp = strtoimax(ch, &end, 10);
		if (errno == ERANGE || end == ch || *end != '\0') {
			fprintf(stderr, "Invalid signed integer input\n");
			return -1;
		}

		int width = getRequiredWidth(temp);
		snprintf(number->input, sizeof number->input, "%s", ch);
		number->isSigned = 1;
		number->width = width;
		switch (width) {
		case 8:
			number->type = INT_8;
			number->value.i8 = (int8_t)temp;
			break;

		case 16:
			number->type = INT_16;
			number->value.i16 = (int16_t)temp;
			break;

		case 32:
			number->type = INT_32;
			number->value.i32 = (int32_t)temp;
			break;

		case 64:
			number->type = INT_64;
			number->value.i64 = (int64_t)temp;
			break;
		}

		return 0;
	} else if (isSigned == 0) {
		if (ch[0] == '-') {
			fprintf(stderr,
					"Negative input is invalid for unsigned integers\n");
			return -1;
		}

		char *end;
		errno = 0;
		uintmax_t temp = strtoumax(ch, &end, 10);
		if (errno == ERANGE || end == ch || *end != '\0') {
			fprintf(stderr, "Invalid unsigned integer input\n");
			return -1;
		}

		int width = getRequiredUnsignedWidth(temp);
		snprintf(number->input, sizeof number->input, "%s", ch);
		number->isSigned = 0;
		number->width = width;
		switch (width) {
		case 8:
			number->type = UINT_8;
			number->value.u8 = (uint8_t)temp;
			break;

		case 16:
			number->type = UINT_16;
			number->value.u16 = (uint16_t)temp;
			break;

		case 32:
			number->type = UINT_32;
			number->value.u32 = (uint32_t)temp;
			break;

		case 64:
			number->type = UINT_64;
			number->value.u64 = (uint64_t)temp;
			break;
		}

		return 0;
	} else {
		fprintf(stderr, "Invalid input in parameter [bool isSigned]: %d\n",
				isSigned);
		return -1;
	}
}

int ParseFloat(const char *input, Floating *number) {
	if (input == NULL || number == NULL)
		return -1;

	char *end;
	errno = 0;

	float temp = strtof(input, &end);

	if (errno == ERANGE || end == input || *end != '\0' || !isfinite(temp)) {
		fprintf(stderr, "Invalid float input\n");
		return -1;
	}

	snprintf(number->input, sizeof number->input, "%s", input);

	number->width = 32;
	number->type = FLOAT_32;
	number->value.f32 = temp;

	return 0;
}

int ParseDouble(const char *input, Floating *number) {
	if (input == NULL || number == NULL)
		return -1;

	char *end;
	errno = 0;

	double temp = strtod(input, &end);

	if (errno == ERANGE || end == input || *end != '\0' || !isfinite(temp)) {
		fprintf(stderr, "Invalid double input\n");
		return -1;
	}

	snprintf(number->input, sizeof number->input, "%s", input);

	number->width = 64;
	number->type = FLOAT_64;
	number->value.f64 = temp;

	return 0;
}
