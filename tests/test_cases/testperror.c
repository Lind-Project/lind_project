#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>

int main() {
    int fd;
    fd = open("", O_RDONLY, S_IRWXU|S_IRWXG|S_IRWXO);

    if (fd < 0) {
        printf("errno before perror: %d\n", errno);
        perror("Error");
        printf("errno after perror: %d\n", errno);
    }
    return 0;
}