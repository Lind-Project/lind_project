#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/wait.h>

#define PORT 8080
#define BACKLOG 5
#define ACK_MSG "Acknowledged\n"
#define N_LISTENERS 24
#define CONNECTIONS_PER_LISTENER 10000
#define INITIAL_CONNECTIONS 50

int main()
{
    int listen_fd, client_fd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_addr_size;
    fd_set read_fds;
    int max_fd, ret, pre_established_fds[INITIAL_CONNECTIONS];

    // Create listening socket
    if ((listen_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    if (setsockopt(listen_fd, SOL_SOCKET, SO_REUSEADDR, &(int){1}, sizeof(int)) < 0)
    {
        perror("setsockopt(SO_REUSEADDR) failed");
        exit(EXIT_FAILURE);
    }

    // Initialize the server address and bind
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(PORT);

    if (bind(listen_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections
    if (listen(listen_fd, BACKLOG) < 0)
    {
        perror("listen failed");
        exit(EXIT_FAILURE);
    }

    // Accept 50 connections, just for polluting the select
    // those 50 connections will not be really touched by this test
    for (int i = 0; i < INITIAL_CONNECTIONS; i++)
    {
        client_addr_size = sizeof(client_addr);
        client_fd = accept(listen_fd, (struct sockaddr *)&client_addr, &client_addr_size);
        if (client_fd < 0)
        {
            perror("accept failed");
            exit(EXIT_FAILURE);
        }
        pre_established_fds[i] = client_fd;
    }

    // Create a master fd_set, which doesn't change throughout the iterations
    fd_set master_fd_set;
    FD_ZERO(&master_fd_set);
    FD_SET(listen_fd, &master_fd_set);
    max_fd = listen_fd;
    // add pre-established connections to master_fd_set
    for (int k = 0; k < INITIAL_CONNECTIONS; k++)
    {
        FD_SET(pre_established_fds[k], &master_fd_set);
        if (pre_established_fds[k] > max_fd)
        {
            max_fd = pre_established_fds[k];
        }
    }

    // Fork N_LISTENERS child processes
    for (int i = 0; i < N_LISTENERS; i++)
    {
        if (fork() == 0)
        {
            // Child process
            printf("Child started\n");

            for (int j = 0; j < CONNECTIONS_PER_LISTENER; j++)
            {
                // Create a working set from the master set
                fd_set working_fd_set;
                memcpy(&working_fd_set, &master_fd_set, sizeof(fd_set));

                ret = select(max_fd + 1, &working_fd_set, NULL, NULL, NULL);

                if (ret < 0)
                {
                    perror("select error");
                    continue;
                }

                if (ret > 0)
                {
                    client_addr_size = sizeof(client_addr);
                    client_fd = accept(listen_fd, (struct sockaddr *)&client_addr, &client_addr_size);
                    if (client_fd < 0)
                    {
                        perror("accept failed");
                        continue;
                    }

                    write(client_fd, ACK_MSG, strlen(ACK_MSG));
                    close(client_fd);
                }
            }

            printf("Child %d finished\n", i);
            exit(0);
        }
    }

    // Parent process: wait chidren to finish
    for (int i = 0; i < N_LISTENERS; i++)
    {
        wait(NULL);
    }

    close(listen_fd);

    return 0;
}