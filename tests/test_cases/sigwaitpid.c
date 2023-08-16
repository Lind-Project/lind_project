#undef _GNU_SOURCE
#define _GNU_SOURCE


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/file.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <signal.h>
#include <errno.h>


static void sig_usr(int signum){
   printf("Received signal %d\n", signum);
}

int main() {
    pid_t child1_pid = fork();

    if(child1_pid < 0) {
        perror("fork");
        return EXIT_FAILURE;
    } else if(child1_pid == 0) {    // Child 1 process
        printf("Child1 process start...\n");
        for(;;); // Didn't return, so wait() blocked
    } else {   
        pid_t child2_pid = fork();
        if(child2_pid < 0) {    // Child 2 process
            perror("fork");
            return EXIT_FAILURE;
        } else if(child2_pid == 0) {
            printf("Child2 process start...\n");
            kill(getppid(), SIGUSR2);
        } else {
            // Set signal handler
            struct sigaction sa_usr;
            sa_usr.sa_flags = 0;
            sa_usr.sa_handler = sig_usr;      
            // Register SIG handler
            sigaction(SIGUSR2, &sa_usr, NULL);
            int ret = wait(NULL);
            if(ret < 0 && errno == EINTR) {
                perror("wait");
                printf("Errno: %d\n", errno);
                return EXIT_FAILURE;
            }
        }
    }
    return 0;
}
