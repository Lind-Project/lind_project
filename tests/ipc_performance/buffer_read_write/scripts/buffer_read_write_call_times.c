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

    struct timespec read_start, read_end;
    struct timespec write_start, write_end;

    int test_fd = open(FILENAME, O_RDWR | O_CREAT, 0644);
    if (test_fd == -1)
    {
        perror("Failed to open file");
        exit(1);
    }

    clock_gettime(CLOCK_MONOTONIC, &write_start);
    for (int i = 0; i < file_size / buffer_size; i++)
    {
        write(test_fd, buffer, buffer_size);
    }
    clock_gettime(CLOCK_MONOTONIC, &write_end);

    lseek(test_fd, 0, SEEK_SET);

    clock_gettime(CLOCK_MONOTONIC, &read_start);
    for (int i = 0; i < file_size / buffer_size; i++)
    {
        read(test_fd, read_buffer, buffer_size);
    }
    clock_gettime(CLOCK_MONOTONIC, &read_end);

    close(test_fd);

    unlink(FILENAME); // Delete the file

    // Calculate the elapsed time in seconds.
    double read_time = (read_end.tv_sec - read_start.tv_sec) * 1000 + (read_end.tv_nsec - read_start.tv_nsec) / 1000000.0;
    double write_time = (write_end.tv_sec - write_start.tv_sec) * 1000 + (write_end.tv_nsec - write_start.tv_nsec) / 1000000.0;

    printf("Write time per call: %f\n", write_time / (file_size / buffer_size));
    printf("Read time per call: %f\n", read_time / (file_size / buffer_size));

    return 0;
}
