#include "../include/file_operations.h"

#include <errno.h>
#include <stdio.h>

/*
 * Reads binary data into a buffer.
 *
 * Unlike text reading, binary reading does not append a null
 * terminator. The returned byte count describes the data length.
 */
int read_binary_file(
    const char *path,
    void *buffer,
    size_t capacity,
    size_t *bytes_read
) {
    if (path == NULL || buffer == NULL ||
        capacity == 0 || bytes_read == NULL) {
        errno = EINVAL;
        return -1;
    }

    *bytes_read = 0;

    FILE *file = fopen(path, "rb");

    if (file == NULL) {
        return -1;
    }

    size_t count = fread(buffer, 1, capacity, file);

    if (ferror(file)) {
        fclose(file);
        return -1;
    }

    /*
     * When the buffer is completely filled, check whether
     * additional bytes remain in the file.
     */
    if (count == capacity) {
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

    *bytes_read = count;

    if (fclose(file) != 0) {
        return -1;
    }

    return 0;
}

/*
 * Writes binary data to a file.
 *
 * The "wb" mode creates the file or truncates an existing file.
 */
int write_binary_file(
    const char *path,
    const void *data,
    size_t size
) {
    if (path == NULL || (data == NULL && size != 0)) {
        errno = EINVAL;
        return -1;
    }

    FILE *file = fopen(path, "wb");

    if (file == NULL) {
        return -1;
    }

    /*
     * fwrite() returns the number of elements written.
     * Since each element is one byte, the result is a byte count.
     */
    if (size > 0 && fwrite(data, 1, size, file) != size) {
        fclose(file);
        return -1;
    }

    if (fclose(file) != 0) {
        return -1;
    }

    return 0;
}

/*
 * Copies a file using a fixed-size buffer.
 *
 * Reading and writing in chunks avoids loading the entire
 * source file into memory.
 */
int copy_file(const char *source, const char *destination) {
    if (source == NULL || destination == NULL) {
        errno = EINVAL;
        return -1;
    }

    FILE *input = fopen(source, "rb");

    if (input == NULL) {
        return -1;
    }

    FILE *output = fopen(destination, "wb");

    if (output == NULL) {
        fclose(input);
        return -1;
    }

    unsigned char buffer[4096];
    int status = 0;

    while (1) {
        // Read up to one buffer of data.
        size_t bytes_read = fread(buffer, 1, sizeof(buffer), input);

        // Write every byte that was successfully read.
        if (bytes_read > 0) {
            size_t bytes_written = fwrite(buffer, 1, bytes_read, output);

            if (bytes_written != bytes_read) {
                status = -1;
                break;
            }
        }

        // Check for a reading error.
        if (ferror(input)) {
            status = -1;
            break;
        }

        // A short read without an error indicates end-of-file.
        if (feof(input)) {
            break;
        }
    }

    // Closing the output also flushes its buffered data.
    if (fclose(output) != 0) {
        status = -1;
    }

    if (fclose(input) != 0) {
        status = -1;
    }

    return status;
}
