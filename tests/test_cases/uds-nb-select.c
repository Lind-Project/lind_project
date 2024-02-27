#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <string.h>
#include <sys/un.h>
#include <pthread.h>
#include <fcntl.h>
#include <sys/select.h>
#include <errno.h>

pthread_barrier_t barrier;
#define SERVER_PATH "unix_sock.server"
#define CLIENT_PATH "unix_sock.client"

void *client(void *v)
{

    int client_sock = 0, valread;
    struct sockaddr_un server_sockaddr, client_sockaddr;
    char *hello = "Hello from client";
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

    int flags = fcntl(client_sock, F_GETFL, 0);
    if (flags < 0)
    {
        perror("fcntl(F_GETFL)");
        return NULL;
    }
    if (fcntl(client_sock, F_SETFL, flags | O_NONBLOCK) < 0)
    {
        perror("fcntl(F_SETFL)");
        return NULL;
    }
    flags = fcntl(client_sock, F_GETFL, 0);

    server_sockaddr.sun_family = AF_UNIX;
    strcpy(server_sockaddr.sun_path, SERVER_PATH);
    pthread_barrier_wait(&barrier);
    int connret = connect(client_sock, (struct sockaddr *)&server_sockaddr, sizeof(server_sockaddr));
    int isTCPConnectInProgress = ((connret == -1) && (errno == EINPROGRESS));
    if ((connret == 0) || (isTCPConnectInProgress))
    {
        if (isTCPConnectInProgress == 0)
        {
            send(client_sock, hello, strlen(hello), 0);
            printf("Client: Hello message sent\n");
            fflush(stdout);
        }
        // TCP connection is happening in the background; our event-loop calls select() to block until it is ready
        while (1)
        {
            fd_set socketsToWatchForReadReady, socketsToWatchForWriteReady;
            FD_ZERO(&socketsToWatchForReadReady);
            FD_ZERO(&socketsToWatchForWriteReady);
            // While connecting, we'll watch the socket for ready-for-write as that will tell us when the
            // TCP connection process has completed.  After it's connected, we'll watch it for ready-for-read
            // to see what Google's web server has to say to us.
            if (isTCPConnectInProgress)
                FD_SET(client_sock, &socketsToWatchForWriteReady);
            else
                FD_SET(client_sock, &socketsToWatchForReadReady);

            int maxFD = client_sock; // if we were watching multiple sockets, we'd compute this to be the max value of all of them
            const int selectResult = select(maxFD + 1, &socketsToWatchForReadReady, &socketsToWatchForWriteReady, NULL, NULL);
            if (selectResult >= 0)
            {
                if ((FD_ISSET(client_sock, &socketsToWatchForWriteReady)) && (isTCPConnectInProgress))
                {
                    printf("Socket is ready for write!  Let's find out if the connection succeeded or not...\n");
                    struct sockaddr_un junk;
                    socklen_t length = sizeof(junk);
                    memset(&junk, 0, sizeof(junk));
                    if (getpeername(client_sock, (struct sockaddr *)&junk, &length) == 0)
                    {
                        printf("TCP Connection succeeded, socket is ready for use!\n");
                        fflush(stdout);

                        isTCPConnectInProgress = 0;

                        send(client_sock, hello, strlen(hello), 0);
                        printf("Client: Hello message sent\n");
                        fflush(stdout);
                    }
                    else
                    {
                        printf("TCP Connection failed!\n");
                        fflush(stdout);
                        break;
                    }
                }

                if (FD_ISSET(client_sock, &socketsToWatchForReadReady))
                {
                    char buf[512];
                    const int numBytesReceived = recv(client_sock, buf, sizeof(buf) - 1, 0);
                    if (numBytesReceived > 0)
                    {
                        buf[numBytesReceived] = '\0'; // ensure NUL-termination before we call printf()
                        printf("Client: recv() returned %i:  [%s]\n", numBytesReceived, buf);
                        fflush(stdout);
                    }
                    else if (numBytesReceived == 0)
                    {
                        printf("TCP Connection severed!\n");
                        fflush(stdout);

                        break;
                    }
                    else
                        perror("recv()");
                }
            }
            else
            {
                perror("select()");
                return NULL;
            }
        }
    }
    else
        perror("connect()");
    close(client_sock);
    return NULL;
}

void *server(void *v)
{
    int server_fd, new_socket, valread, len;
    struct sockaddr_un server_sockaddr, client_sockaddr;
    long opt = 1;
    int addrlen = sizeof(server_sockaddr);
    char buffer[1024] = {0};
    char *hello = "Hello from server";
    memset(&server_sockaddr, 0, sizeof(struct sockaddr_un));
    memset(&client_sockaddr, 0, sizeof(struct sockaddr_un));

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

    sleep(2);

    if ((new_socket = accept(server_fd, (struct sockaddr *)&client_sockaddr,
                             (socklen_t *)&addrlen)) < 0)
    {
        perror("accept");
        exit(EXIT_FAILURE);
    }
    valread = recv(new_socket, buffer, 1024, 0);
    printf("%s\n", buffer);
    send(new_socket, hello, strlen(hello), 0);
    printf("Server: Hello message sent\n");
    close(new_socket);
    return NULL;
}

int main()
{
    pthread_t serverthread, clientthread;
    pthread_barrier_init(&barrier, NULL, 2);
    pthread_create(&serverthread, NULL, server, NULL);
    pthread_create(&clientthread, NULL, client, NULL);
    pthread_join(clientthread, NULL);
    pthread_join(serverthread, NULL);
    return 0;
}