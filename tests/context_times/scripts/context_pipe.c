#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <sys/wait.h> 

#define GB (1 << 30)

void parent(int parent_to_child[2], int child_to_parent[2], int buf_size, int N)
{
    char *send_buf = (char *)malloc(buf_size);
    char *recv_buf = (char *)malloc(buf_size);

    memset(send_buf, 'a', buf_size);

    for (int a = 0; a < N; ++a)
    {
        for (int i = 0; i < GB / buf_size; ++i)
        {
            if (write(parent_to_child[1], send_buf, buf_size) == -1)
            {
                perror("Write P");
                exit(1);
            }
        }
        for (int j = 0; j < GB / buf_size; ++j)
        {
            int total_received = 0;
            while (total_received < buf_size)
            {
                int received = read(child_to_parent[0], recv_buf + total_received, buf_size - total_received);
                if (received == -1)
                {
                    perror("Read P");
                    exit(1);
                }
                total_received += received;
            }
        }
    }
    free(send_buf);
    free(recv_buf);

}

void child(int parent_to_child[2], int child_to_parent[2], int buf_size, int N)
{
    char *send_buf = (char *)malloc(buf_size);
    char *recv_buf = (char *)malloc(buf_size);

    memset(send_buf, 'b', buf_size);
    for (int b = 0; b < N; ++b)
    {
        for (int x = 0; x < GB / buf_size; ++x)
        {
            int total_received = 0;
            while (total_received < buf_size)
            {
                int received = read(parent_to_child[0], recv_buf + total_received, buf_size - total_received);
                if (received == -1)
                {
                    perror("Read C");
                    exit(1);
                }
                total_received += received;
            }
        }
        for (int y = 0; y < GB / buf_size; ++y)
        {
            if (write(child_to_parent[1], send_buf, buf_size) == -1)
            {
                perror("Write C");
                exit(1);
            }
        }
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

    int parent_to_child[2], child_to_parent[2];

    if (pipe(parent_to_child) < 0)
    {
        perror("Failed to initialize parent to child pipe");
        exit(1);
    }

    if (pipe(child_to_parent) < 0)
    {
        perror("Failed to initialize child to parent pipe");
        exit(1);
    }

    pid_t pid;
    
    pid = fork();
    if (pid == -1)
    {
        perror("Fork");
        exit(1);
    }

    if (pid == 0)
    {
        // Child process
        close(parent_to_child[1]);
        close(child_to_parent[0]);
        child(parent_to_child, child_to_parent, buf_size, N);
        close(parent_to_child[0]);
        close(child_to_parent[1]);
        _exit(0);
    }
    else
    {
        // Parent process
        close(parent_to_child[0]);
        close(child_to_parent[1]);
        parent(parent_to_child, child_to_parent, buf_size, N);
        wait(NULL);
        close(parent_to_child[1]);
        close(child_to_parent[0]);
    }
    return 0;
}