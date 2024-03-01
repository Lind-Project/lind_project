#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 8080
#define BACKLOG 5
#define ACK_MSG "Acknowledged\n"
#define N_LISTENERS 24
#define CONNECTIONS_PER_LISTENER 100000
// In total, the client should issue N_LISTENERS * CONNECTIONS_PER_LISTENER connection requests

int main()
{
    int listen_fd, client_fd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_addr_size;
    fd_set read_fds;
    int max_fd, ret;

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

    // Fork N_LISTENERS child processes
    for (int i = 0; i < N_LISTENERS; i++)
    {
        if (fork() == 0)
        {
            // Child process: a select + accept worker
            // each child terminates after CONNECTIONS_PER_LISTENER rounds
            printf("Child started\n");

            for (int j = 0; j < CONNECTIONS_PER_LISTENER; j++)
            {
                FD_ZERO(&read_fds);
                FD_SET(listen_fd, &read_fds);
                max_fd = listen_fd;

                ret = select(max_fd + 1, &read_fds, NULL, NULL, NULL);

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