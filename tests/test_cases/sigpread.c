#undef _GNU_SOURCE
#define _GNU_SOURCE

#include <ctype.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>

static void sig_usr(int signum){
    printf("Received signal %d\n", signum);
    fflush(NULL);
}

int main() {
    // Set signal handler
    struct sigaction sa_usr;
    sa_usr.sa_flags = 0;
    sa_usr.sa_handler = sig_usr;      
    // Register SIG handler
    sigaction(SIGUSR1, &sa_usr, NULL);
    // Open a file
    int fd = open("testfile.txt", O_RDONLY);

    char buffer[1024];
    ssize_t nread;

    // Generate a SIGUSR1 signal to simulate interruption
    printf("Generating signal...\n");
    kill(getpid(), SIGUSR1);

    // Try reading using pread
    nread = pread(fd, buffer, sizeof(buffer), 0);

    if (nread == -1) {
        if (errno == EINTR) {
            printf("pread was interrupted by signal\n");
            fflush(NULL);
        } 
    } 
    close(fd);
    // pid_t pid = fork();

    // if (pid ==0) {
    //     // Cage 2
    //     printf("Start pread()\n");
    //     char buf[512];  
    //     off_t offset = 0;

    //     // Set signal handler
    //     struct sigaction sa_usr;
    //     sa_usr.sa_flags = 0;
    //     sa_usr.sa_handler = sig_usr;   

    //     // Create a test file
    //     int fd = open("testfile.txt", O_CREAT|O_RDWR, 0666);
    //     if (fd < 0) {
    //         printf("Error open file\n");
    //         fflush(NULL);
    //     }

    //     // // Write to the file
    //     // const char *data = "TEST";
    //     // ssize_t wret = write(fd, data, strlen(data));
    //     // if (wret < 0) {
    //     //     printf("Error write to file\n");
    //     //     fflush(NULL);
    //     // }

    //     // Register SIG handler
    //     sigaction(SIGUSR2, &sa_usr, NULL);
    //     ssize_t prret;
    //     do {
    //         prret = pread(fd, buf, sizeof(buf), offset);
    //         printf("Return Value: %zu\n", prret);
    //         fflush(NULL);
    //         if(prret < 0) {
    //             if(errno == EINTR){
    //                 printf("Error code: %d\n", errno);
    //                 printf("EINTR error\n");
    //                 fflush(NULL);
    //             }
    //         }
    //     } while (prret == 0);
    //     // Blocking read
    //     printf("pread value: %zu\n", prret);
    //     fflush(NULL);
    //     close(fd);
    // } else {
    //     sleep(2);
    //     printf("Killing Cage 2 using PID: %ld\n", (long)pid);
    //     fflush(stdout);
    //     kill(pid, SIGUSR2);
    //     sleep(2);
    // }

    
    return 0;
}
