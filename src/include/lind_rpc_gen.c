
/* This file is auto-generated! do not edit it manually!*/

#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <sys/poll.h>
#include "lind_rpc.h"
#include "lind_syscalls.h"
#include "strace.h"
#include "nacl_util.h"
#include "nacl_syscalls.h"
#include "component.h"
#include <nacl_stat.h>
#include <sys/statfs.h>
#include <sys/stat.h>
int lind_access_rpc(int version, const char * file);
int lind_unlink_rpc(const char * name);
int lind_link_rpc(const char * from, const char * to);
int lind_chdir_rpc(const char * name);
int lind_mkdir_rpc(int mode, const char * path);
int lind_rmdir_rpc(const char * path);
int lind_xstat_rpc(int version, const char * path, struct stat * buf);
int lind_open_rpc(int fd, int mode, const char * path);
int lind_close_rpc(int fd);
int lind_read_rpc(int fd, int size, void * buf);
int lind_write_rpc(int desc, size_t count, const void * buf);
int lind_lseek_rpc(off_t offset, int fd, int whence, off_t* ret);
int lind_fxstat_rpc(int fd, int version, struct stat * buf);
int lind_fstatfs_rpc(int fd, struct statfs * buf);
int lind_statfs_rpc(const char * path, struct statfs * buf);
int lind_noop_rpc(void);
int lind_getpid_rpc(pid_t * buf);
int lind_dup_rpc(int oldfd);
int lind_dup2_rpc(int oldfd, int newfd);
int lind_getdents_rpc(int fd, size_t nbytes, char * buf);
int lind_fcntl_get_rpc(int fd, int cmd);
int lind_fcntl_set_rpc(int fd, int cmd, long set_op);
int lind_socket_rpc(int domain, int type, int protocol);
int lind_bind_rpc(int sockfd, socklen_t addrlen, const struct sockaddr * addr);
int lind_send_rpc(int sockfd, size_t len, int flags, const void * buf);
int lind_recv_rpc(int sockfd, size_t len, int flags, void * buf);
int lind_connect_rpc(int sockfd, socklen_t addrlen, const struct sockaddr * src_addr);
int lind_listen_rpc(int sockfd, int backlog);
int lind_sendto_rpc(int sockfd, size_t len, int flags, socklen_t addrlen, const struct sockaddr_in * dest_addr, const void * buf);
int lind_accept_rpc(int sockfd, socklen_t addrlen);
int lind_getpeername_rpc(int sockfd, socklen_t addrlen_in, __SOCKADDR_ARG addr, socklen_t * addrlen_out);
int lind_setsockopt_rpc(int sockfd, int level, int optname, socklen_t optlen, const void * optval);
int lind_getsockopt_rpc(int sockfd, int level, int optname, socklen_t optlen, void * optval);
int lind_shutdown_rpc(int sockfd, int how);
int lind_select_rpc(int nfds, fd_set * readfds, fd_set * writefds, fd_set * exceptfds, struct timeval * timeout, struct select_results * result);
int lind_getifaddrs_rpc(int ifaddrs_buf_siz, void * ifaddrs);
int lind_recvfrom_rpc(int sockfd, size_t len, int flags, socklen_t addrlen, socklen_t* addrlen_out, void * buf, struct sockaddr * src_addr);
int lind_poll_rpc(int nfds, int timeout, struct pollfd * fds_in, struct pollfd * fds_out);
int lind_socketpair_rpc(int domain, int type, int protocol, int * fds);
int lind_getuid_rpc(uid_t * buf);
int lind_geteuid_rpc(uid_t * buf);
int lind_getgid_rpc(gid_t * buf);
int lind_getegid_rpc(gid_t * buf);
int lind_flock_rpc(int fd, int operation);
struct lind_access_rpc_s {
int version;
};

struct lind_unlink_rpc_s {
};

struct lind_link_rpc_s {
};

struct lind_chdir_rpc_s {
};

struct lind_mkdir_rpc_s {
int mode;
};

struct lind_rmdir_rpc_s {
};

struct lind_xstat_rpc_s {
int version;
};

struct lind_open_rpc_s {
int fd;
int mode;
};

struct lind_close_rpc_s {
int fd;
};

struct lind_read_rpc_s {
int fd;
int size;
};

struct lind_write_rpc_s {
int desc;
size_t count;
};

struct lind_lseek_rpc_s {
off_t offset;
int fd;
int whence;
};

struct lind_fxstat_rpc_s {
int fd;
int version;
};

struct lind_fstatfs_rpc_s {
int fd;
};

struct lind_statfs_rpc_s {
};

struct lind_noop_rpc_s {
};

struct lind_getpid_rpc_s {
};

struct lind_dup_rpc_s {
int oldfd;
};

struct lind_dup2_rpc_s {
int oldfd;
int newfd;
};

struct lind_getdents_rpc_s {
int fd;
size_t nbytes;
};

struct lind_fcntl_get_rpc_s {
int fd;
int cmd;
};

struct lind_fcntl_set_rpc_s {
int fd;
int cmd;
long set_op;
};

struct lind_socket_rpc_s {
int domain;
int type;
int protocol;
};

struct lind_bind_rpc_s {
int sockfd;
socklen_t addrlen;
};

struct lind_send_rpc_s {
int sockfd;
size_t len;
int flags;
};

struct lind_recv_rpc_s {
int sockfd;
size_t len;
int flags;
};

struct lind_connect_rpc_s {
int sockfd;
socklen_t addrlen;
};

struct lind_listen_rpc_s {
int sockfd;
int backlog;
};

struct lind_accept_rpc_s {
int sockfd;
socklen_t addrlen;
};

struct lind_setsockopt_rpc_s {
int sockfd;
int level;
int optname;
socklen_t optlen;
};

struct lind_getsockopt_rpc_s {
int sockfd;
int level;
int optname;
socklen_t optlen;
};

struct lind_shutdown_rpc_s {
int sockfd;
int how;
};

struct lind_select_rpc_s {
int nfds;
};

struct lind_getifaddrs_rpc_s {
int ifaddrs_buf_siz;
};

struct lind_recvfrom_rpc_s {
int sockfd;
size_t len;
int flags;
socklen_t addrlen;
};

struct lind_poll_rpc_s {
int nfds;
int timeout;
};

struct lind_socketpair_rpc_s {
int domain;
int type;
int protocol;
};

struct lind_getuid_rpc_s {
};

struct lind_geteuid_rpc_s {
};

struct lind_getgid_rpc_s {
};

struct lind_getegid_rpc_s {
};

struct lind_flock_rpc_s {
int fd;
int operation;
};

/* This file is auto-generated! do not edit it manually!*/

int lind_access_rpc(int version, const char * file) {
lind_request request;
memset(&request, 0, sizeof(request));
int return_code = -1;
size_t reply_size = 0 + sizeof(lind_reply);
lind_reply* reply_buffer = malloc(reply_size);
assert(reply_buffer!=NULL);
/* These memsets are mainly for saftey.*/
memset(reply_buffer, 0, reply_size);
struct lind_access_rpc_s args;
memset(&args, 0, sizeof(struct lind_access_rpc_s));
nacl_strace("lind_access_rpc\n");
args.version = version;
// check if file is NULL
int file_is_null = 0;
if (file == NULL) {
file_is_null = 1;
} else {
file_is_null = 0;
}
unsigned long int nowhere = 0;
ssize_t file_ssize = strlen(file);
const char * strlenfile_file_len_str = "YYY";
const char * file_fmt_str = "ZZZ";
void * file_ptr = NULL;
ssize_t file_data_size = -1;
if (file_is_null) {
file_ptr = &nowhere;
file_fmt_str =  "P";
strlenfile_file_len_str = "";
file_data_size = sizeof (void *);
} else {
file_ptr = (void*)file;
file_fmt_str =  "s"; // if it is not null, treat as a string
strlenfile_file_len_str =  nacl_itoa(file_ssize);
file_data_size = file_ssize;
}
assert( file_ptr != NULL );
assert( file_data_size != -1 );
assert( strcmp(strlenfile_file_len_str, "YYY") != 0 );
assert( strcmp(file_fmt_str, "ZZZ") != 0 );
request.format = combine(4, "", "<i" , strlenfile_file_len_str, file_fmt_str);
request.call_number = 2;
if (! file_is_null) {
free((void*)strlenfile_file_len_str);
}
request.message.len = sizeof(struct lind_access_rpc_s);
request.message.body = &args;
nacl_rpc_syscall_proxy(&request, reply_buffer,1, file_ptr, file_data_size);
/* on error return negative so we can set ERRNO. */
if (reply_buffer->is_error) {
return_code = reply_buffer->return_code * -1;
} else {
return_code = reply_buffer->return_code;
}
free(reply_buffer);
return return_code;
}
/* This file is auto-generated! do not edit it manually!*/

int lind_unlink_rpc(const char * name) {
lind_request request;
memset(&request, 0, sizeof(request));
int return_code = -1;
size_t reply_size = 0 + sizeof(lind_reply);
lind_reply* reply_buffer = malloc(reply_size);
assert(reply_buffer!=NULL);
/* These memsets are mainly for saftey.*/
memset(reply_buffer, 0, reply_size);
struct lind_unlink_rpc_s args;
memset(&args, 0, sizeof(struct lind_unlink_rpc_s));
nacl_strace("lind_unlink_rpc\n");
// check if name is NULL
int name_is_null = 0;
if (name == NULL) {
name_is_null = 1;
} else {
name_is_null = 0;
}
unsigned long int nowhere = 0;
ssize_t name_ssize = strlen(name);
const char * strlenname_name_len_str = "YYY";
const char * name_fmt_str = "ZZZ";
void * name_ptr = NULL;
ssize_t name_data_size = -1;
if (name_is_null) {
name_ptr = &nowhere;
name_fmt_str =  "P";
strlenname_name_len_str = "";
name_data_size = sizeof (void *);
} else {
name_ptr = (void*)name;
name_fmt_str =  "s"; // if it is not null, treat as a string
strlenname_name_len_str =  nacl_itoa(name_ssize);
name_data_size = name_ssize;
}
assert( name_ptr != NULL );
assert( name_data_size != -1 );
assert( strcmp(strlenname_name_len_str, "YYY") != 0 );
assert( strcmp(name_fmt_str, "ZZZ") != 0 );
request.format = combine(3, "", strlenname_name_len_str, name_fmt_str);
request.call_number = 4;
if (! name_is_null) {
free((void*)strlenname_name_len_str);
}
request.message.len = sizeof(struct lind_unlink_rpc_s);
request.message.body = &args;
nacl_rpc_syscall_proxy(&request, reply_buffer,1, name_ptr, name_data_size);
/* on error return negative so we can set ERRNO. */
if (reply_buffer->is_error) {
return_code = reply_buffer->return_code * -1;
} else {
return_code = reply_buffer->return_code;
}
free(reply_buffer);
return return_code;
}
/* This file is auto-generated! do not edit it manually!*/

