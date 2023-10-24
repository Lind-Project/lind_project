#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

void handler(int signum)
{
        printf("Signal Handler!\n");
        printf("Exiting program\n");
        fflush(stdout);
        exit(0);
}


void main()
{
    sigset_t set, oset, pset;
    struct sigaction new_action;
      
    new_action.sa_handler = handler;
    sigaction(SIGUSR2, &new_action, NULL);

    sigemptyset( &set );
    sigaddset( &set, SIGUSR2 );
    printf("blocking SIGUSR2\n");
    fflush(stdout);
    sigprocmask( SIG_BLOCK, &set, &oset );
    printf("Sending SIGUSR2\n");
    fflush(stdout);

    kill( getpid(), SIGUSR2);

    printf("Sleeping 1 second\n");
    fflush(stdout);
    sleep(1);
    printf("unblocking signal\n");
    fflush(stdout);

    sigprocmask( SIG_UNBLOCK, &set, &oset );

    while(1) {
    	sleep(1);
	printf("Error: program should have terminated\n");
	fflush(stdout);
    }

}

