#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>

int main(void)
{
	int pid = -1, cpid = -1, ppid = -1, pret = 0, cret = 0, ppret = 0;
	static const char c[] = "child waiting\n", p[] = "parent waiting\n";

	puts("1st parent forking");
	fflush(0);

	switch ((pid = fork())) {
	case -1:
		perror("fork() failed");
		fflush(0);
		exit(EXIT_FAILURE);

	case 0:
		puts("1st child forking");
		fflush(0);
		switch ((cpid = fork())) {
		case -1:
			perror("fork() failed");
			fflush(0);
			exit(EXIT_FAILURE);
		case 0:
			printf("1st child %d succeeded\n", getpid());
			fflush(0);
			sleep(2);
			exit(EXIT_SUCCESS);
		}

		write(STDOUT_FILENO, c, sizeof c - 1);
		if (waitpid(cpid, &cret, 0) == -1)
			perror("1st child");
		if (wait(&cret) == -1)
			perror("1st child");
		fflush(0);
		printf("1st child %d succeeded after waiting on %d\n", getpid(), cpid);
		fflush(0);
		sleep(2);
		exit(EXIT_SUCCESS);
	}

	fflush(0);
	write(STDOUT_FILENO, p, sizeof p - 1);
	if (waitpid(pid, &pret, 0) == -1)
		perror("1st parent");
	/*
	 * if (wait(&pret) == -1)
	 *         perror("1st parent");
	 */
	fflush(0);
	printf("1st parent %d succeeded after waiting on %d\n", getpid(), pid);
	fflush(0);

	puts("2nd parent forking");
	switch ((ppid = fork())) {
	case -1:
		perror("fork() failed");
		fflush(0);
		exit(EXIT_FAILURE);
	case 0:
		printf("2nd child %d succeeded\n", getpid());
		fflush(0);
		sleep(2);
		exit(EXIT_SUCCESS);
	}
	write(STDOUT_FILENO, p, sizeof p - 1);
	if (waitpid(ppid, &ppret, 0) == -1)
		perror("2nd parent");
	/* if (wait(&ppret) == -1) */
	/*         perror("2nd parent"); */
	fflush(0);
	printf("2nd parent %d succeeded after waiting on %d\n", getpid(), ppid);
	fflush(0);

	return 0;
}
