#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <semaphore.h>
#include <wait.h>

#define SHM_SIZE 1024

int main() {
    sem_t *sem;
    int shm_fd;

    // Create a shared memory region
    shm_fd = shm_open("/myshm", O_CREAT | O_RDWR, 0666);
    if (shm_fd == -1) {
        perror("shm_open");
        exit(1);
    }

    // Set the size of the shared memory region
    if (ftruncate(shm_fd, sizeof(sem_t)) == -1) {
        perror("ftruncate");
        exit(1);
    }

    // Map the shared memory region
    sem = mmap(NULL, sizeof(sem_t), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (sem == MAP_FAILED) {
        perror("mmap");
        exit(1);
    }

    // Initialize the semaphore
    if (sem_init(sem, 1, 1) == -1) {
        perror("sem_init");
        exit(1);
    }

    pid_t pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        exit(1);
    } else if (pid == 0) {
        // Child process
        sem_wait(sem); // Child waits for the semaphore
        printf("Child process: Acquired semaphore\n");
        sleep(2); // Simulate some work
        sem_post(sem); // Release the semaphore
        printf("Child process: Released semaphore\n");
        exit(0);
    } else {
        // Parent process
        sleep(1); // Ensure the child process starts first
        sem_wait(sem); // Parent waits for the semaphore
        printf("Parent process: Acquired semaphore\n");
        sleep(2); // Simulate some work
        sem_post(sem); // Release the semaphore
        printf("Parent process: Released semaphore\n");

        // Wait for the child process to finish
        wait(NULL);
    }

    // Cleanup
    wait(NULL);
    sem_destroy(sem);
    munmap(sem, sizeof(sem_t));
    shm_unlink("/myshm");

    return 0;
}
