#undef _GNU_SOURCE
#define _GNU_SOURCE


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <semaphore.h>
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
    // Create or open the testfile.txt
    int fd = open("testfile.txt", O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
    if (fd == -1) {
        perror("open");
        return EXIT_FAILURE;
    }
    if (lock_pid == -1) {
        perror("fork");
        return 0;
    } else if (lock_pid == 0) {     // lock() process
        // Lock the file
        struct flock lock;
        lock.l_type = F_WRLCK;
        lock.l_whence = SEEK_SET;
        lock.l_start = 0;
        lock.l_len = 0; // Lock the whole file

        int result = fcntl(fd, F_SETLK, &lock);
        if(result < 0) {
            perror("fcntl");
            printf("Error code: %d\n", errno);
            // printf("EINTR error\n");
            fflush(NULL);
        }

        printf("lock() process acquired the lock.\n");
        printf("lock() will waiting for 10s\n");

        sleep(10);
        
        // Release the lock
        printf("lock() process released the lock.\n");

        lock.l_type = F_UNLCK;
        fcntl(fd, F_SETLK, &lock);
        
        exit(0);
    } else {    
        pid_t child_pid = fork();
        if(child_pid < 0){
            perror("fork");
            return EXIT_FAILURE;
        } else if(child_pid == 0){ // Child process
            sleep(2);
            printf("[pread] process start\n");
            // Set signal handler
            struct sigaction sa_usr;
            sa_usr.sa_flags = 0;
            sa_usr.sa_handler = sig_usr;  

            sigaction(SIGUSR2, &sa_usr, NULL);

            char buf[512];
            while(1) {
                int ret = pread(fd, buf, 511, 0);
                printf("[pread]: %d\n", ret);
                perror("pread");
                if(ret < 0) {
                    perror("pread");
                    exit(0);
                }
            }
            
        } else {
            sleep(10);
            printf("Sending SIGUSR2 signal to child process...\n");
            kill(child_pid, SIGUSR2);
            // Wait for child processes to finish
            wait(NULL);
            close(fd);
            
        }
      
    }

    return 0;
}
