#undef _GNU_SOURCE
#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <poll.h>
#include <pthread.h>
#include <errno.h>
#include <signal.h>

#define TIMEOUT -1

static void sig_usr(int signum){
    printf("Thread1 received signal %d\n", signum);
}

// Thread function
void* th(void* arg){
    int id = *((int*)arg);
    printf("Thread %d\n", id);
    int n;
    // Set signal handler
    struct sigaction sa_usr;
    sa_usr.sa_flags = 0;
    sa_usr.sa_handler = sig_usr;   

    sigaction(SIGUSR1, &sa_usr, NULL);
    
    return NULL;
}

 
int main(void){
    int user1 = 1;
    int user2 = 2;
    struct pollfd fds[1];
    int ret;

    /* Checking if stdout (file descriptor 1) is ready for writing. */
    fds[0].fd = 1;
    fds[0].events = POLLOUT;

    /* The poll call is blocked indefinitely. */
    ret = poll(fds, 1, TIMEOUT);

    if (ret == -1) {
        perror("poll");
        return 1;
    }
    
    /* Thread 1 */
    pthread_t thread1;
    if (pthread_create(&thread1, NULL, th, &user1) != 0){
        perror("Thread1 failed");
    }

    /* Thread 2 */
    pthread_t thread2;
    if (pthread_create(&thread2, NULL, th, &user2) != 0){
        perror("Thread2 failed");
    }
    sleep(1);

    pthread_kill(thread1, SIGUSR1);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    printf("End\n");
    return 0;
}
