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
	char *tmp_file = "/dev/shm/.lind_read";
	char str[] = "wark\n", buf[4096] = {0};

	switch (fork()) {
	case -1:
		perror("fork()");
		exit(EXIT_FAILURE);
	case 0:
		if ((fd = open(tmp_file, O_RDWR|O_CREAT|O_TRUNC, S_IRWXU|S_IRWXG|S_IRWXO) == -1)) {
			perror("open()");
			exit(EXIT_FAILURE);
		}
		write(fd, str, sizeof str);
		fsync(fd);
		close(fd);
		exit(EXIT_SUCCESS);
	}

	wait(&ret);
	if ((fd = open(tmp_file, O_RDONLY, S_IRWXU|S_IRWXG|S_IRWXO) == -1)) {
		perror("open()");
		exit(EXIT_FAILURE);
	}
	if ((ret = read(fd, buf, sizeof str)) == -1) {
		perror("read()");
		exit(EXIT_FAILURE);
	}

	fsync(fd);
	printf("read() ret: %d\n", ret);
	puts(buf);
	close(fd);
	unlink(tmp_file);

	return 0;
}
