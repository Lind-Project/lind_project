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
    } else if(child1_pid == 0) {    
        pid_t child1_1_pid = fork();
        if(child1_1_pid < 0) {
            perror("fork");
            return EXIT_FAILURE;
        } else if(child1_1_pid == 0) {  // Child 1-1 process
            printf("Child1-1 process start...\n");
            for(;;);    // never returns
        } else {    // Child 1 process
            printf("Child 1 prcess start...\n");
            // Set signal handler
            struct sigaction sa_usr;
            sa_usr.sa_flags = 0;
            sa_usr.sa_handler = sig_usr;
            // Register signal handler
            sigaction(SIGUSR2, &sa_usr, NULL);

            int ret = waitpid(child1_1_pid, NULL, 0);
            if (ret < 0) {
                perror("waitpid");
                printf("Error code: %d\n", errno);
                return 0;
            }
            printf("Child 1 process end..\n");
        }
    } else {   // Father process 
        sleep(5);
        printf("Father process start...\n");
        sleep(5);
        kill(child1_pid, SIGUSR2);
        waitpid(child1_pid, NULL, 0);
        printf("Father process end...\n");
    }
    return 0;
}
