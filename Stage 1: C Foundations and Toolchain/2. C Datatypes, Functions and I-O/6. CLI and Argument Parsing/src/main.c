
#include "../include/cli.h"

#include <string.h>

int cli_dispatch(int argc, char *argv[]);

int main(int argc, char *argv[]) {
    // No command supplied.
    if (argc < 2) {
        cli_print_usage(argv[0]);
        return 1;
    }

    // Handle global help.
    if (strcmp(argv[1], "--help") == 0 ||
        strcmp(argv[1], "-h") == 0) {
        cli_print_usage(argv[0]);
        return 0;
    }

    // Handle global version.
    if (strcmp(argv[1], "--version") == 0 ||
        strcmp(argv[1], "-V") == 0) {
        cli_print_version();
        return 0;
    }

    // Pass the command and its arguments to the dispatcher.
    return cli_dispatch(argc - 1, argv + 1);
}
