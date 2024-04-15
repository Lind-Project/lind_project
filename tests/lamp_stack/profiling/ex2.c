#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main() {
  char *path = "/bin/ls";
  char *args[] = {path, NULL};
  if(execv(path, args) == -1) {
    perror("execv");
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
