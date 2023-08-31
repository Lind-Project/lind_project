#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <semaphore.h>
#include <signal.h>

sem_t sem;
#define handle_error(msg) \
           do { perror(msg); exit(EXIT_FAILURE); } while (0)

static void
handler(int sig) {
    write(STDOUT_FILENO, "sem_post() from handler\n", 24);
    if (sem_post(&sem) == -1) {
        write(STDERR_FILENO, "sem_post() failed\n", 18);
        _exit(EXIT_FAILURE);
    }
}

int main() {
    // Initial sem with 0
    sem_init(&sem, 0, 0);
    struct sigaction sa;
    int count = 9;
    sa.sa_handler = handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    if (sigaction(SIGALRM, &sa, NULL) == -1)
        handle_error("sigaction");

    alarm(5);

    sem_wait(&sem);
    printf("should display: %d\n", count);
    sem_post(&sem);

    sem_destroy(&sem);

    return 0;
}
