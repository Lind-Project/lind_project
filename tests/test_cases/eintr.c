#undef _GNU_SOURCE
#define _GNU_SOURCE

#include <ctype.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <wait.h>

void handle_signal(int signum) {
    // This handler will be called when a signal is received.

}

int main() {
    // Set up a signal handler for SIGINT (Ctrl+C)
    signal(SIGINT, handle_signal);

    char buffer[100];
    ssize_t bytes_read;

    // Try to read from stdin
    do {
        bytes_read = read(STDIN_FILENO, buffer, sizeof(buffer));
    } while (bytes_read == -1 && errno == EINTR);

    if (bytes_read == -1) {
        perror("read");
        return 1;
    }

    printf("Read %zd bytes: %s\n", bytes_read, buffer);

    return 0;
}
