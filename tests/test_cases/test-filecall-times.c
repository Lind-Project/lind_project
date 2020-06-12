#include <stdio.h> 
#include <fcntl.h> 
#include <stdlib.h> 
#include <unistd.h>
#include <time.h>


#define WRITE_BUFFER_SIZE    1UL << 8

int main()
{

    char buffer[WRITE_BUFFER_SIZE] = "";

    for (int i = 0; i < WRITE_BUFFER_SIZE; i++) buffer[i] = 'A';

    clock_t before;
    clock_t difference;
    int usec;
    char readbuffer[WRITE_BUFFER_SIZE];

    before = clock();
    int test_fd = open("filetimes.txt", O_RDWR | O_CREAT | O_TRUNC);
    difference = clock() - before;
    usec = difference * 1000000 / CLOCKS_PER_SEC;
    fprintf(stderr, "open usec: %d us\n", usec);

    before = clock();
    write(test_fd, buffer, WRITE_BUFFER_SIZE);
    difference = clock() - before;
    usec = difference * 1000000 / CLOCKS_PER_SEC;
    fprintf(stderr, "write usec: %d us\n", usec);

    before = clock();
    lseek(test_fd, 0, SEEK_SET);
    difference = clock() - before;
    usec = difference * 1000000 / CLOCKS_PER_SEC;
    fprintf(stderr, "seek usec: %d us\n", usec);

    before = clock();
    read(test_fd, readbuffer, WRITE_BUFFER_SIZE);
    difference = clock() - before;
    usec = difference * 1000000 / CLOCKS_PER_SEC;
    fprintf(stderr, "read usec: %d us\n", usec);

    before = clock();
    close(test_fd);
    difference = clock() - before;
    usec = difference * 1000000 / CLOCKS_PER_SEC;
    fprintf(stderr, "close usec: %d us\n", usec);

    printf("%s", readbuffer);


    
}