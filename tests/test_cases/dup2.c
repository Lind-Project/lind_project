#include<stdlib.h> 
#include<unistd.h> 
#include<stdio.h> 
#include<fcntl.h> 

#define BUFSIZE 32

int main() 
{ 
    char buf[BUFSIZE] = {0};
    
    printf("Testing dup2\n");
    fflush(stdout);

    int fd = open("dup2test.txt",O_WRONLY | O_APPEND); 
    

    // here the newfd is the file descriptor of stdout (i.e. 1) 
    int stdout_backup = dup(STDOUT_FILENO);

    dup2(fd, STDOUT_FILENO) ;  
          
    // All the printf statements will be written in the file 
    // "dup2test.txt" 
    printf("I will be printed in the file dup2test.txt\n"); 
    fflush(stdout);

    dup2(stdout_backup, STDOUT_FILENO);
    close(stdout_backup);


    printf("I should be printed before the file contents!\n");
    fflush(stdout);
    
    fd = open("dup2test.txt", O_RDONLY);
    read(fd, buf, BUFSIZE);

    printf(buf);
    fflush(stdout);
    close(fd);


      
return 0; 
} 
