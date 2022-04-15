#undef _GNU_SOURCE
#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <wait.h>

static volatile size_t counter = 0;
#define printf(s, ...) printf("[#%zu:L%u] " s, ++counter, __LINE__, __VA_ARGS__)

int main(void)
{
	int pret = -1, cret = -1, ppret = -1, pid = -1, cpid = -1, ppid = -1, unused = -1;

	printf("pid %d forking\n", getpid());
	fflush(NULL);

	switch ((pid = fork())) {
	case -1:
		perror("fork() failed");
		exit(EXIT_FAILURE);
	case 0:
		printf("pid %d forking\n", getpid());
		fflush(NULL);

		switch ((cpid = fork())) {
		case -1:
			perror("fork() failed");
			exit(EXIT_FAILURE);
		case 0:
			printf("pid = %d, ret = %d\n", getpid(), cpid);
			fflush(NULL);
			exit(EXIT_SUCCESS);
		}

		printf("pid = %d, ret = %d\n", getpid(), cpid);
		fflush(NULL);
		exit(EXIT_SUCCESS);
	}

	printf("pid = %d, ret = %d\n", getpid(), pid);
	fflush(NULL);
	printf("pid %d forking again\n", getpid());
	fflush(NULL);

	switch ((ppid = fork())) {
	case -1:
		perror("fork() failed");
		exit(EXIT_FAILURE);
	case 0:
		printf("pid = %d, ret = %d\n", getpid(), ppid);
		fflush(NULL);
		exit(EXIT_SUCCESS);
	}

	printf("pid = %d, ret = %d\n", getpid(), ppid);
	fflush(NULL);

	return 0;
}
