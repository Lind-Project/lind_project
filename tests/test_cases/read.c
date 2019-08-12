#undef _GNU_SOURCE
#define _GNU_SOURCE

#include <ctype.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <wait.h>

int main(void)
{
	int fd;
	ssize_t ret = 0;
	char buf[4096] = {0};
	size_t count = sizeof buf;

	if ((fd = open("/dev/urandom", O_RDONLY, S_IRWXU|S_IRWXG|S_IRWXO)) < 0) {
		perror("open()");
		exit(EXIT_FAILURE);
	}

	for (size_t pos = 0; pos < count; pos += ret) {
		if ((ret = read(fd, buf + pos, count - pos)) < 0) {
			perror("read()");
			exit(EXIT_FAILURE);
		}
		printf("read() ret: [%zd], left: [%zu]\n", ret, count - pos);
	}

	for (size_t i = 0; i < count; i++) {
		int c = buf[i];
		if (isprint(c)) {
			write(STDOUT_FILENO, buf + i, 1);
		}
	}
	write(STDOUT_FILENO, "\n", 1);
	close(fd);

	return 0;
}
