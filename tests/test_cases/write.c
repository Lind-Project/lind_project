#undef _GNU_SOURCE
#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <wait.h>

int main(void)
{
	char str[] = "write succeeded\n";

	printf("attempting to write to STDOUT_FILENO");
	write(STDOUT_FILENO, str, sizeof str - 1);

	return 0;
}
