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
int pipe_fd_2[2];
char buffer[1];
char buffer2[1];

/*--------Process functions--------*/
void process1(int pid) {
    close(pipe_fd[0]);
    // 2. P1 marks the starting time
    start = gettimens();
    // 3. P1 sends a token to P2
    write(pipe_fd[1], "r", 1);
    td_end = gettimens();
    td = td_end - start;
    // 4. P1 attempts to read a response token from P2. This induces a context switch
    close(pipe_fd_2[1]);
    // 8. P1 is scheduled and receives the token
    read(pipe_fd_2[0], buffer2, 1);
    // 9. P1 marks the ending time
    end = gettimens();
    close(pipe_fd[0]);
    close(pipe_fd_2[1]);
}

void process2() {
    // 1. Blocks awaiting data from P1
    close(pipe_fd[1]); // Close write end
    read(pipe_fd[0], buffer, 1);
    // 5. P2 is scheduled and receives the token
    tr_end = gettimens();
    tr = tr_end - td_end;
    // 6. P2 sends a response token to P1.
    close(pipe_fd_2[0]);
    write(pipe_fd_2[1], "r", 1);
    // 7. P2 attempts to read a response token from P1
    _exit(EXIT_SUCCESS);
}

/*--------Main function--------*/
int main() {
    if (pipe(pipe_fd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }
    if (pipe(pipe_fd_2) == -1) {
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
        
    }

    long long t = end - start;
    long long tc = t/2-td-tr;
    // printf("tr: %lld\ntd: %lld\nstart: %lld\nend:%lld\nt:%lld\ntr_end:%lld\n", tr, td, start, end, t, tr_end);
    printf("Context switching time %lld ns\n", tc);
    fflush(NULL);

    return 0;
}
