#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <time.h>
#include <netinet/tcp.h>

#define MAX_BUFFER_SIZE 32768
#define NUM_REQUESTS 100000
#define HEADER_SIZE 256

long long gettimens(void)
{
    struct timespec tp;

    if (clock_gettime(CLOCK_MONOTONIC, &tp) == -1)
    {
        perror("clock gettime");
        exit(EXIT_FAILURE);
    }

    return (tp.tv_sec * 1000000000) + tp.tv_nsec;
}

int main()
{
    // Create socket
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1)
    {
        perror("Failed to create socket");
        exit(EXIT_FAILURE);
    }

    // Set up server address
    struct sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(8080);

    int tcp_nodelay = 1;
    setsockopt(serverSocket, IPPROTO_TCP, TCP_NODELAY,
                   (const void *) &tcp_nodelay, sizeof(int));
    
    if (setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, &(int){1}, sizeof(int)) < 0)
    {
        perror("setsockopt(SO_REUSEADDR) failed");
        exit(EXIT_FAILURE);
    }
    
    // Bind socket to address
    if (bind(serverSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) == -1)
    {
        perror("Failed to bind socket");
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections
    if (listen(serverSocket, 5) == -1)
    {
        perror("Failed to listen for connections");
        exit(EXIT_FAILURE);
    }

    // Accept incoming connection
    int clientSocket = accept(serverSocket, NULL, NULL);
    if (clientSocket == -1)
    {
        perror("Failed to accept connection");
        exit(EXIT_FAILURE);
    }

    setsockopt(clientSocket, IPPROTO_TCP, TCP_NODELAY,
                   (const void *) &tcp_nodelay, sizeof(int));
    
    if (setsockopt(clientSocket, SOL_SOCKET, SO_REUSEADDR, &(int){1}, sizeof(int)) < 0)
    {
        perror("setsockopt(SO_REUSEADDR) failed");
        exit(EXIT_FAILURE);
    }

    int count = 0;
    long long total_rw_time = 0;

    while (count++ < NUM_REQUESTS)
    {
        // printf("server: %d\n", count);
        // fflush(stdout);
        int write_count = 0;

        // Create file descriptor set for select
        fd_set readFds;
        FD_ZERO(&readFds);
        FD_SET(clientSocket, &readFds);

        // Run select call
        if (select(clientSocket + 1, &readFds, NULL, NULL, NULL) == -1)
        {
            perror("Failed to run select");
            exit(EXIT_FAILURE);
        }

        struct timespec start;

        if (clock_gettime(CLOCK_REALTIME, &start) == -1)
        {
            perror("clock gettime");
            exit(EXIT_FAILURE);
        }

        // Check if socket is ready to receive
        if (FD_ISSET(clientSocket, &readFds))
        {
            // Receive data
            char buffer[MAX_BUFFER_SIZE];
            ssize_t bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0);
            if (bytesRead == -1)
            {
                perror("Failed to receive data");
                exit(EXIT_FAILURE);
            }

            // Process received data
            // ...

            // Open HTML file
            int fileDescriptor = open("static.html", O_RDONLY);
            if (fileDescriptor == -1)
            {
                perror("Failed to open file");
                exit(EXIT_FAILURE);
            }

            // Get file size
            struct stat fileStat;

            if (stat("static.html", &fileStat) == -1)
            {
                perror("Failed to get file size");
                exit(EXIT_FAILURE);
            }

            if (fstat(fileDescriptor, &fileStat) == -1)
            {
                perror("Failed to get file size");
                exit(EXIT_FAILURE);
            }
            off_t fileSize = fileStat.st_size;
            // printf("server fileSize: %ld\n", fileSize);
            // fflush(stdout);
            
            // Send file size
            ssize_t bytesWritten = write(clientSocket, &fileSize, sizeof(fileSize));
            if (bytesWritten == -1)
            {
                perror("Failed to write data");
                exit(EXIT_FAILURE);
            }

            // Read and write file in chunks
            char fileBuffer[MAX_BUFFER_SIZE + HEADER_SIZE];
            ssize_t totalBytesWritten = 0;
            long long start = gettimens();
            
            while (totalBytesWritten < fileSize)
            {
                ssize_t bytesRead = pread(fileDescriptor, fileBuffer, sizeof(fileBuffer), totalBytesWritten);
                if (bytesRead == -1)
                {
                    perror("Failed to read file");
                    exit(EXIT_FAILURE);
                }
                
                struct iovec iov[2];
                iov[0].iov_base = fileBuffer;
                iov[0].iov_len = HEADER_SIZE;
                iov[1].iov_base = fileBuffer + 256;
                iov[1].iov_len = MAX_BUFFER_SIZE;
                
                ssize_t bytesWritten = writev(clientSocket, iov, 2);
                if (bytesWritten == -1)
                {
                    perror("Failed to write data");
                    exit(EXIT_FAILURE);
                }
                // ssize_t bytesWritten = write(clientSocket, fileBuffer, bytesRead);
                // if (bytesWritten == -1)
                // {
                //     perror("Failed to write data");
                //     exit(EXIT_FAILURE);
                // }

                totalBytesWritten += bytesWritten;
                
                // printf("bytesWritten: %ld, totalBytesWritten: %ld\n", bytesWritten, totalBytesWritten);
                // fflush(stdout);
            }
            long long end = gettimens();
            total_rw_time += end - start;

            // Close file
            close(fileDescriptor);
        }
    }

    printf("Total time for %d: %lld\n", count, total_rw_time);
    fflush(stdout);
    printf("Average time: %lld\n", total_rw_time / count);
    fflush(stdout);
    // Close sockets
    close(clientSocket);
    close(serverSocket);

    return 0;
}
