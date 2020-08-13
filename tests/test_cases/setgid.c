#undef _GNU_SOURCE
#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main() 
{
	printf("Setting gid to 1000...\n");
	printf("setgid() succeeded? %d\n", setgid(1000));
	return 0;
}