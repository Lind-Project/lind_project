#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <string.h>
#include <sys/un.h>

void main()
{
    int addrlen;
    int rc;
    int server_sock;
    struct sockaddr_un server_addr;

    int server_fd = socket(AF_UNIX, SOCK_STREAM, 0);

    addrlen = sizeof(server_addr);
    rc = getsockname(server_fd, (struct sockaddr *)&server_addr, &addrlen);

    if (rc == -1)
    {
        perror("GETSOCKNAME ERROR: ");
    }

    printf("sun_path = %s\n", server_addr.sun_path);
}
