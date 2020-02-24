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

  printf("first malloc\n");
  fflush(stdout);

  int *mptr1 = (int*)malloc(1000 * sizeof(int));

  *mptr1 = 0xdeadbeef;

  printf("Address of mptr1 %p\n", mptr1);
  printf("Contents of mptr1 %x\n", *mptr1);
  fflush(stdout);

  printf("pre-fork\n");
  fflush(stdout);

  if ((pid = fork()) == -1) {
    perror("fork error");
  }
  else if (pid == 0) {
  
    printf("in child\n");
    fflush(stdout);

    int *mptr2 = (int*) malloc(1000 * sizeof(int));
    
    printf("Address of mptr1 %p\n", mptr2);
    fflush(stdout);

    printf("done\n");
    fflush(stdout);
  }
  
  wait(NULL);
}

