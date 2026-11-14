#include "../include/calculator.h"

float sum(float a, float b) { return a + b; }

float subtraction(float a, float b) { return a - b; }

float product(float a, float b) { return a * b; }

float divison(float a, float b) { return a / b; }

float power(float a, int b) {
	if (b == 0) {
		return 1;
	}
	float ans = a;
	while (--b)
		ans *= a;
	return ans;
}
