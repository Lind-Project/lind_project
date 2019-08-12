#undef _GNU_SOURCE
#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
	int fd = -2;
	char dupstr[] = "write to dup() fd succeeded\n";
	char oldstr[] = "write to old fd succeeded\n";

	fd = dup(STDOUT_FILENO);
	printf("\nduped fd: %d\n", fd);
	if (fd < 0) {
		perror("dup() failed");
		abort();
	}
	puts("attempting to write to dup() fd\n");
	fflush(0);
	write(fd, dupstr, sizeof dupstr - 1);
	fflush(0);
	write(STDOUT_FILENO, oldstr, sizeof oldstr - 1);
	fflush(0);


	return 0;
}
