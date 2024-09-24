#include <stdio.h> 
#include <fcntl.h> 
#include <stdlib.h> 
#include <unistd.h>
#include <time.h>
#include <string.h>

#define TOTAL_SIZE (2LL * 1024 * 1024 * 1024)  // 2GB

long long gettimens() {
    struct timespec tp;
    clock_gettime(CLOCK_MONOTONIC, &tp);
    return (long long)tp.tv_sec * 1000000000LL + tp.tv_nsec;
}

int main(int argc, char *argv[]) {
    int buf_size = atoi(argv[1]);
    char *buffer = (char *)malloc(buf_size);
    if (!buffer) {
        perror("Failed to allocate buffer");
        exit(EXIT_FAILURE);
    }
    memset(buffer, 'A', buf_size);

    unsigned long long loop_count = TOTAL_SIZE / buf_size;
    
    long long start_time = gettimens();
    
    for(int i = 0; i < loop_count; i++) {
        write(STDOUT_FILENO, buffer, buf_size);
    }
    
    long long end_time = gettimens();
    long long total_time = end_time - start_time;
    long long average_time = total_time / loop_count;
    
    printf("\nBuffer size %d bytes: %d write() calls, average time %lld ns\n", buf_size, loop_count, average_time);
    fflush(NULL);
    
    free(buffer);
    
    return 0;
}
