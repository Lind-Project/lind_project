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
  
  /* Adding testdir/ is a different solution that makes sure both directories are the same. 
  It requires creating a testdir/ (with some temp files preferably) inside lindsh root directory as well.
  Lind does not support touch, so creating a folder inside lindsh and pasting it would be way easier.
  Perhaps we can use automated_tests/test_out.
  */
  char* arr[] = {"ls", "automated_tests/",NULL};
  execv("/bin/ls", arr); // Issue: requires coreutils to be preinstalled. We will have to implement it to our CI/CD.
  
  }
  wait(NULL);
}