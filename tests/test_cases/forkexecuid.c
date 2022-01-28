#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

#include <sys/types.h>
#include <sys/wait.h>

int main(void) {
  pid_t pid;
  puts("printing getgid:");
  printf("%d\n", getgid());
  puts("printing getuid:");
  printf("%d\n", getuid());
  puts("printing getegid:");
  printf("%d\n", getegid());
  puts("printing geteuid:");
  printf("%d\n", geteuid());
  
  pid = fork();	
  if (pid == -1) {
    perror("fork error");
  }
  else if (pid == 0) {
    char* arr[] = {"getuid", NULL};
    execv("automated_tests/getuid", arr);
  }
  wait(NULL);
}
