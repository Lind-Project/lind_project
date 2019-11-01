#include <stdio.h> 
#include <unistd.h> 
#include <stdlib.h>



#define MSGSIZE 16 

char* msg1 = "hello, world #1"; 
char* msg2 = "hello, world #2"; 
char* msg3 = "hello, world #3"; 
  
int main() 
{ 
    char inbuf[MSGSIZE]; 
    int p[2], i; 
    int len;

    if (pipe(p) < 0) 
        exit(1); 
    printf("Made pipe with write end %d and read end %d\n", p[0], p[1]); 
    /* continued */
    /* write pipe */
  
    len = write(p[1], msg1, MSGSIZE); 
    printf("wrote %d\n", len);
    len = write(p[1], msg2, MSGSIZE); 
    printf("write %d\n", len);
    len = write(p[1], msg3, MSGSIZE); 
    printf("wrote %d\n", len);

    printf("wrote three messages to the pipe\n");

    for (i = 0; i < 3; i++) { 
        /* read pipe */
        int len = read(p[0], inbuf, MSGSIZE); 
        printf("msg %d, length %d: % s\n", i, len, inbuf); 
    } 
    
    return 0; 
} 
