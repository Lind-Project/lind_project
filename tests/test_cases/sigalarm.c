#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
 
/* Signal Handler */
void sig_handler() {
    printf("ALARM!\n ");   
}
 
int main() {
	int i;

    sigset_t set;
    sigemptyset(&set);
    sigaddset(&set, SIGALRM);
    sigprocmask(SIG_BLOCK, &set, NULL);
    
	alarm(5);

    signal(SIGALRM, sig_handler);

	for (i = 1; i < 11; i++) {
        // Should print alarm on 6th
		printf("sleep %d...\n", i);
		sleep(1);
	}
	return 0;
}
