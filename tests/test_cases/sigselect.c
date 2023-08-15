#include <errno.h>
#include <string.h>
#include <signal.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h> 
#include <poll.h>

#define TIMEOUT -1

void handler(int signum)
{
    printf("Signal Handler Test!\n");
    printf("Exiting Cage 2\n");
    fflush(stdout);
}

int main(void)
{
    struct sigaction new_action;
    struct sigaction old_action;

    pid_t pid = fork();

    if (pid == 0) {
        // Cage 2
        printf("Cage 2 pid: %ld\n", (long)getpid());
        printf("Handler function ptr %p\n", handler);
        fflush(stdout);

        new_action.sa_handler = handler;

        sigaction(SIGUSR2, &new_action, NULL);
        sigaction(SIGUSR2, NULL, &old_action);

        if (new_action.sa_handler == old_action.sa_handler) {
                printf("Successfully changed the signal handler for Signal %d\n", SIGUSR2);
                fflush(NULL);
        } else {
                printf("Fail to correctly change the signal handler for Signal %d\n", SIGUSR2);
                fflush(NULL);
        }

        fd_set read_fds;
    
        FD_ZERO(&read_fds);
            
        FD_SET(STDIN_FILENO, &read_fds);
        
        // Use the select function to wait for the readable status of standard input
        int num_fds = select(STDIN_FILENO + 1, &read_fds, NULL, NULL, NULL);
        if (num_fds < 0 && errno == EINTR) {
            printf("Error code: %d\n", errno);
            printf("EINTR error\n");
            fflush(NULL);
        }
        
    }

    else {
            // Cage 1
            sleep(2);
            printf("Killing Cage 2 using PID: %ld\n", (long)pid);
            fflush(stdout);
            kill(pid, SIGUSR2);
            sleep(2);
    }
    return 0;
}
