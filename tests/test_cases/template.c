#undef _GNU_SOURCE
#define _GNU_SOURCE

#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <wait.h>

static volatile size_t counter = 0;
#define printf(s, ...) printf("[#%zu:L%u] " s, ++counter, __LINE__, __VA_ARGS__)
#define PID_ANY (-1)

int main(void)
{
	int pret = -1, cret = -1, ppret = -1, pid = -1, cpid = -1, ppid = -1;

	printf("pid %d forking\n", getpid());

	switch ((pid = fork())) {
	case -1:
		perror("fork() failed");
		exit(EXIT_FAILURE);

	case 0:
		printf("pid %d forking\n", getpid());
		switch ((cpid = fork())) {
		case -1:
			perror("fork() failed");
			exit(EXIT_FAILURE);
		case 0:
			printf("pid = %d, ret = %d, status = %d\n", getpid(), cpid, EXIT_SUCCESS);
			exit(EXIT_SUCCESS);
		}
		printf("pid %d waiting on -1 (PID_ANY), child is %d\n", getpid(), cpid);
		if (waitpid(PID_ANY, &cret, 0) == -1)
			perror("waitpid()");
		printf("pid = %d, ret = %d, status = %d\n", getpid(), cpid, cret);
		exit(EXIT_SUCCESS);
	}

	printf("pid %d waiting on %d\n", getpid(), pid);
	if (waitpid(pid, &pret, 0) == -1)
		perror("waitpid()");
	printf("pid = %d, ret = %d, status = %d\n", getpid(), pid, pret);

	printf("pid %d forking\n", getpid());

	switch ((ppid = fork())) {
	case -1:
		perror("fork() failed");
		exit(EXIT_FAILURE);
	case 0:
		printf("pid = %d, ret = %d, status = %d\n", getpid(), ppid, EXIT_SUCCESS);
		exit(EXIT_SUCCESS);
	}
	if (wait(&ppret) == -1)
		perror("wait()");
	printf("pid = %d, ret = %d, status = %d\n", getpid(), ppid, ppret);

	return 0;
}
