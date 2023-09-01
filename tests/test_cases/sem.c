#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <semaphore.h>
#include <signal.h>
#include <errno.h>
#include <time.h>


sem_t sem;

int main() {
    // Initial sem with 0
    sem_init(&sem, 0, 0);
    
    struct timespec ts;
    int ret;
    
    ts.tv_sec = 3;

    ret = sem_timedwait(&sem, &ts);
    if(ret < 0) {
        if (errno == ETIMEDOUT)
            printf("sem_timedwait() timed out\n");
        else
            perror("sem_timedwait");
    } else {
        printf("sem_timedwait succeed with %d\n", ret);
    }
    
    sem_post(&sem);

    sem_destroy(&sem);

    return 0;
}
