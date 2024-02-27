#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <string.h>
#include <semaphore.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

// create semaphores
sem_t sems[5];
void run_semaphores(int id, int num)
{

    // wait and post semaphores
    for (int i = 0; i < num; i++)
    {
        int status = sem_wait(&sems[i]);

        if (status != 0)
        {
            perror("in sem_wait");
            exit(1);
        }
        sem_post(&sems[i]);
    }
    // destroy semaphores
    for (int i = num / 2 - 1; i < num / 2 + 2; i++)
    {
        sem_destroy(&sems[i]);
    }
}

int main()
{

    for (int i = 0; i < 5; i++)
    {
        sem_init(&sems[i], 0, 1);
    }
    for (int i = 0; i < 4; i++)
    {
        if (fork() == 0)
        {
            // child process
            run_semaphores(i + 1, 5);
            return 0;
        }
    }
    run_semaphores(0, 5);
    return 0;
}
