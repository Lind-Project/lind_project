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

    /* TEST: not socket */
    sockfd = open("/home/lind/lind_project/tests/test_cases/write.c", O_RDONLY, 0777);

    struct sockaddr_in address;
    int ret = connect(sockfd, (struct sockaddr *)&address, sizeof(address));
    if(ret < 0) {
        perror("connect"); 
        printf("ERROR: %d\n", errno);
        exit(EXIT_FAILURE); 
    }

    printf("Succeed\n");
    return 0;
}