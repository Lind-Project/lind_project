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

	printf("[1] pid %d forking\n", getpid());
	fflush(0);

	switch ((pid = fork())) {
	case 0:
		printf("[2] pid %d forking\n", getpid());
		fflush(0);

		switch ((cpid = fork())) {
		case 0:
			printf("[3] pid = %d fork ret = %d\n", getpid(), cpid);
			fflush(0);
			/* exit(EXIT_SUCCESS); */
		}
		printf("[4] pid = %d fork ret = %d\n", getpid(), cpid);
		fflush(0);
		exit(EXIT_SUCCESS);

		puts("wtf");
		fflush(0);
		abort();
	}

	printf("[5]pid %d forking again\n", getpid());
	fflush(0);

	switch ((ppid = fork())) {
	case 0:
		printf("[6] pid = %d fork ret = %d\n", getpid(), ppid);
		fflush(0);
		exit(EXIT_SUCCESS);
	}

	printf("[7] pid = %d fork ret = %d\n", getpid(), ppid);
	fflush(0);

	return 0;
}
