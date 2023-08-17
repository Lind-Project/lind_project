#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <signal.h>
#include <sys/socket.h>
#include <netinet/in.h>

void signal_handler(int signum) {
    // Just an empty signal handler to interrupt the connect call
}

int main() {
    struct sockaddr_in server_addr;
    int sockfd;

    // Set up a simple TCP server address
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(12345);
    server_addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

    // Create a socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        perror("socket");
        return 1;
    }

    // Register the signal handler for SIGALRM
    signal(SIGALRM, signal_handler);

    // Set a timer to send a SIGALRM after 3 seconds
    alarm(3);
    while(1) {
        // Attempt to connect - this may be interrupted by the alarm signal
        if (connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
            if (errno == EINTR) {
                printf("Connect interrupted by a signal.\n");
            } else {
                perror("connect");
            }
        } else {
            printf("Connected successfully.\n");
        }
    }
    

    // Clean up and close the socket
    close(sockfd);

    return 0;
}
