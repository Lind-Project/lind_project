#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 8080
#define BUFFER_SIZE 32768
#define NUM_REQUESTS 100000

int main()
{
    int clientSocket;
    struct sockaddr_in serverAddr;
    char buffer[BUFFER_SIZE];

    // Create socket
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket < 0)
    {
        perror("Error creating socket");
        exit(EXIT_FAILURE);
    }

    // Set server address
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(SERVER_PORT);
    if (inet_pton(AF_INET, SERVER_IP, &(serverAddr.sin_addr)) <= 0)
    {
        perror("Invalid address/Address not supported");
        exit(EXIT_FAILURE);
    }

    // Connect to server
    if (connect(clientSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0)
    {
        perror("Error connecting to server");
        exit(EXIT_FAILURE);
    }

    int count = 0;
    while (count++ < NUM_REQUESTS)
    {
        // printf("client: %d\n", count);
        // fflush(stdout);
        // Send request
        char *request = "GET / HTTP/1.1\r\nHost: localhost\r\n\r\n";
        if (send(clientSocket, request, strlen(request), 0) < 0)
        {
            perror("Error sending request");
            exit(EXIT_FAILURE);
        }

        // Receive fileSize from clientSocket
        off_t fileSize;
        if (recv(clientSocket, &fileSize, sizeof(fileSize), 0) < 0)
        {
            perror("Error receiving filesize");
            exit(EXIT_FAILURE);
        }

        off_t totalBytesRead = 0;

        // Read response
        memset(buffer, 0, sizeof(buffer));

        while (totalBytesRead < fileSize)
        {
            off_t bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0);
            totalBytesRead += bytesRead;
        }
    }

    // Close socket
    close(clientSocket);

    return 0;
}
