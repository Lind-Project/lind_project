#undef _GNU_SOURCE
#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>

const char* FILENAME = "testfiles/lseekfile.txt";

int main() {
    int fd = open(FILENAME, O_RDONLY);
    if(fd < 0) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    off_t file_size = lseek(fd, 0, SEEK_END);
    if(file_size < 0) {
        perror("lseek");
        close(fd);
        exit(EXIT_FAILURE);
    }
    printf("File size: %lld\n", file_size);
    fflush(NULL);

    if(lseek(fd, 0, SEEK_SET) < 0) {
        perror("lseek");
        close(fd);
        exit(EXIT_FAILURE);
    }

    char buf[12];
    if(read(fd, buf, 12) < 0) {
        perror("read");
        close(fd);
        exit(EXIT_FAILURE);
    }
    
    if(write(STDOUT_FILENO, buf, 12) < 0) {
        perror("write");
        close(fd);
        exit(EXIT_FAILURE);
    }

    off_t file_cur = lseek(fd, 0, SEEK_CUR);
    if(file_cur < 0) {
        perror("lseek");
        close(fd);
        exit(EXIT_FAILURE);
    }
    if(file_cur != 12){
        printf("offset after read should be 12\n");
        perror("lseek");
        close(fd);
        exit(EXIT_FAILURE);
    }
    
    off_t next_data = lseek(fd, 0, SEEK_DATA);
    if(next_data < 0) {
        perror("lseek");
        close(fd);
        exit(EXIT_FAILURE);
    }
    printf("\noffset should be 0, actually: %lld\n", next_data);
    fflush(NULL);

    off_t next_hole = lseek(fd, 0, SEEK_HOLE);
    if(next_hole < 0) {
        perror("lseek");
        close(fd);
        exit(EXIT_FAILURE);
    }
    printf("offset should be 661, actually: %lld\n", next_hole);
    fflush(NULL);

    close(fd);
    return 0;
}