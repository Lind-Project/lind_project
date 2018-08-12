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

int main(void)
{
	size_t total = 0;
	char buf[4096] = {0};

	for (;;) {
		ssize_t ret;
		if ((ret = read(STDIN_FILENO, buf + total, sizeof buf - total - 1)) < 0) {
			if (errno != EINTR && errno != EAGAIN) {
				perror("read()");
				exit(EXIT_FAILURE);
			}
		}
		printf("read() return: [%zd]\n", ret);
		if (!ret || total + ret >= (ssize_t)sizeof buf)
			break;
		total += ret;
	}
	putchar('\n');
	printf("input read read(): [%s]\n", buf);
	printf("total bytes read(): [%zu]\n", total);

	return 0;
}
