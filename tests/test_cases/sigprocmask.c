#include <errno.h>
#include <string.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

static void sig_usr(int signum){
    if(signum == SIGUSR1){
        printf("SIGUSR1 received\n");
    }else{
        printf("signal %d received\n", signum);
    }
}

// Thread 1
void* th1(void* arg){
    printf("I am thread %ld\n", (long)arg);
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

// Thread 2
void* th2(void* arg){
    printf("I am thread02\n");
    char buf[512];
    int n;
    // Set signal handler
    struct sigaction sa_usr;
    sa_usr.sa_flags = 0;
    sa_usr.sa_handler = sig_usr;   

    sigaction(SIGUSR1, &sa_usr, NULL);

    while(1){
        // Blocking thread2
        if((n = read(STDIN_FILENO, buf, 511)) == -1){
            if(errno == EINTR){
                printf("Thread 2 is interrupted by EINTR\n");
                break;
            }
        }
    }
    
    return NULL;
}
 
int main(void){
    /* Test main */
    char buf[512];
    int n;
    // Set signal handler
    struct sigaction sa_usr;
    sa_usr.sa_flags = 0;
    sa_usr.sa_handler = sig_usr;   
    
    sigaction(SIGUSR1, &sa_usr, NULL);
    
    printf("My PID is %d\n", getpid());
    // Type: "kill -USR1 (pid)" from another terminal
    while(1){
        if((n = read(STDIN_FILENO, buf, 511)) == -1){
            if(errno == EINTR){
                printf("Main is interrupted by EINTR\n");
                break;
            }
        }
    }

    /* Thread 1 */
    pthread_t thread1;
    if (pthread_create(&thread1, NULL, th1, (void*)(long)thread1) != 0){
        perror("Thread1 failed");
    }
    sleep(1);
    pthread_kill(thread1, SIGUSR1);
    /* Thread 2 */
    pthread_t thread2;
    if (pthread_create(&thread2, NULL, th1, (void*)(long)thread2) != 0){
        perror("Thread2 failed");
    }
    sleep(1);
    pthread_kill(thread2, SIGUSR1);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    printf("End\n");
    return 0;
}
