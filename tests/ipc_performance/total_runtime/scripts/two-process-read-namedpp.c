#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

// RawPOSIx
#define FIFO_NAME "/myfifo"

int main(int argc, char **argv) {

    int fd;
    int i = atoi(argv[1]);

    if ((fd = open(FIFO_NAME, O_RDONLY)) < 0) {
        perror("Open failed");
        exit(1);
    }

    unsigned long long READ_BUFFER_CHUNK = 1UL << i;

    char *buffer = (char *)calloc(READ_BUFFER_CHUNK, sizeof(char));

    int total_read = 0;
    int readlen = 0;

    while ((readlen = read(fd, buffer, READ_BUFFER_CHUNK)) > 0)
    {
    }

    free(buffer);

    close(fd);
    return 0;
}