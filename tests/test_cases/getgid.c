#undef _GNU_SOURCE
#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main(void)
{
	printf("#1 Printing gid: %d\n", getgid());
	printf("#2 Printing gid: %d\n", getgid());

	printf("#1 Printing egid: %d\n", getegid());
	printf("#2 Printing egid: %d\n", getegid());
	printf("#3 Printing egid: %d\n", getegid());

	return 0;
}