int lind_link_rpc(const char * from, const char * to) {
lind_request request;
memset(&request, 0, sizeof(request));
int return_code = -1;
size_t reply_size = 0 + sizeof(lind_reply);
lind_reply* reply_buffer = malloc(reply_size);
assert(reply_buffer!=NULL);
/* These memsets are mainly for saftey.*/
memset(reply_buffer, 0, reply_size);
struct lind_link_rpc_s args;
memset(&args, 0, sizeof(struct lind_link_rpc_s));
nacl_strace("lind_link_rpc\n");
// check if from is NULL
int from_is_null = 0;
if (from == NULL) {
from_is_null = 1;
} else {
from_is_null = 0;
}
unsigned long int nowhere = 0;
ssize_t from_ssize = strlen(from);
const char * strlenfrom_from_len_str = "YYY";
const char * from_fmt_str = "ZZZ";
void * from_ptr = NULL;
ssize_t from_data_size = -1;
if (from_is_null) {
from_ptr = &nowhere;
from_fmt_str =  "P";
strlenfrom_from_len_str = "";
from_data_size = sizeof (void *);
} else {
from_ptr = (void*)from;
from_fmt_str =  "s"; // if it is not null, treat as a string
strlenfrom_from_len_str =  nacl_itoa(from_ssize);
from_data_size = from_ssize;
}
assert( from_ptr != NULL );
assert( from_data_size != -1 );
assert( strcmp(strlenfrom_from_len_str, "YYY") != 0 );
assert( strcmp(from_fmt_str, "ZZZ") != 0 );
// check if to is NULL
int to_is_null = 0;
if (to == NULL) {
to_is_null = 1;
} else {
to_is_null = 0;
}
ssize_t to_ssize = strlen(to);
const char * strlento_to_len_str = "YYY";
const char * to_fmt_str = "ZZZ";
void * to_ptr = NULL;
ssize_t to_data_size = -1;
if (to_is_null) {
to_ptr = &nowhere;
to_fmt_str =  "P";
strlento_to_len_str = "";
to_data_size = sizeof (void *);
} else {
to_ptr = (void*)to;
to_fmt_str =  "s"; // if it is not null, treat as a string
strlento_to_len_str =  nacl_itoa(to_ssize);
to_data_size = to_ssize;
}
assert( to_ptr != NULL );
assert( to_data_size != -1 );
assert( strcmp(strlento_to_len_str, "YYY") != 0 );
assert( strcmp(to_fmt_str, "ZZZ") != 0 );
request.format = combine(5, "", strlenfrom_from_len_str, from_fmt_str, strlento_to_len_str, to_fmt_str);
request.call_number = 5;
if (! from_is_null) {
free((void*)strlenfrom_from_len_str);
}
if (! to_is_null) {
free((void*)strlento_to_len_str);
}
request.message.len = sizeof(struct lind_link_rpc_s);
request.message.body = &args;
nacl_rpc_syscall_proxy(&request, reply_buffer,2, from_ptr, from_data_size, to_ptr, to_data_size);
/* on error return negative so we can set ERRNO. */
if (reply_buffer->is_error) {
return_code = reply_buffer->return_code * -1;
} else {
return_code = reply_buffer->return_code;
}
free(reply_buffer);
return return_code;
}
/* This file is auto-generated! do not edit it manually!*/

int lind_chdir_rpc(const char * name) {
lind_request request;
memset(&request, 0, sizeof(request));
int return_code = -1;
size_t reply_size = 0 + sizeof(lind_reply);
lind_reply* reply_buffer = malloc(reply_size);
assert(reply_buffer!=NULL);
/* These memsets are mainly for saftey.*/
memset(reply_buffer, 0, reply_size);
struct lind_chdir_rpc_s args;
memset(&args, 0, sizeof(struct lind_chdir_rpc_s));
nacl_strace("lind_chdir_rpc\n");
// check if name is NULL
int name_is_null = 0;
if (name == NULL) {
name_is_null = 1;
} else {
name_is_null = 0;
}
unsigned long int nowhere = 0;
ssize_t name_ssize = strlen(name);
const char * strlenname_name_len_str = "YYY";
const char * name_fmt_str = "ZZZ";
void * name_ptr = NULL;
ssize_t name_data_size = -1;
if (name_is_null) {
name_ptr = &nowhere;
name_fmt_str =  "P";
strlenname_name_len_str = "";
name_data_size = sizeof (void *);
} else {
name_ptr = (void*)name;
name_fmt_str =  "s"; // if it is not null, treat as a string
strlenname_name_len_str =  nacl_itoa(name_ssize);
name_data_size = name_ssize;
}
assert( name_ptr != NULL );
assert( name_data_size != -1 );
assert( strcmp(strlenname_name_len_str, "YYY") != 0 );
assert( strcmp(name_fmt_str, "ZZZ") != 0 );
request.format = combine(3, "", strlenname_name_len_str, name_fmt_str);
request.call_number = 6;
if (! name_is_null) {
free((void*)strlenname_name_len_str);
}
request.message.len = sizeof(struct lind_chdir_rpc_s);
request.message.body = &args;
nacl_rpc_syscall_proxy(&request, reply_buffer,1, name_ptr, name_data_size);
/* on error return negative so we can set ERRNO. */
if (reply_buffer->is_error) {
return_code = reply_buffer->return_code * -1;
} else {
return_code = reply_buffer->return_code;
}
free(reply_buffer);
return return_code;
}
/* This file is auto-generated! do not edit it manually!*/

int lind_mkdir_rpc(int mode, const char * path) {
lind_request request;
memset(&request, 0, sizeof(request));
int return_code = -1;
size_t reply_size = 0 + sizeof(lind_reply);
lind_reply* reply_buffer = malloc(reply_size);
assert(reply_buffer!=NULL);
/* These memsets are mainly for saftey.*/
memset(reply_buffer, 0, reply_size);
struct lind_mkdir_rpc_s args;
memset(&args, 0, sizeof(struct lind_mkdir_rpc_s));
nacl_strace("lind_mkdir_rpc\n");
args.mode = mode;
// check if path is NULL
int path_is_null = 0;
if (path == NULL) {
path_is_null = 1;
} else {
path_is_null = 0;
}
unsigned long int nowhere = 0;
ssize_t path_ssize = strlen(path);
const char * strlenpath_path_len_str = "YYY";
const char * path_fmt_str = "ZZZ";
void * path_ptr = NULL;
ssize_t path_data_size = -1;
if (path_is_null) {
path_ptr = &nowhere;
path_fmt_str =  "P";
strlenpath_path_len_str = "";
path_data_size = sizeof (void *);
} else {
path_ptr = (void*)path;
path_fmt_str =  "s"; // if it is not null, treat as a string
strlenpath_path_len_str =  nacl_itoa(path_ssize);
path_data_size = path_ssize;
}
assert( path_ptr != NULL );
assert( path_data_size != -1 );
assert( strcmp(strlenpath_path_len_str, "YYY") != 0 );
assert( strcmp(path_fmt_str, "ZZZ") != 0 );
request.format = combine(4, "", "<i" , strlenpath_path_len_str, path_fmt_str);
request.call_number = 7;
if (! path_is_null) {
free((void*)strlenpath_path_len_str);
}
request.message.len = sizeof(struct lind_mkdir_rpc_s);
request.message.body = &args;
nacl_rpc_syscall_proxy(&request, reply_buffer,1, path_ptr, path_data_size);
/* on error return negative so we can set ERRNO. */
if (reply_buffer->is_error) {
return_code = reply_buffer->return_code * -1;
} else {
return_code = reply_buffer->return_code;
}
free(reply_buffer);
return return_code;
}
/* This file is auto-generated! do not edit it manually!*/

int lind_rmdir_rpc(const char * path) {
lind_request request;
memset(&request, 0, sizeof(request));
int return_code = -1;
size_t reply_size = 0 + sizeof(lind_reply);
lind_reply* reply_buffer = malloc(reply_size);
assert(reply_buffer!=NULL);
/* These memsets are mainly for saftey.*/
memset(reply_buffer, 0, reply_size);
struct lind_rmdir_rpc_s args;
memset(&args, 0, sizeof(struct lind_rmdir_rpc_s));
nacl_strace("lind_rmdir_rpc\n");
// check if path is NULL
int path_is_null = 0;
if (path == NULL) {
path_is_null = 1;
} else {
path_is_null = 0;
}
unsigned long int nowhere = 0;
ssize_t path_ssize = strlen(path);
const char * strlenpath_path_len_str = "YYY";
const char * path_fmt_str = "ZZZ";
void * path_ptr = NULL;
ssize_t path_data_size = -1;
if (path_is_null) {
path_ptr = &nowhere;
path_fmt_str =  "P";
strlenpath_path_len_str = "";
path_data_size = sizeof (void *);
} else {
path_ptr = (void*)path;
path_fmt_str =  "s"; // if it is not null, treat as a string
strlenpath_path_len_str =  nacl_itoa(path_ssize);
path_data_size = path_ssize;
}
assert( path_ptr != NULL );
assert( path_data_size != -1 );
assert( strcmp(strlenpath_path_len_str, "YYY") != 0 );
assert( strcmp(path_fmt_str, "ZZZ") != 0 );
request.format = combine(3, "", strlenpath_path_len_str, path_fmt_str);
request.call_number = 8;
if (! path_is_null) {
free((void*)strlenpath_path_len_str);
}
request.message.len = sizeof(struct lind_rmdir_rpc_s);
request.message.body = &args;
nacl_rpc_syscall_proxy(&request, reply_buffer,1, path_ptr, path_data_size);
/* on error return negative so we can set ERRNO. */
if (reply_buffer->is_error) {
return_code = reply_buffer->return_code * -1;
} else {
return_code = reply_buffer->return_code;
}
free(reply_buffer);
return return_code;
}
/* This file is auto-generated! do not edit it manually!*/

