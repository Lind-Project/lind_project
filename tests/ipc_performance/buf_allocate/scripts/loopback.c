#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <time.h>
#include <semaphore.h>
#include <sys/mman.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define GB (1 << 30)
#define CHUNK_SIZE 2048

long long gettimens() {
    struct timespec tp;
    clock_gettime(CLOCK_MONOTONIC, &tp);
    return (long long)tp.tv_sec * 1000000000LL + tp.tv_nsec;
}

void parent(int socket, sem_t *semaphore) {
    char *buf = (char *)malloc(CHUNK_SIZE);

    memset(buf, 'a', CHUNK_SIZE);
    
    sem_wait(semaphore);

    fprintf(stderr, "Starts sending: %lld\n", gettimens());
    fflush(stderr);

    for (int i = 0; i < GB / 2048; ++i) {
        if (send(socket, buf, CHUNK_SIZE, 0) == -1) {
            perror("Send");
            exit(1);
        }
        
        if (recv(socket, buf, CHUNK_SIZE, 0) == -1) {
            perror("Recv");
            exit(1);
        }
    }

    fprintf(stderr, "Ends receiving: %lld\n", gettimens());
    fflush(stderr);

    free(buf);
}

void child(int socket, sem_t *semaphore) {
    char *buf = (char *)malloc(CHUNK_SIZE);

    memset(buf, 'b', CHUNK_SIZE);

    if (sem_post(semaphore) < 0) {
        perror("sem_post");
        exit(1);
    }

    for (int x = 0; x < GB / 2048; ++x) {
        if (recv(socket, buf, CHUNK_SIZE, 0) == -1) {
            perror("Recv");
            exit(1);
        }
        
        if (send(socket, buf, CHUNK_SIZE, 0) == -1) {
            perror("Send");
            exit(1);
        }
    }

    free(buf);
}


int create_server_socket() {
    int server_fd;
    struct sockaddr_in server_addr;

    // Create server socket
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    // Set up server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.7"); // Loopback address
    server_addr.sin_port = htons(8080); // Port number

    // Bind server to the loopback address and port
    if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("bind");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections
    if (listen(server_fd, 1) < 0) {
        perror("listen");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    return server_fd;
}

int create_client_socket() {
    int client_fd;
    struct sockaddr_in client_addr;

    // Create client socket
    client_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (client_fd < 0) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    // Set up client address to connect to server
    client_addr.sin_family = AF_INET;
    client_addr.sin_addr.s_addr = inet_addr("127.0.0.7"); // Loopback address
    client_addr.sin_port = htons(8080); // Same port as server

    // Connect to server
    if (connect(client_fd, (struct sockaddr *)&client_addr, sizeof(client_addr)) < 0) {
        perror("connect");
        close(client_fd);
        exit(EXIT_FAILURE);
    }

    return client_fd;
}

int main(int argc, char *argv[]) {
    int sockets[2];
    pid_t pid;

    sem_t *semaphore = mmap(NULL, sizeof(sem_t), PROT_READ | PROT_WRITE,
                      MAP_SHARED | MAP_ANONYMOUS, -1, 0);

    if (sem_init(semaphore, 1, 0) == -1) {
        perror("sem_init");
        exit(EXIT_FAILURE);
    }

    pid = fork();
    if (pid == -1) {
        perror("Fork");
        exit(1);
    }

    if (pid == 0) {
        // Child process
        int client_fd = create_client_socket();

        child(client_fd, semaphore);
        close(client_fd);
    } else {
        // Parent process
        int server_fd = create_server_socket();

        struct sockaddr_in client_addr;
        socklen_t client_len = sizeof(client_addr);
        int accepted_fd = accept(server_fd, (struct sockaddr *)&client_addr, &client_len);
        if (accepted_fd < 0) {
            perror("accept");
            close(server_fd);
            exit(EXIT_FAILURE);
        }

        parent(accepted_fd, semaphore);
        close(accepted_fd);
    }

    sem_destroy(semaphore);

    return 0;
}
