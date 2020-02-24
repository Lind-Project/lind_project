#undef _GNU_SOURCE
#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <wait.h>
#include <string.h>

int main(void)
{
	char str[] = "write succeeded\n";
	
	for (int i = 0; i < strlen(str); i++)
	{
		write(STDOUT_FILENO, str + i, 1);
	}
	return 0;
}
