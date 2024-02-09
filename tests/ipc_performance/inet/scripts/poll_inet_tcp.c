#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <poll.h>

#define MSG "ping"
#define ACK "pong"
#define ROUNDS 1e5

int main()
{
    int listen_fd, conn_fd, parent_conn_fd, addr_len;
    struct sockaddr_in serv_addr, cli_addr;
    char buffer[100];
    for (int i = 0; i < 100; i++)
    {
        *(buffer + i) = 0;
    }
    struct pollfd pfd;
    int ret;

    // Create listening socket
    if ((listen_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("creating listening socket failed");
        exit(1);
    }

    int reuse = 1;
    if (setsockopt(listen_fd, SOL_SOCKET, SO_REUSEADDR, (const char *)&reuse, sizeof(reuse)) < 0)
    {
        perror("setsockopt(SO_REUSEADDR) failed");
        exit(1);
    }

    // Prepare the sockaddr_in structure
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serv_addr.sin_port = htons(8080);

    // bind
    if (bind(listen_fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        perror("bind failed");
        exit(1);
    }

    // Listen
    if (listen(listen_fd, 1) < 0)
    {
        perror("listen failed");
        exit(1);
    }

    pid_t pid = fork();
    if (pid == -1)
    {
        perror("fork failed");
        exit(1);
    }
    else if (pid == 0)
    {
        // child: pinger process
        // make a connected socket to parent
        if ((conn_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        {
            perror("creating connecting socket failed");
            exit(1);
        }
        if (connect(conn_fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
        {
            perror("connect failed");
            exit(1);
        }

        // setup pollfd
        pfd.fd = conn_fd;
        pfd.events = POLLIN;
        int i;
        for (i = 0; i < ROUNDS; i++)
        {
            write(conn_fd, MSG, strlen(MSG));
            ret = poll(&pfd, 1, -1);
            if (ret > 0)
            {
                read(conn_fd, buffer, sizeof(buffer));
                // printf("Pinger received: %s\n", buffer);
                // fflush(stdout);
            }
            else
            {
                perror("poll");
            }
        }
        close(conn_fd);
    }
    else
    {
        // parent: ponger process
        // accept the connection from ponger
        addr_len = sizeof(cli_addr);
        parent_conn_fd = accept(listen_fd, (struct sockaddr *)&cli_addr, (socklen_t *)&addr_len);
        if (parent_conn_fd < 0)
        {
            perror("accept failed");
            exit(1);
        }

        // setup pollfd
        pfd.fd = parent_conn_fd;
        pfd.events = POLLIN;

        // use poll for waiting the message from pinger
        int i;
        for (i = 0; i < ROUNDS; i++)
        {
            ret = poll(&pfd, 1, -1);
            if (ret > 0)
            {
                if (pfd.revents & POLLIN)
                {
                    read(parent_conn_fd, buffer, sizeof(buffer));
                    // printf("Ponger received: %s\n", buffer);
                    // fflush(stdout);
                    write(parent_conn_fd, ACK, strlen(ACK)); // reply to pinger
                }
            }
            else
            {
                perror("poll");
            }
        }
        close(parent_conn_fd);
    }

    close(listen_fd);
    return 0;
}
