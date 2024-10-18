#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <time.h>
#include <poll.h>
#include <semaphore.h>
#include <sys/mman.h>

#define GB (1 << 26)

long long gettimens() {
    struct timespec tp;
    clock_gettime(CLOCK_MONOTONIC, &tp);
    return (long long)tp.tv_sec * 1000000000LL + tp.tv_nsec;
}

void parent(int socket, int buf_size, sem_t *semaphore) {
    char *buf = (char *)malloc(buf_size);
    memset(buf, 'a', buf_size);
    
    sem_wait(semaphore);

    struct pollfd fds[1];
    fds[0].fd = socket;
    fds[0].events = POLLIN;

    fprintf(stderr, "Starts sending: %lld\n", gettimens());
    fflush(stderr);

    for (int i = 0; i < GB / buf_size; ++i) {
        if (write(socket, buf, buf_size) == -1) {
            perror("write");
            exit(1);
        }
        
        // Poll to wait until there is data to read
        int poll_ret = poll(fds, 1, -1);
        if (poll_ret < 0) {
            perror("poll");
            exit(1);
        }

        int bytes_read = 0;
        while (bytes_read < buf_size) {
            int bytes;
            if ((bytes = read(socket, buf, buf_size)) == -1) {
                perror("read");
                exit(1);
            }
            bytes_read += bytes;
        }
    }

    fprintf(stderr, "Ends receiving: %lld\n", gettimens());
    fflush(stderr);

    free(buf);
}

void child(int socket, int buf_size, sem_t *semaphore) {
    char *buf = (char *)malloc(buf_size);
    memset(buf, 'b', buf_size);

    if (sem_post(semaphore) < 0) {
        perror("sem_post");
        exit(1);
    }

    struct pollfd fds[1];
    fds[0].fd = socket;
    fds[0].events = POLLIN;

    for (int x = 0; x < GB / buf_size; ++x) {
        // Poll to wait until there is data to read
        int poll_ret = poll(fds, 1, -1);
        if (poll_ret < 0) {
            perror("poll");
            exit(1);
        }

        int bytes_read = 0;
        while (bytes_read < buf_size) {
            int bytes;
            if ((bytes = read(socket, buf, buf_size)) == -1) {
                perror("read");
                exit(1);
            }
            bytes_read += bytes;
        }

        if (write(socket, buf, buf_size) == -1) {
            perror("write");
            exit(1);
        }
    }

    free(buf);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s [send_recv_buf_size]\n", argv[0]);
        exit(1);
    }

    int buf_size = 1 << atoi(argv[1]);

    pid_t pid;

    int sockets[2];
    // Create the socket
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
        close(sockets[1]); // Close write end of parent-to-child pipe
        child(sockets[0], buf_size, semaphore);
        close(sockets[0]);
    } else {
        // Parent process
        close(sockets[0]); // Close read end of parent-to-child pipe
        parent(sockets[1], buf_size, semaphore);
        close(sockets[1]);
    }

    sem_destroy(semaphore);

    return 0;
}
