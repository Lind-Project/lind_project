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
	char file_name[100] = "testfile.txt";
	if (chmod(file_name, S_IRWXU | S_IRWXG | S_IRWXO) !=  0)
	{
		perror("ERROR with CHMOD");
		exit(1);
	}
	return (0);
}

