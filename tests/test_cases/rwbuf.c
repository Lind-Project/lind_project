#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>

int main(void)
{
	int fd;

	if ((fd = open("testfile.txt",O_RDONLY)) < 0) {
		perror("open()");
		exit(EXIT_FAILURE);
	}

    char buffer[2048];
    if(read(fd, buffer, 19) != 19)  return 1;
    printf("%s\n",buffer);

	
	close(fd);

	return 0;
}
