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
        printf("[Child] process start..\n");
        // Set signal handler
        struct sigaction sa_usr;
        sa_usr.sa_flags = 0;
        sa_usr.sa_handler = sig_usr;  

        sigaction(SIGUSR2, &sa_usr, NULL);
        
        /* nanosleep() test */
        struct timespec req;
        req.tv_nsec = 0;        
        req.tv_sec = 5; 
        int ret = nanosleep(&req, 0);
        if(ret < 0) {
            perror("nanosleep");
            fflush(NULL);
        }
        printf("[Child] nanosleep() ends: %d\n", ret);

        /* clock_nanosleep() test */
        struct timespec reqtp, remtp;
        reqtp.tv_nsec = 0;
        reqtp.tv_sec = 20;
        int clock_ret = clock_nanosleep(CLOCK_REALTIME, 0, &reqtp, &remtp);
        if(errno == EINTR){
            perror("clock_nanosleep");
            fflush(NULL);
        }
        printf("[Child] clock_nanosleep() ends: %d\n", clock_ret);

        /* usleep() test */
        unsigned int microseconds = 5000000;  // 5sec
        int uret = usleep(microseconds);
        if(uret < 0 && errno == EINTR) {
            perror("usleep");
        }
        printf("[Child] usleep() ends: %d\n", uret);


        exit(0);
    } else {
        printf("[Parent] process start..\n");
        sleep(3);
        printf("[Parent] Sending signal for nanosleep()\n");
        kill(child_pid, SIGUSR2);
        sleep(5);
        printf("[Parent] Sending signal for clock_nanosleep()\n");
        kill(child_pid, SIGUSR2);
        sleep(3);
        printf("[Parent] Sending signal for usleep()\n");
        kill(child_pid, SIGUSR2);
        wait(NULL);
        return 0;
    }
}