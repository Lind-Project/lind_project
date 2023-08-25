#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <netinet/in.h>
#include <errno.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/un.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

int main() {
    int sockfd;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    int ret;
    ret = listen(sockfd, 3);
    if(ret < 0) {
        printf("ERROR: %d\n", errno);
        perror("listen"); 
        fflush(NULL);
        printf("Return: %d\n", ret);
        exit(EXIT_FAILURE); 
    }
}