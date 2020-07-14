#undef _GNU_SOURCE
#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
	puts("Exiting...\n");
	exit(0);
	perror("");
	puts("exit() succeeded.");
	return 0;
}