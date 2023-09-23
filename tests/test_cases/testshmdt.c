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
    const void *shmaddr;
    if (shmdt(shmaddr) == -1) {
        printf("ERROR: %d\n", errno);
        fflush(NULL);
        perror("shmdt");
        exit(1);
    }
    
    printf("Success\n");
    fflush(NULL);
    return 0;
}