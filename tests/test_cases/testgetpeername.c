#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <errno.h>

int main() {
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in server_addr;
    socklen_t len = sizeof(server_addr);
    int ret = getpeername(fd, (struct sockaddr*)&server_addr, &len);
    if(ret < 0) {
        printf("ERROR: %d\n", errno);
        perror("getpeername");
        fflush(NULL);
        printf("Return: %d\n", ret);
        exit(1);
    }
    return 0;
}