#include <stdio.h> 
#include <fcntl.h> 
#include <stdlib.h> 
#include <unistd.h>
#include <time.h>
#include <pthread.h>
#include <sys/ipc.h>
#include <signal.h>
#include <sys/wait.h>


/*--------Main function--------*/
int main(int argc, char *argv[]) {

    pid_t pid = fork();

    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {

    } else {
        wait(NULL); // Wait for the child process to finish

    }

    return 0;
}