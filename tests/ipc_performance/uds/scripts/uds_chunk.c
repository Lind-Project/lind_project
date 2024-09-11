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
#define CHUNK_SIZE 2048  // 2KB chunk size

long long gettimens() {
    struct timespec tp;
    clock_gettime(CLOCK_MONOTONIC, &tp);
    return (long long)tp.tv_sec * 1000000000LL + tp.tv_nsec;
}

void parent(int socket, int buf_size, sem_t *sem, sem_t *sem_parent, sem_t *sem_child) {
    char *send_buf = (char *)malloc(buf_size);
    char *recv_buf = (char *)malloc(CHUNK_SIZE);

    memset(send_buf, 'a', buf_size);

    sem_wait(sem);

    fprintf(stderr, "Starts sending: %lld\n", gettimens());
    fflush(stderr);

    for (int i = 0; i < GB / buf_size; ++i) {
        for (int j = 0; j < buf_size; j += CHUNK_SIZE) {
            // Parent sends 2KB
            if (send(socket, send_buf + j, CHUNK_SIZE, 0) == -1) {
                perror("Send");
                exit(1);
            }

            // Wait for child to finish receiving and sending its chunk
            sem_wait(sem_parent);

            // Parent receives 2KB
            int total_received = 0;
            while (total_received < CHUNK_SIZE) {
                int received = recv(socket, recv_buf + total_received, CHUNK_SIZE - total_received, 0);
                if (received == -1) {
                    perror("Recv");
                    exit(1);
                }
                total_received += received;
            }

            // Signal the child that parent finished receiving
            sem_post(sem_child);
        }
    }

    fprintf(stderr, "Ends receiving: %lld\n", gettimens());
    fflush(stderr);

    free(send_buf);
    free(recv_buf);
}

void child(int socket, int buf_size, sem_t *sem, sem_t *sem_parent, sem_t *sem_child) {
    char *send_buf = (char *)malloc(buf_size);
    char *recv_buf = (char *)malloc(CHUNK_SIZE);

    memset(send_buf, 'b', buf_size);

    if (sem_post(sem) < 0) {
        perror("sem_post");
        exit(1);
    }

    for (int i = 0; i < GB / buf_size; ++i) {
        for (int j = 0; j < buf_size; j += CHUNK_SIZE) {
            // Child receives 2KB
            int total_received = 0;
            while (total_received < CHUNK_SIZE) {
                int received = recv(socket, recv_buf + total_received, CHUNK_SIZE - total_received, 0);
                if (received == -1) {
                    perror("Recv");
                    exit(1);
                }
                total_received += received;
            }

            // Signal parent that child finished receiving
            if (sem_post(sem_parent) < 0) {
                perror("sem_post");
                exit(1);
            }

            // Child sends 2KB
            if (send(socket, send_buf + j, CHUNK_SIZE, 0) == -1) {
                perror("Send");
                exit(1);
            }

            // Wait for parent to finish receiving
            sem_wait(sem_child);
        }
    }

    free(send_buf);
    free(recv_buf);
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

    sem_t *sem = mmap(NULL, sizeof(sem_t), PROT_READ | PROT_WRITE,
                      MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    sem_t *sem_parent = mmap(NULL, sizeof(sem_t), PROT_READ | PROT_WRITE,
                      MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    sem_t *sem_child = mmap(NULL, sizeof(sem_t), PROT_READ | PROT_WRITE,
                      MAP_SHARED | MAP_ANONYMOUS, -1, 0);

    if (sem_init(sem, 1, 0) == -1 ||
        sem_init(sem_parent, 1, 0) == -1 || 
        sem_init(sem_child, 1, 0) == -1) {
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
        child(sockets[0], buf_size, sem, sem_parent, sem_child);
        close(sockets[0]);
    } else {
        // Parent process
        close(sockets[0]);
        parent(sockets[1], buf_size, sem, sem_parent, sem_child);
        close(sockets[1]);
    }

    sem_destroy(sem);
    sem_destroy(sem_parent);
    sem_destroy(sem_child);

    return 0;
}
