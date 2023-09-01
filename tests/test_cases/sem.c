#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <semaphore.h>
#include <signal.h>
#include <errno.h>

sem_t sem;
#define handle_error(msg) \
           do { perror(msg); exit(EXIT_FAILURE); } while (0)

static void
handler(int sig) {
    write(STDOUT_FILENO, "sem_post() from handler\n", 24);
    if (sem_post(&sem) == -1) {
        write(STDERR_FILENO, "sem_post() failed\n", 18);
        exit(EXIT_FAILURE);
    }
}

int main() {
    // Initial sem with 0
    sem_init(&sem, 0, 0);
    struct sigaction sa;
    int count = 9;
    int ret;
    sa.sa_handler = handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;
    if (sigaction(SIGALRM, &sa, NULL) == -1)
        handle_error("sigaction");

    alarm(5);

    // while((ret = sem_wait(&sem)) == -1 && errno == EINTR)
    //     continue;

    ret = sem_wait(&sem);

    printf("should display: %d\n", count);
    printf("return value of sem_wait: %d\n", ret);
    sem_post(&sem);

    sem_destroy(&sem);

    return 0;
}
