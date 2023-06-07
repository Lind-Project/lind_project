#undef _GNU_SOURCE
#define _GNU_SOURCE

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char **argv) {
  char dir_name[100] = "testfolder";
  mode_t dir_per = (S_IRUSR | S_IWUSR);
  if (mkdir(dir_name, dir_per) == -1) {
    perror("mkdir");
    exit(EXIT_FAILURE);
  }
  printf("Created directory successfully\n");
  if (rmdir(dir_name) == -1) {
    perror("rmdir");
    exit(EXIT_FAILURE);
  }
  printf("Removed directory successfully\n");

  fflush(stdout);
  return 0;
}
