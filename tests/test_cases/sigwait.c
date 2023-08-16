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
    printf("Father process start...\n");
    if(child1_pid < 0) {
        perror("fork");
        return EXIT_FAILURE;
    } else if(child1_pid == 0) {    // Child 1 process
        printf("Child1 process start...\n");
        for(;;); // Didn't return, so wait() blocked
    } else {   
        printf("Father process waiting...\n");
        // Set signal handler
        struct sigaction sa_usr;
        sa_usr.sa_flags = 0;
        sa_usr.sa_handler = sig_usr;      
        // Register SIG handler
        sigaction(SIGINT, &sa_usr, NULL);
        if(wait(NULL) < 0) {
            perror("wait");
            return 0;
        }
    }
    return 0;
}
