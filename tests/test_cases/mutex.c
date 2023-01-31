#include<pthread.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<stdio.h>
#include<unistd.h>
pthread_mutex_t pmt;
pthread_cond_t pct;

void* lock_and_unlock(void* _) {
    pthread_mutex_lock(&pmt);
    printf("locked child\n");
    pthread_mutex_unlock(&pmt);
    pthread_cond_signal(&pct);
}

int main() {
    pthread_mutex_init(&pmt, NULL);
    pthread_cond_init(&pct, NULL);
    pthread_mutex_lock(&pmt);
    pthread_t pt;
    pthread_create(&pt, NULL, &lock_and_unlock, NULL);
    pthread_cond_wait(&pct, &pmt);
    sleep(1);
    pthread_mutex_unlock(&pmt);
    printf("unlocked parent\n");
    sleep(1);
    pthread_mutex_destroy(&pmt);
    pthread_cond_destroy(&pct);
    pthread_join(pt, NULL);
}
