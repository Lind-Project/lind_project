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
    int ret_r = read(fd, buf, -1);
    if(ret_r < 0) {
        printf("[read] ERROR: %d\n", errno);
        perror("read");
        fflush(NULL);
        printf("[read] Return: %d\n", ret_r);
    }

    int ret_w = write(fd, buf, -1);
    if(ret_w < 0) {
        printf("[write] ERROR: %d\n", errno);
        perror("write");
        fflush(NULL);
        printf("[write] Return: %d\n", ret_w);
    }

    return 0;
}