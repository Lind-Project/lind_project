#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>

int main(void)
{
	int ret;

	puts("forking");
	fflush(0);

	switch (fork()) {
	case -1:
		puts("fork() failed");
		perror("fork()");
		exit(EXIT_FAILURE);
	case 0:
		puts("child succeeded");
		fflush(0);
		exit(EXIT_SUCCESS);
	}

	puts("parent waiting");
	fflush(0);
	wait(&ret);
	puts("parent succeeded");
	fflush(0);

	return 0;
}
