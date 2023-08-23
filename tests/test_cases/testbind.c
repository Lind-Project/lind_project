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
    
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    address.sin_family = AF_INET;
    address.sin_port = htons(12345);  // Port number
    // Bind to a non-existent address (example: 192.168.1.100)
    address.sin_addr.s_addr = inet_addr("192.168.1.100");

    if(bind(sockfd, (struct sockaddr *)&address, sizeof(address)) < 0 ) { 
        perror("bind"); 
        printf("ERROR: %d\n", errno);
        exit(EXIT_FAILURE); 
    } 

    return 0;

}