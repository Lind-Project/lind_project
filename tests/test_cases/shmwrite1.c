#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <string.h>
#include <semaphore.h>
#include <stdlib.h>

int main() {
    key_t key = 31337;
  
    // shmget returns an identifier in shmid
    int shmid = shmget(key, 1024, 0666 | IPC_CREAT);
  
    // shmat to attach to shared memory
    sem_t *shm_ptr = (sem_t *)shmat(shmid, NULL, 0);
    // Link semaphore to shared memory
    if (shm_ptr == (sem_t *)-1) {
        perror("shmat");
        exit(1);
    }
    
    // Initialize the semaphore - let 2nd argu be nonzero for ipc
    if (sem_init(shm_ptr, 1, 1) < 0) {
        perror("sem_init");
        exit(1);
    }
    // Wait for the semaphore - LOCK
    if (sem_wait(shm_ptr) < 0) {
        perror("sem_wait");
        exit(1);
    }

    // Actions
    char str[22] = "Should appear first";
    memcpy(shm_ptr, str, 8); 
    printf("[1] Data written in memory: %s\n", str);
    fflush(stdout); 

    // UNLOCK
    if(sem_post(shm_ptr) < 0) {
        perror("sem_post");
        exit(1);
    }

    //detach from shared memory, we'll rmid in shmwrite2.c
    shmdt(shm_ptr);
  
    return 0;
}
