#undef _GNU_SOURCE
#define _GNU_SOURCE

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <wait.h>

#define COUNT 8

int main(void)
{
	int fd;
	ssize_t ret;
	char buf[4096] = {0};

	if ((fd = open("/dev/urandom", O_RDONLY, S_IRWXU|S_IRWXG|S_IRWXO)) < 0) {
		perror("open()");
		exit(EXIT_FAILURE);
	}

	if ((ret = read(fd, buf, COUNT)) < 0) {
		perror("read()");
		exit(EXIT_FAILURE);
	}

	printf("read() ret: [%zd], expected: [%d]\n", ret, COUNT);
	write(STDOUT_FILENO, buf, COUNT);
	close(fd);

	return 0;
}
