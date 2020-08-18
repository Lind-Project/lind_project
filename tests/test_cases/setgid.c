#undef _GNU_SOURCE
#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main() 
{
	printf("#1 Setting gid to 1000...\n");
	printf("#1 setgid() succeeded? %d\n", setgid(1000));
	printf("#2 Setting gid to 1000...\n");
	printf("#2 setgid() succeeded? %d\n", setgid(1000));
	return 0;
}