#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/statfs.h>
#include <sys/types.h>

int main() {
    int fd, ret;
    struct statfs buf = {0};
    ret = fstatfs(fd, &buf);
    if(ret < 0) {
        printf("ERROR: %d\n", errno);
        perror("fstatfs");
        fflush(NULL);
        printf("Return: %d\n", ret);
        exit(1);
    }
    return 0;
}