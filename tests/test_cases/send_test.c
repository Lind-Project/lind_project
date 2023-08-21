#include <unistd.h>
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 
#include <arpa/inet.h> 
#include <signal.h>
#include <errno.h>
#include <pthread.h> 
#define PORT 9995
pthread_barrier_t barrier;
void* client(void* v) { 
    int sock = 0, valread; 
    struct sockaddr_in serv_addr; 
    char *hello = "Hello from client"; 
    char buffer[1024] = {0}; 
    long opt = 1;
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))) {
        perror("setsockopt"); 
        exit(EXIT_FAILURE); 
    }
    serv_addr.sin_family = AF_INET; 
    serv_addr.sin_port = htons(PORT); 
       
    // Convert IPv4 and IPv6 addresses from text to binary form 
    inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr);
   
    pthread_barrier_wait(&barrier);
    int connret = connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    send(sock , hello , strlen(hello) , 0 );
    printf("Hello message sent\n");
    valread = recv( sock , buffer, 1024, 0); 
    printf("%s\n",buffer ); 
    return NULL; 
} 

void* server(void* v) {
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
       
    // Forcefully attaching socket to the port
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))) {
        perror("setsockopt"); 
        exit(EXIT_FAILURE); 
    } 
    address.sin_family = AF_INET; 
    address.sin_addr.s_addr = INADDR_ANY; 
    address.sin_port = htons( PORT ); 
       
    // Forcefully attaching socket to the port
    if (bind(server_fd, (struct sockaddr *)&address,  
                                 sizeof(address))<0) { 
        perror("bind failed"); 
        exit(EXIT_FAILURE); 
    } 
    if (listen(server_fd, 3) < 0) 
    { 
        perror("listen"); 
        exit(EXIT_FAILURE); 
    } 
    pthread_barrier_wait(&barrier);
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address,  
                       (socklen_t*)&addrlen))<0) { 
        perror("accept"); 
        exit(EXIT_FAILURE); 
    } 
    // valread = recv( new_socket , buffer, 1024, 0);
    // printf("%s\n",buffer ); 
    int ret = send(new_socket , hello , strlen(hello) , 0 ); 
    if (ret < 0) {
        perror("send");
        printf("[send]: %d\n", ret);
    }
    printf("Hello message sent\n"); 
    return NULL;
} 

int main() {
    pthread_t serverthread, clientthread1, clientthread2;
    pthread_barrier_init(&barrier, NULL, 2);
    pthread_create(&serverthread, NULL, server, NULL);
    pthread_create(&clientthread1, NULL, client, NULL);
    pthread_join(clientthread1, NULL);
    pthread_join(serverthread, NULL);
    pthread_barrier_destroy(&barrier);
    return 0;
}

