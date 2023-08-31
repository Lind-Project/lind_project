#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <semaphore.h>

sem_t sem;

int main() {
    // Initial sem with 0
    sem_init(&sem, 0, 0);
    
    int count = 9;

    sem_wait(&sem);
    printf("shouldn't be executed... %d\n", count);
    sem_post(&sem);

    sem_wait(&sem);
    printf("should display: %d\n", count);
    sem_post(&sem);
    
    sem_destroy(&sem);

    return 0;
}
