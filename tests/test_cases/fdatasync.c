#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define PATH    "foo.txt"

int main() {
    // Open a file for writing. Create it if it doesn't exist
    int fd = open(PATH, O_WRONLY | O_CREAT, 0644);
    if (fd == -1) {
        perror("Error opening file");
        return 1;
    }

    // Write some data to the file
    char *data = "Hello, World!";
    if (write(fd, data, 13) != 13) {
        perror("Error writing to file");
        close(fd);
        return 1;
    }

    if (fdatasync(fd) == -1) {
        perror("Error in fdatasync");
        close(fd);
        return 1;
    }

    // Close the file
    close(fd);

    return 0;
}
