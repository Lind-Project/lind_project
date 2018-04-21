#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>

int main(void)
{
	int ret;

	switch (fork()) {
	case -1:
		perror("fork()");
		exit(EXIT_FAILURE);
	case 0:
		puts("child succeeded");
		exit(EXIT_SUCCESS);
	}
	wait(&ret);
	puts("parent succeeded");

	return 0;
}
