#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

/* errno = 43 */
int main() {
    key_t key1 = 2000;
  
    int shmid1 = shmget(key1, 1024, 0666 | IPC_CREAT);
    if(shmid1 == -1) {
        printf("ERROR: %d\n", errno);
        fflush(NULL);
        perror("shmget");
        exit(1);
    }

    void *shm1 = (char*) shmat(shmid1, NULL, 0);
    if(shm1 == (void *)-1) {
        printf("ERROR: %d\n", errno);
        fflush(NULL);
        perror("shmat");
        exit(1);
    }
    
    if(shmctl(shmid1, IPC_RMID, (struct shmid_ds *) NULL) == -1) {
        printf("ERROR: %d\n", errno);
        fflush(NULL);
        perror("shmctl1");
        exit(1);
    }
    
    if(shmctl(shmid1, IPC_STAT, (struct shmid_ds *) NULL) == -1) {
        printf("ERROR: %d\n", errno);
        fflush(NULL);
        perror("shmctl2");
        exit(1);
    }
    if(shmdt(shm1) == -1) {
        printf("ERROR: %d\n", errno);
        fflush(NULL);
        perror("shmdt");
        exit(1);
    }
    printf("Success\n");
    return 0;
}

