#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
    const char *filename = "";
    int ret;

    ret = unlink(filename);
    if(ret < 0) {
        perror("unlink");
        printf("ERROR: %d\n", errno);
        exit(1);
    }

    printf("Succeed\n");
    return 0;
}