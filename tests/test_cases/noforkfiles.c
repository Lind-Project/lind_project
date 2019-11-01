#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
int main()
{

    int fd = open("test.txt", O_RDWR);

    unlink("test.txt");
    close(fd);

    return 0;

}

