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
    key_t key = 31337;
    printf("[2] start...\n");
    fflush(stdout); 
    // shmget returns an identifier in shmid
    int shmid = shmget(key, 1024, 0666 | IPC_CREAT);
    printf("[2] shmid: %d\n", shmid);
    // shmat to attach to shared memory
    sem_t *sem_ptr = (sem_t *)shmat(shmid, NULL, 0);
    if (sem_ptr == NULL) {
        perror("shmat");
        exit(1);
    }
    // Initialize the semaphore - let 2nd argu be nonzero for ipc
    if (sem_init(sem_ptr, 1, 0) < 0) {
        perror("sem_init");
        exit(1);
    }

    int value;
    int ret = sem_getvalue(sem_ptr, &value);
    if (ret < 0) {
        perror("sem_getvalue");
        exit(1);
    }
    printf("Sem value: %d\n", value);
    // Wait for the semaphore - LOCK
    // while(sem_trywait(sem_ptr) < 0) {
    //     printf("[2] Try lock\n");
    //     fflush(NULL);
    //     sleep(5);   /* may not sleep, check the value of sem_ptr, whether they work correctly, donot use sleep */
    // }
    
    // printf("[2] Lock\n");
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