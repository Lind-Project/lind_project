#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>

int main()
{
    const char *filepath = "fileset_test.c";

    // Use lstat to get information about the file
    struct stat file_stat;
    if (lstat(filepath, &file_stat) == -1)
    {
        perror("lstat");
        return 1;
    }

    if (chmod(filepath, S_IRUSR | S_IRGRP | S_IROTH) == -1)
    { // Read-only for owner, group, and others
        perror("Error setting file to read-only");
        return 1;
    }

    // Open the file
    int fd = open(filepath, O_RDONLY);
    if (fd == -1)
    {
        perror("open");
        return 1;
    }

    // Use syncfilerange to synchronize a range of the file with the storage device
    off_t offset = 0;
    off_t nbytes = 0; // Sync the entire file
    unsigned int flags = SYNC_FILE_RANGE_WAIT_BEFORE | SYNC_FILE_RANGE_WRITE | SYNC_FILE_RANGE_WAIT_AFTER;

    if (sync_file_range(fd, offset, nbytes, flags) == -1)
    {
        perror("syncfilerange");
        return 1;
    }

    // Close the file
    if (close(fd) == -1)
    {
        perror("close");
        return 1;
    }

    return 0;
}
