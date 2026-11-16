#ifndef TEST_COMMON_H
#define TEST_COMMON_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define CHECK(condition)                                                       \
	do {                                                                       \
		if (!(condition)) {                                                    \
			fprintf(stderr, "%s:%d: Test failed: %s\n", __FILE__, __LINE__,    \
					#condition);                                               \
			return EXIT_FAILURE;                                               \
		}                                                                      \
	} while (0)

#define CHECK_NEAR(actual, expected, tolerance)                                \
	CHECK(fabs((actual) - (expected)) <= (tolerance))

#define RUN_TEST(test)                                                         \
	do {                                                                       \
		printf("Running %s...\n", #test);                                      \
		if (test() != EXIT_SUCCESS) {                                          \
			fprintf(stderr, "%s FAILED\n", #test);                             \
			return EXIT_FAILURE;                                               \
		}                                                                      \
		printf("%s PASSED\n\n", #test);                                        \
	} while (0)

#endif
