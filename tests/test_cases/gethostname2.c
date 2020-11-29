#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) 
{   
    if( argc != 2 ) {
        printf("Please give exactly one integer as input.\n");
        return 0;
    }

    //assuming the input was an integer, will use the 0 given by atoi if an in-adequate input was supplied

    int buffersize = atoi(argv[1]);
    char hostbuffer[buffersize]; 
  
    gethostname(hostbuffer, buffersize);
  
    printf("Hostname: %s\n", hostbuffer); 

    return 0; 
} 