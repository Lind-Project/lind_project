#include <errno.h>
#include <string.h>
#include <signal.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

void handler(int signum)
{
	printf("Signal Handler Test!\n");
}

int main(void)
{
	struct sigaction new_action;
	struct sigaction old_action;

	pid_t pid = getpid();

	new_action.sa_handler = handler;
	new_action.sa_flags = SA_ONSTACK;
	sigemptyset(&new_action.sa_mask);
	sigaddset(&new_action.sa_mask, SIGUSR2);

	sigaction(SIGUSR1, &new_action, NULL);
	sigaction(SIGUSR1, NULL, &old_action);

	if (new_action.sa_handler == old_action.sa_handler) {
		printf("Successfully changed the signal handler for Signal %d\n", SIGUSR1);
		fflush(NULL);
	} else {
		printf("Fail to correctly change the signal handler for Signal %d\n", SIGUSR1);
		fflush(NULL);
	}

	if (old_action.sa_flags & SA_ONSTACK) {
		printf("Successfully set SA_ONSTACK flag to Signal %d\n", SIGUSR1);
		fflush(NULL);
	} else {
		printf("Fail to set SA_ONSTACK flag to Signal %d\n", SIGUSR1);
		fflush(NULL);
	}

	if (sigismember(&old_action.sa_mask, SIGUSR2)) {
		printf("Successfully adding Signal %d to Signal %d's mask\n", SIGUSR2, SIGUSR1);
		fflush(NULL);
	} else {
		printf("Fail to Signal %d to Signal %d's mask\n", SIGUSR2, SIGUSR1);
		fflush(NULL);
	}

	return 0;
}
