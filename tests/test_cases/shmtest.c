#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

int main()
{
    struct shmid_ds buf1, buf2;

    key_t key1 = 2000;
    key_t key2 = 3000;
  
    int shmid1 = shmget(key1, 2048, 0666 | IPC_CREAT);
    int shmid2 = shmget(key2, 2048, 0666 | IPC_CREAT);

    void *shm1 = (char*) shmat(shmid1, NULL, 0);
    void *shm2 = (char*) shmat(shmid2, NULL, 0);
    void *shm3 = (char*) shmat(shmid1, NULL, 0);
    void *shm4 = (char*) shmat(shmid1, NULL, 0);
    void *shm5 = (char*) shmat(shmid2, NULL, 0);

    shmctl(shmid1, IPC_STAT, &buf1);
    shmctl(shmid2, IPC_STAT, &buf2);

    assert(buf1.shm_nattch == 3);
    assert(buf2.shm_nattch == 2);

    shmctl(shmid1, IPC_RMID, (struct shmid_ds *) NULL); 
    shmctl(shmid2, IPC_RMID, (struct shmid_ds *) NULL);
    shmdt(shm1);
    shmdt(shm2);
    shmdt(shm3);
    shmdt(shm4);
    shmdt(shm5);

    return 0;
}

