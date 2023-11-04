#include <stdio.h> 
#include <fcntl.h> 
#include <stdlib.h> 
#include <unistd.h>
#include <time.h>
#include <pthread.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <semaphore.h>

/*--------Timing functions--------*/
long long execution_time = 0;

long long gettimens(void) {
    struct timespec tp;

    if (clock_gettime(CLOCK_MONOTONIC, &tp) == -1) {
        perror("clock gettime");
        exit(EXIT_FAILURE);
    }

    return (tp.tv_sec * 1000000000) + tp.tv_nsec;
}

/*--------Shared Memory--------*/
int shmid;

typedef struct {
    int a[2];
    sem_t sem;
} SharedMemory;

SharedMemory *shared_memory;

// Initialize shared memory
void init_shared_memory() {
    // Create
    shmid = shmget(IPC_PRIVATE, sizeof(SharedMemory), IPC_CREAT | 0666);
    if (shmid == -1) {
        perror("shmget");
        exit(EXIT_FAILURE);
    }

    // Connect
    shared_memory = (SharedMemory *)shmat(shmid, NULL, 0);
    if ((intptr_t)shared_memory == -1) {
        perror("shmat");
        exit(EXIT_FAILURE);
    }

    if (sem_init(&shared_memory->sem, 1, 1) == -1) {
        perror("sem_init");
        exit(EXIT_FAILURE);
    }

    shared_memory->a[0] = 0;
    shared_memory->a[1] = 0;
}

void destroy_shared_memory() {
    shmdt(shared_memory);
    shmctl(shmid, IPC_RMID, NULL);
    sem_destroy(&shared_memory->sem);
}

/*--------Process functions--------*/
void process1() {
    int count = 0;
    long long start_time = gettimens();
    while (count <= 10) {
        sem_wait(&shared_memory->sem);
        shared_memory->a[0] = shared_memory->a[1] + 1;
        sem_post(&shared_memory->sem);
        count++;
    }
    long long end_time = gettimens();
    long long total_time = end_time - start_time;
    // Average
    long long average_time = total_time / count;
    printf("[process 1] %d shared memory calls, average time %lld ns\n", 10, average_time);
    fflush(NULL);
}

void process2() {
    int count = 0;
    long long start_time = gettimens();
    while (count <= 10) {
        sem_wait(&shared_memory->sem);
        shared_memory->a[1] = shared_memory->a[0];
        sem_post(&shared_memory->sem);
        count++;
    }
    long long end_time = gettimens();
    long long total_time = end_time - start_time;
    // Average
    long long average_time = total_time / count;
    printf("[process 2] %d shared memory calls, average time %lld ns\n", 10, average_time);
    fflush(NULL);
}

/*--------Main function--------*/
int main(int argc, char *argv[]) {
    init_shared_memory();

    pid_t pid = fork();

    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        // Child process
        process1();
    } else {
        // Parent process
        process2();
        wait(NULL); // Wait for the child process to finish
    }

    destroy_shared_memory();

    return 0;
}
