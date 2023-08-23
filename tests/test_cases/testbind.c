#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <netinet/in.h>
#include <errno.h>
#include <string.h>
#include <arpa/inet.h>

int main() {
    int sockfd;
    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_port = htons(12345);

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    /* TEST: non-exitstent address */
    // address.sin_addr.s_addr = inet_addr("192.168.1.100");

    /* TEST: null address */ 
    address.sin_addr.s_addr = inet_addr("");

    if(bind(sockfd, (struct sockaddr *)&address, sizeof(address)) < 0 ) { 
        perror("bind"); 
        printf("ERROR: %d\n", errno);
        exit(EXIT_FAILURE); 
    } 

    printf("Succeed\n");
    
    return 0;

}