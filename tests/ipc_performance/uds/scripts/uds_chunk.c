#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <time.h>
#include <semaphore.h>
#include <sys/mman.h>

#define GB (1 << 30)
#define CHUNK_SIZE 2048

long long gettimens() {
    struct timespec tp;
    clock_gettime(CLOCK_MONOTONIC, &tp);
    return (long long)tp.tv_sec * 1000000000LL + tp.tv_nsec;
}

void parent(int socket, sem_t *semaphore) {
    char *buf = (char *)malloc(CHUNK_SIZE);

    // memset(send_buf, 'a', buf_size);
    memset(buf, 'a', CHUNK_SIZE);
    
    sem_wait(semaphore);

    fprintf(stderr, "Starts sending: %lld\n", gettimens());
    fflush(stderr);

    for (int i = 0; i < GB / CHUNK_SIZE; ++i) {
        if (send(socket, buf, CHUNK_SIZE, 0) == -1) {
            perror("Send");
            exit(1);
        }
    }

    for (int j = 0; j < GB / CHUNK_SIZE; ++j) {
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

    for (int x = 0; x < GB / CHUNK_SIZE; ++x) {
        if (recv(socket, buf, CHUNK_SIZE, 0) == -1) {
            perror("Recv");
            exit(1);
        }
    }

    for (int y = 0; y < GB / CHUNK_SIZE; ++y) {
        if (send(socket, buf, CHUNK_SIZE, 0) == -1) {
            perror("Send");
            exit(1);
        }
    }

    free(buf);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s [send_recv_buf_size]\n", argv[0]);
        exit(1);
    }

    int buf_size = 1 << atoi(argv[1]);

    int sockets[2];
    pid_t pid;

    if (socketpair(AF_UNIX, SOCK_STREAM, 0, sockets) == -1) {
        perror("Socketpair");
        exit(1);
    }

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
        close(sockets[1]);
        child(sockets[0], semaphore);
        close(sockets[0]);
    } else {
        // Parent process
        close(sockets[0]);
        parent(sockets[1], semaphore);
        close(sockets[1]);
    }

    sem_destroy(semaphore);

    return 0;
}