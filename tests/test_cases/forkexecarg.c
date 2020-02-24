#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

#include <sys/types.h>
#include <sys/wait.h>

int main(void)
{
  pid_t pid;
  char *envp[] = {NULL};

  char *const parmList[] = {"/bin/ls", "-a", "/", NULL};
  if ((pid = fork()) == -1) {
    perror("fork error");
  }
  else if (pid == 0) {
    printf("%d\n", pid);
    execve("/bin/ls", parmList, envp);
    perror("execv error");
  }
  wait(NULL);
}

