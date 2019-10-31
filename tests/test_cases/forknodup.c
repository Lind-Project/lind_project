#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char *argv[])
{
    int fd = open("write.txt", O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    pid_t child = fork();

    if(child == 0)
    {
    
        printf("I'm the child\n");
        fflush(stdout);

    }
    else
    {
	printf("I'm the PARENT\n");
        fflush(stdout);
    }
    wait(NULL);

    printf("all done\n");
    close(fd);
    return 0;
}
