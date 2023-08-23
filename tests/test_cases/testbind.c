#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <netinet/in.h>
#include <errno.h>
#include <string.h>
#include <arpa/inet.h>

int main() {
    int sockfd;

    /* TEST: non-exitstent address */
    // sockfd = socket(AF_INET, SOCK_STREAM, 0);
    // struct sockaddr_in address;
    // address.sin_family = AF_INET;
    // address.sin_port = htons(12345);
    // address.sin_addr.s_addr = inet_addr("192.168.1.100");

    /* TEST: null address */ 
    // sockfd = socket(AF_INET, SOCK_STREAM, 0);
    // struct sockaddr_in address;
    // address.sin_family = AF_INET;
    // address.sin_port = htons(12345);
    // address.sin_addr.s_addr = inet_addr("");

    /* TEST: invalid path */
    sockfd = socket(AF_UNIX, SOCK_STREAM, 0);

    struct sockaddr_in address;
    address.sin_family = AF_UNIX;
    address.sin_port = htons(12345);
    const char *invalidPath = "/path/to/invalid/directory";
    address.sin_addr.s_addr = inet_addr(invalidPath);

    if(bind(sockfd, (struct sockaddr *)&address, sizeof(address)) < 0 ) { 
        perror("bind"); 
        printf("ERROR: %d\n", errno);
        exit(EXIT_FAILURE); 
    } 

    printf("Succeed\n");

    return 0;

}