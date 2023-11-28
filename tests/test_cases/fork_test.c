#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid;

    pid = vfork(); // Create a child process

    if (pid < 0) {
        // Error occurred
        perror("vfork failed");
        exit(EXIT_FAILURE);
    } else if (pid != 0) {
        // Child process
        printf("Child process, PID = %d\n", getpid());
        _exit(EXIT_SUCCESS); // Use _exit to exit the child process
    } else {
        // Parent process
        wait(NULL); // Wait for the child process to finish
        printf("Parent process, PID = %d\n", getpid());
    }

    return 0;
}