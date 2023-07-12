#undef _GNU_SOURCE
#define _GNU_SOURCE

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_PATH 1024

int main(void) {
    char path[MAX_PATH];
    
    // Get the current working directory
    char* result = getcwd(path, sizeof(path));
    if (result == NULL) {
        perror("getcwd() error");
        return EXIT_FAILURE;
    }
    
    printf("current working directory is: %s :: %s\n", path, result);
    fflush(stdout);
    

    // Open a directory
    int fd = open("automated_tests/", O_RDONLY);
    if (fd == -1) {
        perror("Error with open");
        return EXIT_FAILURE;
    }

    // Change the current directory to the directory referred to by the open file descriptor
    if (fchdir(fd) == -1) {
        perror("Error with fchdir");
        close(fd);
        return EXIT_FAILURE;
    }

    // Get the current working directory
    char* second_result = getcwd(path, sizeof(path));
    if (second_result == NULL) {
        perror("Error with getcwd");
        close(fd);
        return EXIT_FAILURE;
    } 
    printf("current working directory is: %s :: %s\n", path, second_result);
    fflush(stdout);
    


    // Close the file descriptor
    if (close(fd) == -1) {
        perror("Error with close");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

