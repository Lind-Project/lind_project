#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>

#define GB (1 << 30)
const char *FILENAME = "large_file.txt";

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        fprintf(stderr, "Usage: [executable] [read_write_buffer_size] [total_size_in_GBs]\n");
        exit(1);
    }

    int buffer_size = 1 << atoi(argv[1]);
    int N = atoi(argv[2]);
    int file_size = N * GB;

    char buffer[buffer_size];
    char read_buffer[buffer_size];

    memset(buffer, 'A', sizeof(buffer));
    memset(read_buffer, 0, sizeof(read_buffer));

    int test_fd = open(FILENAME, O_RDWR | O_CREAT, 0644);
    if (test_fd == -1)
    {
        perror("Failed to open file");
        exit(1);
    }

    for (int i = 0; i < file_size / buffer_size; i++)
    {
        write(test_fd, buffer, buffer_size);
    }

    lseek(test_fd, 0, SEEK_SET);

    for (int i = 0; i < file_size / buffer_size; i++)
    {
        read(test_fd, read_buffer, buffer_size);
    }

    close(test_fd);

    unlink(FILENAME); // Delete the file

    return 0;
}