int lind_xstat_rpc(int version, const char * path, struct stat * buf) {
lind_request request;
memset(&request, 0, sizeof(request));
int return_code = -1;
size_t reply_size = sizeof(struct stat) + sizeof(lind_reply);
lind_reply* reply_buffer = malloc(reply_size);
assert(reply_buffer!=NULL);
/* These memsets are mainly for saftey.*/
memset(reply_buffer, 0, reply_size);
struct lind_xstat_rpc_s args;
memset(&args, 0, sizeof(struct lind_xstat_rpc_s));
nacl_strace("lind_xstat_rpc\n");
args.version = version;
// check if path is NULL
int path_is_null = 0;
if (path == NULL) {
path_is_null = 1;
} else {
path_is_null = 0;
}
unsigned long int nowhere = 0;
ssize_t path_ssize = strlen(path);
const char * strlenpath_path_len_str = "YYY";
const char * path_fmt_str = "ZZZ";
void * path_ptr = NULL;
ssize_t path_data_size = -1;
if (path_is_null) {
path_ptr = &nowhere;
path_fmt_str =  "P";
strlenpath_path_len_str = "";
path_data_size = sizeof (void *);
} else {
path_ptr = (void*)path;
path_fmt_str =  "s"; // if it is not null, treat as a string
strlenpath_path_len_str =  nacl_itoa(path_ssize);
path_data_size = path_ssize;
}
assert( path_ptr != NULL );
assert( path_data_size != -1 );
assert( strcmp(strlenpath_path_len_str, "YYY") != 0 );
assert( strcmp(path_fmt_str, "ZZZ") != 0 );
request.format = combine(4, "", "<i" , strlenpath_path_len_str, path_fmt_str);
request.call_number = 9;
if (! path_is_null) {
free((void*)strlenpath_path_len_str);
}
request.message.len = sizeof(struct lind_xstat_rpc_s);
request.message.body = &args;
nacl_rpc_syscall_proxy(&request, reply_buffer,1, path_ptr, path_data_size);
/* on error return negative so we can set ERRNO. */
if (reply_buffer->is_error) {
return_code = reply_buffer->return_code * -1;
} else {
return_code = reply_buffer->return_code;
assert( CONTENTS_SIZ(reply_buffer) <= sizeof(struct stat));
void * ptr = NULL;
ptr = buf;
if (ptr != NULL) { memcpy(ptr, ((&(reply_buffer->contents)) + 0), sizeof(struct stat)); }
}
free(reply_buffer);
return return_code;
}
/* This file is auto-generated! do not edit it manually!*/

int lind_open_rpc(int fd, int mode, const char * path) {
lind_request request;
memset(&request, 0, sizeof(request));
int return_code = -1;
size_t reply_size = 0 + sizeof(lind_reply);
lind_reply* reply_buffer = malloc(reply_size);
assert(reply_buffer!=NULL);
/* These memsets are mainly for saftey.*/
memset(reply_buffer, 0, reply_size);
struct lind_open_rpc_s args;
memset(&args, 0, sizeof(struct lind_open_rpc_s));
nacl_strace("lind_open_rpc\n");
args.fd = fd;
args.mode = mode;
// check if path is NULL
int path_is_null = 0;
if (path == NULL) {
path_is_null = 1;
} else {
path_is_null = 0;
}
unsigned long int nowhere = 0;
ssize_t path_ssize = strlen(path);
const char * strlenpath_path_len_str = "YYY";
const char * path_fmt_str = "ZZZ";
void * path_ptr = NULL;
ssize_t path_data_size = -1;
if (path_is_null) {
path_ptr = &nowhere;
path_fmt_str =  "P";
strlenpath_path_len_str = "";
path_data_size = sizeof (void *);
} else {
path_ptr = (void*)path;
path_fmt_str =  "s"; // if it is not null, treat as a string
strlenpath_path_len_str =  nacl_itoa(path_ssize);
path_data_size = path_ssize;
}
assert( path_ptr != NULL );
assert( path_data_size != -1 );
assert( strcmp(strlenpath_path_len_str, "YYY") != 0 );
assert( strcmp(path_fmt_str, "ZZZ") != 0 );
request.format = combine(5, "", "<i" , "<i" , strlenpath_path_len_str, path_fmt_str);
request.call_number = 10;
if (! path_is_null) {
free((void*)strlenpath_path_len_str);
}
request.message.len = sizeof(struct lind_open_rpc_s);
request.message.body = &args;
nacl_rpc_syscall_proxy(&request, reply_buffer,1, path_ptr, path_data_size);
/* on error return negative so we can set ERRNO. */
if (reply_buffer->is_error) {
return_code = reply_buffer->return_code * -1;
} else {
return_code = reply_buffer->return_code;
}
free(reply_buffer);
return return_code;
}
/* This file is auto-generated! do not edit it manually!*/

int lind_close_rpc(int fd) {
lind_request request;
memset(&request, 0, sizeof(request));
int return_code = -1;
size_t reply_size = 0 + sizeof(lind_reply);
lind_reply* reply_buffer = malloc(reply_size);
assert(reply_buffer!=NULL);
/* These memsets are mainly for saftey.*/
memset(reply_buffer, 0, reply_size);
struct lind_close_rpc_s args;
memset(&args, 0, sizeof(struct lind_close_rpc_s));
nacl_strace("lind_close_rpc\n");
args.fd = fd;
request.format = """<i" ;
request.call_number = 11;
request.message.len = sizeof(struct lind_close_rpc_s);
request.message.body = &args;
nacl_rpc_syscall_proxy(&request, reply_buffer,0);
/* on error return negative so we can set ERRNO. */
if (reply_buffer->is_error) {
return_code = reply_buffer->return_code * -1;
} else {
return_code = reply_buffer->return_code;
}
free(reply_buffer);
return return_code;
}
/* This file is auto-generated! do not edit it manually!*/

int lind_read_rpc(int fd, int size, void * buf) {
lind_request request;
memset(&request, 0, sizeof(request));
int return_code = -1;
size_t reply_size = size + sizeof(lind_reply);
lind_reply* reply_buffer = malloc(reply_size);
assert(reply_buffer!=NULL);
/* These memsets are mainly for saftey.*/
memset(reply_buffer, 0, reply_size);
struct lind_read_rpc_s args;
memset(&args, 0, sizeof(struct lind_read_rpc_s));
nacl_strace("lind_read_rpc\n");
args.fd = fd;
args.size = size;
request.format = """<i" "<i" ;
request.call_number = 12;
request.message.len = sizeof(struct lind_read_rpc_s);
request.message.body = &args;
nacl_rpc_syscall_proxy(&request, reply_buffer,0);
/* on error return negative so we can set ERRNO. */
if (reply_buffer->is_error) {
return_code = reply_buffer->return_code * -1;
} else {
return_code = reply_buffer->return_code;
assert( CONTENTS_SIZ(reply_buffer) <= size);
void * ptr = NULL;
ptr = buf;
if (ptr != NULL) { memcpy(ptr, ((&(reply_buffer->contents)) + 0), size); }
}
free(reply_buffer);
return return_code;
}
/* This file is auto-generated! do not edit it manually!*/

int lind_write_rpc(int desc, size_t count, const void * buf) {
lind_request request;
memset(&request, 0, sizeof(request));
int return_code = -1;
size_t reply_size = 0 + sizeof(lind_reply);
lind_reply* reply_buffer = malloc(reply_size);
assert(reply_buffer!=NULL);
/* These memsets are mainly for saftey.*/
memset(reply_buffer, 0, reply_size);
struct lind_write_rpc_s args;
memset(&args, 0, sizeof(struct lind_write_rpc_s));
nacl_strace("lind_write_rpc\n");
args.desc = desc;
args.count = count;
// check if buf is NULL
int buf_is_null = 0;
if (buf == NULL) {
buf_is_null = 1;
} else {
buf_is_null = 0;
}
unsigned long int nowhere = 0;
ssize_t buf_ssize = count;
const char * count_buf_len_str = "YYY";
const char * buf_fmt_str = "ZZZ";
void * buf_ptr = NULL;
ssize_t buf_data_size = -1;
if (buf_is_null) {
buf_ptr = &nowhere;
buf_fmt_str =  "P";
count_buf_len_str = "";
buf_data_size = sizeof (void *);
} else {
buf_ptr = (void*)buf;
buf_fmt_str =  "s"; // if it is not null, treat as a string
count_buf_len_str =  nacl_itoa(buf_ssize);
buf_data_size = buf_ssize;
}
assert( buf_ptr != NULL );
assert( buf_data_size != -1 );
assert( strcmp(count_buf_len_str, "YYY") != 0 );
assert( strcmp(buf_fmt_str, "ZZZ") != 0 );
request.format = combine(5, "", "<i" , "<I" , count_buf_len_str, buf_fmt_str);
request.call_number = 13;
if (! buf_is_null) {
free((void*)count_buf_len_str);
}
request.message.len = sizeof(struct lind_write_rpc_s);
request.message.body = &args;
nacl_rpc_syscall_proxy(&request, reply_buffer,1, buf_ptr, buf_data_size);
/* on error return negative so we can set ERRNO. */
if (reply_buffer->is_error) {
return_code = reply_buffer->return_code * -1;
} else {
return_code = reply_buffer->return_code;
}
free(reply_buffer);
return return_code;
}
/* This file is auto-generated! do not edit it manually!*/

