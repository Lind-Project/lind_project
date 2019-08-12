#undef _GNU_SOURCE
#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <wait.h>

int main(void)
{
	char buf[4096] = {0}, *ptr;

	while ((ptr = fgets(buf, sizeof buf, stdin)) && !feof(stdin)) {
		if (!ptr && ferror(stdin)) {
			perror("fgets()");
			clearerr(stdin);
		}
		puts(buf);
	}

	return 0;
}
