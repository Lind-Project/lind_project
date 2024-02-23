#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main()
{
    pid_t pid;
    int fd;
    int count = 1e6;
    off_t offset = 0;
    char buffer[8192] = {"c"};

    // Create a child process
    pid = fork();

    if (pid < 0)
    {
        perror("fork() failed");
        exit(1);
    }
    else if (pid == 0)
    {
        // Child process
        fd = open("file.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
        // Loop to write data past the end of the file
        for (int i = 0; i < count; i++)
        {
            ssize_t bytes_written = pwrite(fd, buffer, sizeof(buffer), offset);
            if (bytes_written == -1)
            {
                perror("pwrite() failed");
                exit(1);
            }
            printf("Child process: %ld bytes written at offset %ld\n", bytes_written, offset);
            fflush(stdout);
            offset += bytes_written;
        }
    }
    else
    {
        // Parent process
        fd = open("file.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
        // Loop to write data past the end of the file
        for (int i = 0; i < count; i++)
        {
            ssize_t bytes_written = pwrite(fd, buffer, sizeof(buffer), offset);
            if (bytes_written == -1)
            {
                perror("pwrite() failed");
                exit(1);
            }
            printf("Parent process: %ld bytes written at offset %ld\n", bytes_written, offset);
            fflush(stdout);
            offset += bytes_written;
        }
    }

    if (fd == -1)
    {
        perror("open() failed");
        exit(1);
    }

    close(fd);

    return 0;
}
