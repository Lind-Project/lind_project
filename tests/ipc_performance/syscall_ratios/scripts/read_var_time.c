#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define READ_BUFFER_SIZE 1UL << 30

long long gettimens(void)
{
  struct timespec tp;

  if (clock_gettime(CLOCK_MONOTONIC, &tp) == -1)
  {
    perror("clock gettime");
    exit(EXIT_FAILURE);
  }

  return (tp.tv_sec * 1000000000) + tp.tv_nsec;
}

long long execution_time = 0;

int main(int argc, char *argv[])
{

  char *buffer = (char *)calloc(READ_BUFFER_SIZE, sizeof(char));

  int i = atoi(argv[1]);

  unsigned long long READ_BUFFER_CHUNK = 1UL << i;
  unsigned long long READ_TOTAL = 1UL << (30 - i);

  int total_read = 0;
  int readlen = 1;

  long long start_time = gettimens();
  while (readlen > 0)
  {
    readlen = read(STDIN_FILENO, buffer + total_read, READ_BUFFER_CHUNK);
    total_read += readlen;
  }
  long long end_time = gettimens();
  long long total_time = end_time - start_time;

  free(buffer);

  long long average_time = total_time / READ_TOTAL;
  fprintf(stderr, "%d read calls, average time %lld ns\n", READ_TOTAL, average_time);
  fflush(stderr);
}
