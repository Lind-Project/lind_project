#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>

volatile long long count1 = 0;
volatile long long count2 = 0;

/*--------Timing functions--------*/
long long execution_time = 0;

long long gettimens(void)
{
    struct timespec tp;

    if (clock_gettime(CLOCK_MONOTONIC, &tp) == -1)
    {
        perror("clock gettime");
        exit(EXIT_FAILURE);
    }

    return (tp.tv_sec * 1000000000) + tp.tv_nsec;
}

/*--------Shared Memory--------*/
int shmid;

typedef struct
{
    int a[2];
} SharedMemory;

SharedMemory *shared_memory;

// Initialize shared memory
void init_shared_memory()
{
    // Create
    shmid = shmget(31337, sizeof(SharedMemory), IPC_CREAT | 0666);
    if (shmid == -1)
    {
        perror("shmget");
        exit(EXIT_FAILURE);
    }

    // Connect
    shared_memory = (SharedMemory *)shmat(shmid, NULL, 0);
    if ((intptr_t)shared_memory == -1)
    {
        perror("shmat");
        exit(EXIT_FAILURE);
    }

    shared_memory->a[0] = 0;
    shared_memory->a[1] = 0;
}

void destroy_shared_memory()
{
    shmdt(shared_memory);
    shmctl(shmid, IPC_RMID, NULL);
}

/*--------Main function--------*/
int main(int argc, char *argv[])
{
    init_shared_memory();
    int loop = atoi(argv[1]);
    pid_t pid = fork();

    long long start_time = gettimens();

    if (pid == -1)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0)
    {
        // Child process
        while (count1 < loop)
        {
            shared_memory->a[0] = shared_memory->a[1] + 1;
            count1++;
        }
        exit(EXIT_SUCCESS);
    }
    else
    {
        // Parent process
        while (count2 < loop)
        {
            shared_memory->a[1] = shared_memory->a[0];
            count2++;
        }
    }
    wait(NULL); // Wait for the child process to finish
    long long end_time = gettimens();
    long long total_time = end_time - start_time;
    // Average
    long long average_time = total_time / 100000000;
    printf("%d shared memory calls, average time %lld ns\n", 100000000, average_time);
    fflush(NULL);
    destroy_shared_memory();

    return 0;
}
