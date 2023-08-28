#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>

int main() {
    const char *path = "testfiles/1.txt";
    int ret = access(path,F_OK);
    if(ret < 0){
        printf("ERROR: %d\n", errno);
        perror("access");
        fflush(NULL);
        printf("Return: %d\n", ret);
        exit(1);
    }
    printf("Return: %d\n", ret);
    return 0;
}