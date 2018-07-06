#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <wait.h>

int main(void)
{
	int pret = ~0, cret = ~1, ppret = ~2;
	int pid = -1, cpid = -1, ppid = -1, unused = -1;

	(void)pret, (void)cret, (void)ppret;
	(void)pid, (void)cpid, (void)ppid, (void)unused;

	printf("pid %d forking\n", getpid());
	fflush(0);

	switch ((pid = fork())) {
	case -1:
		perror("fork() failed");
		fflush(0);
		exit(EXIT_FAILURE);

	case 0:
		printf("pid %d forking\n", getpid());
		fflush(0);
		switch ((cpid = fork())) {
		case -1:
			perror("fork() failed");
			fflush(0);
			exit(EXIT_FAILURE);
		case 0:
			printf("pid = %d fork ret = %d\n", getpid(), cpid);
			fflush(0);
			exit(EXIT_SUCCESS);
		}
		printf("pid = %d fork ret = %d\n", getpid(), cpid);
		fflush(0);
		exit(EXIT_SUCCESS);
	}

	printf("pid = %d fork ret = %d\n", getpid(), pid);
	fflush(0);

	printf("pid %d forking\n", getpid());
	fflush(0);

	switch ((ppid = fork())) {
	case -1:
		perror("fork() failed");
		fflush(0);
		exit(EXIT_FAILURE);
	case 0:
		printf("pid = %d fork ret = %d\n", getpid(), ppid);
		fflush(0);
		exit(EXIT_SUCCESS);
	}

	printf("pid = %d fork ret = %d\n", getpid(), ppid);
	fflush(0);

	return 0;
}
