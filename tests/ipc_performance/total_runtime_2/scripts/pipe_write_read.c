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

long long gettimens() {
    struct timespec tp;
    clock_gettime(CLOCK_MONOTONIC, &tp);
    return (long long)tp.tv_sec * 1000000000LL + tp.tv_nsec;
}

void parent(int pipe_to_child[2], int pipe_from_child[2], int buf_size, sem_t *semaphore) {
    char *send_buf = (char *)malloc(buf_size);
    char *recv_buf = (char *)malloc(buf_size);

    memset(send_buf, 'a', buf_size);
    
    sem_wait(semaphore);

    fprintf(stderr, "Starts writing: %lld\n", gettimens());
    fflush(stderr);

    for (int i = 0; i < GB / buf_size; ++i) {
        if (write(pipe_to_child[1], send_buf, buf_size) == -1) {
            perror("write");
            exit(1);
        }
    }
    for (int j = 0; j < GB / buf_size; ++j) {
        int total_received = 0;
        while (total_received < buf_size) {
            int received = read(pipe_from_child[0], recv_buf + total_received, buf_size - total_received);
            if (received == -1) {
                perror("read");
                exit(1);
            }
            total_received += received;
        }
    }

    

    fprintf(stderr, "Ends reading: %lld\n", gettimens());
    fflush(stderr);

    free(send_buf);
    free(recv_buf);
}

void child(int pipe_to_parent[2], int pipe_from_parent[2], int buf_size, sem_t *semaphore) {
    char *send_buf = (char *)malloc(buf_size);
    char *recv_buf = (char *)malloc(buf_size);

    memset(send_buf, 'b', buf_size);

    if (sem_post(semaphore) < 0) {
        perror("sem_post");
        exit(1);
    }

    for (int x = 0; x < GB / buf_size; ++x) {
        int total_received = 0;
        while (total_received < buf_size) {
            int received = read(pipe_from_parent[0], recv_buf + total_received, buf_size - total_received);
            if (received == -1)
            {
                perror("read");
                exit(1);
            }
            total_received += received;
        }
    }
    for (int y = 0; y < GB / buf_size; ++y) {
        if (write(pipe_to_parent, send_buf, buf_size) == -1) {
            perror("write");
            exit(1);
        }
    }
    free(send_buf);
    free(recv_buf);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s [write_read_buf_size]\n", argv[0]);
        exit(1);
    }

    int buf_size = 1 << atoi(argv[1]);

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
        child(pipe_to_parent, pipe_to_child, buf_size, semaphore);
        close(pipe_to_child[0]);
        close(pipe_to_parent[1]);
    } else {
        // Parent process
        close(pipe_to_child[0]); // Close read end of parent-to-child pipe
        close(pipe_to_parent[1]); // Close write end of child-to-parent pipe
        parent(pipe_to_child, pipe_to_parent, buf_size, semaphore);
        cclose(pipe_to_child[1]);
        close(pipe_to_parent[0]); 
    }

    sem_destroy(semaphore);

    return 0;
}