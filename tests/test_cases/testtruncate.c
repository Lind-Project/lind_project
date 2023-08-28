#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>

int main() {
    const char *path = "";
    int fd, ret, ret_f;

    ret = truncate(path, 5);
    ret_f = ftruncate(fd, 5);

    if(ret < 0){
        printf("ERROR: %d\n", errno);
        perror("truncate");
        fflush(NULL);
        printf("Return: %d\n", ret);
    }

    if(ret_f < 0) {
        printf("ERROR: %d\n", errno);
        perror("ftruncate");
        fflush(NULL);
        printf("Return: %d\n", ret_f);
    }
    printf("Return: %d\n", ret);
    printf("Return: %d\n", ret_f);
    return 0;
}