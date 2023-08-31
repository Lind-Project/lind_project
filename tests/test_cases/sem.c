#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>

sem_t sem;

void* func1() {
    // Lock
    sem_wait(&sem);
    printf("[Thread 1] running... \n");
}

void* func2(void* arg) {
    printf("[Thread 2] running... \n");
    // Unlock
    sem_post(&sem);
}

int main() {
    // Initial sem with 0
    sem_init(&sem, 0, 0);
    pthread_t thread1, thread2;
    
    pthread_create(&thread1, NULL, func1, NULL);
    printf("[main] created thread 1...\n");

    sleep(5);

    pthread_create(&thread2, NULL, func2, NULL);
    printf("[main] created thread 2...\n");

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    sem_destroy(&sem);

    return 0;
}
