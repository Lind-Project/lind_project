#include <errno.h>
#include <string.h>
#include <signal.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h> 

void handler(int signum)
{
	printf("Signal Handler Test!\n");
        fflush(stdout);
	exit(0);
}

int main(void)
{
	struct sigaction new_action;
	struct sigaction old_action;

	pid_t pid = getpid();
	new_action.sa_handler = handler;

	sigaction(SIGUSR2, &new_action, NULL);
	sigaction(SIGUSR2, NULL, &old_action);

	if (new_action.sa_handler == old_action.sa_handler) {
		printf("Successfully changed the signal handler for Signal %d\n", SIGUSR2);
		fflush(NULL);
	} else {
		printf("Fail to correctly change the signal handler for Signal %d\n", SIGUSR2);
		fflush(NULL);
	}

	
	kill(pid, SIGUSR2);

	while(1);

	return 0;
}

