#undef _GNU_SOURCE
#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main(void)
{
	printf("#1 Printing uid: %d\n", getuid());
	printf("#2 Printing uid: %d\n", getuid());

	printf("#1 Printing euid: %d\n", geteuid());
	printf("#2 Printing euid: %d\n", geteuid());

	return 0;
}