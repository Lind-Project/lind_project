#undef _GNU_SOURCE
#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <semaphore.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <signal.h>
#include <errno.h>

static void sig_usr(int signum){
    printf("Received signal %d\n", signum);
}

int main() {
    if (mkfifo("testfifo", S_IRUSR | S_IWUSR) == -1) {
        perror("mkfifo");
        return 1;
    }

    pid_t child_open_pid = fork();

    if (child_open_pid == -1) {
        perror("fork");
        return 1;
    } else if (child_open_pid == 0) {
        // Child process: Wait for the signal and handle open interruption
        printf("Child process waiting for the signal...\n");
        
        // Set signal handler
        struct sigaction sa_usr;
        sa_usr.sa_flags = 0;
        sa_usr.sa_handler = sig_usr;   

        sigaction(SIGUSR2, &sa_usr, NULL);


        printf("Child process received the signal.\n");

        // Try to open the FIFO
        int child_fd = open("testfifo", O_RDONLY);
        if (child_fd < 0) {
            perror("open");
        } else {
            printf("Child process successfully opened the FIFO.\n");
            close(child_fd);
        }

        exit(0);
    } else {
        // Parent process
        sleep(2);

        // Send SIGUSR2 signal to child_open_pid
        printf("Sending SIGUSR2 signal to child process...\n");
        kill(child_open_pid, SIGUSR2);

        // Wait for the child process to finish
        waitpid(child_open_pid, NULL, 0);

        // Remove the FIFO
        unlink("testfifo");
    }

    return 0;
}