int lind_lseek_rpc(off_t offset, int fd, int whence, off_t* ret) {
lind_request request;
memset(&request, 0, sizeof(request));
int return_code = -1;
size_t reply_size = sizeof(off_t) + sizeof(lind_reply);
lind_reply* reply_buffer = malloc(reply_size);
assert(reply_buffer!=NULL);
/* These memsets are mainly for saftey.*/
memset(reply_buffer, 0, reply_size);
struct lind_lseek_rpc_s args;
memset(&args, 0, sizeof(struct lind_lseek_rpc_s));
nacl_strace("lind_lseek_rpc\n");
args.offset = offset;
args.fd = fd;
args.whence = whence;
request.format = """<q" "<i" "<i" ;
request.call_number = 14;
request.message.len = sizeof(struct lind_lseek_rpc_s);
request.message.body = &args;
nacl_rpc_syscall_proxy(&request, reply_buffer,0);
/* on error return negative so we can set ERRNO. */
if (reply_buffer->is_error) {
return_code = reply_buffer->return_code * -1;
} else {
return_code = reply_buffer->return_code;
assert( CONTENTS_SIZ(reply_buffer) <= sizeof(off_t));
void * ptr = NULL;
ptr = ret;
if (ptr != NULL) { memcpy(ptr, ((&(reply_buffer->contents)) + 0), sizeof(off_t)); }
}
free(reply_buffer);
return return_code;
}
/* This file is auto-generated! do not edit it manually!*/

int lind_fxstat_rpc(int fd, int version, struct stat * buf) {
lind_request request;
memset(&request, 0, sizeof(request));
int return_code = -1;
size_t reply_size = sizeof(struct stat) + sizeof(lind_reply);
lind_reply* reply_buffer = malloc(reply_size);
assert(reply_buffer!=NULL);
/* These memsets are mainly for saftey.*/
memset(reply_buffer, 0, reply_size);
struct lind_fxstat_rpc_s args;
memset(&args, 0, sizeof(struct lind_fxstat_rpc_s));
nacl_strace("lind_fxstat_rpc\n");
args.fd = fd;
args.version = version;
request.format = """<i" "<i" ;
request.call_number = 17;
request.message.len = sizeof(struct lind_fxstat_rpc_s);
request.message.body = &args;
nacl_rpc_syscall_proxy(&request, reply_buffer,0);
/* on error return negative so we can set ERRNO. */
if (reply_buffer->is_error) {
return_code = reply_buffer->return_code * -1;
} else {
return_code = reply_buffer->return_code;
assert( CONTENTS_SIZ(reply_buffer) <= sizeof(struct stat));
void * ptr = NULL;
ptr = buf;
if (ptr != NULL) { memcpy(ptr, ((&(reply_buffer->contents)) + 0), sizeof(struct stat)); }
}
free(reply_buffer);
return return_code;
}
/* This file is auto-generated! do not edit it manually!*/

int lind_fstatfs_rpc(int fd, struct statfs * buf) {
lind_request request;
memset(&request, 0, sizeof(request));
int return_code = -1;
size_t reply_size = sizeof(struct statfs) + sizeof(lind_reply);
lind_reply* reply_buffer = malloc(reply_size);
assert(reply_buffer!=NULL);
/* These memsets are mainly for saftey.*/
memset(reply_buffer, 0, reply_size);
struct lind_fstatfs_rpc_s args;
memset(&args, 0, sizeof(struct lind_fstatfs_rpc_s));
nacl_strace("lind_fstatfs_rpc\n");
args.fd = fd;
request.format = """<i" ;
request.call_number = 19;
request.message.len = sizeof(struct lind_fstatfs_rpc_s);
request.message.body = &args;
nacl_rpc_syscall_proxy(&request, reply_buffer,0);
/* on error return negative so we can set ERRNO. */
if (reply_buffer->is_error) {
return_code = reply_buffer->return_code * -1;
} else {
return_code = reply_buffer->return_code;
assert( CONTENTS_SIZ(reply_buffer) <= sizeof(struct statfs));
void * ptr = NULL;
ptr = buf;
if (ptr != NULL) { memcpy(ptr, ((&(reply_buffer->contents)) + 0), sizeof(struct statfs)); }
}
free(reply_buffer);
return return_code;
}
/* This file is auto-generated! do not edit it manually!*/

int lind_statfs_rpc(const char * path, struct statfs * buf) {
lind_request request;
memset(&request, 0, sizeof(request));
int return_code = -1;
size_t reply_size = sizeof(struct statfs) + sizeof(lind_reply);
lind_reply* reply_buffer = malloc(reply_size);
assert(reply_buffer!=NULL);
/* These memsets are mainly for saftey.*/
memset(reply_buffer, 0, reply_size);
struct lind_statfs_rpc_s args;
memset(&args, 0, sizeof(struct lind_statfs_rpc_s));
nacl_strace("lind_statfs_rpc\n");
// check if path is NULL
int path_is_null = 0;
if (path == NULL) {
path_is_null = 1;
} else {
path_is_null = 0;
}
unsigned long int nowhere = 0;
ssize_t path_ssize = strlen(path);
const char * strlenpath_path_len_str = "YYY";
const char * path_fmt_str = "ZZZ";
void * path_ptr = NULL;
ssize_t path_data_size = -1;
if (path_is_null) {
path_ptr = &nowhere;
path_fmt_str =  "P";
strlenpath_path_len_str = "";
path_data_size = sizeof (void *);
} else {
path_ptr = (void*)path;
path_fmt_str =  "s"; // if it is not null, treat as a string
strlenpath_path_len_str =  nacl_itoa(path_ssize);
path_data_size = path_ssize;
}
assert( path_ptr != NULL );
assert( path_data_size != -1 );
assert( strcmp(strlenpath_path_len_str, "YYY") != 0 );
assert( strcmp(path_fmt_str, "ZZZ") != 0 );
request.format = combine(3, "", strlenpath_path_len_str, path_fmt_str);
request.call_number = 26;
if (! path_is_null) {
free((void*)strlenpath_path_len_str);
}
request.message.len = sizeof(struct lind_statfs_rpc_s);
request.message.body = &args;
nacl_rpc_syscall_proxy(&request, reply_buffer,1, path_ptr, path_data_size);
/* on error return negative so we can set ERRNO. */
if (reply_buffer->is_error) {
return_code = reply_buffer->return_code * -1;
} else {
return_code = reply_buffer->return_code;
assert( CONTENTS_SIZ(reply_buffer) <= sizeof(struct statfs));
void * ptr = NULL;
ptr = buf;
if (ptr != NULL) { memcpy(ptr, ((&(reply_buffer->contents)) + 0), sizeof(struct statfs)); }
}
free(reply_buffer);
return return_code;
}
/* This file is auto-generated! do not edit it manually!*/

int lind_noop_rpc(void) {
lind_request request;
memset(&request, 0, sizeof(request));
int return_code = -1;
size_t reply_size = 0 + sizeof(lind_reply);
lind_reply* reply_buffer = malloc(reply_size);
assert(reply_buffer!=NULL);
/* These memsets are mainly for saftey.*/
memset(reply_buffer, 0, reply_size);
struct lind_noop_rpc_s args;
memset(&args, 0, sizeof(struct lind_noop_rpc_s));
nacl_strace("lind_noop_rpc\n");
request.format = "";
request.call_number = 1;
request.message.len = sizeof(struct lind_noop_rpc_s);
request.message.body = &args;
nacl_rpc_syscall_proxy(&request, reply_buffer,0);
/* on error return negative so we can set ERRNO. */
if (reply_buffer->is_error) {
return_code = reply_buffer->return_code * -1;
} else {
return_code = reply_buffer->return_code;
}
free(reply_buffer);
return return_code;
}
/* This file is auto-generated! do not edit it manually!*/

int lind_getpid_rpc(pid_t * buf) {
lind_request request;
memset(&request, 0, sizeof(request));
int return_code = -1;
size_t reply_size = sizeof(pid_t) + sizeof(lind_reply);
lind_reply* reply_buffer = malloc(reply_size);
assert(reply_buffer!=NULL);
/* These memsets are mainly for saftey.*/
memset(reply_buffer, 0, reply_size);
struct lind_getpid_rpc_s args;
memset(&args, 0, sizeof(struct lind_getpid_rpc_s));
nacl_strace("lind_getpid_rpc\n");
request.format = "";
request.call_number = 31;
request.message.len = sizeof(struct lind_getpid_rpc_s);
request.message.body = &args;
nacl_rpc_syscall_proxy(&request, reply_buffer,0);
/* on error return negative so we can set ERRNO. */
if (reply_buffer->is_error) {
return_code = reply_buffer->return_code * -1;
} else {
return_code = reply_buffer->return_code;
assert( CONTENTS_SIZ(reply_buffer) <= sizeof(pid_t));
void * ptr = NULL;
ptr = buf;
if (ptr != NULL) { memcpy(ptr, ((&(reply_buffer->contents)) + 0), sizeof(pid_t)); }
}
free(reply_buffer);
return return_code;
}
/* This file is auto-generated! do not edit it manually!*/

int lind_dup_rpc(int oldfd) {
lind_request request;
memset(&request, 0, sizeof(request));
int return_code = -1;
size_t reply_size = 0 + sizeof(lind_reply);
lind_reply* reply_buffer = malloc(reply_size);
assert(reply_buffer!=NULL);
/* These memsets are mainly for saftey.*/
memset(reply_buffer, 0, reply_size);
struct lind_dup_rpc_s args;
memset(&args, 0, sizeof(struct lind_dup_rpc_s));
nacl_strace("lind_dup_rpc\n");
args.oldfd = oldfd;
request.format = """<i" ;
request.call_number = 24;
request.message.len = sizeof(struct lind_dup_rpc_s);
request.message.body = &args;
nacl_rpc_syscall_proxy(&request, reply_buffer,0);
/* on error return negative so we can set ERRNO. */
if (reply_buffer->is_error) {
return_code = reply_buffer->return_code * -1;
} else {
return_code = reply_buffer->return_code;
}
free(reply_buffer);
return return_code;
}
/* This file is auto-generated! do not edit it manually!*/

int lind_dup2_rpc(int oldfd, int newfd) {
lind_request request;
memset(&request, 0, sizeof(request));
int return_code = -1;
size_t reply_size = 0 + sizeof(lind_reply);
lind_reply* reply_buffer = malloc(reply_size);
assert(reply_buffer!=NULL);
/* These memsets are mainly for saftey.*/
memset(reply_buffer, 0, reply_size);
struct lind_dup2_rpc_s args;
memset(&args, 0, sizeof(struct lind_dup2_rpc_s));
nacl_strace("lind_dup2_rpc\n");
args.oldfd = oldfd;
args.newfd = newfd;
request.format = """<i" "<i" ;
request.call_number = 25;
request.message.len = sizeof(struct lind_dup2_rpc_s);
request.message.body = &args;
nacl_rpc_syscall_proxy(&request, reply_buffer,0);
/* on error return negative so we can set ERRNO. */
if (reply_buffer->is_error) {
return_code = reply_buffer->return_code * -1;
} else {
return_code = reply_buffer->return_code;
}
free(reply_buffer);
return return_code;
}
/* This file is auto-generated! do not edit it manually!*/

int lind_getdents_rpc(int fd, size_t nbytes, char * buf) {
lind_request request;
memset(&request, 0, sizeof(request));
int return_code = -1;
size_t reply_size = nbytes + sizeof(lind_reply);
lind_reply* reply_buffer = malloc(reply_size);
assert(reply_buffer!=NULL);
/* These memsets are mainly for saftey.*/
memset(reply_buffer, 0, reply_size);
struct lind_getdents_rpc_s args;
memset(&args, 0, sizeof(struct lind_getdents_rpc_s));
nacl_strace("lind_getdents_rpc\n");
args.fd = fd;
args.nbytes = nbytes;
request.format = """<i" "<I" ;
request.call_number = 23;
request.message.len = sizeof(struct lind_getdents_rpc_s);
request.message.body = &args;
nacl_rpc_syscall_proxy(&request, reply_buffer,0);
/* on error return negative so we can set ERRNO. */
if (reply_buffer->is_error) {
return_code = reply_buffer->return_code * -1;
} else {
return_code = reply_buffer->return_code;
assert( CONTENTS_SIZ(reply_buffer) <= nbytes);
void * ptr = NULL;
ptr = buf;
if (ptr != NULL) { memcpy(ptr, ((&(reply_buffer->contents)) + 0), nbytes); }
}
free(reply_buffer);
return return_code;
}
/* This file is auto-generated! do not edit it manually!*/

