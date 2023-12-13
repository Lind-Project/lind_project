#include <stdio.h> 
#include <fcntl.h> 
#include <stdlib.h> 
#include <unistd.h>
#include <time.h>
#include <string.h>

#define DATA_SIZE (4*1024*1024) 

volatile int count = 0;

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
  int loop = atoi(argv[1]);
  int data_size = atoi(argv[2]);
  // calloc
  char *src = (char *)calloc(DATA_SIZE, sizeof(char));
  char *dest = (char *)calloc(DATA_SIZE, sizeof(char));
  // set mem
  memset(src, 'A', DATA_SIZE);

  if(!src || !dest) {
      perror("calloc");
      exit(EXIT_FAILURE);
  }

  int data_size_4K = 1024*4;
  int data_size_1M = 1024*1024;
  
  long long start_time = gettimens();

  while(count < loop) {
      memcpy(dest, src, data_size_1M);
      count++;
  }
  // memcpy(dest, src, data_size_1M);

  // Get sum of time
  long long end_time = gettimens();
  long long total_time = end_time - start_time;
  // Average
  // count--;
  long long average_time = total_time/count;
  long long average_speed = average_time/data_size_1M;

  free(src);
  free(dest);

  printf("average time %lld ns, average speed %lld\n", average_time, average_speed);
  fflush(NULL);
  
}

