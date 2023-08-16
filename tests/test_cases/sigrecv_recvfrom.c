#include <unistd.h>
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <string.h> 
#include <errno.h>
#include <signal.h>
#include <sys/wait.h>

static void sig_usr(int signum){
    printf("Received signal %d\n", signum);
}

int main() {
    pid_t child = fork();

    if(child < 0) {
        perror("fork");
        return EXIT_FAILURE;
    } else if(child == 0) {
        printf("Child process start...\n");
        // Create a socket
        int sockfd = socket(AF_INET, SOCK_STREAM, 0);
        if (sockfd == -1) {
            perror("socket");
            return 1;
        }

        // Set signal handler
        struct sigaction sa_usr;
        sa_usr.sa_flags = 0;
        sa_usr.sa_handler = sig_usr;   

        sigaction(SIGUSR2, &sa_usr, NULL);

        // Now let's attempt to receive data with recv
        char buffer[256];
        ssize_t bytes_received = recv(sockfd, buffer, sizeof(buffer), 0);
        if (bytes_received == -1) {
            if (errno == EINTR) {
                printf("recv was interrupted by a signal EINTR\n");
            } else {
                perror("recv");
            }
        } else {
            printf("Received %zd bytes: %.*s\n", bytes_received, (int)bytes_received, buffer);
        }

        // Clean up and close the socket
        close(sockfd);
        exit(0);
    } else {
        printf("Parent process starts...\n");
        sleep(5);
        kill(child, SIGUSR2);
        wait(NULL);
        return 0;
    }
    

    return 0;
}
