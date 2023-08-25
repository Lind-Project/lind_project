#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <netinet/in.h>
#include <errno.h>
#include <string.h>

int main( int argc, char *argv[] ) {
    int sockfd;
   
   /* Test: invalid protocal */
   sockfd = socket(AF_INET, SOCK_STREAM, 99);
   
    if (sockfd < 0) {
        printf("ERROR: %d\n", errno);
        perror("socket");
        printf("Return: %d\n", sockfd);
        fflush(NULL);
        exit(1);
    }
    printf("Return: %d\n", sockfd);

    /* Test: non-blocking */ 
    // sockfd = socket(AF_INET, SOCK_NONBLOCK, 0);
    // if(sockfd < 0) {
    //     perror("socket");
    //     printf("ERROR: %d\n", errno);
    //     exit(1);
    // }
    
    printf("Socket opened succesfully.");
      
    return 0;
}