int lind_fcntl_get_rpc(int fd, int cmd) {
lind_request request;
memset(&request, 0, sizeof(request));
int return_code = -1;
size_t reply_size = 0 + sizeof(lind_reply);
lind_reply* reply_buffer = malloc(reply_size);
assert(reply_buffer!=NULL);
/* These memsets are mainly for saftey.*/
memset(reply_buffer, 0, reply_size);
struct lind_fcntl_get_rpc_s args;
memset(&args, 0, sizeof(struct lind_fcntl_get_rpc_s));
nacl_strace("lind_fcntl_get_rpc\n");
args.fd = fd;
args.cmd = cmd;
request.format = """<i" "<i" ;
request.call_number = 28;
request.message.len = sizeof(struct lind_fcntl_get_rpc_s);
request.message.body = &args;
nacl_rpc_syscall_proxy(&request, reply_buffer,0);
/* on error return negative so we can set ERRNO. */
if (reply_buffer->is_error) {
return_code = reply_buffer->return_code * -1;
} else {
return_code = reply_buffer->return_code;
}
free(reply_buffer);
return return_code;
}
/* This file is auto-generated! do not edit it manually!*/

int lind_fcntl_set_rpc(int fd, int cmd, long set_op) {
lind_request request;
memset(&request, 0, sizeof(request));
int return_code = -1;
size_t reply_size = 0 + sizeof(lind_reply);
lind_reply* reply_buffer = malloc(reply_size);
assert(reply_buffer!=NULL);
/* These memsets are mainly for saftey.*/
memset(reply_buffer, 0, reply_size);
struct lind_fcntl_set_rpc_s args;
memset(&args, 0, sizeof(struct lind_fcntl_set_rpc_s));
nacl_strace("lind_fcntl_set_rpc\n");
args.fd = fd;
args.cmd = cmd;
args.set_op = set_op;
request.format = """<i" "<i" "<i" ;
request.call_number = 28;
request.message.len = sizeof(struct lind_fcntl_set_rpc_s);
request.message.body = &args;
nacl_rpc_syscall_proxy(&request, reply_buffer,0);
/* on error return negative so we can set ERRNO. */
if (reply_buffer->is_error) {
return_code = reply_buffer->return_code * -1;
} else {
return_code = reply_buffer->return_code;
}
free(reply_buffer);
return return_code;
}
/* This file is auto-generated! do not edit it manually!*/

int lind_socket_rpc(int domain, int type, int protocol) {
lind_request request;
memset(&request, 0, sizeof(request));
int return_code = -1;
size_t reply_size = 0 + sizeof(lind_reply);
lind_reply* reply_buffer = malloc(reply_size);
assert(reply_buffer!=NULL);
/* These memsets are mainly for saftey.*/
memset(reply_buffer, 0, reply_size);
struct lind_socket_rpc_s args;
memset(&args, 0, sizeof(struct lind_socket_rpc_s));
nacl_strace("lind_socket_rpc\n");
args.domain = domain;
args.type = type;
args.protocol = protocol;
request.format = """<i" "<i" "<i" ;
request.call_number = 32;
request.message.len = sizeof(struct lind_socket_rpc_s);
request.message.body = &args;
nacl_rpc_syscall_proxy(&request, reply_buffer,0);
/* on error return negative so we can set ERRNO. */
if (reply_buffer->is_error) {
return_code = reply_buffer->return_code * -1;
} else {
return_code = reply_buffer->return_code;
}
free(reply_buffer);
return return_code;
}
/* This file is auto-generated! do not edit it manually!*/

int lind_bind_rpc(int sockfd, socklen_t addrlen, const struct sockaddr * addr) {
lind_request request;
memset(&request, 0, sizeof(request));
int return_code = -1;
size_t reply_size = 0 + sizeof(lind_reply);
lind_reply* reply_buffer = malloc(reply_size);
assert(reply_buffer!=NULL);
/* These memsets are mainly for saftey.*/
memset(reply_buffer, 0, reply_size);
struct lind_bind_rpc_s args;
memset(&args, 0, sizeof(struct lind_bind_rpc_s));
nacl_strace("lind_bind_rpc\n");
args.sockfd = sockfd;
args.addrlen = addrlen;
// check if addr is NULL
int addr_is_null = 0;
if (addr == NULL) {
addr_is_null = 1;
} else {
addr_is_null = 0;
}
unsigned long int nowhere = 0;
ssize_t addr_ssize = addrlen;
const char * addrlen_addr_len_str = "YYY";
const char * addr_fmt_str = "ZZZ";
void * addr_ptr = NULL;
ssize_t addr_data_size = -1;
if (addr_is_null) {
addr_ptr = &nowhere;
addr_fmt_str =  "P";
addrlen_addr_len_str = "";
addr_data_size = sizeof (void *);
} else {
addr_ptr = (void*)addr;
addr_fmt_str =  "s"; // if it is not null, treat as a string
addrlen_addr_len_str =  nacl_itoa(addr_ssize);
addr_data_size = addr_ssize;
}
assert( addr_ptr != NULL );
assert( addr_data_size != -1 );
assert( strcmp(addrlen_addr_len_str, "YYY") != 0 );
assert( strcmp(addr_fmt_str, "ZZZ") != 0 );
request.format = combine(5, "", "<i" , "<i" , addrlen_addr_len_str, addr_fmt_str);
request.call_number = 33;
if (! addr_is_null) {
free((void*)addrlen_addr_len_str);
}
request.message.len = sizeof(struct lind_bind_rpc_s);
request.message.body = &args;
nacl_rpc_syscall_proxy(&request, reply_buffer,1, addr_ptr, addr_data_size);
/* on error return negative so we can set ERRNO. */
if (reply_buffer->is_error) {
return_code = reply_buffer->return_code * -1;
} else {
return_code = reply_buffer->return_code;
}
free(reply_buffer);
return return_code;
}
/* This file is auto-generated! do not edit it manually!*/

int lind_send_rpc(int sockfd, size_t len, int flags, const void * buf) {
lind_request request;
memset(&request, 0, sizeof(request));
int return_code = -1;
size_t reply_size = 0 + sizeof(lind_reply);
lind_reply* reply_buffer = malloc(reply_size);
assert(reply_buffer!=NULL);
/* These memsets are mainly for saftey.*/
memset(reply_buffer, 0, reply_size);
struct lind_send_rpc_s args;
memset(&args, 0, sizeof(struct lind_send_rpc_s));
nacl_strace("lind_send_rpc\n");
args.sockfd = sockfd;
args.len = len;
args.flags = flags;
// check if buf is NULL
int buf_is_null = 0;
if (buf == NULL) {
buf_is_null = 1;
} else {
buf_is_null = 0;
}
unsigned long int nowhere = 0;
ssize_t buf_ssize = len;
const char * len_buf_len_str = "YYY";
const char * buf_fmt_str = "ZZZ";
void * buf_ptr = NULL;
ssize_t buf_data_size = -1;
if (buf_is_null) {
buf_ptr = &nowhere;
buf_fmt_str =  "P";
len_buf_len_str = "";
buf_data_size = sizeof (void *);
} else {
buf_ptr = (void*)buf;
buf_fmt_str =  "s"; // if it is not null, treat as a string
len_buf_len_str =  nacl_itoa(buf_ssize);
buf_data_size = buf_ssize;
}
assert( buf_ptr != NULL );
assert( buf_data_size != -1 );
assert( strcmp(len_buf_len_str, "YYY") != 0 );
assert( strcmp(buf_fmt_str, "ZZZ") != 0 );
request.format = combine(6, "", "<i" , "<I" , "<i" , len_buf_len_str, buf_fmt_str);
request.call_number = 34;
if (! buf_is_null) {
free((void*)len_buf_len_str);
}
request.message.len = sizeof(struct lind_send_rpc_s);
request.message.body = &args;
nacl_rpc_syscall_proxy(&request, reply_buffer,1, buf_ptr, buf_data_size);
/* on error return negative so we can set ERRNO. */
if (reply_buffer->is_error) {
return_code = reply_buffer->return_code * -1;
} else {
return_code = reply_buffer->return_code;
}
free(reply_buffer);
return return_code;
}
/* This file is auto-generated! do not edit it manually!*/

int lind_recv_rpc(int sockfd, size_t len, int flags, void * buf) {
lind_request request;
memset(&request, 0, sizeof(request));
int return_code = -1;
size_t reply_size = len + sizeof(lind_reply);
lind_reply* reply_buffer = malloc(reply_size);
assert(reply_buffer!=NULL);
/* These memsets are mainly for saftey.*/
memset(reply_buffer, 0, reply_size);
struct lind_recv_rpc_s args;
memset(&args, 0, sizeof(struct lind_recv_rpc_s));
nacl_strace("lind_recv_rpc\n");
args.sockfd = sockfd;
args.len = len;
args.flags = flags;
request.format = """<i" "<I" "<i" ;
request.call_number = 36;
request.message.len = sizeof(struct lind_recv_rpc_s);
request.message.body = &args;
nacl_rpc_syscall_proxy(&request, reply_buffer,0);
/* on error return negative so we can set ERRNO. */
if (reply_buffer->is_error) {
return_code = reply_buffer->return_code * -1;
} else {
return_code = reply_buffer->return_code;
assert( CONTENTS_SIZ(reply_buffer) <= len);
void * ptr = NULL;
ptr = buf;
if (ptr != NULL) { memcpy(ptr, ((&(reply_buffer->contents)) + 0), len); }
}
free(reply_buffer);
return return_code;
}
/* This file is auto-generated! do not edit it manually!*/

