#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h> 

#define FILE_PATH "close.txt"
#define ITERATIONS 2000

/*
*   The purpose of adding this test is to ensure that file descriptors (fd) 
*   are properly closed, which is useful for large software systems such 
*   as the LAMP stack that frequently open and close fds during runtime. 
*   Improper handling of fds can have implications because both RustPOSIX 
*   / RawPOSIX and Linux impose limits on the maximum number of fds that a 
*   single process can use (typically set to 1024). This test simplifies 
*   the debugging process for large software systems by providing 
*   a straightforward method to verify correct fd management.
*/

int main(int argc, char **argv) {
    int fd;
    char *filename = FILE_PATH;

    // Create the test file
    fd = open(filename, O_CREAT | O_WRONLY, 0777);
    if (fd == -1) {
        perror("Failed to create test file");
        exit(EXIT_FAILURE);
    }
    close(fd);

    for (int i = 0; i < ITERATIONS; i++) {
        fd = open(filename, O_RDONLY);
        if (fd == -1) {
            perror("Failed to open file");
            exit(EXIT_FAILURE);
        }

        if (close(fd) == -1) {
            perror("Failed to close file");
            exit(EXIT_FAILURE);
        }

        // Check if the file descriptor is invalid after closing
        if (fcntl(fd, F_GETFD) != -1 || errno != EBADF) {
            fprintf(stderr, "File descriptor %d was not properly closed\n", fd);
            exit(EXIT_FAILURE);
        }
    }

    printf("File opened and closed %d times successfully.\n", ITERATIONS);
    fflush(stdout);

    // Cleanup: remove the test file
    if (remove(filename) != 0) {
        perror("Failed to remove test file");
        exit(EXIT_FAILURE);
    }

    return 0;
}
