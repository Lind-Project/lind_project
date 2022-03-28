#undef _GNU_SOURCE
#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <wait.h>

int main(void)
{
	puts("printing getgid:");
	printf("%d\n", getgid());
	puts("printing getuid:");
	printf("%d\n", getuid());
	puts("printing getegid:");
	printf("%d\n", getegid());
	puts("printing geteuid:");
	printf("%d\n", geteuid());

	return 0;
}