#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <poll.h>

#define MSG "ping"
#define ACK "pong"

int main() {
    int fds[2];
    char buffer[100];
    struct pollfd pfd;
    int ret;

    // create a pair of domain sockets, UDP
    if (socketpair(AF_UNIX, SOCK_STREAM, 0, fds) < 0) {
        perror("creating socket pair failed!\n");
        exit(1);
    }

    pid_t pid = fork();
    if (pid == -1) {
        perror("fork failed");
        exit(1);
    } else if (pid == 0) {
        // child: pinger process
        close(fds[0]); // close the reading end
        write(fds[1], MSG, strlen(MSG));
        read(fds[1], buffer, sizeof(buffer));
        printf("Pinger received: %s\n", buffer);
        close(fds[1]);
    } else {
        // parent: ponger process
        close(fds[1]); // close the writing end

        // setup pollfd
        pfd.fd = fds[0];
        pfd.events = POLLIN;

        // use poll for waiting the message from pinger
        ret = poll(&pfd, 1, -1);
        if (ret > 0) {
            if (pfd.revents & POLLIN) {
                read(fds[0], buffer, sizeof(buffer));
                printf("Ponger received: %s\n", buffer);
                write(fds[0], ACK, strlen(ACK)); // reply to pinger
            }
        } else {
            perror("poll");
        }

        close(fds[0]);
    }

    return 0;
}
