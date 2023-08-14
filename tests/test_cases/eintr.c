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


int main() {
    printf("Thread 1\n");
    char buf[512];
    int n;
    // Set signal handler
    struct sigaction sa_usr;
    sa_usr.sa_flags = 0;
    sa_usr.sa_handler = sig_usr;   

    sigaction(SIGUSR1, &sa_usr, NULL);

    while(1){
        // Blocking thread1
        if((n = read(STDIN_FILENO, buf, 511)) == -1){
            if(errno == EINTR){
                printf("Thread 1 is interrupted by EINTR\n");
                break;
            }
        }
    }

    return 0;
}
