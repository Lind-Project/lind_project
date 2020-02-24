#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
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
  
    printf("in child\n");
    fflush(stdout);

    int *ptr = (int*) malloc(1000 * sizeof(int));

    printf("pointer address is %p\n", ptr);
    fflush(stdout);

    printf("done\n");
    fflush(stdout);
  }
  
  wait(NULL);
}

