#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>

int main(void)
{
	int pid, ret;

	printf("%d\n", getpid());
	puts("forking 1");
	puts("forking 2");
	puts("forking 3");
	puts("forking 4");
	puts("forking 5");
	puts("forking 6");
	puts("forking 7");
	puts("forking 8");
	puts("forking 9");
	puts("forking 10");
	fflush(0);

	fork();
	puts("fork() succeeed");
	fflush(0);

	_exit(EXIT_SUCCESS);
	return 0;
}
