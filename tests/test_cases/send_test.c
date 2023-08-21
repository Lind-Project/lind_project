#include <unistd.h>
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 
#include <arpa/inet.h> 
#include <pthread.h> 
#include <errno.h>
#define PORT 9995
int main() {
    int server_fd; 
    char *hello = "Hello from server"; 
       
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("socket failed"); 
        exit(EXIT_FAILURE); 
    } 
    
    int ret = send(server_fd, hello, strlen(hello), 0); 
    // printf("[send]: %d\n", ret);
    printf("[send]");
    if(ret < 0) {
        perror("send");
        printf("[send]: %d\n", ret);
    }
    return 0;
}
