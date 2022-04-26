#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
 
int main()
{
    pid_t cpid;
    cpid = fork();
    if (cpid == 0)
        exit(0);           /* terminate child */
    else
        wait(NULL); /* reaping parent */
    printf("Parent pid = %d\n", getpid());
    printf("Child pid = %d\n", cpid);
    fflush(stdout);

    return 0;
}

