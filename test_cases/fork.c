#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <wait.h>

static volatile size_t counter = 0;
#define printf(s, ...) printf("[#%zu:L%u] " s, ++counter, __LINE__, __VA_ARGS__)

int main(void)
{
	int pret = -1, cret = -1, ppret = -1;
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
		printf("pid %d waiting on %d\n", getpid(), cpid);
		fflush(0);
		if (waitpid(cpid, &cret, 0) == -1)
			perror("waitpid()");
		/*
		 * if (wait(&cret) == -1)
		 *         perror("wait()");
		 */

		printf("pid = %d fork ret = %d\n", getpid(), pid);
		fflush(0);
		exit(EXIT_SUCCESS);
	}

	printf("pid %d waiting on %d\n", getpid(), pid);
	fflush(0);
	if (waitpid(pid, &pret, 0) == -1)
		perror("waitpid()");
	/*
	 * if (wait(&pret) == -1)
	 *         perror("wait()");
	 */
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
	if (waitpid(ppid, &ppret, 0) == -1)
		perror("waitpid()");
	/*
	 * if (wait(&ppret) == -1)
	 *         perror("wait()");
	 */
	printf("pid = %d fork ret = %d\n", getpid(), ppid);
	fflush(0);

	return 0;
}
