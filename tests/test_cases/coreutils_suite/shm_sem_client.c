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
    printf("[client] start...\n");
    fflush(stdout);
    // shmget returns an identifier in shmid
    int shmid = shmget(key, 1024, 0666);

    // shmat to attach to shared memory
    sem_t *sem_ptr = (sem_t *)shmat(shmid, NULL, 0);

    key_t key2 = 13371;
    // shmget returns an identifier in shmid
    int shmid2 = shmget(key2, 1024, 0666);

    // shmat to attach to shared memory
    char *shared_buffer = (char *)shmat(shmid2, NULL, 0);

    int count = 0;
    while (count++ < 5)
    {
        printf("[client] wait\n");
        fflush(stdout);
        int status = sem_wait(sem_ptr);

        if (status != 0)
        {
            perror("in sem_wait");
        }
        sleep(2);
        strcat(shared_buffer, "c");
        printf("[client] %s\n", shared_buffer);
        fflush(stdout);
        sem_post(sem_ptr);
        printf("[client] sent post\n");
        fflush(stdout);
        sleep(1);
    }

    // detach from shared memory
    shmdt(sem_ptr);
    // mark the shared memory for removal
    shmctl(shmid, IPC_RMID, NULL);

    sem_destroy(sem_ptr);

    memset(shared_buffer, 0, strlen(shared_buffer));
    // detach from shared memory
    shmdt(shared_buffer);
    // mark the shared memory for removal
    shmctl(shmid2, IPC_RMID, NULL);

    printf("[client] end...\n");
    fflush(stdout);
    return 0;
}
