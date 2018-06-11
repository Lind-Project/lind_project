#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <wait.h>

int main(void)
{
	int ret;

	/* printf("%d\n", getpid()); */
	switch (fork()) {
	case -1:
		perror("fork()");
		exit(EXIT_FAILURE);
	case 0:
		puts("child succeeded");
		fflush(0);
		exit(EXIT_SUCCESS);
	}
	wait(&ret);
	fflush(0);
	puts("parent succeeded");

	return 0;
}
