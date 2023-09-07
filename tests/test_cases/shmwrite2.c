#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <string.h>
#include <semaphore.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h> 

int main() {
    // sleep(2);
    key_t key = 31337;
    printf("[2] start...\n");
    fflush(stdout); 
    // shmget returns an identifier in shmid
    int shmid = shmget(key, 1024, 0666 | IPC_CREAT);
    printf("[2] shmid: %d\n", shmid);
    // shmat to attach to shared memory
    sem_t *sem_ptr = (sem_t *)shmat(shmid, NULL, 0);

    int value;
    sem_getvalue(sem_ptr, &value);
    printf("[2] sem_value: %d\n", value);

    // Wait for the semaphore - LOCK
    while(sem_trywait(sem_ptr) < 0) {
        printf("[2] Try lock\n");
        fflush(NULL);
        sleep(5);
    }
    
    printf("[2] Lock\n");
    fflush(NULL);

    // UNLOCK
    if(sem_post(sem_ptr) < 0) {
        perror("sem_post");
        exit(1);
    }

    // detach from shared memory
    shmdt(sem_ptr);
    // mark the shared memory for removal
    shmctl(shmid, IPC_RMID, NULL);
    
    sem_destroy(sem_ptr);
    printf("[2] End...\n");
    fflush(NULL);
    return 0;
}