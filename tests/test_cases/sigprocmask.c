#include <errno.h>
#include <string.h>
#include <signal.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <wait.h>

int sig_handled = 0;

void handler(int signum)
{
	printf("Handler Test! Signal %d\n", signum);
	fflush(stdout);
	sig_handled++;
}

void sigismember_verbose(sigset_t *set, int sig, char *set_name)
{
	if (sigismember(set, sig))
	{
		printf("Signal %d is in %s\n", sig, set_name);
		fflush(NULL);
	}
	else
	{
		printf("Signal %d is NOT in %s\n", sig, set_name);
		fflush(NULL);
	}
}

void send_signals(pid_t pid)
{
	// printf("Parent sending signal %d to child %u\n", SIGUSR2, pid);
	// fflush(stdout);
	// kill(pid, SIGUSR2);
	printf("Parent sending signal %d to child %u\n", SIGUSR1, pid);
	fflush(stdout);
	kill(pid, SIGUSR1);
}

void test_signal_block()
{
	printf("Testing SIG_BLOCK\n");
	fflush(stdout);
	sigset_t set;

	struct sigaction action;
	// Initialize
	sigemptyset(&set);

	sigaddset(&set, SIGUSR1);
	sigaddset(&set, SIGUSR2);
	sigismember_verbose(&set, SIGUSR1, "set");
	sigismember_verbose(&set, SIGUSR2, "set");

	pid_t pid = fork();
	if (pid == 0)
	{
		printf("Child running %u\n", getpid());

		// Initialize signal handlers
		action.sa_handler = handler;
		sigaction(SIGUSR1, &action, NULL);
		sigaction(SIGUSR2, &action, NULL);

		printf("Adding Signal %d to sigset using sigprocmask\n", SIGUSR1);
		printf("Adding Signal %d to sigset using sigprocmask\n", SIGUSR2);
		fflush(stdout);

		sigprocmask(SIG_BLOCK, &set, NULL);
		while (1)
			;
	}
	else
	{
		sleep(1);
		send_signals(pid);
		sleep(3);
		kill(pid, SIGKILL);
	}
	return;
}

void test_signal_unblock()
{
	printf("\nTesting SIG_UNBLOCK\n");
	fflush(stdout);
	sigset_t new_set;
	sigset_t old_set;

	struct sigaction action;
	// Initialize
	sigemptyset(&old_set);
	sigemptyset(&new_set);

	sigaddset(&old_set, SIGUSR1);
	sigaddset(&old_set, SIGUSR2);
	sigismember_verbose(&old_set, SIGUSR1, "old_set");
	sigismember_verbose(&old_set, SIGUSR2, "old_set");

	pid_t pid = fork();
	if (pid == 0)
	{
		printf("Child running %u\n", getpid());

		// Initialize signal handlers
		action.sa_handler = handler;
		sigaction(SIGUSR1, &action, NULL);
		sigaction(SIGUSR2, &action, NULL);

		printf("Adding Signal %d to sigset using sigprocmask\n", SIGUSR1);
		printf("Adding Signal %d to sigset using sigprocmask\n", SIGUSR2);
		fflush(stdout);

		sigprocmask(SIG_BLOCK, &old_set, NULL);
		sleep(2);

		// Initialize new_set
		sigaddset(&new_set, SIGUSR2);
		sigismember_verbose(&new_set, SIGUSR2, "new_set");

		printf("Remove Signal %d from sigset using sigprocmask\n", SIGUSR2);
		fflush(stdout);

		sigprocmask(SIG_UNBLOCK, &new_set, &old_set);
		sleep(2);
		exit(0);
	}
	else
	{
		sleep(1);
		send_signals(pid);
	}
	return;
}

void test_signal_setmask()
{
	printf("\nTesting SIG_SETMASK\n");
	fflush(stdout);
	sigset_t new_set;
	sigset_t old_set;

	struct sigaction action;
	// Initialize
	sigemptyset(&old_set);
	sigemptyset(&new_set);

	sigaddset(&old_set, SIGUSR1);
	sigaddset(&old_set, SIGUSR2);
	sigismember_verbose(&old_set, SIGUSR1, "old_set");
	sigismember_verbose(&old_set, SIGUSR2, "old_set");

	pid_t pid = fork();
	if (pid == 0)
	{
		printf("Child running %u\n", getpid());

		// Initialize signal handlers
		action.sa_handler = handler;
		sigaction(SIGUSR1, &action, NULL);
		sigaction(SIGUSR2, &action, NULL);

		printf("Adding Signal %d to sigset using sigprocmask\n", SIGUSR1);
		printf("Adding Signal %d to sigset using sigprocmask\n", SIGUSR2);
		fflush(stdout);

		sigprocmask(SIG_BLOCK, &old_set, NULL);
		sleep(2);

		// Initialize new_set
		sigaddset(&new_set, SIGUSR2);
		sigismember_verbose(&new_set, SIGUSR2, "new_set");

		printf("Setting Signal Mask %d using sigprocmask\n", SIGUSR2);
		fflush(stdout);

		sigprocmask(SIG_SETMASK, &new_set, &old_set);
		sleep(2);
		exit(0);
	}
	else
	{
		sleep(1);
		send_signals(pid);
	}
	return;
}

int main(void)
{
	test_signal_block();
	sleep(5);
	test_signal_unblock();
	sleep(5);
	test_signal_setmask();
	sleep(5);
	return 0;
}
