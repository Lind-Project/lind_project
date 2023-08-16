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
    struct sigaction new_action;
    struct sigaction old_action;

    pid_t pid = fork();

    if (pid == 0) {
        char buf[512];
        // Set signal handler
        struct sigaction sa_usr;
        sa_usr.sa_flags = 0;
        sa_usr.sa_handler = sig_usr;   

        sigaction(SIGINT, &sa_usr, NULL);

        // Blocking read
        int ret = read(STDIN_FILENO, buf, 511);
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
        printf("Killing Cage 2 using PID: %ld\n", (long)pid);
        fflush(stdout);
        kill(pid, SIGUSR2);
        sleep(2);
    }
    return 0;
}
