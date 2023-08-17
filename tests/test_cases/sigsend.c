#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <sys/socket.h>

volatile sig_atomic_t received_signal = 0;

void signal_handler(int signum) {
    received_signal = signum;
}

int main() {
    signal(SIGINT, signal_handler);  // Set up signal handler for SIGINT (Ctrl+C)

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        perror("socket");
        return 1;
    }

    // You would normally set up a proper socket address structure here.
    // For the purpose of this example, we'll just assume the address is set up.

    int send_result;
    char buffer[] = "Hello, world!";

    do {
        send_result = send(sockfd, buffer, sizeof(buffer), 0);
    } while (send_result == -1 && errno == EINTR);

    if (send_result == -1) {
        perror("send");
        return 1;
    }

    printf("Message sent successfully.\n");
    
    close(sockfd);
    return 0;
}
