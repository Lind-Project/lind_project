/*
 * lind_platform.h
 *
 *  Created on: Jul 23, 2013
 *      Author: sji, Ali Gholami
 */

#ifndef LIND_PLATFORM_H_
#define LIND_PLATFORM_H_


#include <sys/types.h>
#if NACL_LINUX
#include <sys/statfs.h>
#endif
#include <sys/stat.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <sys/poll.h>
#include <sys/epoll.h>
#include <unistd.h>
#include <stdint.h>

#include "lind_stat.h"
 /* These values are according to /lind_glibc/sysdeps/nacl/lind_syscalls.h constants. */

#define LIND_debug_noop                 1
#define LIND_safe_fs_access             2
#define LIND_debug_trace                3
#define LIND_safe_fs_unlink             4
#define LIND_safe_fs_link               5
#define LIND_safe_fs_chdir              6
#define LIND_safe_fs_mkdir              7
#define LIND_safe_fs_rmdir              8
#define LIND_safe_fs_xstat              9
#define LIND_safe_fs_open               10
#define LIND_safe_fs_close              11
#define LIND_safe_fs_read               12
#define LIND_safe_fs_write              13
#define LIND_safe_fs_lseek              14
#define LIND_fs_ioctl                   15
#define LIND_safe_fs_fxstat             17
#define LIND_safe_fs_fstatfs            19
#define LIND_safe_fs_getdents           23
#define LIND_safe_fs_dup                24
#define LIND_safe_fs_dup2               25
#define LIND_safe_fs_statfs             26
#define LIND_safe_fs_fcntl              28
#define LIND_sys_getpid                 31
#define LIND_safe_net_socket            32
#define LIND_safe_net_bind              33
#define LIND_safe_net_send              34
#define LIND_safe_net_sendto            35
#define LIND_safe_net_recv              36
#define LIND_safe_net_recvfrom          37
#define LIND_safe_net_connect           38
#define LIND_safe_net_listen            39
#define LIND_safe_net_accept            40
#define LIND_safe_net_getpeername       41
#define LIND_safe_net_getsockname       42
#define LIND_safe_net_getsockopt        43
#define LIND_safe_net_setsockopt        44
#define LIND_safe_net_shutdown          45
#define LIND_safe_net_select            46
#define LIND_safe_net_getifaddrs        47
#define LIND_safe_net_poll              48
#define LIND_safe_net_socketpair        49
#define LIND_safe_sys_getuid            50
#define LIND_safe_sys_geteuid           51
#define LIND_safe_sys_getgid            52
#define LIND_safe_sys_getegid           53
#define LIND_safe_fs_flock              54
#define LIND_safe_fs_rename             55
#define LIND_safe_net_epoll_create      56
#define LIND_safe_net_epoll_ctl		    57
#define LIND_safe_net_epoll_wait        58
#define LIND_safe_net_sendmsg           59
#define LIND_safe_net_recvmsg           60
#define LIND_safe_fs_openat             61
#define LIND_safe_fs_dup3             	62
#define LIND_safe_fs_readv              63
#define LIND_safe_fs_wrtiev             64
#define LIND_safe_net_epoll_create1      65

#define LIND_safe_fs_pipe              66
#define LIND_safe_fs_pipe2             67
#define LIND_safe_fs_fork               68

#define LIND_comp_cia                   105
#define LIND_comp_call                  106
#define LIND_comp_accept                107
#define LIND_comp_recv                  108

int GetHostFdFromLindFd(int lindFd);

