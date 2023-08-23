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

static void sig_usr(int signum){
   printf("Received signal %d\n", signum);
}

int main() {
    int server_fd; 
    char *hello = "Hello from server"; 
       
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    printf("server fd: %d\n", server_fd);

    struct sigaction sa_usr;
    sa_usr.sa_flags = 0;
    sa_usr.sa_handler = sig_usr;  
    sigaction(SIGINT, &sa_usr, NULL);

    while (1) {
        int ret = send(server_fd, hello, strlen(hello), 0); 
        if(ret < 0) {
            perror("send");
            printf("[send]: %d\n", ret);
            return 0;
        }
    }
    
    return 0;
}
