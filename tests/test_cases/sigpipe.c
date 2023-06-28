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
    if(sig == 13) {
        printf("Signal Pipe Test!\n");
        fflush(stdout);
        exit(0);
    }
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

    if (pid == 0)
    {                     /* Child reads from pipe */
        close(pipefd[1]); /* Close unused write end */
        int count = 0;

        while (read(pipefd[0], &buf, 1) > 0) {
            count++;
            if (count > 20) {
                write(STDOUT_FILENO, "exiting child\n", 14);
                exit(0);
            }
        }
        write(STDOUT_FILENO, "\n", 1);
        close(pipefd[0]);
        exit(0);
    }
    else
    {                     /* Parent writes buf_str to pipe */
        close(pipefd[0]); /* Close unused read end */
        while(1) {
            write(STDOUT_FILENO, "parent writing\n", 15);
            write(pipefd[1], buf_str, strlen(buf_str));
            sleep(1);
        }
        close(pipefd[1]); /* Reader will see EOF */
        wait(NULL);       /* Wait for child */
        exit(0);
    }
}
