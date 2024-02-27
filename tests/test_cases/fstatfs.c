#undef _GNU_SOURCE
#define _GNU_SOURCE

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/statfs.h>

int main(int argc, char **argv) {
  int fd = open("testfiles/fstatfsfile.txt", O_RDONLY);
  if (fd < 0){
    perror("Error in open()\n");
    exit(EXIT_FAILURE);
  }
  
  // fstatfs
  struct statfs buf = {0};
  if (fstatfs(fd, &buf) == -1) {
    perror("Error in fstatfs\n");
    close(fd);
    exit(EXIT_FAILURE);
  }
  close(fd);

  // system file info
  printf("Filesystem type: %lx\n", buf.f_type);
  fflush(stdout);
  return 0;
}