int lind_connect_rpc(int sockfd, socklen_t addrlen, const struct sockaddr * src_addr) {
lind_request request;
memset(&request, 0, sizeof(request));
int return_code = -1;
size_t reply_size = 0 + sizeof(lind_reply);
lind_reply* reply_buffer = malloc(reply_size);
assert(reply_buffer!=NULL);
/* These memsets are mainly for saftey.*/
memset(reply_buffer, 0, reply_size);
struct lind_connect_rpc_s args;
memset(&args, 0, sizeof(struct lind_connect_rpc_s));
nacl_strace("lind_connect_rpc\n");
args.sockfd = sockfd;
args.addrlen = addrlen;
// check if src_addr is NULL
int src_addr_is_null = 0;
if (src_addr == NULL) {
src_addr_is_null = 1;
} else {
src_addr_is_null = 0;
}
unsigned long int nowhere = 0;
ssize_t src_addr_ssize = addrlen;
const char * addrlen_src_addr_len_str = "YYY";
const char * src_addr_fmt_str = "ZZZ";
void * src_addr_ptr = NULL;
ssize_t src_addr_data_size = -1;
if (src_addr_is_null) {
src_addr_ptr = &nowhere;
src_addr_fmt_str =  "P";
addrlen_src_addr_len_str = "";
src_addr_data_size = sizeof (void *);
} else {
src_addr_ptr = (void*)src_addr;
src_addr_fmt_str =  "s"; // if it is not null, treat as a string
addrlen_src_addr_len_str =  nacl_itoa(src_addr_ssize);
src_addr_data_size = src_addr_ssize;
}
assert( src_addr_ptr != NULL );
assert( src_addr_data_size != -1 );
assert( strcmp(addrlen_src_addr_len_str, "YYY") != 0 );
assert( strcmp(src_addr_fmt_str, "ZZZ") != 0 );
request.format = combine(5, "", "<i" , "<i" , addrlen_src_addr_len_str, src_addr_fmt_str);
request.call_number = 38;
if (! src_addr_is_null) {
free((void*)addrlen_src_addr_len_str);
}
request.message.len = sizeof(struct lind_connect_rpc_s);
request.message.body = &args;
nacl_rpc_syscall_proxy(&request, reply_buffer,1, src_addr_ptr, src_addr_data_size);
/* on error return negative so we can set ERRNO. */
if (reply_buffer->is_error) {
return_code = reply_buffer->return_code * -1;
} else {
return_code = reply_buffer->return_code;
}
free(reply_buffer);
return return_code;
}
/* This file is auto-generated! do not edit it manually!*/

int lind_listen_rpc(int sockfd, int backlog) {
lind_request request;
memset(&request, 0, sizeof(request));
int return_code = -1;
size_t reply_size = 0 + sizeof(lind_reply);
lind_reply* reply_buffer = malloc(reply_size);
assert(reply_buffer!=NULL);
/* These memsets are mainly for saftey.*/
memset(reply_buffer, 0, reply_size);
struct lind_listen_rpc_s args;
memset(&args, 0, sizeof(struct lind_listen_rpc_s));
nacl_strace("lind_listen_rpc\n");
args.sockfd = sockfd;
args.backlog = backlog;
request.format = """<i" "<i" ;
request.call_number = 39;
request.message.len = sizeof(struct lind_listen_rpc_s);
request.message.body = &args;
nacl_rpc_syscall_proxy(&request, reply_buffer,0);
/* on error return negative so we can set ERRNO. */
if (reply_buffer->is_error) {
return_code = reply_buffer->return_code * -1;
} else {
return_code = reply_buffer->return_code;
}
free(reply_buffer);
return return_code;
}
/* This file is auto-generated! do not edit it manually!*/

int lind_sendto_rpc(int sockfd, size_t len, int flags, socklen_t addrlen, const struct sockaddr_in * dest_addr, const void * buf) {
return 0; }
/* This file is auto-generated! do not edit it manually!*/

int lind_accept_rpc(int sockfd, socklen_t addrlen) {
lind_request request;
memset(&request, 0, sizeof(request));
int return_code = -1;
size_t reply_size = 0 + sizeof(lind_reply);
lind_reply* reply_buffer = malloc(reply_size);
assert(reply_buffer!=NULL);
/* These memsets are mainly for saftey.*/
memset(reply_buffer, 0, reply_size);
struct lind_accept_rpc_s args;
memset(&args, 0, sizeof(struct lind_accept_rpc_s));
nacl_strace("lind_accept_rpc\n");
args.sockfd = sockfd;
args.addrlen = addrlen;
request.format = """<i" "<i" ;
request.call_number = 40;
request.message.len = sizeof(struct lind_accept_rpc_s);
request.message.body = &args;
nacl_rpc_syscall_proxy(&request, reply_buffer,0);
/* on error return negative so we can set ERRNO. */
if (reply_buffer->is_error) {
return_code = reply_buffer->return_code * -1;
} else {
return_code = reply_buffer->return_code;
}
free(reply_buffer);
return return_code;
}
/* This file is auto-generated! do not edit it manually!*/

int lind_getpeername_rpc(int sockfd, socklen_t addrlen_in, __SOCKADDR_ARG addr, socklen_t * addrlen_out) {
return 0; }
/* This file is auto-generated! do not edit it manually!*/

int lind_setsockopt_rpc(int sockfd, int level, int optname, socklen_t optlen, const void * optval) {
lind_request request;
memset(&request, 0, sizeof(request));
int return_code = -1;
size_t reply_size = 0 + sizeof(lind_reply);
lind_reply* reply_buffer = malloc(reply_size);
assert(reply_buffer!=NULL);
/* These memsets are mainly for saftey.*/
memset(reply_buffer, 0, reply_size);
struct lind_setsockopt_rpc_s args;
memset(&args, 0, sizeof(struct lind_setsockopt_rpc_s));
nacl_strace("lind_setsockopt_rpc\n");
args.sockfd = sockfd;
args.level = level;
args.optname = optname;
args.optlen = optlen;
// check if optval is NULL
int optval_is_null = 0;
if (optval == NULL) {
optval_is_null = 1;
} else {
optval_is_null = 0;
}
unsigned long int nowhere = 0;
ssize_t optval_ssize = optlen;
const char * optlen_optval_len_str = "YYY";
const char * optval_fmt_str = "ZZZ";
void * optval_ptr = NULL;
ssize_t optval_data_size = -1;
if (optval_is_null) {
optval_ptr = &nowhere;
optval_fmt_str =  "P";
optlen_optval_len_str = "";
optval_data_size = sizeof (void *);
} else {
optval_ptr = (void*)optval;
optval_fmt_str =  "s"; // if it is not null, treat as a string
optlen_optval_len_str =  nacl_itoa(optval_ssize);
optval_data_size = optval_ssize;
}
assert( optval_ptr != NULL );
assert( optval_data_size != -1 );
assert( strcmp(optlen_optval_len_str, "YYY") != 0 );
assert( strcmp(optval_fmt_str, "ZZZ") != 0 );
request.format = combine(7, "", "<i" , "<i" , "<i" , "<i" , optlen_optval_len_str, optval_fmt_str);
request.call_number = 44;
if (! optval_is_null) {
free((void*)optlen_optval_len_str);
}
request.message.len = sizeof(struct lind_setsockopt_rpc_s);
request.message.body = &args;
nacl_rpc_syscall_proxy(&request, reply_buffer,1, optval_ptr, optval_data_size);
/* on error return negative so we can set ERRNO. */
if (reply_buffer->is_error) {
return_code = reply_buffer->return_code * -1;
} else {
return_code = reply_buffer->return_code;
}
free(reply_buffer);
return return_code;
}
/* This file is auto-generated! do not edit it manually!*/

int lind_getsockopt_rpc(int sockfd, int level, int optname, socklen_t optlen, void * optval) {
lind_request request;
memset(&request, 0, sizeof(request));
int return_code = -1;
size_t reply_size = optlen + sizeof(lind_reply);
lind_reply* reply_buffer = malloc(reply_size);
assert(reply_buffer!=NULL);
/* These memsets are mainly for saftey.*/
memset(reply_buffer, 0, reply_size);
struct lind_getsockopt_rpc_s args;
memset(&args, 0, sizeof(struct lind_getsockopt_rpc_s));
nacl_strace("lind_getsockopt_rpc\n");
args.sockfd = sockfd;
args.level = level;
args.optname = optname;
args.optlen = optlen;
request.format = """<i" "<i" "<i" "<i" ;
request.call_number = 43;
request.message.len = sizeof(struct lind_getsockopt_rpc_s);
request.message.body = &args;
nacl_rpc_syscall_proxy(&request, reply_buffer,0);
/* on error return negative so we can set ERRNO. */
if (reply_buffer->is_error) {
return_code = reply_buffer->return_code * -1;
} else {
return_code = reply_buffer->return_code;
assert( CONTENTS_SIZ(reply_buffer) <= optlen);
void * ptr = NULL;
ptr = optval;
if (ptr != NULL) { memcpy(ptr, ((&(reply_buffer->contents)) + 0), optlen); }
}
free(reply_buffer);
return return_code;
}
/* This file is auto-generated! do not edit it manually!*/

int lind_shutdown_rpc(int sockfd, int how) {
lind_request request;
memset(&request, 0, sizeof(request));
int return_code = -1;
size_t reply_size = 0 + sizeof(lind_reply);
lind_reply* reply_buffer = malloc(reply_size);
assert(reply_buffer!=NULL);
/* These memsets are mainly for saftey.*/
memset(reply_buffer, 0, reply_size);
struct lind_shutdown_rpc_s args;
memset(&args, 0, sizeof(struct lind_shutdown_rpc_s));
nacl_strace("lind_shutdown_rpc\n");
args.sockfd = sockfd;
args.how = how;
request.format = """<i" "<i" ;
request.call_number = 45;
request.message.len = sizeof(struct lind_shutdown_rpc_s);
request.message.body = &args;
nacl_rpc_syscall_proxy(&request, reply_buffer,0);
/* on error return negative so we can set ERRNO. */
if (reply_buffer->is_error) {
return_code = reply_buffer->return_code * -1;
} else {
return_code = reply_buffer->return_code;
}
free(reply_buffer);
return return_code;
}
/* This file is auto-generated! do not edit it manually!*/

