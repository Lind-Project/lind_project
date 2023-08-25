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
    /* TEST: NOT socket*/
    sockfd = open("/home/lind/lind_project/tests/test_cases/write.c", O_RDONLY, 0777);
    struct sockaddr_in address;
    /* AF_INET */
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

    /* AF_UNIX */ 
    // sockfd = socket(AF_UNIX, SOCK_STREAM, 0);

    // struct sockaddr_un address;
    // address.sun_family = AF_UNIX;

    /* TEST: invalid path */
    // const char *invalidPath = "/path/to/invalid/directory";

    /* TEST: null path */
    // const char *invalidPath = "";
    // const char *invalidPath = "/home/lind/lind_project/tests/test_cases";
    // strncpy(address.sun_path, invalidPath, sizeof(address.sun_path)-1);

    int ret = bind(sockfd, (struct sockaddr *)&address, sizeof(address));
    if( ret < 0 ) { 
        printf("ERROR: %d\n", errno);
        perror("bind"); 
        fflush(NULL);
        printf("Return: %d\n", ret);
        exit(EXIT_FAILURE); 
    } 

    printf("Succeed\n");

    return 0;

}