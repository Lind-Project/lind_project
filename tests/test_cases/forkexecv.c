#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

#include <sys/types.h>
#include <sys/wait.h>

int main(void)
{
  pid_t pid;
  char *envp[] = {NULL};

  if ((pid = fork()) == -1) {
    perror("fork error");
  }
  else if (pid == 0) {
  
  char* arr[] = {"/bin/ls", "-l", "-a", NULL};
  execv("/bin/ls", arr);
  
  }
  wait(NULL);
}

