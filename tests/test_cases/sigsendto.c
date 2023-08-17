#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 9999

volatile sig_atomic_t interrupt = 0;

void signal_handler(int signum) {
    interrupt = 1;
}

int main() {
    signal(SIGUSR1, signal_handler);  // Set up signal handler for SIGUSR1

    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd == -1) {
        perror("socket");
        return 1;
    }

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("bind");
        return 1;
    }

    char message[] = "Hello, world!";
    struct sockaddr_in client_addr;
    socklen_t client_len = sizeof(client_addr);

    printf("Waiting for a message...\n");

    while (1) {
        ssize_t send_result;
        while ((send_result = sendto(sockfd, message, sizeof(message), 0, (struct sockaddr *)&client_addr, client_len)) == -1 && errno == EINTR) {
            if (interrupt) {
                printf("Sending interrupted.\n");
                interrupt = 0;
            }
        }

        if (send_result == -1) {
            perror("sendto");
            return 1;
        } else {
            printf("Message sent successfully.\n");
        }

        sleep(1); // Sleep to prevent busy loop
    }

    close(sockfd);
    return 0;
}
