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

// static void sig_usr(int signum){
//    printf("Received signal %d\n", signum);
// }

// int main() {
//     pid_t child_pid = fork();
    
//     if(child_pid < 0){
//         perror("fork");
//         return EXIT_FAILURE;
//     } else if(child_pid == 0) {
//         printf("[Child] process start..\n");
//         // Set signal handler
//         struct sigaction sa_usr;
//         sa_usr.sa_flags = 0;
//         sa_usr.sa_handler = sig_usr;  

//         sigaction(SIGUSR2, &sa_usr, NULL);
        
//         struct timespec req;
//         req.tv_nsec = 0;        
//         req.tv_sec = 5; 
//         int ret = nanosleep(&req, 0);
//         if(ret < 0) {
//             perror("nanosleep");
//             fflush(NULL);
//         }
//         printf("[Child] nanosleep() ends...\n");
//         struct timespec reqtp, remtp;
//         reqtp.tv_nsec = 0;
//         reqtp.tv_sec = 20;
//         int clock_ret = clock_nanosleep(CLOCK_REALTIME, 0, &reqtp, &remtp);
//         printf("clock_nanosleep returns: %d\n", clock_ret);
//         if(clock_ret < 0){
//             perror("clock_nanosleep");
//             fflush(NULL);
//         }

//         exit(0);
//     } else {
//         printf("[Parent] process start..\n");
//         sleep(3);
//         printf("[Parent] Sending signal for nanosleep()\n");
//         kill(child_pid, SIGUSR2);
//         sleep(5);
//         printf("[Parent] Sending signal for clock_nanosleep()\n");
//         kill(child_pid, SIGUSR2);
//         wait(NULL);
//         return 0;
//     }
// }
void interrupt_handler(int signum) {
    // Empty signal handler, just to interrupt clock_nanosleep
}

int main() {
    struct timespec req, rem;
    
    req.tv_sec = 5;   // 5 seconds
    req.tv_nsec = 0;  // 0 nanoseconds
    
    // Set up signal handler for SIGINT
    signal(SIGINT, interrupt_handler);
    
    printf("Sleeping for 5 seconds. Press Ctrl+C to interrupt.\n");
    
    if (clock_nanosleep(CLOCK_REALTIME, 0, &req, &rem) != 0) {
        // Check if clock_nanosleep was interrupted by a signal
        if (errno == EINTR) {
            printf("clock_nanosleep interrupted by a signal.\n");
            printf("Remaining time: %ld seconds %ld nanoseconds\n", rem.tv_sec, rem.tv_nsec);
        } else {
            perror("clock_nanosleep failed");
            return 1;
        }
    }
    
    return 0;
}
