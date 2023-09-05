#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <semaphore.h>
#include <wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SHM_SIZE 1024

int main() {
    int shmid;
    key_t key = 2000;

    // Create a shared memory region
    if ((shmid = shmget(key, SHM_SIZE, IPC_CREAT | 0666)) == -1) {
        perror("shmget");
        exit(1);
    }

    // Attach the shared memory region
    sem_t *shm_ptr = (sem_t *)shmat(shmid, NULL, 0);
    if (shm_ptr == (sem_t *)-1) {
        perror("shmat");
        exit(1);
    }

    // Initialize the semaphore - let 2nd argu be nonzero for ipc
    if (sem_init(shm_ptr, 1, 1) < 0) {
        perror("sem_init");
        exit(1);
    }

    pid_t pid = fork();
    int sval, psval;
    if (pid < 0) {
        perror("Fork failed");
        exit(1);
    } else if (pid == 0) {
        // Child process
        sem_wait(shm_ptr); // Child waits for the semaphore
        printf("Child process: Acquired semaphore\n");
        // sem_getvalue(shm_ptr, &sval);
        // printf("[CP] Current sval: %d\n", sval);
        sleep(5); 
        sem_post(shm_ptr); // Release the semaphore
        printf("Child process: Released semaphore\n");
        exit(0);
    } else {
        // Parent process
        sleep(1); // Ensure the child process starts first
        // sem_getvalue(shm_ptr, &psval);
        // printf("[PP] Current sval: %d\n", psval);
        sem_wait(shm_ptr); // Parent waits for the semaphore
        printf("Parent process: Acquired semaphore\n");
        sleep(2); 
        sem_post(shm_ptr); // Release the semaphore
        printf("Parent process: Released semaphore\n");
    }

    // Cleanup
    wait(NULL);
    shmdt(shm_ptr);
    shmctl(shmid, IPC_RMID, NULL);
    sem_destroy(shm_ptr);

    return 0;
}
