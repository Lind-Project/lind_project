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
        return 0;
    }

    // Initialize and create a named semaphore
    sem_t *file_lock = sem_open("/file_lock", O_CREAT | O_EXCL, S_IRUSR | S_IWUSR, 1);
    if (file_lock == SEM_FAILED) {
        perror("sem_open");
        return 0;
    }



    // Fork a child process
    pid_t child_pid = fork();
    pid_t parent_pid = getppid();

    if (child_pid == -1) {
        perror("fork");
        return 0;
    } else if (child_pid == 0) {
        // Child process
        sem_wait(file_lock);  // Acquire the lock
        printf("Child process acquired the lock.\n");
        sleep(2);
        kill(parent_pid, SIGUSR2);
        // Simulate some work
        sleep(5);

        sem_post(file_lock);  // Release the lock
        printf("Child process released the lock.\n");

        // Close and unlink the semaphore
        sem_close(file_lock);
        sem_unlink("/file_lock");
        
        return EXIT_FAILURE;
    } else {
        // Parent process
        printf("open() process trying to open the file...\n");

        // Set signal handler
        struct sigaction sa_usr;
        sa_usr.sa_flags = 0;
        sa_usr.sa_handler = sig_usr;   

        sigaction(SIGUSR2, &sa_usr, NULL);

        // Try to open the file while the lock is held by the child
        int parent_fd = open("testfile.txt", O_RDWR);
        if (parent_fd < 0 && errno == EINTR) {
            printf("Error code: %d\n", errno);
            printf("EINTR error\n");
            fflush(NULL);
        } else {
            printf("open() process successfully opened the file.\n");
            close(parent_fd);
        }

        // Wait for the child process to finish
        wait(NULL);
        
        // Close and unlink the semaphore
        sem_close(file_lock);
        sem_unlink("/file_lock");

        close(fd);
    }

    return 0;
}
