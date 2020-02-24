#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
int main()
{

    char buf = 0;

    int fd = open("test.txt", O_RDWR | O_CREAT, 0777);
    char writebuf[] = "This is a test of the wonderful fork call in lind.";
    write(fd, writebuf, sizeof(writebuf));
    close(fd);



    fd = open("test.txt", O_RDWR);
    while (read(fd, &buf, 1) > 0)
        write(STDOUT_FILENO, &buf, 1);

    close(fd);

    return 0;
}

