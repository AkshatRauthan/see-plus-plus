#include "../include/file_operations.h"

#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>

/*
 * Prints a hexadecimal and ASCII representation of a file.
 *
 * Each row contains:
 *
 * - An offset showing the position of the first byte.
 * - Up to 16 bytes represented in hexadecimal.
 * - An ASCII representation of printable characters.
 *
 * Non-printable bytes are represented by '.'.
 *
 * The output stream remains open; the caller owns it.
 *
 * Returns:
 *    0 on success.
 *   -1 on failure.
 */
int hexdump_file(const char *path, FILE *output) {
    if (path == NULL || output == NULL) {
        errno = EINVAL;
        return -1;
    }

    FILE *input = fopen(path, "rb");

    if (input == NULL) {
        return -1;
    }

    unsigned char buffer[16];
    uintmax_t offset = 0;

    int status = 0;
    int saved_errno = 0;

    while (1) {
        // Read one row containing up to 16 bytes.
        size_t count = fread(buffer, 1, sizeof(buffer), input);

        if (count == 0) {
            if (ferror(input)) {
                status = -1;
                saved_errno = errno != 0 ? errno : EIO;
            }

            break;
        }

        // Print the offset of the current row.
        if (fprintf(output, "%08" PRIxMAX "  ", offset) < 0) {
            status = -1;
            saved_errno = errno != 0 ? errno : EIO;
            break;
        }

        // Print the hexadecimal representation.
        for (size_t i = 0; i < 16; i++) {
            if (i < count) {
                if (fprintf(output, "%02x ", buffer[i]) < 0) {
                    status = -1;
                    saved_errno = errno != 0 ? errno : EIO;
                    break;
                }
            } else {
                // Preserve alignment for incomplete final rows.
                if (fputs("   ", output) == EOF) {
                    status = -1;
                    saved_errno = errno != 0 ? errno : EIO;
                    break;
                }
            }
        }

        if (status != 0) {
            break;
        }

        // Separate hexadecimal bytes from the ASCII column.
        if (fputs(" |", output) == EOF) {
            status = -1;
            saved_errno = errno != 0 ? errno : EIO;
            break;
        }

        // Print printable characters; replace others with '.'.
        for (size_t i = 0; i < count; i++) {
            int character = isprint((unsigned char)buffer[i])
                ? buffer[i]
                : '.';

            if (fputc(character, output) == EOF) {
                status = -1;
                saved_errno = errno != 0 ? errno : EIO;
                break;
            }
        }

        if (status != 0) {
            break;
        }

        if (fputs("|\n", output) == EOF) {
            status = -1;
            saved_errno = errno != 0 ? errno : EIO;
            break;
        }

        // Protect the offset from unsigned integer overflow.
        if (UINTMAX_MAX - offset < count) {
            status = -1;
            saved_errno = EOVERFLOW;
            break;
        }

        offset += count;

        if (ferror(input)) {
            status = -1;
            saved_errno = errno != 0 ? errno : EIO;
            break;
        }
    }

    // Detect delayed output errors while keeping output open.
    if (status == 0 && fflush(output) != 0) {
        status = -1;
        saved_errno = errno != 0 ? errno : EIO;
    }

    // Always close the input file.
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
