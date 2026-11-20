#include "../include/file_operations.h"

#include <errno.h>
#include <stdio.h>

/*
 * Reads the contents of a text file into a character buffer.
 *
 * The function reserves one byte for the terminating '\0'.
 *
 * If the file does not fit inside the buffer, the operation
 * fails instead of silently returning incomplete contents.
 */
int read_text_file(
    const char *path,
    char *buffer,
    size_t capacity,
    size_t *bytes_read
) {
    if (path == NULL || buffer == NULL ||
        capacity == 0 || bytes_read == NULL) {
        errno = EINVAL;
        return -1;
    }

    *bytes_read = 0;

    // Open in text mode.
    FILE *file = fopen(path, "r");

    if (file == NULL) {
        return -1;
    }

    /*
     * Read at most capacity - 1 characters.
     *
     * fread() returns the number of elements successfully read.
     * Here, each element is one byte.
     */
    size_t count = fread(buffer, 1, capacity - 1, file);

    // Detect errors that occurred during reading.
    if (ferror(file)) {
        fclose(file);
        return -1;
    }

    /*
     * If the buffer was filled, check whether more data remains.
     *
     * This distinguishes a file that exactly fits from one
     * that would overflow the buffer.
     */
    if (count == capacity - 1) {
        int next = fgetc(file);

        if (next != EOF) {
            fclose(file);
            errno = ENOBUFS;
            return -1;
        }

        if (ferror(file)) {
            fclose(file);
            return -1;
        }
    }

    // Add the null terminator required by C strings.
    buffer[count] = '\0';

    *bytes_read = count;

    if (fclose(file) != 0) {
        return -1;
    }

    return 0;
}
