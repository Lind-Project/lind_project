#include <stdio.h> 
#include <fcntl.h> 
#include <stdlib.h> 
#include <unistd.h>
#include <time.h>
#include <string.h>

#define DATA_SIZE (4*1024*1024) 


long long gettimens(void) {
  struct timespec tp;

  if( clock_gettime(CLOCK_MONOTONIC, &tp) == -1 ) {
    perror( "clock gettime" );
    exit( EXIT_FAILURE );
  }

  return (tp.tv_sec * 1000000000) + tp.tv_nsec;
}

long long execution_time = 0;

int main() {
    char *src = malloc(DATA_SIZE);
    char *dest = malloc(DATA_SIZE);

    if(!src || !dest) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    for(int i = 0; i < DATA_SIZE; i++) {
        src[i] = (char)(i%256);
    }

    int count = 0;
    
    long long start_time = gettimens();
    int data_size_1M = 1024*1024;

    // while(count <= 1073741824) {
    //     memcpy(dest, src, data_size_1M);
    //     count++;
    // }
    
    // Get sum of time
    long long end_time = gettimens();
    long long total_time = end_time - start_time;
    // Average
    // long long average_time = total_time/count;
    memcpy(dest, src, 4096);
    printf("%s\n", dest);
    fflush(NULL);
    
    free(src);
    free(dest);

    printf("%d memcpy function calls, average time %lld ns\n", --count, total_time);
    fflush(NULL);
    
}

