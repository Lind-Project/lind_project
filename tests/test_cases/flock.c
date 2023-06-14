#undef _GNU_SOURCE
#define _GNU_SOURCE

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

int remove_file(char file_name[]) {
  int rm = remove(file_name);
  if (rm == -1) {
    perror("FAILED TO REMOVE FILE\n");
    exit(EXIT_FAILURE);
  }
  return 0;
}

int main(int argc, char **argv) {
  // Open a file to use
  char file_name[100] = "flock.txt";
  int fd = open(file_name, O_RDWR | O_CREAT, 0777);
  if (fd == -1) {
    perror("OPEN FAILED\n");
    exit(EXIT_FAILURE);
  }

  // Get an exclusive lock on the file
  int lock = flock(fd, LOCK_EX);
  if (lock == -1) {
    perror("FAILED TO GET EXCLUSIVE LOCK\n");
    close(fd);
    remove_file(file_name);
    exit(EXIT_FAILURE);
  }
  printf("Obtained exclusive lock on file\n");

  // Release the exclusive lock on the file
  lock = flock(fd, LOCK_UN);
  if (lock == -1) {
    perror("FAILED TO RELEASE EXCLUSIVE LOCK\n");
    close(fd);
    remove_file(file_name);
    exit(EXIT_FAILURE);
  }
  printf("Released exclusive lock on file\n");

  // Get a shared lock on the file
  lock = flock(fd, LOCK_SH);
  if (lock == -1) {
    perror("FAILED TO GET SHARED LOCK\n");
    close(fd);
    remove_file(file_name);
    exit(EXIT_FAILURE);
  }
  printf("Obtained shared lock on file\n");

  // Release the shared lock on the file
  lock = flock(fd, LOCK_UN);
  if (lock == -1) {
    perror("FAILED TO RELEASE SHARED LOCK\n");
    close(fd);
    remove_file(file_name);
    exit(EXIT_FAILURE);
  }
  printf("Released shared lock on file\n");

  // Close file before removing
  close(fd);

  // Remove the file
  remove(file_name);
  return 0;
}
