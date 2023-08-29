#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/epoll.h>

#define MAX_EVENTS 10

int main() {
    int epoll_fd, nfds;
    struct epoll_event ev, events[MAX_EVENTS];

    epoll_fd = epoll_create(0);
    if (epoll_fd == -1) {
        perror("epoll_create1");
        return 1;
    }

    // Add stdin (file descriptor 0) to the epoll set
    ev.events = EPOLLIN;
    ev.data.fd = 0;
    if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, 0, &ev) == -1) {
        perror("epoll_ctl: stdin");
        return 1;
    }

    while (1) {
        nfds = epoll_wait(epoll_fd, events, MAX_EVENTS, -1); // Wait for events
        if (nfds == -1) {
            perror("epoll_wait");
            return 1;
        }

        for (int i = 0; i < nfds; i++) {
            if (events[i].data.fd == 0) {
                printf("Input is available on stdin.\n");

                // Read and print the input
                char buffer[1024];
                ssize_t bytesRead = read(0, buffer, sizeof(buffer));
                if (bytesRead > 0) {
                    buffer[bytesRead] = '\0';
                    printf("Read %zd bytes from stdin: %s\n", bytesRead, buffer);
                } else if (bytesRead == 0) {
                    printf("EOF detected on stdin.\n");
                    close(epoll_fd);
                    return 0;
                } else {
                    perror("read");
                }
            }
        }
    }

    close(epoll_fd);
    return 0;
}
