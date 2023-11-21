#include <stdio.h> 
#include <fcntl.h> 
#include <stdlib.h> 
#include <unistd.h>
#include <time.h>
#include <string.h>

#define DATA_SIZE (4*1024*1024)  // 4K


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

    // int count = 0;
    
    // long long start_time = gettimens();

    // while(count <= 2 << 30) {
    //     memcpy(dest, src, 4096);
    //     count++;
    // }
    
    // // Get sum of time
    // long long end_time = gettimens();
    // long long total_time = end_time - start_time;
    // // Average
    // long long average_time = total_time/count;

    free(src);
    free(dest);

    // printf("%d dummy function calls, average time %lld ns\n", --count, average_time);
    fflush(NULL);
    
}

