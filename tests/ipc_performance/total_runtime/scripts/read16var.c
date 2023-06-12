#include <stdio.h> 
#include <fcntl.h> 
#include <stdlib.h> 
#include <unistd.h>


int main(int argc, char *argv[])
{
    int i = atoi(argv[1]);

    unsigned long long READ_BUFFER_CHUNK = 1UL << i;

    char* buffer = (char*)calloc(READ_BUFFER_CHUNK, sizeof(char));

    int total_read = 0;
    int readlen = 0;

    while((readlen = read(STDIN_FILENO, buffer, READ_BUFFER_CHUNK)) > 0){
    }

    free(buffer);
    
}
