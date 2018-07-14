#undef _GNU_SOURCE
#define _GNU_SOURCE

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
	char str[] = "wark\n", buf[4096] = {0};

	if ((fd = open("/tmp/", O_RDWR|O_TMPFILE|O_TRUNC, S_IRWXU|S_IRWXG|S_IRWXO) == -1))
		perror("open()");

	switch (fork()) {
	case -1:
		perror("fork()");
		exit(EXIT_FAILURE);
	case 0:
		write(fd, str, sizeof str);
		fsync(fd);
		close(fd);
		exit(EXIT_SUCCESS);
	}

	if ((ret = read(fd, buf, sizeof str)) == -1) {
		perror("read()");
		exit(EXIT_FAILURE);
	}

	fsync(fd);
	printf("read() ret: %d\n", ret);
	puts(buf);
	close(fd);

	return 0;
}
