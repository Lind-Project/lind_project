#define _GNU_SOURCE

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_PATH 1024

int main(void)
{
    char path[MAX_PATH];

    if (getcwd(path, sizeof(path)) == NULL) {
        perror("Error with getcwd");
        return EXIT_FAILURE;
    } 
    printf("Before: %s\n", path);
    fflush(stdout);

    int fd = open("automated_tests/", O_RDWR);
    if (fd == -1) {
        perror("Error with open");
        return EXIT_FAILURE;
    }

    if (fchdir(fd) == -1) {
        perror("Error with fchdir");
        close(fd);
        return EXIT_FAILURE;
    }

    if (getcwd(path, sizeof(path)) == NULL) {
        perror("Error with getcwd");
        close(fd);
        return EXIT_FAILURE;
    } 
    printf("After: %s\n", path);
    fflush(stdout);

    if (close(fd) == -1) {
        perror("Error with close");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

