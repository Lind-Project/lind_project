#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <string.h>
#include <semaphore.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

int main()
{
    key_t key = 31337;
    printf("[server] start...\n");
    fflush(stdout);
    // shmget returns an identifier in shmid
    int shmid = shmget(key, 1024, 0666 | IPC_CREAT);

    // shmat to attach to shared memory
    sem_t *sem_ptr = (sem_t *)shmat(shmid, NULL, 0);

    key_t key2 = 13371;
    // shmget returns an identifier in shmid
    int shmid2 = shmget(key2, 1024, 0666 | IPC_CREAT);

    // shmat to attach to shared memory
    char *shared_buffer = (char *)shmat(shmid2, NULL, 0);

    // Initialize the semaphore
    if (sem_init(sem_ptr, 1, 1) < 0)
    {
        perror("sem_init");
        exit(1);
    }

    int count = 0;
    while (count++ < 5)
    {
        printf("[server] wait\n");
        fflush(stdout);
        int status = sem_wait(sem_ptr);

        if (status != 0)
        {
            perror("in sem_wait");
        }
        sleep(2);
        strcat(shared_buffer, "s");
        printf("[server] %s\n", shared_buffer);
        fflush(stdout);
        sem_post(sem_ptr);
        printf("[server] sent post\n");
        fflush(stdout);
        sleep(1);
    }

    // detach from shared memory, we'll rmid in client.c
    shmdt(sem_ptr);

    printf("[server] end...\n");
    fflush(stdout);
    return 0;
}
