#undef _GNU_SOURCE
#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void) {

  // Get pid of current process
  pid_t pid = getpid();

  // Fork
  int f = fork();
  if(f == -1){
    perror("fork() failed");
    exit(1);
  }

  // Child process
  if(f == 0){
    pid_t ppid = getppid();
    if (ppid == pid){
      printf("getppid() succeeded\n");
      fflush(stdout);
      exit(EXIT_SUCCESS);
    }
    else {
      printf("getppid() failed\n");
      fflush(stdout);
      exit(EXIT_FAILURE);
    }
  }
  // Parent process
  else {
    // Wait till child process returns, and only then exit
    wait(NULL);
  }
  return 0;
}

