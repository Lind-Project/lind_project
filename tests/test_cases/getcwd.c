#include <stdio.h>
#include <unistd.h>

#define BUFSIZE 32

int main() {
    char buf[BUFSIZE]; 
    gethostname(&buf, BUFSIZE);
    printf("Current working directory: %s\n", buf); 
    return 0; 
} 