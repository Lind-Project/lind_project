#include <stdio.h> 
#include <fcntl.h> 
#include <stdlib.h> 
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

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
int compare_memory(const char *src, const char *dest, size_t size) {
    for(size_t i = 0; i < size; i++) {
        if(src[i] != dest[i]) {
            return 0; // Memory differs
        }
    }
    return 1; // Memory is identical
}

int main(int argc, char *argv[]) {
  int loop = atoi(argv[1]);
  int test_data_size = atoi(argv[2]);
  // calloc
  size_t size = 2ULL * 1024 * 1024 * 1024;
  char *src = (char *)calloc(size, sizeof(char));
  char *dest = (char *)calloc(size, sizeof(char));
  // set mem randomly
  srand(time(NULL));
  for(int i = 0; i < size; i++) {
      src[i] = 'A' + rand() % 26; // Random character from A to Z
  }

  if(!src || !dest) {
      perror("calloc");
      exit(EXIT_FAILURE);
  }
  
  long long start_time = gettimens();
  // only do 2 loops, so count = 0 or 1
  while(count < loop) {
      int r = rand() % 2 + 1;
      memcpy(dest+count, src+count, test_data_size);
      if(!compare_memory(src+count, dest+count, test_data_size)) {
          printf("Memory comparison failed at iteration %d\n", count);
          break;
      }
      test_data_size = r + test_data_size;
      count++;
  }
  // memcpy(dest, src, data_size_1M);

  // Get sum of time
  long long end_time = gettimens();
  long long total_time = end_time - start_time;
  // Average
  // count--;
  long long average_time = total_time/count;
  long long average_speed = average_time/test_data_size;

  free(src);
  free(dest);

  printf("average time %lld ns, average speed %lld\n", total_time, average_speed);
  fflush(NULL);
  
}