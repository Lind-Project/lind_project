#define _GNU_SOURCE
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>

int main(int argc, char** argv) {
    if(argc == 1) {
        char *const nenvp[] = {NULL};
        int fd1 = open("asdfasdf", O_CREAT | O_RDWR, 0777);
        int fd2 = open("asdfasdf2", O_CREAT | O_RDWR | O_CLOEXEC, 0777);
        char fd1buf[8], fd2buf[8];
        snprintf(fd1buf, 8, "%d", fd1);
        snprintf(fd2buf, 8, "%d", fd2);
        char *const nargv[] = {argv[0], fd1buf, fd2buf, NULL};
        execve(argv[0], nargv, nenvp);
    } else {
        struct stat statbuf;
        int fd1 = atoi(argv[1]);
        int fd2 = atoi(argv[2]);
        printf("fstat on fd1 returns %d, should succeed\n", fstat(fd1, &statbuf));
        printf("fstat on fd2 returns %d, should fail\n", fstat(fd2, &statbuf));
        close(fd2);
        unlink("asdfasdf");
        unlink("asdfasdf2");
    }
}
