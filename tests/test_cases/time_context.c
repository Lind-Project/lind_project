#include <stdio.h> 
#include <fcntl.h> 
#include <stdlib.h> 
#include <unistd.h>
#include <time.h>
#include <pthread.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <semaphore.h>

/*--------Timing functions--------*/
long long execution_time = 0;

long long gettimens(void) {
    struct timespec tp;

    if (clock_gettime(CLOCK_MONOTONIC, &tp) == -1) {
        perror("clock gettime");
        exit(EXIT_FAILURE);
    }

    return (tp.tv_sec * 1000000000) + tp.tv_nsec;
}

long long tr, start, end; // Timestamp
int token = 0;
int response = 0;

/*--------Process functions--------*/
void process1() {
    printf("[process 1] Starting...");
    int count = 0;
    // P1 marks the starting time
    start = gettimens();
    // P1 sends a token to P2
    token = 1;
    // P1 attempts to read a response token from P2. This induces a context switch
    while(response == 0) {
    }
    // P1 marks the ending time
    end = gettimens();
}

void process2() {
    // Blocks awaiting data from P1
    while(token == 0) {
    }
    tr = gettimens();
    // P2 sends a response token to P1.
    response = 1;
}

/*--------Main function--------*/
int main(int argc, char *argv[]) {

    pid_t pid = fork();

    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        // Child process
        process2();
    } else {
        // Parent process
        process1();
        wait(NULL); // Wait for the child process to finish
    }

    int tc = (end-start)/2-start-tr;

    printf("Context switching time: %d\n", tc);
    fflush(NULL);

    return 0;
}
