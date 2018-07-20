#undef _GNU_SOURCE
#define _GNU_SOURCE

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <wait.h>

int main(void)
{
	char str[4096] = {0};
	int ret, fd[2];

	pipe(fd);
	printf("pipe() ret: [%d, %d]\n", fd[0], fd[1]);

	if ((ret = write(fd[1], "hi\n", 3)) < 0) {
		printf("write(): %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	printf("write() ret: %d\n", ret);

	if ((ret = read(fd[0], str, 3)) < 0) {
		printf("read(): %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	printf("read() ret: %d\n", ret);

	close(fd[0]);
	close(fd[1]);
	puts(str);

	return 0;
}
