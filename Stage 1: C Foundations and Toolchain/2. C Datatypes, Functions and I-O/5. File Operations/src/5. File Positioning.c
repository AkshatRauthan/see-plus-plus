#include "../include/file_operations.h"

#include <errno.h>
#include <stdio.h>

/*
 * Retrieves the size of a file in bytes.
 *
 * fseek() moves the file position indicator.
 * SEEK_END moves it to the end of the file.
 * ftell() reports the current position.
 *
 * This approach is suitable for seekable files.
 */
int get_file_size(const char *path, long *size) {
    if (path == NULL || size == NULL) {
        errno = EINVAL;
        return -1;
    }

    FILE *file = fopen(path, "rb");

    if (file == NULL) {
        return -1;
    }

    // Move to the end of the file.
    if (fseek(file, 0, SEEK_END) != 0) {
        fclose(file);
        return -1;
    }

    // The position at the end represents the file size in bytes.
    long file_size = ftell(file);

    if (file_size < 0) {
        fclose(file);
        return -1;
    }

    *size = file_size;

    if (fclose(file) != 0) {
        return -1;
    }

    return 0;
}
