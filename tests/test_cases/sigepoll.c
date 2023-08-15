#include <errno.h>
#include <string.h>
#include <signal.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h> 
#include <poll.h>
#include <sys/epoll.h>

#define MAX_EVENTS 5

void handler(int signum)
{
    printf("Signal Handler Test!\n");
    printf("Exiting Cage 2\n");
    fflush(stdout);
}

int main(void)
{
    struct sigaction new_action;
    struct sigaction old_action;

    pid_t pid = fork();

    if (pid == 0) {
        // Cage 2
        printf("Cage 2 pid: %ld\n", (long)getpid());
        printf("Handler function ptr %p\n", handler);
        fflush(stdout);

        new_action.sa_handler = handler;

        sigaction(SIGUSR2, &new_action, NULL);
        sigaction(SIGUSR2, NULL, &old_action);

        if (new_action.sa_handler == old_action.sa_handler) {
                printf("Successfully changed the signal handler for Signal %d\n", SIGUSR2);
                fflush(NULL);
        } else {
                printf("Fail to correctly change the signal handler for Signal %d\n", SIGUSR2);
                fflush(NULL);
        }

        int epoll_fd, num_events, i;
        struct epoll_event events[MAX_EVENTS];

        epoll_fd = epoll_create(256);
        if (epoll_fd < 0) {
            perror("epoll_create");
            fflush(NULL);
        }

        struct epoll_event event;
        event.events = EPOLLIN;
        event.data.fd = STDIN_FILENO;

        if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, STDIN_FILENO, &event) < 0) {
            perror("epoll_ctl");
            fflush(NULL);
        }

        num_events = epoll_wait(epoll_fd, events, MAX_EVENTS, -1);
        if (num_events < 0 && errno == EINTR) {
            printf("Error code: %d\n", errno);
            printf("EINTR error\n");
            fflush(NULL);
        }
    
    }

    else {
            // Cage 1
            sleep(2);
            printf("Killing Cage 2 using PID: %ld\n", (long)pid);
            fflush(stdout);
            kill(pid, SIGUSR2);
            sleep(2);
    }
    return 0;
}
