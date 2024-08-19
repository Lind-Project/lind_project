#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>
#include "lind_platform.h"

unsigned long long WRITE_BUFFER_SIZE = 1ULL << 16;
unsigned long long NUMBER_OF_WRITES = 1ULL << (30 - 16);
unsigned long long READ_BUFFER_SIZE = 1ULL << 16;
unsigned long long OUTLOOP = 1UL << 5;

int fd[2];

long long gettimens() {
    struct timespec tp;
    clock_gettime(CLOCK_MONOTONIC, &tp);
    return (long long)tp.tv_sec * 1000000000LL + tp.tv_nsec;
}

void* writerThreadFuncion(void *arg) {
    (void)arg;

    // Cage 2 should close the read end
    if(lind_close(fd[0], 2) < 0) {
        perror("writer lind_close failed\n");
    }

    // preapre the write buffer
    char *buffer = malloc(sizeof(char) * WRITE_BUFFER_SIZE);
    for (int i = 0; i < WRITE_BUFFER_SIZE; i++) buffer[i] = 'A';

    fprintf(stderr, "write-start: %lld\n", gettimens());
    fflush(stderr);   

    for (unsigned long long count = 0; count < NUMBER_OF_WRITES; count++) {
        lind_write(fd[1], buffer, WRITE_BUFFER_SIZE, 2);
    }
    lind_close(fd[1], 2);
    free(buffer);
    return NULL;
}

void* readerThreadFunction(void *arg) {
    (void)arg;

    // Cage 3 should close the write end
    if(lind_close(fd[1], 3) < 0) {
        perror("reader lind_close failed\n");
    }

    // prepare the read buffer
    char *buffer = (char *)calloc(READ_BUFFER_SIZE, sizeof(char));

    while ((lind_read(fd[0], buffer, READ_BUFFER_SIZE, 3)) > 0) {}
    
    fprintf(stderr, "read-end: %lld\n", gettimens());
    fflush(stderr);
    free(buffer);
    return NULL;
}

int main(int argc, char *argv[])
{   
    // Setup the buffer sizes, default writer size is 2^16
    if (argc > 2) {
        int digitWriter = atoi(argv[1]);
        int digitReader = atoi(argv[2]);
        if (digitWriter >= 0 && digitWriter <= 63) {
            WRITE_BUFFER_SIZE = 1ULL << digitWriter;
            NUMBER_OF_WRITES = 1ULL << (30 - digitWriter);
            READ_BUFFER_SIZE = 1ULL << digitReader;
        } else {
            perror("power out of range");
            exit(EXIT_FAILURE);
        }
    }

    lindrustinit(0);

    // make the pipes
    if (lind_pipe(fd, 1) < 0) {
		perror("pipe()");
		exit(EXIT_FAILURE);
	}

    // create the cages (these don't really fork)
    rustposix_thread_init(1, 0);
    if(lind_fork(2, 1) < 0) {
        perror("lind_fork() failed\n");
        return 1;
    } else if (lind_fork(3, 1) < 0) {
        perror("lind_fork() failed\n");
        return 1;
    }

    // then Cage 1 can close both ends
    lind_close(fd[0], 1);
    lind_close(fd[1], 1);

    // create the reader and writer threads
    pthread_t writerThread, readerThread;

    if(pthread_create(&writerThread, NULL, writerThreadFuncion, NULL)) {
        perror("Failred to create writer thread!");
        return 1;
    }

    if(pthread_create(&readerThread, NULL, readerThreadFunction, NULL)) {
        perror("Failred to create reader thread!");
        return 1;
    }

    pthread_join(readerThread, NULL);
    pthread_join(writerThread, NULL);

    return 0;
}
