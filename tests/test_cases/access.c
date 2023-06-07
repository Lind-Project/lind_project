#undef _GNU_SOURCE
#define _GNU_SOURCE

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
  int file_perm = S_IRUSR | S_IWUSR; // set file permissions
  int fd = creat("create_foo.txt", file_perm);
  if (fd == -1) {
    perror("ERROR WITH CREATE");
    exit(EXIT_FAILURE);
  }
  close(fd);
  printf("Created fd %d\n", fd);

  // Check if file exists
  int access_result = access("create_foo.txt", F_OK);
  if (access_result == -1) {
    perror("COULD NOT ACCESS FILE");
    exit(EXIT_FAILURE);
  }
  printf("File exists\n");

  // Check if file permissions are valid
  access_result = access("create_foo.txt", R_OK | W_OK);
  if (access_result == -1) {
    perror("INVALID PERMISSIONS FOR FILE");
    exit(EXIT_FAILURE);
  }
  printf("File has the right permissions\n");

  // Cleanup
  remove("create_foo.txt");
  fflush(stdout);
  return 0;
}
