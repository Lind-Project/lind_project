#include <errno.h>
#include <string.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

static void sig_usr(int signum){
    printf("Thread1 received signal %d\n", signum);
}

// Thread function
void* th1(void* arg){
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
    
    return NULL;
}

void* th2(void* arg){
    printf("Thread 2\n");
    char buf[512];
    int n;

    while(1){
        // Blocking thread2
        if((n = read(STDIN_FILENO, buf, 511)) == -1){
            // Print any signals received
            sigset_t pending_signals;
            if (sigpending(&pending_signals) == 0){
                for (int i = 1; i < NSIG; i++) {
                    if (sigismember(&pending_signals, i)){
                        printf("Thread 2 received signal: %d\n", i);
                    }
                }
            } else {
                perror("sigpending");
            }
            if(errno == EINTR){
                printf("Thread 2 is interrupted by EINTR\n");

                break;
            }
        }
    }
    
    return NULL;
}
 
int main(void){
    /* Thread 1 */
    pthread_t thread1;
    if (pthread_create(&thread1, NULL, th1, NULL) != 0){
        perror("Thread1 failed");
    }

    /* Thread 2 */
    pthread_t thread2;
    if (pthread_create(&thread2, NULL, th2, NULL) != 0){
        perror("Thread2 failed");
    }
    sleep(1);

    pthread_kill(thread1, SIGUSR1);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    printf("End\n");
    return 0;
}
