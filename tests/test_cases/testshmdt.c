#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <errno.h>

#define SHM_SIZE 1024
int main() {
    int shmid;
    if ((shmid = shmdt(shmid)) == -1) {
        printf("ERROR: %d\n", errno);
        fflush(NULL);
        perror("shmget");
        exit(1);
    }
    
    printf("Success\n");
    fflush(NULL);
    return 0;
}