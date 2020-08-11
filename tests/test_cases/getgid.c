#undef _GNU_SOURCE
#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main(void)
{
	puts("Printing gid: ");
	printf("%d\n", getgid());
	perror("");
	puts("getgid() succeeded.");

    puts("Printing effective gid: ");
    printf("%d\n", getegid());
	perror("");
	puts("getegid() succeeded.");

	return 0;
}