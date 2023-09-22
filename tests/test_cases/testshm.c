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
    key_t key;
    for(int i = 0; i < 4097; i++) {
        key = ftok("tests/test_cases/testfiles/shmfile.txt", 'A' + i);
        if(key == -1) {
            perror("ftok");
            exit(1);
        }
        if ((shmid = shmget(key, 0, 0666)) == -1) {
            printf("ERROR: %d\n", errno);
            fflush(NULL);
            perror("shmget");
            exit(1);
        }
    }
    
    printf("Success\n");
    fflush(NULL);
    return 0;
}

/* errno = 2 */
// int main() {
//     int shmid;
//     key_t key = 2000;
//     if ((shmid = shmget(key, 0, 0666)) == -1) {
//         printf("ERROR: %d\n", errno);
//         fflush(NULL);
//         perror("shmget");
//         exit(1);
//     }
//     printf("Success\n");
//     fflush(NULL);
//     return 0;
// }

/* errno = 22 */
// int main() {
//     int shmid;
//     key_t key = 2000;
//     if ((shmid = shmget(key, SHM_SIZE, IPC_CREAT | 0666)) == -1) {
//         printf("ERROR: %d\n", errno);
//         fflush(NULL);
//         perror("shmget");
//         exit(1);
//     }
//     if ((shmid = shmget(key, 1200, IPC_CREAT | 0666)) == -1) {
//         printf("ERROR: %d\n", errno);
//         fflush(NULL);
//         perror("shmget");
//         exit(1);
//     }
    
//     printf("Success\n");
//     fflush(NULL);
//     return 0;
// }