int lind_select_rpc(int nfds, fd_set * readfds, fd_set * writefds, fd_set * exceptfds, struct timeval * timeout, struct select_results * result) {
lind_request request;
memset(&request, 0, sizeof(request));
int return_code = -1;
size_t reply_size = sizeof(struct select_results) + sizeof(lind_reply);
lind_reply* reply_buffer = malloc(reply_size);
assert(reply_buffer!=NULL);
/* These memsets are mainly for saftey.*/
memset(reply_buffer, 0, reply_size);
struct lind_select_rpc_s args;
memset(&args, 0, sizeof(struct lind_select_rpc_s));
nacl_strace("lind_select_rpc\n");
args.nfds = nfds;
// check if readfds is NULL
int readfds_is_null = 0;
if (readfds == NULL) {
readfds_is_null = 1;
} else {
readfds_is_null = 0;
}
unsigned long int nowhere = 0;
ssize_t readfds_ssize = sizeof(fd_set);
const char * sizeoffdset_readfds_len_str = "YYY";
const char * readfds_fmt_str = "ZZZ";
void * readfds_ptr = NULL;
ssize_t readfds_data_size = -1;
if (readfds_is_null) {
readfds_ptr = &nowhere;
readfds_fmt_str =  "P";
sizeoffdset_readfds_len_str = "";
readfds_data_size = sizeof (void *);
} else {
readfds_ptr = (void*)readfds;
readfds_fmt_str =  "s"; // if it is not null, treat as a string
sizeoffdset_readfds_len_str =  nacl_itoa(readfds_ssize);
readfds_data_size = readfds_ssize;
}
assert( readfds_ptr != NULL );
assert( readfds_data_size != -1 );
assert( strcmp(sizeoffdset_readfds_len_str, "YYY") != 0 );
assert( strcmp(readfds_fmt_str, "ZZZ") != 0 );
// check if writefds is NULL
int writefds_is_null = 0;
if (writefds == NULL) {
writefds_is_null = 1;
} else {
writefds_is_null = 0;
}
ssize_t writefds_ssize = sizeof(fd_set);
const char * sizeoffdset_writefds_len_str = "YYY";
const char * writefds_fmt_str = "ZZZ";
void * writefds_ptr = NULL;
ssize_t writefds_data_size = -1;
if (writefds_is_null) {
writefds_ptr = &nowhere;
writefds_fmt_str =  "P";
sizeoffdset_writefds_len_str = "";
writefds_data_size = sizeof (void *);
} else {
writefds_ptr = (void*)writefds;
writefds_fmt_str =  "s"; // if it is not null, treat as a string
sizeoffdset_writefds_len_str =  nacl_itoa(writefds_ssize);
writefds_data_size = writefds_ssize;
}
assert( writefds_ptr != NULL );
assert( writefds_data_size != -1 );
assert( strcmp(sizeoffdset_writefds_len_str, "YYY") != 0 );
assert( strcmp(writefds_fmt_str, "ZZZ") != 0 );
// check if exceptfds is NULL
int exceptfds_is_null = 0;
if (exceptfds == NULL) {
exceptfds_is_null = 1;
} else {
exceptfds_is_null = 0;
}
ssize_t exceptfds_ssize = sizeof(fd_set);
const char * sizeoffdset_exceptfds_len_str = "YYY";
const char * exceptfds_fmt_str = "ZZZ";
void * exceptfds_ptr = NULL;
ssize_t exceptfds_data_size = -1;
if (exceptfds_is_null) {
exceptfds_ptr = &nowhere;
exceptfds_fmt_str =  "P";
sizeoffdset_exceptfds_len_str = "";
exceptfds_data_size = sizeof (void *);
} else {
exceptfds_ptr = (void*)exceptfds;
exceptfds_fmt_str =  "s"; // if it is not null, treat as a string
sizeoffdset_exceptfds_len_str =  nacl_itoa(exceptfds_ssize);
exceptfds_data_size = exceptfds_ssize;
}
assert( exceptfds_ptr != NULL );
assert( exceptfds_data_size != -1 );
assert( strcmp(sizeoffdset_exceptfds_len_str, "YYY") != 0 );
assert( strcmp(exceptfds_fmt_str, "ZZZ") != 0 );
// check if timeout is NULL
int timeout_is_null = 0;
if (timeout == NULL) {
timeout_is_null = 1;
} else {
timeout_is_null = 0;
}
ssize_t timeout_ssize = sizeof(struct timeval);
const char * sizeofstructtimeval_timeout_len_str = "YYY";
const char * timeout_fmt_str = "ZZZ";
void * timeout_ptr = NULL;
ssize_t timeout_data_size = -1;
if (timeout_is_null) {
timeout_ptr = &nowhere;
timeout_fmt_str =  "P";
sizeofstructtimeval_timeout_len_str = "";
timeout_data_size = sizeof (void *);
} else {
timeout_ptr = (void*)timeout;
timeout_fmt_str =  "s"; // if it is not null, treat as a string
sizeofstructtimeval_timeout_len_str =  nacl_itoa(timeout_ssize);
timeout_data_size = timeout_ssize;
}
assert( timeout_ptr != NULL );
assert( timeout_data_size != -1 );
assert( strcmp(sizeofstructtimeval_timeout_len_str, "YYY") != 0 );
assert( strcmp(timeout_fmt_str, "ZZZ") != 0 );
request.format = combine(10, "", "<i" , sizeoffdset_readfds_len_str, readfds_fmt_str, sizeoffdset_writefds_len_str, writefds_fmt_str, sizeoffdset_exceptfds_len_str, exceptfds_fmt_str, sizeofstructtimeval_timeout_len_str, timeout_fmt_str);
request.call_number = 46;
if (! readfds_is_null) {
free((void*)sizeoffdset_readfds_len_str);
}
if (! writefds_is_null) {
free((void*)sizeoffdset_writefds_len_str);
}
if (! exceptfds_is_null) {
free((void*)sizeoffdset_exceptfds_len_str);
}
if (! timeout_is_null) {
free((void*)sizeofstructtimeval_timeout_len_str);
}
request.message.len = sizeof(struct lind_select_rpc_s);
request.message.body = &args;
nacl_rpc_syscall_proxy(&request, reply_buffer,4, readfds_ptr, readfds_data_size, writefds_ptr, writefds_data_size, exceptfds_ptr, exceptfds_data_size, timeout_ptr, timeout_data_size);
/* on error return negative so we can set ERRNO. */
if (reply_buffer->is_error) {
return_code = reply_buffer->return_code * -1;
} else {
return_code = reply_buffer->return_code;
assert( CONTENTS_SIZ(reply_buffer) <= sizeof(struct select_results));
void * ptr = NULL;
ptr = result;
if (ptr != NULL) { memcpy(ptr, ((&(reply_buffer->contents)) + 0), sizeof(struct select_results)); }
}
free(reply_buffer);
return return_code;
}
/* This file is auto-generated! do not edit it manually!*/

int lind_getifaddrs_rpc(int ifaddrs_buf_siz, void * ifaddrs) {
lind_request request;
memset(&request, 0, sizeof(request));
int return_code = -1;
size_t reply_size = ifaddrs_buf_siz + sizeof(lind_reply);
lind_reply* reply_buffer = malloc(reply_size);
assert(reply_buffer!=NULL);
/* These memsets are mainly for saftey.*/
memset(reply_buffer, 0, reply_size);
struct lind_getifaddrs_rpc_s args;
memset(&args, 0, sizeof(struct lind_getifaddrs_rpc_s));
nacl_strace("lind_getifaddrs_rpc\n");
args.ifaddrs_buf_siz = ifaddrs_buf_siz;
request.format = """<i" ;
request.call_number = 47;
request.message.len = sizeof(struct lind_getifaddrs_rpc_s);
request.message.body = &args;
nacl_rpc_syscall_proxy(&request, reply_buffer,0);
/* on error return negative so we can set ERRNO. */
if (reply_buffer->is_error) {
return_code = reply_buffer->return_code * -1;
} else {
return_code = reply_buffer->return_code;
assert( CONTENTS_SIZ(reply_buffer) <= ifaddrs_buf_siz);
void * ptr = NULL;
ptr = ifaddrs;
if (ptr != NULL) { memcpy(ptr, ((&(reply_buffer->contents)) + 0), ifaddrs_buf_siz); }
}
free(reply_buffer);
return return_code;
}
/* This file is auto-generated! do not edit it manually!*/

int lind_recvfrom_rpc(int sockfd, size_t len, int flags, socklen_t addrlen, socklen_t* addrlen_out, void * buf, struct sockaddr * src_addr) {
lind_request request;
memset(&request, 0, sizeof(request));
int return_code = -1;
size_t reply_size = sizeof(socklen_t) + len + sizeof(struct sockaddr) + sizeof(lind_reply);
lind_reply* reply_buffer = malloc(reply_size);
assert(reply_buffer!=NULL);
/* These memsets are mainly for saftey.*/
memset(reply_buffer, 0, reply_size);
struct lind_recvfrom_rpc_s args;
memset(&args, 0, sizeof(struct lind_recvfrom_rpc_s));
nacl_strace("lind_recvfrom_rpc\n");
args.sockfd = sockfd;
args.len = len;
args.flags = flags;
args.addrlen = addrlen;
request.format = """<i" "<I" "<i" "<i" ;
request.call_number = 37;
request.message.len = sizeof(struct lind_recvfrom_rpc_s);
request.message.body = &args;
nacl_rpc_syscall_proxy(&request, reply_buffer,0);
/* on error return negative so we can set ERRNO. */
if (reply_buffer->is_error) {
return_code = reply_buffer->return_code * -1;
} else {
return_code = reply_buffer->return_code;
void * ptr = NULL;
void * base = &(reply_buffer->contents);
int * sizes = base;
int offset=(sizeof(int) * 3), cur_size = 0;

ptr = (void *)addrlen_out;
cur_size = sizes[0];
if (ptr != NULL) {
assert( cur_size <= sizeof(socklen_t) );
memcpy(ptr, base +  offset, cur_size);
} // end of ptr != NULL
offset += cur_size;

ptr = (void *)buf;
cur_size = sizes[1];
if (ptr != NULL) {
assert( cur_size <= len );
memcpy(ptr, base +  offset, cur_size);
} // end of ptr != NULL
offset += cur_size;

ptr = (void *)src_addr;
cur_size = sizes[2];
if (ptr != NULL) {
assert( cur_size <= sizeof(struct sockaddr) );
memcpy(ptr, base +  offset, cur_size);
} // end of ptr != NULL
offset += cur_size;

}
free(reply_buffer);
return return_code;
}
/* This file is auto-generated! do not edit it manually!*/

