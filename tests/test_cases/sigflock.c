#undef _GNU_SOURCE
#define _GNU_SOURCE


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/file.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <signal.h>
#include <errno.h>


static void sig_usr(int signum){
   printf("Received signal %d\n", signum);
}


int main() {
    pid_t lock_pid = fork();

    if (lock_pid == -1) {
            perror("fork");
            return 0;
    } else if (lock_pid == 0) {     // lock() process
            int fd = open("testfile.txt", O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
            if (fd == -1) {
                perror("open");
                return EXIT_FAILURE;
            }
        // Lock the file
        int result = flock(fd, LOCK_EX);
        if(result < 0) {
            perror("fcntl");
        }
        printf("lock() process acquired the lock.\n");
        sleep(10);

        // Release the lock
        printf("lock() process released the lock.\n");

        flock(fd, LOCK_UN);
        
        exit(0);
    } else {    // Parent process
        pid_t child_pid = fork();
        if(child_pid < 0){
            perror("fork");
            return EXIT_FAILURE;
        } else if(child_pid == 0){ // Child process
            sleep(5);
            printf("Child process waiting for the lock...\n");
            // Set signal handler
            struct sigaction sa_usr;
            sa_usr.sa_flags = 0;
            sa_usr.sa_handler = sig_usr;  

            sigaction(SIGUSR2, &sa_usr, NULL);
            int fd = open("testfile.txt", O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
            // Try to lock the file while the lock is held 
            int ret = flock(fd, LOCK_EX);
            if(ret < 0) {
                perror("flock");
                printf("Error code: %d\n", errno);
                // printf("EINTR error\n");
                fflush(NULL);
                return EXIT_FAILURE;
            }
        } else {
            sleep(10);
            printf("Sending SIGUSR2 signal to child process...\n");
            kill(child_pid, SIGUSR2);
            // Wait for child processes to finish
            waitpid(lock_pid, NULL, 0);
            waitpid(child_pid, NULL, 0);
            
        }
        
    }


    return 0;
}




