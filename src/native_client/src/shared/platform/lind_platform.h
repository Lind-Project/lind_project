/*
 * lind_platform.h
 *
 *  Created on: Jul 23, 2013
 *      Author: sji
 */

#ifndef LIND_PLATFORM_H_
#define LIND_PLATFORM_H_

#include <sys/types.h>
#if NACL_LINUX
# include <sys/statfs.h>
#endif
#include <sys/stat.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <sys/poll.h>

/* avoid errors caused by conflicts with feature_test_macros(7) */
#undef _POSIX_C_SOURCE
#undef _XOPEN_SOURCE

#include <unistd.h>
#include <stdint.h>
#include <Python.h>

#include "native_client/src/shared/platform/lind_stat.h"

#if NACL_OSX
# define sockaddr_in sockaddr
# define __SOCKADDR_ARG struct sockaddr
#endif

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

#define LIND_comp_cia                   105
#define LIND_comp_call                  106
#define LIND_comp_accept                107
#define LIND_comp_recv                  108


struct select_results {
    struct timeval used_t;
    fd_set r;
    fd_set w;
    fd_set e;
};

int GetHostFdFromLindFd(int lindFd);

int LindPythonInit(void);
int LindPythonFinalize(void);

PyObject* CallPythonFunc(PyObject* context, const char* func, PyObject* args);
int ParseResponse(PyObject* response, int* isError, int* code, char** dataOrMessage, int* len);

int lind_pread(int fd, void* buf, int count, off_t offset);
int lind_pwrite(int fd, const void *buf, int count, off_t offset);
int lind_access (int version, const char *file);
int lind_unlink (const char *name);
int lind_link (const char *from, const char *to);
int lind_chdir (const char *name);
int lind_mkdir (int mode, const char *path);
int lind_rmdir (const char *path);
int lind_xstat (int version, const char *path, struct lind_stat *buf);
int lind_open (int flags, int mode, const char *path);
int lind_close (int fd);
int lind_read (int fd, int size, void *buf);
int lind_write (int fd, size_t count, const void *buf);
int lind_lseek (off_t offset, int fd, int whence);
int lind_fxstat (int fd, int version, struct lind_stat *buf);
int lind_fstatfs (int fd, struct lind_statfs *buf);
int lind_statfs (const char *path, struct lind_statfs *buf);
int lind_noop (void);
int lind_getpid (pid_t * buf);
int lind_dup (int oldfd);
int lind_dup2 (int oldfd, int newfd);
int lind_getdents (int fd, size_t nbytes, char *buf);
int lind_fcntl_get (int fd, int cmd);
int lind_fcntl_set (int fd, int cmd, long set_op);
int lind_socket (int domain, int type, int protocol);
int lind_bind (int sockfd, socklen_t addrlen, const struct sockaddr *addr);
int lind_send (int sockfd, size_t len, int flags, const void *buf);
int lind_recv (int sockfd, size_t len, int flags, void *buf);
int lind_connect (int sockfd, socklen_t addrlen, const struct sockaddr *src_addr);
int lind_listen (int sockfd, int backlog);
int lind_sendto (int sockfd, size_t len, int flags, socklen_t addrlen, const struct sockaddr_in *dest_addr, const void *buf);
int lind_accept (int sockfd, socklen_t addrlen);
int lind_getpeername (int sockfd, socklen_t addrlen_in, __SOCKADDR_ARG addr, socklen_t * addrlen_out);
int lind_setsockopt (int sockfd, int level, int optname, socklen_t optlen, const void *optval);
int lind_getsockopt (int sockfd, int level, int optname, socklen_t optlen, void *optval);
int lind_shutdown (int sockfd, int how);
int lind_select (int nfds, fd_set * readfds, fd_set * writefds, fd_set * exceptfds, struct timeval *timeout, struct select_results *result);
int lind_getifaddrs (int ifaddrs_buf_siz, void *ifaddrs);
int lind_recvfrom (int sockfd, size_t len, int flags, socklen_t addrlen, socklen_t * addrlen_out, void *buf, struct sockaddr *src_addr);
int lind_poll (int nfds, int timeout, struct pollfd *fds_in, struct pollfd *fds_out);
int lind_socketpair (int domain, int type, int protocol, int *fds);
int lind_getuid (uid_t * buf);
int lind_geteuid (uid_t * buf);
int lind_getgid (gid_t * buf);
int lind_getegid (gid_t * buf);
int lind_flock (int fd, int operation);

#endif /* LIND_PLATFORM_H_ */
