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
  int fd = open("/dev/urandom", O_RDONLY, S_IRWXU|S_IRWXG|S_IRWXO);
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
  // expected output is: NFS_SUPER_MAGIC 0x6969 on native CentOS 7 on CIMS
  printf("Filesystem type: %lx\n", buf.f_type);
  printf("Total blocks: %ld\n", buf.f_blocks);
  printf("Free blocks: %ld\n", buf.f_bfree);
  printf("Available blocks (non-root): %ld\n", buf.f_bavail);
  printf("Total file inodes: %ld\n", buf.f_files);
  printf("Free file inodes: %ld\n", buf.f_ffree);
  fflush(stdout);
  return 0;
}
