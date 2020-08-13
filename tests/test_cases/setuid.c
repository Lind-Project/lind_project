#undef _GNU_SOURCE
#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main() 
{
	printf("Setting uid to 1000...\n");
	printf("setuid() succeeded? %d\n", setuid(1000));
	return 0;
}