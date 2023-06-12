#include <stdio.h> 
#include <fcntl.h> 
#include <stdlib.h> 
#include <unistd.h>

int main(int argc, char *argv[])
{

    int i = atoi(argv[1]);

    unsigned long long WRITE_BUFFER_SIZE = 1UL << i;
    unsigned long long NUMBER_OF_WRITES = 1UL << (30 - i);
    unsigned long long OUTLOOP = 1UL << 4;
    char* buffer = malloc(sizeof(char) * WRITE_BUFFER_SIZE); 

    for (int i = 0; i < WRITE_BUFFER_SIZE; i++) buffer[i] = 'A';
    
    for (int n = 0; n < OUTLOOP; n++) {
   	for (int count = 0; count < NUMBER_OF_WRITES; count++)
    	{
        	write(STDOUT_FILENO, buffer, WRITE_BUFFER_SIZE);
    	}
    }
    free(buffer);

}

