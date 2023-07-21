#include <errno.h>
#include <string.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

void sh1(int sig){
    printf("signal %d received\n", sig);
    fflush(stdout);
}

void sh2(int sig){
    printf("signal %d received\n", sig);
    fflush(stdout);
}

void* th1(void* arg){
    printf("I am thread01\n");
    fflush(stdout);
    
    struct sigaction sa1;
    sa1.sa_handler = sh1;
    sa1.sa_flags = 0;
    sigaction(SIGUSR2, &sa1, NULL);
    
    sigset_t mask;
    sigemptyset(&mask);
    sigaddset(&mask, SIGUSR2);
    sigprocmask(SIG_BLOCK, &mask, NULL);
    
    return NULL;
}

void* th2(void* arg){
    printf("I am thread02\n");
    fflush(stdout);
    
    struct sigaction sa2;
    sa2.sa_handler = sh2;
    sa2.sa_flags = 0;
    sigaction(SIGUSR2, &sa2, NULL);
    
    sigset_t mask;
    sigemptyset(&mask);
    sigaddset(&mask, SIGUSR2);
    sigprocmask(SIG_BLOCK, &mask, NULL);
    
    return NULL;
}

int main(void) {
    pthread_t thread1, thread2;
    
    pthread_create(&thread1, NULL, th1, NULL);
    pthread_create(&thread2, NULL, th2, NULL);
    
    sleep(2);
    
    // Send signal to threads
    if (pthread_kill(thread1, SIGUSR1) != 0){
        printf("Error of Thread 1 is: %s\n", strerror(errno));
        fflush(stdout);
    }
    if (pthread_kill(thread2, SIGUSR1) != 0){
        printf("Error of Thread 2 is: %s\n", strerror(errno));
        fflush(stdout);
    }
    
//    // Send signal to main
//    char buf[512];
//    printf("My PID is %d\n", getpid());
//    while (1) {
//        if (read(STDIN_FILENO, buf, 511) == -1){
//            printf("Error of Main is: %d\n", errno);
//            fflush(stdout);
//        }
//    }
    
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    printf("Successfule\n");
    fflush(stdout);
    return EXIT_SUCCESS;

}
