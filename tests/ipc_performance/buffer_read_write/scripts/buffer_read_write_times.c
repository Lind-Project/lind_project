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

    struct timespec start, end;
    struct timespec rw_start, rw_end;
    
    clock_gettime(CLOCK_MONOTONIC, &start);

    int test_fd = open(FILENAME, O_RDWR | O_CREAT, 0644);
    if (test_fd == -1)
    {
        perror("Failed to open file");
        exit(1);
    }

    clock_gettime(CLOCK_MONOTONIC, &rw_start);

    for (int i = 0; i < file_size / buffer_size; i++)
    {
        write(test_fd, buffer, buffer_size);
    }

    lseek(test_fd, 0, SEEK_SET);

    for (int i = 0; i < file_size / buffer_size; i++)
    {
        read(test_fd, buffer, buffer_size);
    }

    clock_gettime(CLOCK_MONOTONIC, &rw_end);

    close(test_fd);

    unlink(FILENAME); // Delete the file

    clock_gettime(CLOCK_MONOTONIC, &end);

    // Calculate the elapsed time in seconds.
    double total_elapsed_time = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1000000000.0;
    double rw_elapsed_time = (rw_end.tv_sec - rw_start.tv_sec) + (rw_end.tv_nsec - rw_start.tv_nsec) / 1000000000.0;

    printf("Total time taken: %f\n", total_elapsed_time);
    printf("Read-Write time taken: %f\n", rw_elapsed_time);

    return 0;
}
