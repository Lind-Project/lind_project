#include <stdio.h> 
#include <fcntl.h> 
#include <stdlib.h> 
#include <unistd.h>
#include <time.h>


#define WRITE_BUFFER_SIZE    1UL << 14
#define NUMBER_OF_WRITES     1UL << 11

int main()
{

    char buffer[WRITE_BUFFER_SIZE] = "";

    for (int i = 0; i < WRITE_BUFFER_SIZE; i++) buffer[i] = 'A';

    clock_t before = clock();

    for (int count = 0; count < NUMBER_OF_WRITES; count++)
    {
        if (count == (NUMBER_OF_WRITES - 1)) buffer[WRITE_BUFFER_SIZE - 1] = '\0';
        write(STDOUT_FILENO, buffer, WRITE_BUFFER_SIZE);
    } 
    clock_t difference = clock() - before;
    int msec = difference * 1000 / CLOCKS_PER_SEC;

    fprintf(stderr, "write msec: %d ms\n", msec);
}

