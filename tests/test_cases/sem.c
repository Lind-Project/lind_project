#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <semaphore.h>
#include <signal.h>
#include <errno.h>
#include <time.h>

int main() {
    sem_t sem;
    
    // Initial sem with 0
    int r = sem_init(&sem, 0, 3);
    printf("sem_initial: %d\n", r);
    
    int val;
    sem_getvalue(&sem, &val);
    printf("value: %d\n", val);

    // struct timespec ts;
    // int ret;
    
    // // 1. sem_timedwait with open sem=1
    // // 2. make sem_timedwait work: maybe check the ts with clock_gettime?


    // ts.tv_sec = 3;

    // ret = sem_timedwait(&sem, &ts);
    // if(ret < 0) {
    //     if (errno == ETIMEDOUT)
    //         printf("sem_timedwait() timed out\n");
    //     else
    //         perror("sem_timedwait");
    // } else {
    //     printf("sem_timedwait succeed with %d\n", ret);
    // }
    
    // sem_post(&sem);

    // sem_destroy(&sem);

    return 0;
}
