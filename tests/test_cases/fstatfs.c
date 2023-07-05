#undef _GNU_SOURCE
#define _GNU_SOURCE

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/statfs.h>

int main(int argc, char **argv) {
  // int fd = open("/dev/urandom", O_RDONLY, S_IRWXU|S_IRWXG|S_IRWXO);
  int fd = open("testfiles/fstatfsfile.txt", O_RDONLY | O_CREAT, S_IRWXU | S_IRWXG | S_IRWXO);
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

  // check system file info
  if (buf.f_type != 0xBEEFC0DE)
  {
    fprintf(stderr, "Expected fstatfsfile.txt to have file type beefc0de but was  %lx\n", buf.f_type);
		exit(EXIT_FAILURE);
  }
  if (buf.f_blocks != 4096)
  {
    fprintf(stderr, "Expected fstatfsfile.txt to have total block 4096 but was  %ld\n", buf.f_blocks);
		exit(EXIT_FAILURE);
  }
  if (buf.f_bavail != 1073741824)
  {
    fprintf(stderr, "Expected fstatfsfile.txt to have available blocks (non-root) 1073741824 but was  %ld\n", buf.f_bavail);
		exit(EXIT_FAILURE);
  }
  fprintf(stdout, "Getting file info successfully\n");
  // printf("Filesystem type: %lx\n", buf.f_type);
  // printf("Total blocks: %ld\n", buf.f_blocks);
  // printf("Free blocks: %ld\n", buf.f_bfree);
  // printf("Available blocks (non-root): %ld\n", buf.f_bavail);
  // printf("Total file inodes: %ld\n", buf.f_files);
  // printf("Free file inodes: %ld\n", buf.f_ffree);
  fflush(stdout);
  return 0;
}
