#undef _GNU_SOURCE 
#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <wait.h>

int main(void)
{
	char cmd[] = "/bin/ls";
	char * argVec[] = {NULL};
	char * envVec[] = {NULL};

	execve(cmd, argVec, envVec);
	return 0;
	
}
