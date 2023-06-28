#include <errno.h>
#include <string.h>
#include <signal.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

void handler(int signum)
{
    printf("Signal Handler Test!\n");
    printf("Exiting Cage 2\n");
    fflush(stdout);
    exit(0);
}

int main(void)
{
    struct sigaction new_action;
    struct sigaction old_action;

    pid_t pid = fork();

    if (pid == 0)
    {
        // Cage 2
        printf("Cage 2 pid: %ld\n", (long)getpid());
        printf("Handler function ptr %p\n", handler);
        fflush(stdout);

        new_action.sa_handler = handler;

        sigaction(SIGUSR2, &new_action, NULL);
        sigaction(SIGUSR2, NULL, &old_action);

        if (new_action.sa_handler == old_action.sa_handler)
        {
            printf("Successfully changed the signal handler for Signal %d\n", SIGUSR1);
            fflush(NULL);
        }
        else
        {
            printf("Fail to correctly change the signal handler for Signal %d\n", SIGUSR1);
            fflush(NULL);
        }
        while (1)
            ;
    }

    else
    {
        // Cage 1
        sleep(2);
        printf("Killing Cage 2 using PID: %ld\n", (long)pid);
        fflush(stdout);
        kill(pid, SIGUSR2);
        sleep(2);
    }
    return 0;
}