#undef _GNU_SOURCE
#define _GNU_SOURCE


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <errno.h>
#include <time.h>

static void sig_usr(int signum){
   printf("Received signal %d\n", signum);
}

int main() {
    pid_t child_pid = fork();
    
    if(child_pid < 0){
        perror("fork");
        return EXIT_FAILURE;
    } else if(child_pid == 0) {
        printf("Child process start..\n");
        // Set signal handler
        struct sigaction sa_usr;
        sa_usr.sa_flags = 0;
        sa_usr.sa_handler = sig_usr;  

        sigaction(SIGUSR2, &sa_usr, NULL);
        
        struct timespec req;
    
        req.tv_sec = 0;        
        req.tv_sec = 10; 
        int ret = nanosleep(&req, 0);
        printf("Nanosleep failed..\n");
        if(ret < 0) {
            perror("nanosleep");
            fflush(NULL);
        }
        exit(0);
    } else {
        printf("Parent process start..\n");
        sleep(3);
        kill(SIGUSR2, child_pid);
        wait(NULL);
        return 0;
    }
}