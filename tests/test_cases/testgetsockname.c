#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <errno.h>

int main() {
    int fd = 0;
    struct sockaddr_in server_addr;
    socklen_t len = sizeof(server_addr);
    int ret = getsockname(fd, (struct sockaddr*)&server_addr, &len);
    if(ret < 0) {
        printf("ERROR: %d\n", errno);
        perror("getsockname");
        fflush(NULL);
        printf("Return: %d\n", ret);
        exit(1);
    }
    return 0;
}