int LindPythonInit(void);
int LindPythonFinalize(void);
int lind_access (const char *pathname, int mode);
int lind_unlink (const char *name);
int lind_link (const char *from, const char *to);
int lind_chdir (const char *name);
int lind_mkdir (const char *path, int mode);
int lind_rmdir (const char *path);
int lind_stat (const char *path, struct lind_stat *buf);
int lind_open (const char *path, int flags, int mode);
int lind_openat (int dir_fd, const char *path, int flags, int mode);
int lind_close (int fd);
ssize_t lind_read (int fd, void *buf, size_t count);
ssize_t lind_write (int fd, const void *buf, size_t count);
off_t lind_lseek (int fd, off_t offset, int whence);
int lind_fstat (int fd, struct lind_stat *buf);
int lind_fstatfs (int fd, struct lind_statfs *buf);
int lind_statfs (const char *path, struct lind_statfs *buf);
int lind_noop (void);
int lind_getpid (void);
int lind_dup (int oldfd);
int lind_dup2 (int oldfd, int newfd);
int lind_dup3 (int oldfd, int newfd, int flags);
int lind_getdents (unsigned int fd, char *dirp,
                    unsigned int count);
int lind_fcntl_get (int fd, int cmd);
int lind_fcntl_set (int fd, int cmd, long set_op);
int lind_socket (int domain, int type, int protocol);
int lind_bind (int sockfd, const struct lind_sockaddr *addr, lind_socklen_t addrlen);
ssize_t lind_send (int sockfd, const void *buf, size_t len, int flags);
ssize_t lind_recv (int sockfd, void *buf, size_t len, int flags);
int lind_connect (int sockfd, const struct lind_sockaddr *addr, lind_socklen_t addrlen);
int lind_listen (int sockfd, int backlog);
ssize_t lind_sendto (int sockfd, const void *buf, size_t len, int flags, const struct lind_sockaddr *dest_addr, lind_socklen_t addrlen);
ssize_t lind_recvfrom (int sockfd, void *buf, size_t len, int flags, struct lind_sockaddr *src_addr, lind_socklen_t* addrlen);
ssize_t lind_sendmsg(int sockfd, const struct lind_msghdr *msg, int flags);
ssize_t lind_recvmsg(int sockfd, struct lind_msghdr *msg, int flags);
int lind_accept (int sockfd, const struct lind_sockaddr *addr, lind_socklen_t* addrlen);
int lind_getpeername(int sockfd, struct lind_sockaddr* addr, lind_socklen_t * addrlen);
int lind_getsockname(int sockfd, struct lind_sockaddr *addr, lind_socklen_t *addrlen);
int lind_setsockopt (int sockfd, int level, int optname, const void *optval, lind_socklen_t optlen);
int lind_getsockopt (int sockfd, int level, int optname, void *optval, lind_socklen_t* optlen);
int lind_shutdown (int sockfd, int how);
int lind_select (int nfds, fd_set * readfds, fd_set * writefds, fd_set * exceptfds, struct timeval *timeout);
int lind_getifaddrs (int ifaddrs_buf_siz, void *ifaddrs);
int lind_poll(struct lind_pollfd *fds, lind_nfds_t nfds, int timeout);
int lind_socketpair (int domain, int type, int protocol, int *fds);
int lind_getuid (void);
int lind_geteuid (void);
int lind_getgid (void);
int lind_getegid (void);
int lind_flock (int fd, int operation);
char* lind_getcwd(char* buf, size_t size);
int lind_fcntl(int fd, int cmd, ...);
int lind_epoll_create(int size);
int lind_epoll_ctl(int epfd, int op, int fd, struct lind_epoll_event *event);
int lind_epoll_wait(int epfd, struct lind_epoll_event *events, int maxevents, int timeout);
ssize_t lind_pread(int fd, void* buf, int count, off_t offset);
ssize_t lind_pwrite(int fd, const void *buf, int count, off_t offset);
ssize_t lind_readv(int fd, void* buf, int count);
ssize_t lind_writev(int fd, const void *buf, int count);
int lind_epoll_create1(int flags);
int lind_pipe(int* pipefds);
int lind_pipe2(int* pipefds, int flags);
int lind_fork(int newcageid);

void add_mapping(int src, int dest);
int get_mapping(int fd);
const char *get_repy_path();

#endif /* LIND_PLATFORM_H_ */
