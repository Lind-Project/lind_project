#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// In RawPOSIX
#define FIFO_NAME "/myfifo"

long long gettimens() {
    struct timespec tp;
    clock_gettime(CLOCK_MONOTONIC, &tp);
    return (long long)tp.tv_sec * 1000000000LL + tp.tv_nsec;
}

int main(int argc, char**argv)
{
    // char buf[1024];
    int fd;
    pid_t pid;

    int i = atoi(argv[1]);
    int m = atoi(argv[2]);
    unsigned long long WRITE_BUFFER_SIZE = 1UL << i;
    unsigned long long READ_BUFFER_SIZE = 1UL << i;
    unsigned long long NUMBER_OF_WRITES = 1UL << (30 - i);
    // unsigned long long OUTLOOP = 1UL << 5; 
    char *buffer = malloc(sizeof(char) * WRITE_BUFFER_SIZE);

    for (int i = 0; i < WRITE_BUFFER_SIZE; i++)
        buffer[i] = 'A';

    char *buf = (char *)calloc(READ_BUFFER_SIZE, sizeof(char));

    pid = fork();

    if(pid < 0) {
        printf("Failed to fork.\n");
        exit(1);
    }

    if(pid > 0) {
        if((fd = open(FIFO_NAME, O_WRONLY)) < 0) {
            printf("Open failed.\n");
            exit(1);
        }

        fprintf(stderr, "write-start: %lld\n", gettimens());
        fflush(stderr);  

        for (int count = 0; count < NUMBER_OF_WRITES; count++){
            write(fd, buffer, WRITE_BUFFER_SIZE);
        }
        free(buffer);
        exit(0);
    }

    if(pid == 0) {
        if((fd = open(FIFO_NAME, O_RDONLY)) < 0) {
            printf("Open failed.\n");
            exit(1);
        }
        int total_read = 0;
        int readlen = 0;

        while ((readlen = read(fd, buf, READ_BUFFER_SIZE)) > 0)
        {
        }
        fprintf(stderr, "read-end: %lld\n", gettimens());
        fflush(stderr);

        free(buf);
        close(fd);
        exit(0);
    }

    return 0;
}
