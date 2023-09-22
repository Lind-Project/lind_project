#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>

#define SHM_SIZE 1024

int main() {
    int shmid;
    key_t key = 2000;
    if ((shmid = shmget(key, SHM_SIZE, IPC_CREAT | 0666)) == -1) {
        printf("ERROR: %d\n", errno);
        fflush(NULL);
        perror("shmget");
        exit(1);
    }
    void *shm = (char*) shmat(1, NULL, 0);

    printf("Success\n");
    fflush(NULL);
    return 0;
}