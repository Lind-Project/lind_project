#undef _GNU_SOURCE
#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
	long ret;

	puts("calling sysconf(sysconf())");
	ret = sysconf(_SC_PAGESIZE);
	if (ret < 0) {
		perror("sysconf() failed");
		exit(EXIT_FAILURE);
	}
	printf("page size: %ld\n", ret);

	return 0;
}
