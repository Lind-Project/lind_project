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
    struct sockaddr_in address;
    // struct sockaddr_un address;

    /* TEST: not socket */
    // sockfd = open("/home/lind/lind_project/tests/test_cases/write.c", O_RDONLY, 0777);

    /* TEST: passed address didnt have the correct addr family */
    // sockfd = socket(AF_INET, SOCK_STREAM, 0);

    // address.sin_family = AF_UNIX;

    /* TEST: invalid file descriptor */
    // sockfd = -1;
    
    /* TEST: no one listening */
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    address.sin_family = AF_INET; 
    address.sin_port = htons(9995); 
    inet_pton(AF_INET, "127.0.0.1", &address.sin_addr);

    /* TEST: EINPROGRESS*/
    // sockfd = socket(AF_UNIX, SOCK_STREAM, 0);
    // if (sockfd == -1) {
    //     perror("socket");
    //     return 1;
    // }

    // int flags = fcntl(sockfd, F_GETFL, 0);
    // if (flags == -1) {
    //     perror("fcntl F_GETFL");
    //     close(sockfd);
    //     return 1;
    // }
    // if (fcntl(sockfd, F_SETFL, flags | O_NONBLOCK) == -1) {
    //     perror("fcntl F_SETFL");
    //     close(sockfd);
    //     return 1;
    // }

    // memset(&address, 0, sizeof(struct sockaddr_un));
    // address.sun_family = AF_UNIX;
    // strncpy(address.sun_path, "/home/lind/lind_project/tests/test_cases/testbind.c", sizeof(address.sun_path) - 1);
       
    int ret = connect(sockfd, (struct sockaddr *)&address, sizeof(address));
    if(ret < 0) {
        printf("ERROR: %d\n", errno);
        fflush(NULL);
        perror("connect"); 
        printf("Return: %d\n", ret);
        exit(EXIT_FAILURE); 
    }

    printf("Succeed\n");
    return 0;
}