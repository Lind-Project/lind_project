#undef _GNU_SOURCE
#define _GNU_SOURCE

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/statfs.h>

int main(int argc, char **argv) {
  char FILENAME[100] = "testfiles/statfsfile.txt";
  
  // statfs
  struct statfs buf = {0};
  if (statfs(FILENAME, &buf) == -1) {
    perror("Error in statfs\n");
    exit(EXIT_FAILURE);
  }
  // system file info
  printf("Filesystem type: %lx\n", buf.f_type);
  fflush(stdout);
  return 0;
}
