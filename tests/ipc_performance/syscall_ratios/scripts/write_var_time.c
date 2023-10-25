#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

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

  int i = atoi(argv[1]);

  unsigned long long WRITE_BUFFER_SIZE = 1UL << i;
  unsigned long long NUMBER_OF_WRITES = 1UL << (30 - i);

  char *buffer = malloc(sizeof(char) * WRITE_BUFFER_SIZE);

  for (int i = 0; i < WRITE_BUFFER_SIZE; i++)
    buffer[i] = 'A';

  long long start_time = gettimens();
  for (int count = 0; count < NUMBER_OF_WRITES; count++)
  {
    if (count == (NUMBER_OF_WRITES - 1))
      buffer[WRITE_BUFFER_SIZE - 1] = '\0';
    write(STDOUT_FILENO, buffer, WRITE_BUFFER_SIZE);
  }
  long long end_time = gettimens();
  execution_time = (end_time - start_time);

  free(buffer);

  long long average_time = execution_time / NUMBER_OF_WRITES;
  fprintf(stderr, "%d write calls, average time %lld ns\n", NUMBER_OF_WRITES, average_time);
  fflush(stderr);
}
