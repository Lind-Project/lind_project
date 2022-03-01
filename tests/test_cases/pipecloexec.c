#define _GNU_SOURCE
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>

int main(int argc, char** argv) {
    if(argc == 1) {
        char *const nenvp[] = {NULL};
        int pipefds[2];
        int opipefds[2];
        pipe(pipefds);
        pipe2(opipefds, O_CLOEXEC);
        char fd1buf[8], fd2buf[8];
        char ofd1buf[8], ofd2buf[8];
        snprintf(fd1buf, 8, "%d", pipefds[0]);
        snprintf(fd2buf, 8, "%d", pipefds[1]);
        snprintf(ofd1buf, 8, "%d", opipefds[0]);
        snprintf(ofd2buf, 8, "%d", opipefds[1]);
        char *const nargv[] = {argv[0], fd1buf, fd2buf, ofd1buf, ofd2buf, NULL};
        execve(argv[0], nargv, nenvp);
    } else {
        struct stat statbuf;
        int fd1 = atoi(argv[1]);
        int fd2 = atoi(argv[2]);
        int ofd1 = atoi(argv[3]);
        int ofd2 = atoi(argv[4]);
        printf("fstat on fd1 returns %d, should fail\n", fstat(ofd1, &statbuf));
        printf("fstat on fd2 returns %d, should fail\n", fstat(ofd2, &statbuf));
        printf("fstat on ofd1 returns %d, should succeed\n", fstat(fd1, &statbuf));
        printf("fstat on ofd2 returns %d, should succeed\n", fstat(fd2, &statbuf));
        close(ofd1);
        close(ofd2);
    }
}
