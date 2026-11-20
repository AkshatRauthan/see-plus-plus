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
        int saved_errno = errno != 0 ? errno : EIO;
        fclose(file);
        errno = saved_errno;
        return -1;
    }

    /*
     * If the buffer is full, check whether additional bytes
     * remain in the file.
     */
    if (count == capacity) {
        int next = fgetc(file);

        if (next != EOF) {
            fclose(file);
            errno = ENOBUFS;
            return -1;
        }

        if (ferror(file)) {
            int saved_errno = errno != 0 ? errno : EIO;
            fclose(file);
            errno = saved_errno;
            return -1;
        }
    }

    if (fclose(file) != 0) {
        return -1;
    }

    *bytes_read = count;

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
        int saved_errno = errno != 0 ? errno : EIO;
        fclose(file);
        errno = saved_errno;
        return -1;
    }

    /*
     * fclose() flushes buffered output.
     * Checking its return value detects delayed write errors.
     */
    if (fclose(file) != 0) {
        return -1;
    }

    return 0;
}
