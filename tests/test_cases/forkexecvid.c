#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

#include <sys/types.h>
#include <sys/wait.h>

int main(void)
{
  pid_t pid;

  printf("Forkexecv \n");
    puts("Gid:");
    printf("%d\n", getgid());
    puts("Uid:");
    printf("%d\n", getuid());
    puts("Egid");
    printf("%d\n", getegid());
    puts("Euid");
    printf("%d\n", geteuid());

  if ((pid = fork()) == -1) {
    perror("fork error");
  }
  else if (pid == 0) {
    char* arr[] = {"getids", NULL};
    execv("automated_tests/getids", arr);
  }
  wait(NULL);
}