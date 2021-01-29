#include <stdio.h>
#include <unistd.h>

int main() 
{   
    int buffersize = 256;
    char hostbuffer[buffersize]; 
  
    gethostname(hostbuffer, buffersize);
  
    printf("Hostname: %s\n", hostbuffer); 

    return 0; 
} 