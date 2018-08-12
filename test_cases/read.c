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
	int ret, fd;
	char *tmp_file = "./.lind_read";
	size_t total = 0;
	char str[] = "wark\n", buf[4096] = {0};

	if ((fd = open(tmp_file, O_RDWR|O_CREAT|O_TRUNC, S_IRWXU|S_IRWXG|S_IRWXO) < 0)) {
		perror("open()");
		exit(EXIT_FAILURE);
	}
	for (;;) {
		ssize_t pos;
		if ((pos = write(fd, str + total, sizeof str - total - 1)) < 0) {
			if (errno != EINTR && errno != EAGAIN)
				continue;
			perror("read()");
			exit(EXIT_FAILURE);
		}
		if (!pos)
			break;
		total += pos;
	}
	fsync(fd);
	close(fd);

	total = 0;
	wait(&ret);
	if ((fd = open(tmp_file, O_RDONLY, S_IRWXU|S_IRWXG|S_IRWXO) < 0)) {
		perror("open()");
		exit(EXIT_FAILURE);
	}
	for (;;) {
		ssize_t pos;
		if ((pos = read(fd, buf + total, sizeof str - total - 1)) < 0) {
			if (errno != EINTR && errno != EAGAIN)
				continue;
			perror("read()");
			exit(EXIT_FAILURE);
		}
		if (!pos || pos + total >= sizeof buf)
			break;
		total += pos;
	}

	fsync(fd);
	puts(buf);
	close(fd);
	unlink(tmp_file);

	return 0;
}
