#include <errno.h>
#include <string.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>

void check_errno(int res) {
	if (res != 0) {
		printf("errno: %s\n", strerror(errno));
		fflush(NULL);
	}
}

void sigismember_verbose(sigset_t *set, int sig, char *set_name) {
	if (sigismember(set, sig)) {
		printf("Signal %d is in %s\n", sig, set_name);
		fflush(NULL);
	} else { 
		printf("Signal %d is NOT in %s\n", sig, set_name);
		fflush(NULL);
	}
}

int main(void)
{
	sigset_t new_set;
	sigset_t old_set;

	// Initialize
	sigemptyset(&new_set);
	sigemptyset(&old_set);
	
	sigaddset(&new_set, SIGUSR1);
	sigismember_verbose(&new_set, SIGUSR1, "new_set");

	check_errno(sigprocmask(SIG_SETMASK, NULL, &old_set));
	sigismember_verbose(&old_set, SIGUSR1, "old_set");

	// Test SIG_BLOCK
	printf("Adding Signal %d to sigset using sigprocmask\n", SIGUSR1);
	fflush(NULL);
	check_errno(sigprocmask(SIG_BLOCK, &new_set, NULL));
	check_errno(sigprocmask(SIG_SETMASK, NULL, &old_set));
	sigismember_verbose(&old_set, SIGUSR1, "old_set");

	// Test SIG_UNBLOCK
	printf("Remove Signal %d from sigset using sigprocmask\n", SIGUSR1);
	fflush(NULL);
	check_errno(sigprocmask(SIG_UNBLOCK, &new_set, NULL));
	check_errno(sigprocmask(SIG_SETMASK, NULL, &old_set));
	sigismember_verbose(&old_set, SIGUSR1, "old_set");

	// Test SIG_SETMASK
	printf("Set sigset using sigprocmask\n");
	fflush(NULL);
	sigemptyset(&new_set);
	sigaddset(&new_set, SIGUSR2);
	check_errno(sigprocmask(SIG_SETMASK, &new_set, NULL));
	check_errno(sigprocmask(SIG_SETMASK, NULL, &old_set));
	sigismember_verbose(&old_set, SIGUSR1, "old_set");
	sigismember_verbose(&old_set, SIGUSR2, "old_set");

	// Test blocking SIGKILL and SIGSTOP
	printf("Attempt to block SIGKILL and SIGSTOP\n");
	fflush(NULL);
	sigemptyset(&new_set);
	sigaddset(&new_set, SIGKILL);
	sigaddset(&new_set, SIGSTOP);
	check_errno(sigprocmask(SIG_SETMASK, &new_set, NULL));
	check_errno(sigprocmask(SIG_SETMASK, NULL, &old_set));
	sigismember_verbose(&old_set, SIGKILL, "old_set");
	sigismember_verbose(&old_set, SIGSTOP, "old_set");

	return 0;
}
