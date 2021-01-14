#include <stdio.h>
#include <unistd.h>

#define BUFSIZE 64

int main() {
    char buf[BUFSIZE]; 
    getcwd(buf, BUFSIZE);
    printf("Current working directory: %s\n", buf); 
    return 0; 
} 