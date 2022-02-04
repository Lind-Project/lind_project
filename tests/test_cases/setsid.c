#include <unistd.h>
#include <stdio.h>

int main() {

  int result = setsid();

  if(result < 0){
    printf("setsid() failed!\n");
  }
  else {
    printf("setsid() succeeded.\n");
  }

  return 0;
}
