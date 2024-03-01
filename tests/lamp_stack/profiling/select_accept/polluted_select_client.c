#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 8080
#define NUMBER_OF_ROUNDS 240000
#define BUFFER_SIZE 1024
#define INITIAL_CONNECTIONS 50

int main()
{
    int pre_established_fd[INITIAL_CONNECTIONS];
    struct sockaddr_in server_addr;
    char buffer[BUFFER_SIZE];
    ssize_t bytes_received;

    // Initialize server address
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(SERVER_IP);
    server_addr.sin_port = htons(SERVER_PORT);

    // Create and connect 50 pre-established long-lasting sockets
    for (int i = 0; i < INITIAL_CONNECTIONS; ++i)
    {
        pre_established_fd[i] = socket(AF_INET, SOCK_STREAM, 0);
        if (pre_established_fd[i] < 0)
        {
            perror("pre-establish socket failed");
            exit(EXIT_FAILURE);
        }

        if (connect(pre_established_fd[i], (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
        {
            perror("pre-establish connect failed");
            exit(EXIT_FAILURE);
        }
    }

    // Connect-close iterations
    for (int i = 0; i < NUMBER_OF_ROUNDS; ++i)
    {
        int sock = socket(AF_INET, SOCK_STREAM, 0);
        if (sock < 0)
        {
            perror("socket failed");
            exit(EXIT_FAILURE);
        }

        if (connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
        {
            perror("connect failed");
            close(sock);
            continue;
        }

        bytes_received = read(sock, buffer, BUFFER_SIZE - 1);
        if (bytes_received > 0)
        {
            buffer[bytes_received] = '\0';
            // printf("Received: %s\n", buffer);
        }
        else
        {
            perror("read failed");
        }

        close(sock);
    }

    // Close the long-lasting pre-established connections
    for (int i = 0; i < INITIAL_CONNECTIONS; ++i)
    {
        close(pre_established_fd[i]);
    }

    return 0;
}