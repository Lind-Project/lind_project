#include <unistd.h>
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 
#include <arpa/inet.h> 
#include <pthread.h> 
#include <errno.h>
#include <signal.h>

int main() {
    int server_fd; 
    char *hello = "Hello from server"; 
       
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    printf("server fd: %d\n", server_fd);

    int ret = send(server_fd, hello, strlen(hello), 0); 
    if(ret < 0) {
        printf("ERROR: %d\n", errno);
        perror("send");
        fflush(NULL);
        printf("Return: %d\n", ret);
        return 0;
    }
    
    return 0;
}
