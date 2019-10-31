

#include <stdio.h> 
#include <unistd.h> 
#include <stdlib.h>
  
int main() 

{	
  char buffer[10];
  read(STDIN_FILENO, buffer, 10);
  buffer[10] = '\0';
  printf(buffer);
  
		
  return 0;

}
