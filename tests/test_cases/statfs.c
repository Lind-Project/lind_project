#undef _GNU_SOURCE
#define _GNU_SOURCE

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/statfs.h>

int main(int argc, char **argv) {
  char file_name[100] = "testfiles/statfsfile.txt";

  // statfs
  struct statfs buf = {0};
  if (statfs(file_name, &buf) == -1) {
    perror("Error in fstatfs\n");
    exit(EXIT_FAILURE);
  }
  // expected output is: NFS_SUPER_MAGIC 0x6969 on native CentOS 7 on CIMS
  printf("filesystem type: %d", buf.f_type);
  fflush(stdout);
  return 0;
}
