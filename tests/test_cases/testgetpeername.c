#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <errno.h>

int main() {
    // int fd;
    // struct sockaddr_in server_addr;
    // socklen_t len = sizeof(server_addr);
    // int ret = getpeername(fd, (struct sockaddr*)&server_addr, &len);
    // if(ret < 0) {
    //     printf("ERROR: %d\n", errno);
    //     perror("getpeername");
    //     fflush(NULL);
    //     printf("Return: %d\n", ret);
    //     exit(1);
    // }
    // return 0;
    int server_socket;
    struct sockaddr_in server_addr;

    // Create socket
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        perror("socket");
        return 1;
    }

    // Bind
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(12345);

    if (bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        perror("bind");
        close(server_socket);
        return 1;
    }

    // Listen
    if (listen(server_socket, 10) == -1) {
        perror("listen");
        close(server_socket);
        return 1;
    }

    printf("Waiting for incoming connection...\n");

    while (1) {
        int client_socket;
        struct sockaddr_in client_addr;
        socklen_t addr_size = sizeof(client_addr);

        // Accept connection
        client_socket = accept(server_socket, (struct sockaddr*)&client_addr, &addr_size);
        if (client_socket == -1) {
            perror("accept");
            continue;
        }

        char client_ip[INET_ADDRSTRLEN];
        int client_port;

        // Get remote address information using getpeername()
        struct sockaddr_in peer_addr;
        socklen_t peer_addr_len = sizeof(peer_addr);
        if (getpeername(client_socket, (struct sockaddr*)&peer_addr, &peer_addr_len) == -1) {
            perror("getpeername");
            close(client_socket);
            continue;
        }

        struct sockaddr_in* pV4Addr = (struct sockaddr_in*)&peer_addr;
        inet_ntop(AF_INET, &(pV4Addr->sin_addr), client_ip, INET_ADDRSTRLEN);
        client_port = ntohs(pV4Addr->sin_port);

        printf("Connection established with %s:%d\n", client_ip, client_port);

        close(client_socket);
    }

    close(server_socket);
    return 0;
}