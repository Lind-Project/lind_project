#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

// int main() {
//     pid_t pid = fork();
//     key_t key1 = 2000;
//     struct shmid_ds buf1;
    
//     if(pid < 0) {
//         perror("fork");
//         exit(1);
//     } else if(pid == 0) {   // Child
//         printf("Child\n");
//         int shmid1 = shmget(key1, 1024, 0666 | IPC_CREAT);
//         if(shmid1 == -1) {
//             printf("ERROR: %d\n", errno);
//             fflush(NULL);
//             perror("shmget");
//             exit(1);
//         }
//         void *shm1 = (char*)shmat(shmid1, NULL, 0);

//         sleep(10);
//         // Should fail bc already destroy
//         if(shmctl(shmid1, SHM_STAT, &buf1) == -1) {
//             printf("ERROR: %d\n", errno);
//             fflush(NULL);
//             perror("shmctl2");
//             exit(1);
//         }
//         if(shmdt(shm1) == -1) {
//             printf("ERROR: %d\n", errno);
//             fflush(NULL);
//             perror("shmdt");
//             exit(1);
//         }
//     } else { // Parent
//         sleep(2);
//         printf("Parent\n");
//         int shmid2 = shmget(key1, 0, 0666);
//         if(shmid2 == -1) {
//             printf("ERROR: %d\n", errno);
//             fflush(NULL);
//             perror("shmget[p]");
//             exit(1);
//         }
//         if(shmctl(shmid2, IPC_RMID, (struct shmid_ds *) NULL) == -1) {
//             printf("ERROR: %d\n", errno);
//             fflush(NULL);
//             perror("shmctl1");
//             exit(1);
//         }
//     }
//     wait(NULL);
//     return 0;
// }
/* errno = 14 */
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
    struct shmid_ds *buf = (struct shmid_ds *) NULL;

    if(shmctl(shmid1, IPC_RMID, buf) == -1) {
        printf("ERROR: %d\n", errno);
        fflush(NULL);
        perror("shmctl1");
        exit(1);
    }
    printf("%p:\n", buf);
    // print buf

    if(shmctl(shmid1, IPC_STAT, buf) == -1) {
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

