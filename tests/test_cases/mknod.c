#undef _GNU_SOURCE
#define _GNU_SOURCE

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>

#define DEVICE_PATH "/dev/test"
#define MODE S_IFCHR | 0666

int main() {

  if (mknod(DEVICE_PATH, MODE, 0) == -1) {
    perror("mknod");
    exit(EXIT_FAILURE);
  }

  printf("Test char device created successfully.\n");

  if (unlink(DEVICE_PATH) == -1) {
    perror("unlink");
    exit(EXIT_FAILURE);
  }
  printf("Unlinked test char device.\n");

  return 0;
}
