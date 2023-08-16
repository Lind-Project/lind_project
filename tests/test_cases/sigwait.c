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
        kill(getppid(), SIGUSR2);
        for(;;); // Didn't return, so wait() blocked
    } else {   
        sleep(5);
        // Set signal handler
        struct sigaction sa_usr;
        sa_usr.sa_flags = 0;
        sa_usr.sa_handler = sig_usr;  

        sigaction(SIGUSR2, &sa_usr, NULL);
        wait(NULL);
    }
    return 0;
}
