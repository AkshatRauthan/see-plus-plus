#include "../include/file_operations.h"

#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>

/*
 * Writes all requested bytes to a stream.
 *
 * fwrite() may write fewer bytes than requested.
 * This function continues writing until all bytes are written
 * or an error occurs.
 *
 * Returns:
 *    0 on success.
 *   -1 on failure.
 */
static int write_all(
    FILE *file,
    const unsigned char *buffer,
    size_t size
) {
    size_t total_written = 0;

    while (total_written < size) {
        size_t written = fwrite(
            buffer + total_written,
            1,
            size - total_written,
            file
        );

        total_written += written;

        if (written == 0) {
            if (ferror(file)) {
                return -1;
            }

            errno = EIO;
            return -1;
        }
    }

    return 0;
}

/*
 * Copies a file using a fixed-size buffer.
 *
 * The source is opened in binary read mode and the destination
 * in binary write mode.
 *
 * Reading and writing in chunks avoids loading the entire file
 * into memory.
 *
 * Existing destination contents are overwritten.
 *
 * The source and destination must refer to different files.
 *
 * Returns:
 *    0 on success.
 *   -1 on failure.
 */
int copy_file(const char *source, const char *destination) {
    if (source == NULL || destination == NULL) {
        errno = EINVAL;
        return -1;
    }

    /*
     * Reject identical path strings before opening the destination.
     */
    if (strcmp(source, destination) == 0) {
        errno = EINVAL;
        return -1;
    }

    /*
     * Detect existing paths referring to the same underlying file.
     *
     * This catches hard links and symbolic links resolving
     * to the same file.
     */
    struct stat source_info;
    struct stat destination_info;

    if (stat(source, &source_info) == 0 &&
        stat(destination, &destination_info) == 0) {

        if (source_info.st_dev == destination_info.st_dev &&
            source_info.st_ino == destination_info.st_ino) {
            errno = EINVAL;
            return -1;
        }
    }

    // Open the source for binary reading.
    FILE *input = fopen(source, "rb");

    if (input == NULL) {
        return -1;
    }

    // Create or overwrite the destination.
    FILE *output = fopen(destination, "wb");

    if (output == NULL) {
        int saved_errno = errno;
        fclose(input);
        errno = saved_errno;
        return -1;
    }

    unsigned char buffer[4096];

    int status = 0;
    int saved_errno = 0;

    while (1) {
        /*
         * Read up to 4096 bytes.
         *
         * fread() returns the number of bytes successfully read
         * because the element size is one byte.
         */
        size_t bytes_read = fread(buffer, 1, sizeof(buffer), input);

        // Write every byte obtained from the current read.
        if (bytes_read > 0) {
            if (write_all(output, buffer, bytes_read) != 0) {
                status = -1;
                saved_errno = errno;
                break;
            }
        }

        // Detect source read errors.
        if (ferror(input)) {
            status = -1;
            saved_errno = errno != 0 ? errno : EIO;
            break;
        }

        // EOF means the complete source has been read.
        if (feof(input)) {
            break;
        }

        /*
         * A zero-byte read without EOF or an error must not
         * cause an infinite loop.
         */
        if (bytes_read == 0) {
            status = -1;
            saved_errno = EIO;
            break;
        }
    }

    /*
     * fclose() flushes buffered output.
     * It can report delayed write failures.
     */
    if (fclose(output) != 0 && status == 0) {
        status = -1;
        saved_errno = errno != 0 ? errno : EIO;
    }

    if (fclose(input) != 0 && status == 0) {
        status = -1;
        saved_errno = errno != 0 ? errno : EIO;
    }

    if (status != 0) {
        errno = saved_errno != 0 ? saved_errno : EIO;
        return -1;
    }

    return 0;
}
