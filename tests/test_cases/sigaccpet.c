#undef _GNU_SOURCE
#define _GNU_SOURCE

#include <ctype.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <arpa/inet.h>
#include <netinet/in.h>

void handle_interrupt(int signum) {
    printf("Received signal %d\n", signum);
}

int main() {
    // Set up a signal handler
    struct sigaction sa;
    memset(&sa, 0, sizeof(sa));
    sa.sa_handler = handle_interrupt;
    sigaction(SIGINT, &sa, NULL);

    // Create a socket
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1) {
        perror("socket");
        return 1;
    }

    // Bind the socket to an address
    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(12345);

    if (bind(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        perror("bind");
        close(server_fd);
        return 1;
    }

    // Listen for incoming connections
    if (listen(server_fd, 5) == -1) {
        perror("listen");
        close(server_fd);
        return 1;
    }

    printf("Server listening on port 12345...\n");

    struct sockaddr_in client_addr;
    socklen_t client_len = sizeof(client_addr);

    // Try to accept a connection
    int client_fd = accept(server_fd, (struct sockaddr*)&client_addr, &client_len);
    if (client_fd == -1) {
        if (errno == EINTR) {
            printf("accept returned EINTR due to interrupt signal.\n");
        } else {
            perror("accept");
            close(server_fd);
            return 1;
        }
    }

    close(server_fd);
    return 0;
}
