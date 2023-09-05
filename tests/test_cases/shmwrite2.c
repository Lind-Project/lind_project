#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <string.h>
#include <semaphore.h>
#include <wait.h>

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
    
    // Wait for the semaphore - LOCK
    if (sem_wait(shm_ptr) < 0) {
        perror("sem_wait");
        exit(1);
    }

    // Actions
    char str[22] = "Should appear second!";
    memcpy(shm, str, 22); 
    printf("[2] Data written in memory: %s\n", str);
    fflush(stdout); 

    // UNLOCK
    if(sem_post(shm_ptr) < 0) {
        perror("sem_post");
        exit(1);
    }

    // mark the shared memory for removal
    shmctl(shmid, IPC_RMID, NULL);
    // detach from shared memory
    shmdt(shm);
  
    return 0;
}
