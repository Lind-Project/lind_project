#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>

int main() {
  mode_t mode = S_IFIFO | 0666;

  if (mknod("namedpipe", mode, 0) == -1) {
    perror("mknod");
    exit(EXIT_FAILURE);
  }

  printf("Named pipe created successfully.\n");

  if (unlink("namedpipe") == -1) {
    perror("unlink");
    exit(EXIT_FAILURE);
  }
  printf("Unlinked named pipe.");

  // Not testing using mknod to create a device file since major and minor
  // numbers may change.
  return 0;
}
