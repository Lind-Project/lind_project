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
    int new_socket; 
    char *hello = "[Client] Hello from server"; 
    int ret = send(new_socket, hello, strlen(hello), 0);
    if(ret < 0){
        perror("send");
        printf("[!] send %d; %s\n", ret, strerror(errno));
    } 
    return 0;
}
