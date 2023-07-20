#include <errno.h>
#include <string.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

void sigusr2_handler(int signum) {
    printf("Received SIGUSR2 signal!\n");
}

void* thread_function(void* arg) {
   // Block SIGUSR2 in this thread
    sigset_t mask;
    sigemptyset(&mask);
    sigaddset(&mask, SIGUSR2);

    if (sigprocmask(SIG_BLOCK, &mask, NULL) == -1) {
        perror("sigprocmask");
        exit(EXIT_FAILURE);
    }
    printf("New thread succeed\n");
    fflush(stdout);
    
    // Wait for SIGUSR2 signal
    int sig;
    sigwait(&mask, &sig);
    printf("Received SIGUSR2 signal in the thread!\n");
    fflush(stdout);
    
    return NULL;
}

int main(void) {
    pthread_t thread;
    int ret;
    printf("Program start\n");
    fflush(stdout);
    // Register the SIGUSR2 signal handler for the main thread
    if (signal(SIGUSR2, sigusr2_handler) == SIG_ERR) {
        perror("signal");
        exit(EXIT_FAILURE);
    }
    printf("Register succeed\n");
    fflush(stdout);
    // Create the thread
    ret = pthread_create(&thread, NULL, thread_function, NULL);


    if (ret != 0) {
        perror("pthread_create");
        exit(EXIT_FAILURE);
    }

    // Sleep briefly to ensure the thread has started
    sleep(1);

    // Send SIGUSR2 to the new thread
    pthread_kill(thread, SIGUSR2);

    // Wait for the thread to finish
    pthread_join(thread, NULL);
    printf("Successful\n");
    fflush(stdout);
    return EXIT_SUCCESS;
}

