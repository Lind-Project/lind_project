
#include <stdio.h> 
#include <sys/types.h> 
#include <unistd.h> 
#include <fcntl.h> 
#include <errno.h>

int main() 
{ 
  
    int pid = fork(); 
    
    if (pid == 0) 
    {
        printf("Child: Testing open in child: pid %d!\n", pid); 

        int fd = open("foo.txt", O_RDONLY | O_CREAT);

        printf("Child: Pid %d opened fd %d\n", pid, fd);

        close(fd);
    }
    else
    {
        printf("Parent: Testing open in parent: pid %d!\n", pid); 

        int fd = open("foo.txt", O_RDONLY | O_CREAT);

        printf("Parent: Pid %d opened fd %d\n", pid, fd);

        close(fd);
    }
   

    return 0; 
} 
