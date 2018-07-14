#undef _GNU_SOURCE
#define _GNU_SOURCE

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <wait.h>

int main(void)
{
	char str[4096] = {0};
	int ret, fd[2];

	pipe(fd);
	printf("pipe() ret: [%d, %d]\n", fd[0], fd[1]);
	write(fd[1], "hi\n", 3);
	if ((ret = read(fd[0], str, sizeof str)) == -1) {
		perror("read()");
		return 1;
	}
	printf("read() ret: %d\n", ret);
	puts(str);

	return 0;
}
