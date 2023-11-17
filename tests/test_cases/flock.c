#undef _GNU_SOURCE
#define _GNU_SOURCE

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/file.h>
#include <sys/wait.h>

#define FILE "testfiles/flock.txt"

// Helper function to remove a file
int remove_file(char file_name[]) {
  int rm = remove(file_name);
  if (rm == -1) {
    perror("FAILED TO REMOVE FILE\n");
    exit(EXIT_FAILURE);
  }
  return 0;
}

int main(int argc, char **argv) {
  // Create a temporary file to use
  int fd = open(FILE, O_RDWR | O_CREAT, 0777);
  if (fd == -1) {
    perror("OPEN FAILED\n");
    exit(EXIT_FAILURE);
  }

  // Get an exclusive lock on the file
  int lock = flock(fd, LOCK_EX);
  if (lock == -1) {
    perror("FAILED TO GET EXCLUSIVE LOCK\n");
    close(fd);
    remove_file(FILE);
    exit(EXIT_FAILURE);
  }
  printf("Obtained exclusive lock on file\n");
  fflush(stdout);

  // Release the exclusive lock on the file
  lock = flock(fd, LOCK_UN);
  if (lock == -1) {
    perror("FAILED TO RELEASE EXCLUSIVE LOCK\n");
    close(fd);
    remove_file(FILE);
    exit(EXIT_FAILURE);
  }
  printf("Released exclusive lock on file\n");
  fflush(stdout);

  // Get an shared lock on the file
  lock = flock(fd, LOCK_SH);
  if (lock == -1) {
    perror("FAILED TO GET SHARED LOCK\n");
    close(fd);
    remove_file(FILE);
    exit(EXIT_FAILURE);
  }
  printf("Obtained shared lock on file\n");
  fflush(stdout);

  // Now fork this process
  int f = fork();
  if(f == -1){
    perror("FAILED TO FORK\n");
    exit(EXIT_FAILURE);
  }

  /* 
  * We cannot use the same file descriptor in the child process,
  * since the locks created by flock are associated with an open file table entry.
  * This means that duplicate file descriptors refer to the same lock,
  * and can be hence used across processes to acquire/release it.
  */
  if(f == 0){
    // Get a new file descriptor in the child process
    fd = open(FILE, O_RDWR, 0777);
    if (fd == -1) {
      perror("OPEN FAILED\n");
      exit(EXIT_FAILURE);
    }

    // Get an shared lock on the file
    lock = flock(fd, LOCK_SH);
    if (lock == -1) {
      perror("FAILED TO GET SHARED LOCK\n");
      close(fd);
      remove_file(FILE);
      exit(EXIT_FAILURE);
    }
    printf("Obtained shared lock on file\n");
    fflush(stdout);
  }
  else {
    // Wait for the child process to finish first
    wait(NULL);
  }

  // Release the shared lock on the file
  lock = flock(fd, LOCK_UN);
  if (lock == -1) {
    perror("FAILED TO RELEASE SHARED LOCK\n");
    close(fd);
    remove_file(FILE);
    exit(EXIT_FAILURE);
  }
  printf("Released shared lock on file\n");
  fflush(stdout);

  // Close file before removing
  close(fd);

  // Let only the parent process remove the temporary file
  if(f != 0) {
    remove(FILE);
  }
  return 0;
}
