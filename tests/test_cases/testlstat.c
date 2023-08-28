#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

int main() {
    const char new_name[] = "testfiles/statfile1.txt";
    struct stat st;
    int ret;

    ret = lstat(new_name, &st);
    if(ret < 0) {
        printf("ERROR: %d\n", errno);
        perror("lstat");
        fflush(NULL);
        printf("Return: %d\n", ret);
        exit(1);
    }

    printf("Return: %d\n", ret);
    return 0;
}