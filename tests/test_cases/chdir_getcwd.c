#include <unistd.h>
#include <stdio.h>

int main() {
  int buffersize = 256;
  char cwd[buffersize];

  char* result = getcwd(cwd, sizeof(cwd));

  if (result == NULL)
    perror("getcwd() error");
  else
    printf("current working directory is: %s :: %s\n", cwd, result);
  //---------------------------
  /* Chdir into /test causes issues on native as we don't have the permissions to create a folder in /. 
  Creating a folder "test" under cwd would be better. Note that we still need to create folders manually/by an external script. -Kapkic */
  chdir("automated_tests/"); 
  //---------------------------
  result = getcwd(cwd, sizeof(cwd));

  if (result == NULL)
    perror("getcwd() error");
  else
    printf("current working directory is: %s :: %s\n", cwd, result);

  return 0;
}
