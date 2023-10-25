#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <string.h>
#include <sys/un.h>
#include <pthread.h>
pthread_barrier_t barrier, barrier2;
#define SERVER_PATH "unix_sock.server"
#define CLIENT_PATH "us1.client"
#define CLIENT_PATH2 "us2.client"

void *client(void *v)
{
    int client_sock = 0, valread;
    struct sockaddr_un server_sockaddr, client_sockaddr;
    char *hello = "Hello from client1";
    char buffer[1024] = {0};
    long opt = 1;
    memset(&server_sockaddr, 0, sizeof(struct sockaddr_un));
    memset(&client_sockaddr, 0, sizeof(struct sockaddr_un));

    client_sock = socket(AF_UNIX, SOCK_STREAM, 0);

    client_sockaddr.sun_family = AF_UNIX;
    strcpy(client_sockaddr.sun_path, CLIENT_PATH);
    unlink(CLIENT_PATH);
    if (bind(client_sock, (struct sockaddr *)&client_sockaddr, sizeof(client_sockaddr)) < 0)
    {
        perror("BIND ERROR: ");
        close(client_sock);
        exit(1);
    }

    server_sockaddr.sun_family = AF_UNIX;
    strcpy(server_sockaddr.sun_path, SERVER_PATH);
    pthread_barrier_wait(&barrier);
    int connret = connect(client_sock, (struct sockaddr *)&server_sockaddr, sizeof(server_sockaddr));
    int ret = send(client_sock, hello, strlen(hello), 0);
    printf("Client 1 -- Hello message 1 sent ret: %d\n", ret);
    fflush(stdout);
    valread = recv(client_sock, buffer, 1024, 0);
    printf("client 1 -- %s\n", buffer);
    fflush(stdout);
    return NULL;
}

void *client2(void *v)
{
    int client_sock = 0, valread;
    struct sockaddr_un server_sockaddr, client_sockaddr2;
    char *hello = "Hello from client2";
    char buffer[1024] = {0};
    long opt = 1;
    memset(&server_sockaddr, 0, sizeof(struct sockaddr_un));
    memset(&client_sockaddr2, 0, sizeof(struct sockaddr_un));

    client_sock = socket(AF_UNIX, SOCK_STREAM, 0);

    client_sockaddr2.sun_family = AF_UNIX;
    strcpy(client_sockaddr2.sun_path, CLIENT_PATH2);
    unlink(CLIENT_PATH2);
    if (bind(client_sock, (struct sockaddr *)&client_sockaddr2, sizeof(client_sockaddr2)) < 0)
    {
        perror("BIND ERROR: ");
        close(client_sock);
        exit(1);
    }

    server_sockaddr.sun_family = AF_UNIX;
    strcpy(server_sockaddr.sun_path, SERVER_PATH);

    pthread_barrier_wait(&barrier2);
    int connret = connect(client_sock, (struct sockaddr *)&server_sockaddr, sizeof(server_sockaddr));
    int ret = send(client_sock, hello, strlen(hello), 0);
    printf("client 2 -- Hello message 2 sent ret: %d\n", ret);
    if (ret < 0)
    {
        perror("SEND CLIENT: ");
        fflush(stdout);
    }

    // fflush(stdout);
    valread = recv(client_sock, buffer, 1024, 0);

    printf("client 2 -- %s\n", buffer);
    fflush(stdout);
    if (valread < 0)
    {
        printf("valread err\n");
        fflush(stdout);
    }

    return NULL;
}

void *server(void *v)
{
    int server_fd, new_socket1, new_socket2, valread, len;
    struct sockaddr_un server_sockaddr, client_sockaddr, client_sockaddr2;
    long opt = 1;
    int addrlen = sizeof(server_sockaddr);
    char buffer[1024] = {0};
    char *hello = "Hello from server";
    memset(&server_sockaddr, 0, sizeof(struct sockaddr_un));
    memset(&client_sockaddr, 0, sizeof(struct sockaddr_un));
    memset(&client_sockaddr2, 0, sizeof(struct sockaddr_un));

    // Creating socket file descriptor
    if ((server_fd = socket(AF_UNIX, SOCK_STREAM, 0)) == -1)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    server_sockaddr.sun_family = AF_UNIX;
    strcpy(server_sockaddr.sun_path, SERVER_PATH);
    len = sizeof(server_sockaddr);

    unlink(SERVER_PATH);
    if (bind(server_fd, (struct sockaddr *)&server_sockaddr, len) < 0)
    {
        perror("bind: ");
        close(server_fd);
        exit(1);
    }

    if (listen(server_fd, 3) < 0)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    pthread_barrier_wait(&barrier);
    if ((new_socket1 = accept(server_fd, (struct sockaddr *)&client_sockaddr,
                              (socklen_t *)&addrlen)) < 0)
    {
        perror("accept");
        exit(EXIT_FAILURE);
    }

    sleep(0.1);
    valread = recv(new_socket1, buffer, 1024, 0);
    printf("server -- %s\n", buffer);
    send(new_socket1, hello, strlen(hello), 0);
    printf("server -- Hello message 1 sent\n");
    fflush(stdout);
    pthread_barrier_wait(&barrier2);

    if ((new_socket2 = accept(server_fd, (struct sockaddr *)&client_sockaddr2,
                              (socklen_t *)&addrlen)) < 0)
    {
        perror("accept");
        exit(EXIT_FAILURE);
    }

    valread = recv(new_socket2, buffer, 1024, 0);
    printf("server -- %s\n", buffer);
    fflush(stdout);
    send(new_socket2, hello, strlen(hello), 0);
    printf("server -- Hello message 2 sent\n");
    fflush(stdout);
    close(new_socket1);
    close(new_socket2);
    return NULL;
}

int main()
{
    pthread_t serverthread, clientthread1, clientthread2;
    pthread_barrier_init(&barrier, NULL, 2);
    pthread_barrier_init(&barrier2, NULL, 2);

    pthread_create(&serverthread, NULL, server, NULL);
    pthread_create(&clientthread1, NULL, client, NULL);
    pthread_create(&clientthread2, NULL, client2, NULL);
    pthread_join(clientthread1, NULL);
    pthread_join(clientthread2, NULL);
    pthread_join(serverthread, NULL);
    return 0;
}