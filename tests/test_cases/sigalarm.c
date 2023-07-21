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

    signal(SIGALRM, sig_handler);

    signal(SIGALRM, SIG_DFL);
    
	alarm(5);

	for (i = 1; i < 11; i++) {
        // Should print alarm on 6th
		printf("sleep %d...\n", i);
		sleep(1);
	}
	return 0;
}
