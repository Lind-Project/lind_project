#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>

#define GB (1 << 30)

void parent(int socket, int buf_size) {
    char* send_buf = (char*) malloc(buf_size);
    char* recv_buf = (char*) malloc(buf_size);

    memset(send_buf, 'a', buf_size);

    for (int i = 0; i < GB/buf_size; ++i) {
        if (send(socket, send_buf, buf_size, 0) == -1) {
            perror("Send");
            exit(1);
        }
        if (recv(socket, recv_buf, buf_size, 0) == -1) {
            perror("Recv");
            exit(1);
        }
    }

    free(send_buf);
    free(recv_buf);
}

void child(int socket, int buf_size) {
    char* send_buf = (char*) malloc(buf_size);
    char* recv_buf = (char*) malloc(buf_size);

    memset(send_buf, 'b', buf_size);

    for(int i = 0; i < GB/buf_size; ++i) {
        if (recv(socket, recv_buf, buf_size, 0) == -1) {
            perror("Recv");
            exit(1);
        }
        if (send(socket, send_buf, buf_size, 0) == -1) {
            perror("Send");
            exit(1);
        }
    }

    free(send_buf);
    free(recv_buf);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: [executable] [send_recv_buf_size]\n");
        exit(1);
    }

    int buf_size = 1 << atoi(argv[1]);

    int sockets[2];
    pid_t pid;

    if (socketpair(AF_UNIX, SOCK_STREAM, 0, sockets) == -1) {
        perror("Socketpair");
        exit(1);
    }

    pid = fork();
    if (pid == -1) {
        perror("Fork");
        exit(1);
    }

    if (pid == 0) {
        // Child process
        close(sockets[1]);
        child(sockets[0], buf_size);
    } else {
        // Parent process
        close(sockets[0]);
        parent(sockets[1], buf_size);
    }
    return 0;
}
