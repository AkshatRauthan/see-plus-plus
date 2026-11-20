#include "../include/file_operations.h"

#include <errno.h>

/*
 * Opens a file using the specified access mode.
 *
 * Common modes:
 *
 * "r"  - Open an existing file for reading.
 * "w"  - Open a file for writing, replacing its contents.
 * "a"  - Open a file for appending.
 * "r+" - Open an existing file for reading and writing.
 * "w+" - Open a file for reading and writing, replacing its contents.
 * "a+" - Open a file for reading and appending.
 *
 * The binary equivalents add a 'b':
 * "rb", "wb", "ab", and so on.
 */
FILE *file_open(const char *path, const char *mode) {
	// Validate the arguments before calling fopen().
	if (path == NULL || mode == NULL) {
		errno = EINVAL;
		return NULL;
	}

	// fopen() returns a FILE pointer on success or NULL on failure.
	return fopen(path, mode);
}

/*
 * Closes an open file and releases its associated resources.
 *
 * fclose() also flushes buffered output before closing.
 */
int file_close(FILE *file) {
	if (file == NULL) {
		errno = EINVAL;
		return -1;
	}

	return fclose(file) == 0 ? 0 : -1;
}
