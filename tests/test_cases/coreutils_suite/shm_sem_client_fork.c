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
    // shmget returns an identifier in shmid
    int shmid = shmget(key, 1024, 0666);

    // shmat to attach to shared memory
    sem_t *sem_ptr = (sem_t *)shmat(shmid, NULL, 0);

    key_t key2 = 13371;
    // shmget returns an identifier in shmid
    int shmid2 = shmget(key2, 1024, 0666);

    // shmat to attach to shared memory
    char *shared_buffer = (char *)shmat(shmid2, NULL, 0);

    if (fork() == 0) {
        // child process
        sleep(0.5);
        int count = 0;
        while (count++ < 3)
        {
            int status = sem_wait(sem_ptr);

            if (status != 0)
            {
                perror("in sem_wait");
            }
            sleep(2);
            strcat(shared_buffer, "u");
            printf("[client2] %s\n", shared_buffer);
            fflush(stdout);
            sem_post(sem_ptr);
            sleep(1);
        }
    } else {
        // parent process
        int count = 0;
        while (count++ < 3)
        {
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
            sleep(1);
        }
    }
    // detach from shared memory
    shmdt(sem_ptr);
    // mark the shared memory for removal
    shmctl(shmid, IPC_RMID, NULL);

    sem_destroy(sem_ptr);
    if (strlen(shared_buffer) == 15)
        memset(shared_buffer, 0, sizeof(shared_buffer));
    // detach from shared memory
    shmdt(shared_buffer);
    // mark the shared memory for removal
    shmctl(shmid2, IPC_RMID, NULL);
    return 0;
}
