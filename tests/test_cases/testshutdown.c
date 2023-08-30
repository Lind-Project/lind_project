#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <errno.h>

int main() {
    int fd = 0;
    int ret = shutdown(fd, SHUT_RD);
    if(ret < 0) {
        printf("ERROR: %d\n", errno);
        perror("shutdown");
        fflush(NULL);
        printf("Return: %d\n", ret);
        exit(1);
    }
    return 0;
}