#include <unistd.h>
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 
#include <arpa/inet.h> 
#include <signal.h>
#include <errno.h>
#define PORT 9995
int main() {
    int server_fd, new_socket, valread; 
    struct sockaddr_in address; 
    long opt = 1;
    int addrlen = sizeof(address); 
    char buffer[1024] = {0}; 
    char *hello = "Hello from server"; 
       
    // Creating socket file descriptor 
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("socket failed"); 
        exit(EXIT_FAILURE); 
    } 

    int ret = send(server_fd, hello, strlen(hello), 0); 
    printf("[send]: %d\n", ret);
    if(ret < 0) {
        perror("send");
        printf("[send]: %d\n", ret);
    }
    return 0;
}
