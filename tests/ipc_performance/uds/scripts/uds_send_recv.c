#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>

#define GB (1 << 30)

void parent(int socket, int buf_size, int N)
{
    char *send_buf = (char *)malloc(buf_size);
    char *recv_buf = (char *)malloc(buf_size);

    memset(send_buf, 'a', buf_size);
    for (int a = 0; a < N; ++a)
    {
        // printf("iter,a : %d\n", a);
        for (int i = 0; i < GB / buf_size; ++i)
        {
            // printf("parent send\n");
            if (send(socket, send_buf, buf_size, 0) == -1)
            {
                perror("Send");
                exit(1);
            }
        }
        // printf("Done sending in parent\n");
        for (int j = 0; j < GB / buf_size; ++j)
        {
            // printf("parent recv\n");
            int total_received = 0;
            while (total_received < buf_size)
            {
                int received = recv(socket, recv_buf + total_received, buf_size - total_received, 0);
                if (received == -1)
                {
                    perror("Recv");
                    exit(1);
                }
                total_received += received;
            }
        }
        // printf("Done receiving in parent\n");
    }
    free(send_buf);
    free(recv_buf);
}

void child(int socket, int buf_size, int N)
{
    char *send_buf = (char *)malloc(buf_size);
    char *recv_buf = (char *)malloc(buf_size);

    memset(send_buf, 'b', buf_size);
    for (int b = 0; b < N; ++b)
    {
        // printf("iter,b : %d\n", b);
        for (int x = 0; x < GB / buf_size; ++x)
        {
            // printf("child recv\n");
            int total_received = 0;
            while (total_received < buf_size)
            {
                int received = recv(socket, recv_buf + total_received, buf_size - total_received, 0);
                if (received == -1)
                {
                    perror("Recv");
                    exit(1);
                }
                total_received += received;
            }
        }
        // printf("Done receiving in child\n");
        for (int y = 0; y < GB / buf_size; ++y)
        {
            // printf("child send\n");
            if (send(socket, send_buf, buf_size, 0) == -1)
            {
                perror("Send");
                exit(1);
            }
        }
        // printf("Done sending in child\n");
    }
    free(send_buf);
    free(recv_buf);
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        fprintf(stderr, "Usage: [executable] [send_recv_buf_size] [total_size_in_GBs]\n");
        exit(1);
    }

    int buf_size = 1 << atoi(argv[1]);
    int N = atoi(argv[2]);

    int sockets[2];
    pid_t pid;

    if (socketpair(AF_UNIX, SOCK_STREAM, 0, sockets) == -1)
    {
        perror("Socketpair");
        exit(1);
    }

    pid = fork();
    if (pid == -1)
    {
        perror("Fork");
        exit(1);
    }

    if (pid == 0)
    {
        // Child process
        close(sockets[1]);
        child(sockets[0], buf_size, N);
        close(sockets[0]);
    }
    else
    {
        // Parent process
        close(sockets[0]);
        parent(sockets[1], buf_size, N);
        close(sockets[1]);
    }
    return 0;
}