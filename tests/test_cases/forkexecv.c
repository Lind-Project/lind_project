#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

#include <sys/types.h>
#include <sys/wait.h>

int main(void)
{
  pid_t pid;

  if ((pid = fork()) == -1) {
    perror("fork error");
  }
  else if (pid == 0) {
  
  char* arr[] = {"ls", NULL};
  execv("/bin/ls", arr);
  
  }
  wait(NULL);
}