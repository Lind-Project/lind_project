#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/statfs.h>
#include <sys/types.h>

int main() {
    char *name = "testfiles/1.txt";
    struct statfs buf = {0};
    int ret = statfs(name, &buf);
    if (ret < 0) {
        printf("ERROR: %d\n", errno);
        perror("statfs");
        fflush(NULL);
        printf("Return: %d\n", ret);
        exit(1);
    }
    printf("Return: %d\n", ret);
    return 0;
}