#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <pthread.h>

/* 
*   In this test case, we choose to use Unix Domain Sockets (UDS) instead of IPv4/IPv6. 
*   While running individual tests with IPv4/IPv6 works fine, we encounter "connection in 
*   use" issues when running them as part of a larger test suite. The purpose of this test 
*   is solely to verify that the getpeername function works as expected. Therefore, we 
*   opted to use UDS for this test.
*/

#define SERVER_SOCKET_PATH "unix_sock.server"
#define CLIENT_SOCKET_PATH "unix_sock.client"
#define BUFFER_SIZE 1024

void error(const char *msg) {
    perror(msg);
    exit(EXIT_FAILURE);
}

void *run_server(void *arg) {
    int server_fd, client_fd;
    struct sockaddr_un server_addr, client_addr;
    socklen_t addr_len = sizeof(client_addr);

    if ((server_fd = socket(AF_UNIX, SOCK_STREAM, 0)) == 0) {
        error("Socket failed");
    }

    // Set server sockaddr structure
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sun_family = AF_UNIX;
    strncpy(server_addr.sun_path, SERVER_SOCKET_PATH, sizeof(server_addr.sun_path) - 1);

    if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        error("Bind failed");
    }

    if (listen(server_fd, 3) < 0) {
        error("Listen failed");
    }

    printf("Server is listening on %s\n", SERVER_SOCKET_PATH);
    fflush(stdout);

    if ((client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &addr_len)) < 0) {
        error("Accept failed");
    }

    printf("Client connected\n");
    fflush(stdout);

    char peer_path[108];
    socklen_t peer_addr_len = sizeof(client_addr);
    if (getpeername(client_fd, (struct sockaddr *)&client_addr, &peer_addr_len) == -1) {
        error("getpeername failed");
    }

    strncpy(peer_path, client_addr.sun_path, sizeof(peer_path) - 1);
    printf("Client socket path: %s\n", peer_path);

    close(client_fd);
    close(server_fd);
    unlink(SERVER_SOCKET_PATH);
    unlink(CLIENT_SOCKET_PATH);

    return NULL;
}

void run_client() {
    int sock = 0;
    struct sockaddr_un server_addr, client_addr;

    if ((sock = socket(AF_UNIX, SOCK_STREAM, 0)) < 0) {
        error("Socket creation error");
    }

    memset(&client_addr, 0, sizeof(client_addr));
    client_addr.sun_family = AF_UNIX;
    strncpy(client_addr.sun_path, CLIENT_SOCKET_PATH, sizeof(client_addr.sun_path) - 1);

    if (bind(sock, (struct sockaddr *)&client_addr, sizeof(client_addr)) < 0) {
        error("Client bind failed");
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sun_family = AF_UNIX;
    strncpy(server_addr.sun_path, SERVER_SOCKET_PATH, sizeof(server_addr.sun_path) - 1);

    if (connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        error("Connection failed");
    }

    printf("Connected to server\n");
    fflush(stdout);

    close(sock);
}

int main() {
    pthread_t server_thread;

    if (pthread_create(&server_thread, NULL, run_server, NULL) != 0) {
        error("Failed to create server thread");
    }

    sleep(1);

    run_client();

    pthread_join(server_thread, NULL);

    return 0;
}
