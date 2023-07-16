#undef _GNU_SOURCE
#define _GNU_SOURCE

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

#define FILE "testfiles/create_foo.txt"

int main() {
  int file_perm = S_IRUSR | S_IWUSR; // set file permissions
  int fd = creat(FILE, file_perm);
  if (fd == -1) {
    perror("ERROR WITH CREATE");
    exit(EXIT_FAILURE);
  }
  close(fd);
  printf("Created file\n");
  fflush(stdout);

  // Check if file exists
  int access_result = access(FILE, F_OK);
  if (access_result == -1) {
    perror("COULD NOT ACCESS FILE");
    exit(EXIT_FAILURE);
  }
  printf("File exists\n");
  fflush(stdout);

  // Check if file permissions are valid
  access_result = access(FILE, R_OK | W_OK);
  if (access_result == -1) {
    perror("INVALID PERMISSIONS FOR FILE");
    exit(EXIT_FAILURE);
  }
  printf("File has the right permissions\n");
  fflush(stdout);

  // Cleanup
  remove(FILE);
  fflush(stdout);
  return 0;
}

