#include <stdio.h> 
#include <fcntl.h> 
#include <stdlib.h> 
#include <unistd.h>
#include <time.h>


#define READ_BUFFER_SIZE    1UL << 30
#define READ_BUFFER_CHUNK   1 << 17


int main()
{

    char* buffer = (char*)calloc(READ_BUFFER_SIZE, sizeof(char));

    int total_read = 0;
    int readlen = 0;

    clock_t before = clock();
    while((readlen = read(STDIN_FILENO, buffer + total_read, READ_BUFFER_CHUNK)) > 0){
        total_read += readlen;

    }
    clock_t difference = clock() - before;
    int msec = difference * 1000 / CLOCKS_PER_SEC;

    fprintf(stderr, "read msec: %d ms\n", msec);

    
}
