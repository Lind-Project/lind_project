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

/* Check whether a specific signal (int sig) is a member of a given signal set (sigset_t *set)*/
void sigIsMember(sigset_t *set, int sig, char *set_name){
    if (sigismember(set, sig)){
        printf("Signal %d is in %s\n", sig, set_name);
        fflush(stdout);
    } else {
        printf("Signal %d is NOT in %s\n", sig, set_name);
        fflush(stdout);
    }
}

/* Check error message for sigprocmask */
void check_errno(int res) {
    if (res != 0) {
        printf("errno: %s\n", strerror(errno));
        fflush(stdout);
    }
}

void* thread_function(void* arg) {
    // Initialze
    sigset_t mask;
    sigemptyset(&mask);
    sigaddset(&mask, SIGUSR2);
    sigset_t old_mask;
    sigemptyset(&old_mask);
    sigset_t new_mask;
    sigemptyset(&new_mask);

    
    // Block SIGUSR2 in this thread
    check_errno(sigprocmask(SIG_BLOCK, &mask, NULL));
    // Get current SIG mask
    check_errno(sigprocmask(SIG_SETMASK, NULL, &old_mask));
    // Check whether SIGUSR2 is in current mask
    sigIsMember(&mask, SIGUSR2, "current signal set");
    printf("Block SIGUSR2 in new thread succeed\n");
    fflush(stdout);
    
    // Wait for SIGUSR2 signal
    int received;
    check_errno(sigwait(&mask, &received));
    if (received == 31) {
        printf("SIGUSR2 received\n");
        fflush(stdout);
    } else {
        exit(EXIT_FAILURE);
    }
    
    // Add to the new signal set
    sigaddset(&new_mask, received);
    
    // Unblock SIGUSR2 in this thread
    check_errno(sigprocmask(SIG_UNBLOCK, &new_mask, NULL));
    check_errno(sigprocmask(SIG_SETMASK, NULL, &old_mask));
    sigIsMember(&old_mask, SIGUSR2, "current signal set");;
    
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
