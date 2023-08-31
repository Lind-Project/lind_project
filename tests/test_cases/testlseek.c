#include <ctype.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>

int main() {
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    int ret = lseek(fd, 5, SEEK_SET);
    if(ret < 0) {
        printf("[lseek] ERROR: %d\n", errno);
        perror("lseek");
        printf("[lseek] Return: %d\n", ret);
        fflush(NULL);
        exit(1);
    }

    return 0;
}
