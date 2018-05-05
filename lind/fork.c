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

	switch ((pid = fork())) {
	case -1:
		perror("fork() failed");
		fflush(0);
		exit(EXIT_FAILURE);
	case 0:
		puts("child succeeded");
		printf("%d\n", getpid());
		fflush(0);
		switch ((pid = fork())) {
		case -1:
			perror("fork() failed");
			fflush(0);
			exit(EXIT_FAILURE);
		case 0:
			puts("child succeeded");
			printf("%d\n", getpid());
			fflush(0);
			exit(EXIT_SUCCESS);
		}
		exit(EXIT_SUCCESS);
	}

	printf("%d\n", getpid());
	puts("parent waiting");
	fflush(0);
	wait(&ret);
	printf("parent %d succeeded after waiting on %d\n", getpid(), pid);
	fflush(0);

	return 0;
}
