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

  return 0;
}
