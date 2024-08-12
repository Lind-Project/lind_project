#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

long long gettimens() {
    struct timespec tp;
    clock_gettime(CLOCK_MONOTONIC, &tp);
    return (long long)tp.tv_sec * 1000000000LL + tp.tv_nsec;
}

int main(int argc, char *argv[])
{

    int i = atoi(argv[1]);

    unsigned long long WRITE_BUFFER_SIZE = 1UL << i;
    unsigned long long NUMBER_OF_WRITES = 1UL << (30 - i);
    unsigned long long OUTLOOP = 1UL << 5;
    char *buffer = malloc(sizeof(char) * WRITE_BUFFER_SIZE);

    for (int i = 0; i < WRITE_BUFFER_SIZE; i++)
        buffer[i] = 'A';

    fprintf(stderr, "write-start: %lld\n", gettimens());
    fflush(stderr);    

    for (int count = 0; count < NUMBER_OF_WRITES; count++)
    {
        write(STDOUT_FILENO, buffer, WRITE_BUFFER_SIZE);
    }
    free(buffer);
}
