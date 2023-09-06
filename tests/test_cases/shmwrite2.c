#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <string.h>
#include <semaphore.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h> 

int main() {
    key_t key = 31337;
  
    // shmget returns an identifier in shmid
    int shmid = shmget(key, 1024, 0666 | IPC_CREAT);
  
    // shmat to attach to shared memory
    sem_t *sem_ptr = (sem_t *)shmat(shmid, NULL, 0);
    
    printf("[2] start...\n");
    fflush(stdout); 

    // Initialize the semaphore - let 2nd argu be nonzero for ipc
    if (sem_ptr == NULL) {
        perror("sem_open");
        exit(1);
    }

    
    // Wait for the semaphore - LOCK
    if (sem_wait(sem_ptr) < 0) {
        perror("sem_wait");
        exit(1);
    }

    // Actions
    printf("[2] processing...\n");
    fflush(stdout); 

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
  
    return 0;
}
