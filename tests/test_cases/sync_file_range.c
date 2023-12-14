#define _GNU_SOURCE
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#define SYNC_FILE_RANGE_WRITE 2
#define PATH    "foo.txt"

int main() {
    ssize_t ret;
    char *data = "This is a test data for sync_file_range.\n";
    size_t length = strlen(data);

    // Open a file
    int fd = open(PATH, O_WRONLY | O_CREAT, 0644);
    if (fd < 0) {
        perror("Error opening file");
        return 1;
    }

    // Write data to the file
    ret = write(fd, data, length);
    if (ret < 0) {
        perror("Error writing to file");
        close(fd);
        return 1;
    }

    // Synchronize a range of the file
    ret = sync_file_range(fd, 0, length, SYNC_FILE_RANGE_WRITE);
    if (ret != 0) {
        perror("Error in sync_file_range");
        close(fd);
        return 1;
    }

    // Close the file
    close(fd);
    printf("sync_file_range test completed successfully.\n");
    fflush(stdout);
    return 0;
}
