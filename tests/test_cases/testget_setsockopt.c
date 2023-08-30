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
    int get_option_value;
    socklen_t option_size = sizeof(int);
    int ret_get = getsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &get_option_value, &option_size);
    if(ret_get < 0) {
        printf("ERROR: %d\n", errno);
        perror("getsockopt");
        fflush(NULL);
        printf("Return: %d\n", ret_get);
    }
    int option_value = 1;
    int ret_set = setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &option_value, sizeof(int));
    if(ret_set < 0) {
        printf("ERROR: %d\n", errno);
        perror("setsockopt");
        fflush(NULL);
        printf("Return: %d\n", ret_get);
        exit(1);
    }
    return 0;
}