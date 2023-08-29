#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/epoll.h>
#include <errno.h>

#define MAX_EVENTS 10

int main() {
    int epoll_fd, nfds;
    struct epoll_event ev, events[MAX_EVENTS];
    int ret_create, ret_ctl, ret_wait;

    ret_create = epoll_create(0);
    if(ret_create < 0) {
        printf("ERROR: %d\n", errno);
        perror("epoll_create");
        fflush(NULL);
        printf("Return: %d\n", ret_create);
    }

    epoll_fd = epoll_create(MAX_EVENTS); 
    if (epoll_fd == -1) {
        perror("epoll_create");
        return 1;
    }
    printf("[epoll_create] return fd: %d\n", epoll_fd);
    fflush(NULL);

    int fds[2]; // File descriptors for pipe
    if (pipe(fds) == -1) {
        perror("pipe");
        return 1;
    }

    // Add read end of the pipe to the epoll set
    ev.events = EPOLLIN;
    ev.data.fd = fds[0];
    int rv = epoll_ctl(epoll_fd, EPOLL_CTL_ADD, fds[0], &ev);
    if (rv < 0) {
        perror("epoll_ctl: pipe read end");
        return 1;
    }
    printf("[epoll_ctl] return: %d\n", rv);
    fflush(NULL);

    ret_ctl = epoll_ctl(epoll_fd, EPOLL_CTL_ADD, fds[0], &ev);
    if(ret_ctl < 0) {
        printf("ERROR: %d\n", errno);
        perror("epoll_ctl");
        fflush(NULL);
        printf("Return: %d\n", ret_create);
    }

    int wait_fd;
    ret_wait = epoll_wait(wait_fd, events, MAX_EVENTS, -1);
    if(ret_wait < 0) {
        printf("ERROR: %d\n", errno);
        perror("epoll_wait");
        fflush(NULL);
        printf("Return: %d\n", ret_create);
    }

    close(epoll_fd);
    return 0;
}
