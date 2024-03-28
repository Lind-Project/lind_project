#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 8080
#define NUMBER_OF_ROUNDS 2400000
#define BUFFER_SIZE 1024

int main()
{
    int sock;
    struct sockaddr_in server_addr;
    char buffer[BUFFER_SIZE];
    ssize_t bytes_received;

    // Initialize server address
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(SERVER_IP);
    server_addr.sin_port = htons(SERVER_PORT);

    for (int i = 0; i < NUMBER_OF_ROUNDS; ++i)
    {
        // Create socket
        sock = socket(AF_INET, SOCK_STREAM, 0);
        if (sock < 0)
        {
            perror("socket failed");
            exit(EXIT_FAILURE);
        }

        // Connect to server
        if (connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
        {
            perror("connect failed");
            close(sock);
            continue;
        }

        // Receive acknowledgment message
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

    return 0;
}