#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>

#define SHM_SIZE 1024

// Structure for a semaphore
union semun {
    int val;
    struct semid_ds *buf;
    unsigned short *array;
};

// Function to perform the wait operation on a semaphore
void sem_wait(int sem_id) {
    struct sembuf sem_buf;
    sem_buf.sem_num = 0;
    sem_buf.sem_op = -1;
    sem_buf.sem_flg = SEM_UNDO;
    semop(sem_id, &sem_buf, 1);
}

// Function to perform the signal operation on a semaphore
void sem_signal(int sem_id) {
    struct sembuf sem_buf;
    sem_buf.sem_num = 0;
    sem_buf.sem_op = 1;
    sem_buf.sem_flg = SEM_UNDO;
    semop(sem_id, &sem_buf, 1);
}

int main() {
    int shmid, semid;
    key_t key = ftok("shm_semaphore_example", 'A');

    // Create shared memory segment
    if ((shmid = shmget(key, SHM_SIZE, IPC_CREAT | 0666)) == -1) {
        perror("shmget");
        exit(1);
    }

    // Attach shared memory
    char *shm_ptr = shmat(shmid, NULL, 0);
    if (shm_ptr == (char *)-1) {
        perror("shmat");
        exit(1);
    }

    // Create a semaphore
    if ((semid = semget(key, 1, IPC_CREAT | 0666)) == -1) {
        perror("semget");
        exit(1);
    }

    // Initialize the semaphore to 1 (unlocked)
    union semun sem_union;
    sem_union.val = 1;
    semctl(semid, 0, SETVAL, sem_union);

    // Shared counter
    int *counter = (int *)shm_ptr;
    *counter = 0;

    pid_t pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        exit(1);
    } else if (pid == 0) {
        // Child process
        for (int i = 0; i < 5; i++) {
            sem_wait(semid);
            (*counter)++;
            printf("Child process: Counter = %d\n", *counter);
            sem_signal(semid);
            sleep(1);
        }
        exit(0);
    } else {
        // Parent process
        for (int i = 0; i < 5; i++) {
            sem_wait(semid);
            (*counter)++;
            printf("Parent process: Counter = %d\n", *counter);
            sem_signal(semid);
            sleep(1);
        }
    }

    // Cleanup
    wait(NULL);
    shmdt(shm_ptr);
    shmctl(shmid, IPC_RMID, NULL);
    semctl(semid, 0, IPC_RMID);

    return 0;
}
