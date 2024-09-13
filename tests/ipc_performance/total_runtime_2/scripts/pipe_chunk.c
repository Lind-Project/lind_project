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

void parent(int pipe_to_child[2], int pipe_from_child[2], sem_t *semaphore) {
    char *buf = (char *)malloc(CHUNK_SIZE);

    memset(buf, 'a', CHUNK_SIZE);
    
    sem_wait(semaphore);

    fprintf(stderr, "Starts writing: %lld\n", gettimens());
    fflush(stderr);

    for (int i = 0; i < GB / 2048; ++i) {
        if (write(pipe_to_child[1], buf, CHUNK_SIZE) == -1) {
            perror("write");
            exit(1);
        }
    }
    for (int j = 0; j < GB / 2048; ++j) {
        int total_received = 0;
        if (read(pipe_from_child[0], buf, CHUNK_SIZE) == -1) {
            perror("read");
            exit(1);
        }
    }

    fprintf(stderr, "Ends reading: %lld\n", gettimens());
    fflush(stderr);

    free(buf);
}

void child(int pipe_to_parent[2], int pipe_from_parent[2], sem_t *semaphore) {
    char *buf = (char *)malloc(CHUNK_SIZE);

    memset(buf, 'b', CHUNK_SIZE);

    if (sem_post(semaphore) < 0) {
        perror("sem_post");
        exit(1);
    }

    for (int x = 0; x < GB / 2048; ++x) {
        if (read(pipe_from_parent[0], buf, CHUNK_SIZE) == -1) {
            perror("read");
            exit(1);
        }
    }

    for (int y = 0; y < GB / 2048; ++y) {
        if (write(pipe_to_parent[1], buf, CHUNK_SIZE) == -1) {
            perror("write");
            exit(1);
        }
    }

    free(buf);
}

int main(int argc, char *argv[]) {
    int pipe_to_child[2], pipe_to_parent[2];
    pid_t pid;

    if (pipe(pipe_to_child) == -1 || pipe(pipe_to_parent) == -1) {
        perror("Pipe");
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
        close(pipe_to_child[1]); // Close write end of parent-to-child pipe
        close(pipe_to_parent[0]); // Close read end of child-to-parent pipe
        child(pipe_to_parent, pipe_to_child, semaphore);
        close(pipe_to_child[0]);
        close(pipe_to_parent[1]);
    } else {
        // Parent process
        close(pipe_to_child[0]); // Close read end of parent-to-child pipe
        close(pipe_to_parent[1]); // Close write end of child-to-parent pipe
        parent(pipe_to_child, pipe_to_parent, semaphore);
        close(pipe_to_child[1]);
        close(pipe_to_parent[0]); 
    }

    sem_destroy(semaphore);

    return 0;
}