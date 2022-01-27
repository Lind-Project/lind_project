#include <stdio.h> 
#include <fcntl.h> 
#include <stdlib.h> 
#include <unistd.h>
#include <time.h>


#define WRITE_BUFFER_SIZE    1UL << 8

int main()
{
    char buffer[WRITE_BUFFER_SIZE] = "";
    char readbuffer[WRITE_BUFFER_SIZE];
    for (int i = 0; i < WRITE_BUFFER_SIZE - 1; i++) buffer[i] = 'A';
    buffer[WRITE_BUFFER_SIZE] = 0;
	
    for (int j = 0; j < 1000; j++) {

    	int test_fd = open("filetimes.txt", O_RDWR);
    	write(test_fd, buffer, WRITE_BUFFER_SIZE);
    	lseek(test_fd, 0, SEEK_SET);
    	read(test_fd, readbuffer, WRITE_BUFFER_SIZE);
    	close(test_fd);
    }

    printf("%s\n", readbuffer);


    
}

