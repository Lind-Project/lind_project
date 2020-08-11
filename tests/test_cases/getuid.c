#undef _GNU_SOURCE
#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main() 
{
	puts("Printing uid: ");
	printf("%d\n", getuid());
	perror("");
	puts("getuid() succeeded.");

    puts("Printing effective uid: ");
    printf("%d\n", geteuid());
	perror("");
	puts("geteuid() succeeded.");

	return 0;
}