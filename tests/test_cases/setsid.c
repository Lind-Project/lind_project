#include <unistd.h>
#include <stdio.h>

int main() {

  int result = setsid();

  printf("setsid() returned: %d\n", result);

  if(result < 0){
    printf("setsid() failed!\n");
  }
  else {
    printf("setsid() succeeded.\n");
  }

  return 0;
}
