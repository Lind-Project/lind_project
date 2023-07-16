#undef _GNU_SOURCE
#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <poll.h>

#define TIMEOUT 5

int main(void) {
    struct pollfd fds[1];
    int ret;

    /* Checking if stdout (file descriptor 1) is ready for writing. */
    fds[0].fd = 1;
    fds[0].events = POLLOUT;

    /* The poll call is blocked for the specified duration (in this case, 5 seconds). */
    ret = poll(fds, 1, TIMEOUT * 1000);

    if (ret == -1) {
        perror("poll");
        return EXIT_FAILURE;
    }

    if (!ret) {
        printf("%d seconds elapsed.\n", TIMEOUT);
        return EXIT_SUCCESS;
    }

    if (fds[0].revents & POLLOUT) {
        printf("stdout is ready for writing.\n");
        return EXIT_SUCCESS;
    }

    fprintf(stderr, "unexpected poll events: %d\n", fds[0].revents);
    return EXIT_FAILURE;
}

