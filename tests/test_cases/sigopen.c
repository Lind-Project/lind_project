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
    // Create or open the testfile.txt
    int fd = open("testfile.txt", O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
    if (fd == -1) {
        perror("open");
        return EXIT_FAILURE;
    }

    pid_t lock_pid = fork();
    // Fork a child process
    pid_t child_pid = fork();
    pid_t parent_pid = getppid();

    if (child_pid == -1) {
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
            return EXIT_FAILURE;
        }
        printf("lock() process acquired the lock.\n");
        
        sleep(5);

        // Release the lock
        printf("Child process released the lock.\n");

        lock.l_type = F_UNLCK;
        fcntl(fd, F_SETLK, &lock);
        
        exit(0);
    } else {    // Parent process
        // Fork open() process
        pid_t open_pid = fork();
        if(open_pid < 0){
            perror("fork");
            return EXIT_FAILURE;
        } else if(open_pid == 0){ // open() process
            printf("open() process waiting for the lock...\n");
            // Set signal handler
            struct sigaction sa_usr;
            sa_usr.sa_flags = 0;
            sa_usr.sa_handler = sig_usr;   

            sigaction(SIGUSR2, &sa_usr, NULL);

            // Try to open the file while the lock is held by the child
            int open_fd = open("testfile.txt", O_RDWR);
            if (open_fd < 0 && errno == EINTR) {
                printf("Error code: %d\n", errno);
                printf("EINTR error\n");
                fflush(NULL);
            } else {
                printf("open() process successfully opened the file.\n");
                close(open_fd);
            }
            exit(0);
        } else {
            sleep(2);

            printf("Sending SIGUSR2 signal to open() process...\n");
            kill(open_pid, SIGUSR2);
            // Wait for child processes to finish
            waitpid(lock_pid, NULL, 0);
            waitpid(open_pid, NULL, 0);

            // Close and unlink the semaphore
            close(fd);
        }
        
    }

    return 0;
}
