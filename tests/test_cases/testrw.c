#include <ctype.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
    int fd = 0;
    char buf[4096] = {0};
	size_t count = sizeof buf;
    fd = open("/dev/urandom", O_RDONLY, S_IRWXU|S_IRWXG|S_IRWXO);
    close(fd);
    int ret_r = read(fd, buf, 10);
    if(ret_r < 0) {
        printf("[read] ERROR: %d\n", errno);
        perror("read");
        fflush(NULL);
        printf("[read] Return: %d\n", ret_r);
    }

    int ret_w = write(fd, buf, 10);
    if(ret_w < 0) {
        printf("[write] ERROR: %d\n", errno);
        perror("write");
        fflush(NULL);
        printf("[write] Return: %d\n", ret_w);
    }

    int ret_pr = pread(fd, buf, 10, 1);
    if(ret_pr < 0) {
        printf("[pread] ERROR: %d\n", errno);
        perror("pread");
        fflush(NULL);
        printf("[pread] Return: %d\n", ret_pr);
    }

    int ret_pw = pwrite(fd, buf, 10, 1);
    if(ret_pw < 0) {
        printf("[pwrite] ERROR: %d\n", errno);
        perror("pwrite");
        fflush(NULL);
        printf("[pwrite] Return: %d\n", ret_pw);
    }
    return 0;
}