int lind_poll_rpc(int nfds, int timeout, struct pollfd * fds_in, struct pollfd * fds_out) {
lind_request request;
memset(&request, 0, sizeof(request));
int return_code = -1;
size_t reply_size = (sizeof(struct pollfd) * nfds) + sizeof(lind_reply);
lind_reply* reply_buffer = malloc(reply_size);
assert(reply_buffer!=NULL);
/* These memsets are mainly for saftey.*/
memset(reply_buffer, 0, reply_size);
struct lind_poll_rpc_s args;
memset(&args, 0, sizeof(struct lind_poll_rpc_s));
nacl_strace("lind_poll_rpc\n");
args.nfds = nfds;
args.timeout = timeout;
// check if fds_in is NULL
int fds_in_is_null = 0;
if (fds_in == NULL) {
fds_in_is_null = 1;
} else {
fds_in_is_null = 0;
}
unsigned long int nowhere = 0;
ssize_t fds_in_ssize = (sizeof(struct pollfd) * nfds);
const char * sizeofstructpollfdnfds_fds_in_len_str = "YYY";
const char * fds_in_fmt_str = "ZZZ";
void * fds_in_ptr = NULL;
ssize_t fds_in_data_size = -1;
if (fds_in_is_null) {
fds_in_ptr = &nowhere;
fds_in_fmt_str =  "P";
sizeofstructpollfdnfds_fds_in_len_str = "";
fds_in_data_size = sizeof (void *);
} else {
fds_in_ptr = (void*)fds_in;
fds_in_fmt_str =  "s"; // if it is not null, treat as a string
sizeofstructpollfdnfds_fds_in_len_str =  nacl_itoa(fds_in_ssize);
fds_in_data_size = fds_in_ssize;
}
assert( fds_in_ptr != NULL );
assert( fds_in_data_size != -1 );
assert( strcmp(sizeofstructpollfdnfds_fds_in_len_str, "YYY") != 0 );
assert( strcmp(fds_in_fmt_str, "ZZZ") != 0 );
request.format = combine(5, "", "<i" , "<i" , sizeofstructpollfdnfds_fds_in_len_str, fds_in_fmt_str);
request.call_number = 48;
if (! fds_in_is_null) {
free((void*)sizeofstructpollfdnfds_fds_in_len_str);
}
request.message.len = sizeof(struct lind_poll_rpc_s);
request.message.body = &args;
nacl_rpc_syscall_proxy(&request, reply_buffer,1, fds_in_ptr, fds_in_data_size);
/* on error return negative so we can set ERRNO. */
if (reply_buffer->is_error) {
return_code = reply_buffer->return_code * -1;
} else {
return_code = reply_buffer->return_code;
assert( CONTENTS_SIZ(reply_buffer) <= (sizeof(struct pollfd) * nfds));
void * ptr = NULL;
ptr = fds_out;
if (ptr != NULL) { memcpy(ptr, ((&(reply_buffer->contents)) + 0), (sizeof(struct pollfd) * nfds)); }
}
free(reply_buffer);
return return_code;
}
/* This file is auto-generated! do not edit it manually!*/

int lind_socketpair_rpc(int domain, int type, int protocol, int * fds) {
lind_request request;
memset(&request, 0, sizeof(request));
int return_code = -1;
size_t reply_size = sizeof(int) * 2 + sizeof(lind_reply);
lind_reply* reply_buffer = malloc(reply_size);
assert(reply_buffer!=NULL);
/* These memsets are mainly for saftey.*/
memset(reply_buffer, 0, reply_size);
struct lind_socketpair_rpc_s args;
memset(&args, 0, sizeof(struct lind_socketpair_rpc_s));
nacl_strace("lind_socketpair_rpc\n");
args.domain = domain;
args.type = type;
args.protocol = protocol;
request.format = """<i" "<i" "<i" ;
request.call_number = 49;
request.message.len = sizeof(struct lind_socketpair_rpc_s);
request.message.body = &args;
nacl_rpc_syscall_proxy(&request, reply_buffer,0);
/* on error return negative so we can set ERRNO. */
if (reply_buffer->is_error) {
return_code = reply_buffer->return_code * -1;
} else {
return_code = reply_buffer->return_code;
assert( CONTENTS_SIZ(reply_buffer) <= sizeof(int) * 2);
void * ptr = NULL;
ptr = fds;
if (ptr != NULL) { memcpy(ptr, ((&(reply_buffer->contents)) + 0), sizeof(int) * 2); }
}
free(reply_buffer);
return return_code;
}
/* This file is auto-generated! do not edit it manually!*/

int lind_getuid_rpc(uid_t * buf) {
lind_request request;
memset(&request, 0, sizeof(request));
int return_code = -1;
size_t reply_size = sizeof(uid_t) + sizeof(lind_reply);
lind_reply* reply_buffer = malloc(reply_size);
assert(reply_buffer!=NULL);
/* These memsets are mainly for saftey.*/
memset(reply_buffer, 0, reply_size);
struct lind_getuid_rpc_s args;
memset(&args, 0, sizeof(struct lind_getuid_rpc_s));
nacl_strace("lind_getuid_rpc\n");
request.format = "";
request.call_number = 50;
request.message.len = sizeof(struct lind_getuid_rpc_s);
request.message.body = &args;
nacl_rpc_syscall_proxy(&request, reply_buffer,0);
/* on error return negative so we can set ERRNO. */
if (reply_buffer->is_error) {
return_code = reply_buffer->return_code * -1;
} else {
return_code = reply_buffer->return_code;
assert( CONTENTS_SIZ(reply_buffer) <= sizeof(uid_t));
void * ptr = NULL;
ptr = buf;
if (ptr != NULL) { memcpy(ptr, ((&(reply_buffer->contents)) + 0), sizeof(uid_t)); }
}
free(reply_buffer);
return return_code;
}
/* This file is auto-generated! do not edit it manually!*/

int lind_geteuid_rpc(uid_t * buf) {
lind_request request;
memset(&request, 0, sizeof(request));
int return_code = -1;
size_t reply_size = sizeof(uid_t) + sizeof(lind_reply);
lind_reply* reply_buffer = malloc(reply_size);
assert(reply_buffer!=NULL);
/* These memsets are mainly for saftey.*/
memset(reply_buffer, 0, reply_size);
struct lind_geteuid_rpc_s args;
memset(&args, 0, sizeof(struct lind_geteuid_rpc_s));
nacl_strace("lind_geteuid_rpc\n");
request.format = "";
request.call_number = 51;
request.message.len = sizeof(struct lind_geteuid_rpc_s);
request.message.body = &args;
nacl_rpc_syscall_proxy(&request, reply_buffer,0);
/* on error return negative so we can set ERRNO. */
if (reply_buffer->is_error) {
return_code = reply_buffer->return_code * -1;
} else {
return_code = reply_buffer->return_code;
assert( CONTENTS_SIZ(reply_buffer) <= sizeof(uid_t));
void * ptr = NULL;
ptr = buf;
if (ptr != NULL) { memcpy(ptr, ((&(reply_buffer->contents)) + 0), sizeof(uid_t)); }
}
free(reply_buffer);
return return_code;
}
/* This file is auto-generated! do not edit it manually!*/

int lind_getgid_rpc(gid_t * buf) {
lind_request request;
memset(&request, 0, sizeof(request));
int return_code = -1;
size_t reply_size = sizeof(gid_t) + sizeof(lind_reply);
lind_reply* reply_buffer = malloc(reply_size);
assert(reply_buffer!=NULL);
/* These memsets are mainly for saftey.*/
memset(reply_buffer, 0, reply_size);
struct lind_getgid_rpc_s args;
memset(&args, 0, sizeof(struct lind_getgid_rpc_s));
nacl_strace("lind_getgid_rpc\n");
request.format = "";
request.call_number = 52;
request.message.len = sizeof(struct lind_getgid_rpc_s);
request.message.body = &args;
nacl_rpc_syscall_proxy(&request, reply_buffer,0);
/* on error return negative so we can set ERRNO. */
if (reply_buffer->is_error) {
return_code = reply_buffer->return_code * -1;
} else {
return_code = reply_buffer->return_code;
assert( CONTENTS_SIZ(reply_buffer) <= sizeof(gid_t));
void * ptr = NULL;
ptr = buf;
if (ptr != NULL) { memcpy(ptr, ((&(reply_buffer->contents)) + 0), sizeof(gid_t)); }
}
free(reply_buffer);
return return_code;
}
/* This file is auto-generated! do not edit it manually!*/

int lind_getegid_rpc(gid_t * buf) {
lind_request request;
memset(&request, 0, sizeof(request));
int return_code = -1;
size_t reply_size = sizeof(gid_t) + sizeof(lind_reply);
lind_reply* reply_buffer = malloc(reply_size);
assert(reply_buffer!=NULL);
/* These memsets are mainly for saftey.*/
memset(reply_buffer, 0, reply_size);
struct lind_getegid_rpc_s args;
memset(&args, 0, sizeof(struct lind_getegid_rpc_s));
nacl_strace("lind_getegid_rpc\n");
request.format = "";
request.call_number = 53;
request.message.len = sizeof(struct lind_getegid_rpc_s);
request.message.body = &args;
nacl_rpc_syscall_proxy(&request, reply_buffer,0);
/* on error return negative so we can set ERRNO. */
if (reply_buffer->is_error) {
return_code = reply_buffer->return_code * -1;
} else {
return_code = reply_buffer->return_code;
assert( CONTENTS_SIZ(reply_buffer) <= sizeof(gid_t));
void * ptr = NULL;
ptr = buf;
if (ptr != NULL) { memcpy(ptr, ((&(reply_buffer->contents)) + 0), sizeof(gid_t)); }
}
free(reply_buffer);
return return_code;
}
/* This file is auto-generated! do not edit it manually!*/

int lind_flock_rpc(int fd, int operation) {
lind_request request;
memset(&request, 0, sizeof(request));
int return_code = -1;
size_t reply_size = 0 + sizeof(lind_reply);
lind_reply* reply_buffer = malloc(reply_size);
assert(reply_buffer!=NULL);
/* These memsets are mainly for saftey.*/
memset(reply_buffer, 0, reply_size);
struct lind_flock_rpc_s args;
memset(&args, 0, sizeof(struct lind_flock_rpc_s));
nacl_strace("lind_flock_rpc\n");
args.fd = fd;
args.operation = operation;
request.format = """<i" "<i" ;
request.call_number = 54;
request.message.len = sizeof(struct lind_flock_rpc_s);
request.message.body = &args;
nacl_rpc_syscall_proxy(&request, reply_buffer,0);
/* on error return negative so we can set ERRNO. */
if (reply_buffer->is_error) {
return_code = reply_buffer->return_code * -1;
} else {
return_code = reply_buffer->return_code;
}
free(reply_buffer);
return return_code;
}