#undef _GNU_SOURCE
#define _GNU_SOURCE

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/statfs.h>

int main(int argc, char **argv) {
  // Open the file first
  char file_name[100] = "testfiles/fstatfsfile.txt";
  int fd = open(file_name, O_RDONLY);
  if (fd == -1) {
    perror("Error opening file for statfs\n");
    exit(EXIT_FAILURE);
  }

  // fstatfs
  struct statfs buf = {0};
  if (fstatfs(file_name, &buf) == -1) {
    perror("Error in fstatfs\n");
    close(fd);
    exit(EXIT_FAILURE);
  }
  close(fd);

  // expected output is: NFS_SUPER_MAGIC 0x6969 on native CentOS 7 on CIMS
  printf("filesystem type: %d\n", buf.f_type);
  fflush(stdout);
  return 0;
}
