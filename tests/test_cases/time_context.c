#include <stdio.h> 
#include <fcntl.h> 
#include <stdlib.h> 
#include <unistd.h>
#include <time.h>
#include <pthread.h>
#include <sys/ipc.h>
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

long long tr, start, end, td; // Timestamp
long long td_end, tr_end;

int pipe_fd[2]; // Pipe fd

/*--------Signal functions--------*/
static void sig_usr(int signum){
    printf("Received signal %d\n", signum);
    fflush(NULL);
    if(signum == SIGUSR2) {
        // P2 is scheduled and receives the token
        write(pipe_fd[1], "r", 1);
    }
}

/*--------Process functions--------*/
void process1(int pid) {
    // 2. P1 marks the starting time
    start = gettimens();
    // 3. P1 sends a token to P2
    kill(pid, SIGUSR2);
    td_end = gettimens();
    td = td_end - start;
    // 4. P1 attempts to read a response token from P2. This induces a context switch
    // 8. P1 is scheduled and receives the token
    char buffer[1];
    close(pipe_fd[1]); // Close write end
    read(pipe_fd[0], buffer, 1);
    // 9. P1 marks the ending time
    end = gettimens();
}

void process2() {
    // Set signal handler
    struct sigaction sa_usr;
    sa_usr.sa_handler = sig_usr;   

    sigaction(SIGUSR2, &sa_usr, NULL);
    // 1. Blocks awaiting data from P1
    pause();
    // 5. P2 is scheduled and receives the token
    tr_end = gettimens();
    tr = tr_end - td_end;
    // 6. P2 sends a response token to P1.
    // 7. P2 attempts to read a response token from P1
    _exit(EXIT_SUCCESS);
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
    } else {
        // Parent process
        process1(pid);
        wait(NULL); // Wait for the child process to finish
        close(pipe_fd[0]);
        close(pipe_fd[1]);
    }

    long long t = end - start;
    long long tc = t/2-td-tr;
    printf("tr: %lld\ntd: %lld\nstart: %lld\nend:%lld\nt:%lld\n", tr, td, start, end, t);
    printf("Context switching time: %lld\n", tc);
    fflush(NULL);

    return 0;
}
