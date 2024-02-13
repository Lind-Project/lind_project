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
    printf("Signal Pipe Test!\n");
    fflush(stdout);
    exit(0);
}

int main(int argc, char *argv[])
{
    struct sigaction action;
    action.sa_handler = handler;
    sigaction(SIGPIPE, &action, NULL);

    int pipefd[2];
    pid_t pid;
    char buf_str[] = "0123456789";
    char buf;

    if (pipe(pipefd) == -1)
    {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid = fork();
    if (pid == -1)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        close(pipefd[1]); 
        close(pipefd[0]); // close both pipe ends
	sleep(3);
        exit(0);
    }
    else
    {                     /* Parent writes buf_str to pipe */
        close(pipefd[0]); /* Close unused read end */
        while(1) {
            write(pipefd[1], buf_str, strlen(buf_str));
            sleep(1);
        }
        close(pipefd[1]); /* Reader will see EOF */
        wait(NULL);       /* Wait for child */
        exit(0);
    }
}

