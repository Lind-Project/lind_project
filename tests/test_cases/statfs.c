#undef _GNU_SOURCE
#define _GNU_SOURCE

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/statfs.h>

// extern char **environ;

// const char* FILENAME = "testfiles/statfsfile.txt";

int main(int argc, char **argv) {
  // char file_name[100] = "testfiles/statfsfile.txt";
  // FILE *fp = stdout;
  char FILENAME[100] = "/dev/urandom";
  // statfs
  struct statfs buf = {0};
  if (statfs(FILENAME, &buf) == -1) {
    perror("Error in statfs\n");
    exit(EXIT_FAILURE);
  }
  // expected output is: 
  printf("Filesystem type: %lx\n", buf.f_type);
  printf("Total blocks: %ld\n", buf.f_blocks);
  printf("Free blocks: %ld\n", buf.f_bfree);
  printf("Available blocks (non-root): %ld\n", buf.f_bavail);
  printf("Total file inodes: %ld\n", buf.f_files);
  printf("Free file inodes: %ld\n", buf.f_ffree);
  fflush(stdout);
  return 0;
}