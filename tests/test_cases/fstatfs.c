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
  // FILE *file = fopen("testfiles/fstatfsfile.txt", "r");
  // int fd = open(file_name, O_RDONLY);
  // if (fd == -1) {
  //   perror("Error opening file for statfs\n");
  //   exit(EXIT_FAILURE);
  // }
  // if (file == NULL){
  //   perror("Error opening file\n");
  //   exit(EXIT_FAILURE);
  // }
  // int fd = fileno(file);

  if ((fd = open("/dev/urandom", O_RDONLY, S_IRWXU|S_IRWXG|S_IRWXO))){
    perror("open()");
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
  printf("filesystem type: %d\n", buf.f_type);
  printf("Total blocks: %ld\n", buf.f_blocks);
  printf("Free blocks: %ld\n", buf.f_bfree);
  printf("Available blocks (non-root): %ld\n", buf.f_bavail);
  printf("Total file inodes: %ld\n", buf.f_files);
  printf("Free file inodes: %ld\n", buf.f_ffree);
  fflush(stdout);
  return 0;
}
