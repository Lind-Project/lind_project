#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
    int fd;
    /* TEST: null path */
    fd = open("", O_RDONLY, S_IRWXU|S_IRWXG|S_IRWXO);

    /* TEST: file already exits */
    // fd = open("/home/lind/lind_project/tests/test_cases/read.c", O_CREAT, S_IRWXU|S_IRWXG|S_IRWXO);

    if(fd < 0) {
        printf("ERROR: %d\n", errno);
        perror("open");
        fflush(NULL);
        exit(1);
    }

    
    return 0;
}
