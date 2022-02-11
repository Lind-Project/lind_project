#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define BUFSIZE 16

int main(int argc, char *argv[])
{
    int pipefd[2];
    pid_t cpid;
    char buf[BUFSIZE] = {0};

    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }
    cpid = fork();
    if (cpid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    if (cpid == 0) {    /* Child reads from pipe */
        printf("I'm child with pid: %d\n", cpid);

        close(pipefd[1]);          /* Close unused write end */
        read(pipefd[0], buf, BUFSIZE);
        write(STDOUT_FILENO, buf, BUFSIZE);

        close(pipefd[0]);
        _exit(EXIT_SUCCESS);
    } else {            /* Parent writes argv[1] to pipe */
        close(pipefd[0]);          /* Close unused read end */
        printf("about to write to pipe in parent\n");
        printf("I'm parent with pid: %d\n", cpid);

	    write(pipefd[1], "Hey Nick!\n", strlen("Hey Nick!\n"));
        close(pipefd[1]);          /* Reader will see EOF */
        wait(NULL);                /* Wait for child */
        exit(EXIT_SUCCESS);
    }
}

