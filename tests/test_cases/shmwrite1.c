#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <string.h>
#include <semaphore.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h> 
#include <unistd.h>

int main() {
    key_t key = 31337;
    // sem_unlink("/semaphore_x");
    // shmget returns an identifier in shmid
    int shmid = shmget(key, 1024, 0666 | IPC_CREAT);
  
    // shmat to attach to shared memory
    sem_t *sem_ptr = (sem_t *)shmat(shmid, NULL, 0);
    
    // Initialize the semaphore - let 2nd argu be nonzero for ipc
    if (sem_init(sem_ptr, 1, 1) < 0) {
        perror("sem_init");
        exit(1);
    }
    // Wait for the semaphore - LOCK
    if (sem_wait(sem_ptr) < 0) {
        perror("sem_wait");
        exit(1);
    }
    sleep(20);
    // Actions
    printf("[1] Unlock..\n");
    fflush(stdout); 

    // UNLOCK
    if(sem_post(sem_ptr) < 0) {
        perror("sem_post");
        exit(1);
    }

    //detach from shared memory, we'll rmid in shmwrite2.c
    shmdt(sem_ptr);
  
    return 0;
}
