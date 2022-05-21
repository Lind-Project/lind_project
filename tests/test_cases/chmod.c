#undef _GNU_SOURCE
#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char **argv)
{
	char mode[] = "0777";
	char buf[100] = "chmod_text.txt";
	int i;
	i = strtol(mode, 0, 8);
	char error[] = "ERROR with CHMOD\n";
	if (chmod(buf, i) < 0)
	{
		write(STDERR_FILENO, error, sizeof error - 1);
		exit(1);
	}
	return (0);
}
