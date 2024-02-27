#include <errno.h>
#include <string.h>
#include <signal.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <wait.h>

void handler(int sig)
{
    printf("Signal Child Test!\n");
    fflush(stdout);
    exit(0);
}
int main()
{
    struct sigaction action;
    action.sa_handler = handler;
    sigaction(SIGCHLD, &action, NULL);
    
    pid_t pid = fork();
    if (pid == 0)
    {
        sleep(1);
        exit(0);
    }
    waitpid(pid, NULL, 0);
    return 0;
}

