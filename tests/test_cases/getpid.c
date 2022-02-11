#undef _GNU_SOURCE
#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <wait.h>

int main(void)
{
	puts("printing pid");

	printf("%d\n", getpid());
	perror("");
	puts("getpid() succeeded");

	return 0;
}
