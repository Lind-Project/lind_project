#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include<sys/wait.h> 

int main(int argc, char *argv[])
{
    int fd = open("write.txt", O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    pid_t child = fork();

    if(child == 0)
    {
        int backup = dup(STDOUT_FILENO);   // make backup of stdout
        dup2(fd,STDOUT_FILENO);// use dup2 so child printf() goes into file, not screen
        printf("I'm the child\n");
        fflush(stdout);
        dup2(backup,STDOUT_FILENO);
	printf("back to stdout\n");
	fflush(stdout);
	exit(0);
    }
    else
    {
        printf("I'm the parent\n");
	fflush(stdout);
    }
    
    wait(NULL);
    printf("all done\n");
    fflush(stdout);
    close(fd);
    return 0;
}
