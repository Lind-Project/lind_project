#include <stdio.h> 
#include <fcntl.h> 
#include <stdlib.h> 
#include <unistd.h>
#include <time.h>

long long gettimens(void) {
  struct timespec tp;

  if( clock_gettime(CLOCK_MONOTONIC, &tp) == -1 ) {
    perror( "clock gettime" );
    exit( EXIT_FAILURE );
  }

  return (tp.tv_sec * 1000000000) + tp.tv_nsec;
}

long long execution_time = 0;

int main(int argc, char *argv[]) {
    int i = atoi(argv[1]);
    int count = 0;
    long long start_time = gettimens();
    
    while(count <= i) {
        getpid();
        count++;
    }
    
    // Get sum of time
    long long end_time = gettimens();
    long long total_time = end_time - start_time;
    // Average
    long long average_time = total_time/count;
    printf("%d getpid function calls, average time %lld ns\n", i, average_time);
    fflush(NULL);
    
}

