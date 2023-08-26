#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
    int ret, rv;
    int fd;
    fd = open("/dev/urandom", O_RDONLY, S_IRWXU|S_IRWXG|S_IRWXO);
    
    rv = close(fd);
    printf("Success return value: %d\n", rv);

    ret = close(fd);
    if(ret < 0) {
        printf("ERROR: %d\n", errno);
        fflush(NULL);
        perror("close");
        printf("Return: %d\n", ret);
        fflush(NULL);
        exit(1);
    }
    
    printf("Succeed\n");
    return 0;
}
