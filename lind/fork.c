#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>

int main(void)
{
	int ret;

	/* puts("forking"); */
	switch (fork()) {
	case -1:
		puts("fork() failed");
		perror("fork()");
		exit(EXIT_FAILURE);
	case 0:
		puts("child succeeded");
		exit(EXIT_SUCCESS);
	}
	puts("parent waiting");
	wait(&ret);
	puts("parent succeeded");

	return 0;
}
