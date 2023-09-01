#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <semaphore.h>
#include <signal.h>
#include <errno.h>
#include <time.h>


sem_t sem;
#define handle_error(msg) \
           do { perror(msg); exit(EXIT_FAILURE); } while (0)

static void
handler(int sig) {
    write(STDOUT_FILENO, "sem_post() from handler\n", 24);
    if (sem_post(&sem) == -1) {
        write(STDERR_FILENO, "sem_post() failed\n", 18);
        exit(EXIT_FAILURE);
    }
}

int main() {
    // Initial sem with 0
    sem_init(&sem, 0, 0);
    
    struct timespec ts;
    int ret;

    struct sigaction sa;
    sa.sa_handler = handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;
    if (sigaction(SIGALRM, &sa, NULL) == -1)
        handle_error("sigaction");
    
    ts.tv_sec = 5;
    alarm(3);

    ret = sem_timedwait(&sem, &ts);
    if(ret < 0) {
        if (errno == ETIMEDOUT)
            printf("sem_timedwait() timed out\n");
        else
            perror("sem_timedwait");
    }
    printf("sem_timedwait succeed with %d\n", ret);
    sem_post(&sem);

    sem_destroy(&sem);

    return 0;
}
