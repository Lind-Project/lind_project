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

int main() {
    // Create or open the testfile.txt
    int fd = open("testfile.txt", O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
    if (fd == -1) {
        perror("open");
        return 1;
    }

    // Initialize and create a named semaphore
    sem_t *file_lock = sem_open("/file_lock", O_CREAT | O_EXCL, S_IRUSR | S_IWUSR, 1);
    if (file_lock == SEM_FAILED) {
        perror("sem_open");
        return 1;
    }

    // Fork a child process
    pid_t child_pid = fork();

    if (child_pid == -1) {
        perror("fork");
        return 1;
    } else if (child_pid == 0) {
        // Child process
        sem_wait(file_lock);  // Acquire the lock
        printf("Child process acquired the lock.\n");

        // Simulate some work
        sleep(5);

        sem_post(file_lock);  // Release the lock
        printf("Child process released the lock.\n");

        // Close and unlink the semaphore
        sem_close(file_lock);
        sem_unlink("/file_lock");
        
        exit(0);
    } else {
        // Parent process
        printf("Parent process trying to open the file...\n");

        // Try to open the file while the lock is held by the child
        int parent_fd = open("testfile.txt", O_RDWR);
        if (parent_fd == -1) {
            perror("open");
        } else {
            printf("Parent process successfully opened the file.\n");
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
