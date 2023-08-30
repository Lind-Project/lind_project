#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>

int main() {
    int sockets[2], child;
    char buf[1024];

    int ret = socketpair(AF_UNIX, SOCK_STREAM, 3, sockets);
    if(ret < 0) {
        printf("ERROR: %d\n", errno);
        perror("socketpair");
        fflush(NULL);
        printf("Return: %d\n", ret);
        exit(1);
    }

    return 0;
}