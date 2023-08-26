#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

int main() {
    char new_name[] = "testfiles/renamefile.txt";
    int fd = open(new_name, O_RDONLY);
    struct stat st;
    int ret;

    ret = fstat(fd, &st);
    if(ret < 0) {
        printf("ERROR: %d\n", errno);
        perror("fstat");
        fflush(NULL);
        printf("Return: %d\n", ret);
        exit(1);
    }
    printf("Return: %d\n", ret);
    return 0;
}
