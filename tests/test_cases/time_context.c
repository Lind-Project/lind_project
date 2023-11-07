#include <stdio.h> 
#include <fcntl.h> 
#include <stdlib.h> 
#include <unistd.h>
#include <time.h>
#include <pthread.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <semaphore.h>
#include <signal.h>
#include <sys/wait.h>

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

int pipe_fd[2]; // Pipe fd

/*--------Signal functions--------*/
static void sig_usr(int signum){
    printf("Received signal %d\n", signum);
    fflush(NULL);
    if(signum == SIGUSR2) {
        // P2 is scheduled and receives the token
        tr = gettimens();
        write(pipe_fd[1], "received SIGUSR2", sizeof("received SIGUSR2"));
    }
}

/*--------Process functions--------*/
void process1(int pid) {
    printf("[process 1] Starting...");
    fflush(NULL);
    int count = 0;
    // 2. P1 marks the starting time
    start = gettimens();
    // 3. P1 sends a token to P2
    kill(pid, SIGUSR2);
    // 4. P1 attempts to read a response token from P2. This induces a context switch
    // 8. P1 is scheduled and receives the token
    char buffer[100];
    read(pipe_fd[0], buffer, sizeof(buffer));
    // 9. P1 marks the ending time
    end = gettimens();
    printf("Start: %d, End: %d\n", start, end);
    fflush(NULL);
}

void process2() {
    // Set signal handler
    struct sigaction sa_usr;
    sa_usr.sa_handler = sig_usr;   

    sigaction(SIGUSR2, &sa_usr, NULL);
    // 1. Blocks awaiting data from P1
    pause();
    // 5. P2 is scheduled and receives the token
    // 6. P2 sends a response token to P1.
    // 7. P2 attempts to read a response token from P1
    // printf("[Process 2] End...\n");
    // fflush(NULL);
}

/*--------Main function--------*/
int main(int argc, char *argv[]) {
    printf("Start\n");
    fflush(NULL);
    if (pipe(pipe_fd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid_t pid = fork();

    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        // Child process
        process2();
        printf("[Process 2] End...\n");
        fflush(NULL);
    } else {
        // Parent process
        process1(pid);
        wait(NULL); // Wait for the child process to finish
        close(pipe_fd[0]);
        close(pipe_fd[1]);
    }

    // int tc = (end-start)/2-start-tr;

    // printf("Context switching time: %d\n", tc);
    // fflush(NULL);

    return 0;
}
