#undef _GNU_SOURCE
#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main(void) {
  puts("printing pid");

  printf("%d\n", getppid());
  perror("");
  puts("getppid() succeeded");

  return 0;
}
