#undef _GNU_SOURCE
#define _GNU_SOURCE

#include <ctype.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>

static void sig_usr(int signum){
    printf("Received signal %d\n", signum);
}

int main() {
    pid_t pid = fork();

    if (pid == 0) {
        // Set signal handler
        struct sigaction sa_usr;
        sa_usr.sa_flags = 0;
        sa_usr.sa_handler = sig_usr;   

        sigaction(SIGUSR2, &sa_usr, NULL);

        // Blocking read
        int ret = open("test.txt", O_RDONLY);
        if(ret < 0) {
            if(errno == EINTR){
                printf("Error code: %d\n", errno);
                printf("EINTR error\n");
                fflush(NULL);
            }
        }
        
    } else {
        // Cage 1
        sleep(2);
        printf("Killing open() thread using PID: %ld\n", (long)pid);
        fflush(stdout);
        kill(pid, SIGUSR2);
        sleep(2);
    }
    return 0;
}
