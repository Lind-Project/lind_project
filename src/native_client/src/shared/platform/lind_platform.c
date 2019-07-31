/*
 * lind_platform.c
 *
 *  Created on: Jul 23, 2013
 *      Author: sji
 */

/* avoid errors caused by conflicts with feature_test_macros(7) */
#undef _POSIX_C_SOURCE
#undef _XOPEN_SOURCE

#include <Python.h>
#include <errno.h>

#include "native_client/src/shared/platform/lind_platform.h"
#include "native_client/src/shared/platform/nacl_log.h"
#include "native_client/src/trusted/service_runtime/include/bits/nacl_syscalls.h"

int lind_syscall_counter;
int lind_syscall_invoked_times[NACL_MAX_SYSCALLS];
double lind_syscall_execution_time[NACL_MAX_SYSCALLS];

PyObject *py_repylib;
PyObject *py_code;
PyObject *py_context;

static int initialized;

/* wrap goto statement to guard against early if/else termination */
#define GOTO_ERROR_IF_NULL(x) do { if (!(x)) goto error; } while (0)

PyObject *CallPythonFunc(PyObject *context, const char *func, PyObject *args)
{
    PyObject *func_obj = NULL;
    PyObject *result = NULL;
    func_obj = PyDict_GetItemString(context, func);
    GOTO_ERROR_IF_NULL(func_obj);
    GOTO_ERROR_IF_NULL(args);
    result = PyObject_CallObject(func_obj, args);
    GOTO_ERROR_IF_NULL(result);
    return result;
error:
    PyErr_Print();
    Py_XDECREF(func_obj);
    return 0;
}

static PyObject *CallPythonFunc0(PyObject *context, const char *func)
{
    PyObject *func_obj = NULL;
    PyObject *args = NULL;
    PyObject *result = NULL;
    func_obj = PyDict_GetItemString(context, func);
    GOTO_ERROR_IF_NULL(func_obj);
    args = Py_BuildValue("()");
    GOTO_ERROR_IF_NULL(args);
    result = PyObject_CallObject(func_obj, args);
    GOTO_ERROR_IF_NULL(result);
    return result;
error:
    PyErr_Print();
    Py_XDECREF(func_obj);
    Py_XDECREF(args);
    return 0;
}

static PyObject *CallPythonFunc1(PyObject *context, const char *func, PyObject *arg)
{
    PyObject *func_obj = NULL;
    PyObject *args = NULL;
    PyObject *result = NULL;
    func_obj = PyDict_GetItemString(context, func);
    GOTO_ERROR_IF_NULL(func_obj);
    args = Py_BuildValue("(O)", arg);
    GOTO_ERROR_IF_NULL(args);
    result = PyObject_CallObject(func_obj, args);
    GOTO_ERROR_IF_NULL(result);
    return result;
error:
    PyErr_Print();
    Py_XDECREF(func_obj);
    Py_XDECREF(args);
    return 0;
}

int LindPythonInit(void)
{
    PyObject *path = NULL;
    PyObject *repylib_name = NULL;
    PyObject *result = NULL;
    PyObject *repy_main_func = NULL;
    PyObject *repy_main_args = NULL;
    char *argv[] = {"dummy"};

    if(initialized++) {
        return 1;
    }
    Py_SetProgramName("dummy");
    PyEval_InitThreads();
    Py_InitializeEx(0);
    PySys_SetArgvEx(1, argv, 0);

    path = PySys_GetObject("path");
    GOTO_ERROR_IF_NULL(path);
    PyList_Append(path, PyString_FromString("../repy/"));

    repylib_name = PyString_FromString("repylib");
    py_repylib = PyImport_Import(repylib_name);
    GOTO_ERROR_IF_NULL(py_repylib);
    repy_main_func = PyObject_GetAttrString(py_repylib, "repy_main");
    GOTO_ERROR_IF_NULL(repy_main_func);
    repy_main_args = Py_BuildValue("([sssss])", "lind", "--safebinary",
                                   "../repy/restrictions.lind",
                                   "../repy/lind_server.py",
                                   "./dummy.nexe");
    result = PyObject_CallObject(repy_main_func, repy_main_args);
    GOTO_ERROR_IF_NULL(result);
    PyOS_AfterFork();
    PyArg_ParseTuple(result, "OO", &py_code, &py_context);
    GOTO_ERROR_IF_NULL(py_code && py_context);
    GOTO_ERROR_IF_NULL(result);
    result = PyEval_EvalCode((PyCodeObject *)py_code, py_context, py_context);
    UNREFERENCED_PARAMETER(result);
    PyEval_ReleaseLock();
    return 1;

error:
    initialized = 0;
    PyErr_Print();
    PyEval_ReleaseLock();
    return 0;
}

int LindPythonFinalize(void)
{
    int retval = 0;
    PyObject *repy_finalize_func = NULL;
    PyObject *repy_finalize_args = NULL;
    PyObject *result = NULL;
    PyGILState_STATE gstate;
    gstate = PyGILState_Ensure();
    if(!initialized) {
        return 0;
    }
    result = CallPythonFunc0(py_context, "finalize");
    GOTO_ERROR_IF_NULL(result);
    repy_finalize_func = PyObject_GetAttrString(py_repylib, "finalize");
    GOTO_ERROR_IF_NULL(repy_finalize_func);
    repy_finalize_args = Py_BuildValue("()");
    result = PyObject_CallObject(repy_finalize_func, repy_finalize_args);
    GOTO_ERROR_IF_NULL(result);
    Py_Finalize();
    initialized = 0;
    retval = 1;
    goto cleanup;
error:
    PyErr_Print();
cleanup:
    Py_XDECREF(repy_finalize_func);
    Py_XDECREF(result);
    Py_XDECREF(py_code);
    Py_XDECREF(py_context);
    Py_XDECREF(py_repylib);
    PyGILState_Release(gstate);
    return retval;
}

int GetHostFdFromLindFd(int lindFd)
{
    int retval = -1;
    PyObject *pyLindFd = NULL;
    PyObject *pyHostFd = NULL;
    PyGILState_STATE gstate;
    gstate = PyGILState_Ensure();
    if(lindFd < 0) {
        goto cleanup;
    }
    pyLindFd = PyInt_FromLong(lindFd);
    pyHostFd = CallPythonFunc1(py_context, "GetHostFdFromLindFd", pyLindFd);
    GOTO_ERROR_IF_NULL(pyHostFd);
    if(!PyInt_CheckExact(pyHostFd)) {
        goto error;
    }
    retval = (int)PyInt_AsLong(pyHostFd);
    goto cleanup;
error:
    PyErr_Print();
cleanup:
    Py_XDECREF(pyLindFd);
    Py_XDECREF(pyHostFd);
    NaClLog(3, "host_fd:%d for lind_fd:%d\n", retval, lindFd);
    PyGILState_Release(gstate);
    return retval;
}

int ParseResponse(PyObject *response, int *isError, int *code, char **dataOrMessage, int *len)
{
    int retval = 0;
    PyObject *attrIsError = NULL;
    PyObject *attrCode = NULL;
    PyObject *attrDataOrMessage = NULL;

    NaClLog(3, "Entered ParseResponse\n");

    attrIsError = PyObject_GetAttrString(response, "is_error");
    GOTO_ERROR_IF_NULL(attrIsError);

    attrCode = PyObject_GetAttrString(response, "return_code");
    GOTO_ERROR_IF_NULL(attrCode);

    *dataOrMessage = NULL;
    *len = 0;

    if(attrIsError == Py_True) {
        *isError = 1;
        attrDataOrMessage = PyObject_GetAttrString(response, "message");
        GOTO_ERROR_IF_NULL(attrDataOrMessage);
    } else {
        *isError = 0;
        attrDataOrMessage = PyObject_GetAttrString(response, "data");
    }

    *code = PyInt_AsLong(attrCode);
    if(PyErr_Occurred()) {
        goto error;
    }

    if(attrDataOrMessage) {
        *dataOrMessage = PyString_AsString(attrDataOrMessage);
        if(PyErr_Occurred()) {
            goto error;
        }
        *len = (int)PyString_Size(attrDataOrMessage);
        if(PyErr_Occurred()) {
            goto error;
        }
    }
    NaClLog(3, "ParseResponse isError=%d, code=%d, len=%d\n", *isError, *code, *len);
    if(*isError) {
        NaClLog(3, "Error message: %s\n", *dataOrMessage);
    }
    retval = 1;
    goto cleanup;
error:
    NaClLog(LOG_ERROR, "ParseResponse Python error\n");
    PyErr_Print();
cleanup:
    Py_XDECREF(attrIsError);
    Py_XDECREF(attrCode);
    Py_XDECREF(attrDataOrMessage);
    return retval;
}


#define CHECK_NOT_NULL(x) do { if (!(x)) return -EINVAL; } while (0)

#define LIND_API_PART1                                                  \
        int retval = 0;                                                 \
        int _code = 0;                                                  \
        int _isError = 0;                                               \
        char *_data = NULL;                                             \
        int _len = 0;                                                   \
        int _offset = 0;                                                \
        PyObject *callArgs = NULL;                                      \
        PyObject *response = NULL;                                      \
        PyGILState_STATE gstate;                                        \
        gstate = PyGILState_Ensure()

#define LIND_API_PART2                                                  \
        if (!py_context) {                                              \
            retval = -1;                                                \
            errno = ENOSYS;                                             \
            goto cleanup;                                               \
        }                                                               \
        GOTO_ERROR_IF_NULL(callArgs);                                   \
        response = CallPythonFunc(py_context, "LindSyscall", callArgs); \
        ParseResponse(response, &_isError, &_code, &_data, &_len);      \
        errno = _isError ? _code : 0;                                   \
        retval = _isError ? -1 : _code;                                 \
        UNREFERENCED_PARAMETER(_offset)

#define LIND_API_PART3                                                  \
        goto cleanup;                                                   \
        error:                                                          \
            PyErr_Print();                                              \
        cleanup:                                                        \
            Py_XDECREF(callArgs);                                       \
            Py_XDECREF(response);                                       \
            PyGILState_Release(gstate);                                 \
            return retval

#define COPY_DATA(var, maxlen)                                          \
        if (!_isError) {                                                \
            assert(_len<=(int)(maxlen));                                \
            if(var) {                                                   \
                assert(_data!=NULL);                                    \
                memcpy((var), _data, _len);                             \
            }                                                           \
        }

#define COPY_DATA_OFFSET(var, maxlen, total, current)                   \
        if (_data) {                                                    \
            if (!_isError) {                                            \
                assert(((int*)_data)[(current)]<=(int)(maxlen));        \
                if (var) {                                              \
                    assert(_data!=NULL);                                \
                    memcpy((var),                                       \
                           _data + sizeof(int) * (total) + _offset,     \
                           ((int *)_data)[(current)]);                  \
                }                                                       \
            }                                                           \
            _offset += ((int*)_data)[(current)];                        \
        }

int lind_pread(int fd, void *buf, int count, off_t offset)
{
    off_t cur_pos=0;
    int ret = 0;
    cur_pos = lind_lseek (0, fd, SEEK_CUR);
    lind_lseek(offset, fd, SEEK_SET);
    ret = lind_read(fd, count, buf);
    lind_lseek(cur_pos, fd, SEEK_SET);
    return ret;
}

int lind_pwrite(int fd, const void *buf, int count, off_t offset)
{
    off_t cur_pos=0;
    int ret = 0;
    cur_pos = lind_lseek (0, fd, SEEK_CUR);
    lind_lseek(offset, fd, SEEK_SET);
    ret = lind_write(fd, count, buf);
    lind_lseek(cur_pos, fd, SEEK_SET);
    return ret;
}

int lind_access (int version, const char *file)
{
    LIND_API_PART1;
    callArgs = Py_BuildValue("(i[is])", LIND_safe_fs_access, version, file);
    LIND_API_PART2;
    LIND_API_PART3;
}

int lind_unlink (const char *name)
{
    LIND_API_PART1;
    callArgs = Py_BuildValue("(i[s])", LIND_safe_fs_unlink, name);
    LIND_API_PART2;
    LIND_API_PART3;
}

int lind_link (const char *from, const char *to)
{
    LIND_API_PART1;
    callArgs = Py_BuildValue("(i[ss])", LIND_safe_fs_link, from, to);
    LIND_API_PART2;
    LIND_API_PART3;
}

int lind_chdir (const char *name)
{
    LIND_API_PART1;
    callArgs = Py_BuildValue("(i[s])", LIND_safe_fs_chdir, name);
    LIND_API_PART2;
    LIND_API_PART3;
}

int lind_mkdir (int mode, const char *path)
{
    LIND_API_PART1;
    callArgs = Py_BuildValue("(i[is])", LIND_safe_fs_mkdir, mode, path);
    LIND_API_PART2;
    LIND_API_PART3;
}

int lind_rmdir (const char *path)
{
    LIND_API_PART1;
    callArgs = Py_BuildValue("(i[is])", LIND_safe_fs_rmdir, path);
    LIND_API_PART2;
    LIND_API_PART3;
}

int lind_xstat (int version, const char *path, struct lind_stat *buf)
{
    LIND_API_PART1;
    callArgs = Py_BuildValue("(i[is])", LIND_safe_fs_xstat, version, path);
    LIND_API_PART2;
    COPY_DATA(buf, sizeof(*buf))
    LIND_API_PART3;
}

int lind_open (int flags, int mode, const char *path)
{
    LIND_API_PART1;
    callArgs = Py_BuildValue("(i[iis])", LIND_safe_fs_open, flags, mode, path);
    LIND_API_PART2;
    LIND_API_PART3;
}

int lind_close (int fd)
{
    LIND_API_PART1;
    callArgs = Py_BuildValue("(i[i])", LIND_safe_fs_close, fd);
    LIND_API_PART2;
    LIND_API_PART3;
}

int lind_read (int fd, int size, void *buf)
{
    LIND_API_PART1;
    callArgs = Py_BuildValue("(i[ii])", LIND_safe_fs_read, fd, size);
    LIND_API_PART2;
    COPY_DATA(buf, size)
    LIND_API_PART3;
}

int lind_write (int fd, size_t count, const void *buf)
{
    LIND_API_PART1;
    CHECK_NOT_NULL(buf);
    callArgs = Py_BuildValue("(i[iis#])", LIND_safe_fs_write, fd, count, buf, count);
    LIND_API_PART2;
    LIND_API_PART3;
}

int _lind_lseek (off_t offset, int fd, int whence, off_t * ret)
{
    LIND_API_PART1;
    callArgs = Py_BuildValue("(i[iii])", LIND_safe_fs_lseek, offset, fd, whence);
    LIND_API_PART2;
    COPY_DATA(ret, sizeof(*ret))
    LIND_API_PART3;
}

int lind_lseek (off_t offset, int fd, int whence)
{
    off_t ret_off=0;
    int ret=0;
    ret = _lind_lseek (offset, fd, whence, &ret_off);
    if(ret<0) {
        return ret;
    }
    return ret_off;
}

int lind_fxstat (int fd, int version, struct lind_stat *buf)
{
    LIND_API_PART1;
    callArgs = Py_BuildValue("(i[ii])", LIND_safe_fs_fxstat, fd, version);
    LIND_API_PART2;
    COPY_DATA(buf, sizeof(*buf))
    LIND_API_PART3;
}

int lind_fstatfs (int fd, struct lind_statfs *buf)
{
    LIND_API_PART1;
    callArgs = Py_BuildValue("(i[i])", LIND_safe_fs_fstatfs, fd);
    LIND_API_PART2;
    COPY_DATA(buf, sizeof(*buf))
    LIND_API_PART3;
}

int lind_statfs (const char *path, struct lind_statfs *buf)
{
    LIND_API_PART1;
    callArgs = Py_BuildValue("(i[s])", LIND_safe_fs_statfs, path);
    LIND_API_PART2;
    COPY_DATA(buf, sizeof(*buf))
    LIND_API_PART3;
}

int lind_noop (void)
{
    LIND_API_PART1;
    callArgs = Py_BuildValue("(i[])", LIND_debug_noop);
    LIND_API_PART2;
    LIND_API_PART3;
}

int lind_getpid (pid_t *buf)
{
    LIND_API_PART1;
    callArgs = Py_BuildValue("(i[])", LIND_sys_getpid);
    LIND_API_PART2;
    COPY_DATA(buf, sizeof(*buf))
    LIND_API_PART3;
}

int lind_dup (int oldfd)
{
    LIND_API_PART1;
    callArgs = Py_BuildValue("(i[i])", LIND_safe_fs_dup, oldfd);
    LIND_API_PART2;
    LIND_API_PART3;
}

int lind_dup2 (int oldfd, int newfd)
{
    LIND_API_PART1;
    callArgs = Py_BuildValue("(i[ii])", LIND_safe_fs_dup, oldfd, newfd);
    LIND_API_PART2;
    LIND_API_PART3;
}

int lind_getdents (int fd, size_t nbytes, char *buf)
{
    LIND_API_PART1;
    callArgs = Py_BuildValue("(i[ii])", LIND_safe_fs_getdents, fd, nbytes);
    LIND_API_PART2;
    COPY_DATA(buf, nbytes)
    LIND_API_PART3;
}

int lind_fcntl_get (int fd, int cmd)
{
    LIND_API_PART1;
    callArgs = Py_BuildValue("(i[ii])", LIND_safe_fs_fcntl, fd, cmd);
    LIND_API_PART2;
    LIND_API_PART3;
}

int lind_fcntl_set (int fd, int cmd, long set_op)
{
    LIND_API_PART1;
    callArgs = Py_BuildValue("(i[iil])", LIND_safe_fs_fcntl, fd, cmd, set_op);
    LIND_API_PART2;
    LIND_API_PART3;
}

int lind_socket (int domain, int type, int protocol)
{
    LIND_API_PART1;
    callArgs = Py_BuildValue("(i[iii])", LIND_safe_net_socket, domain, type, protocol);
    LIND_API_PART2;
    LIND_API_PART3;
}

int lind_bind (int sockfd, socklen_t addrlen, const struct sockaddr *addr)
{
    LIND_API_PART1;
    CHECK_NOT_NULL(addr);
    callArgs = Py_BuildValue("(i[iis#])", LIND_safe_net_bind, sockfd, addrlen, addr, addrlen);
    LIND_API_PART2;
    LIND_API_PART3;
}

int lind_send (int sockfd, size_t len, int flags, const void *buf)
{
    LIND_API_PART1;
    CHECK_NOT_NULL(buf);
    callArgs = Py_BuildValue("(i[iiis#])", LIND_safe_net_send, sockfd, len, flags, buf, len);
    LIND_API_PART2;
    LIND_API_PART3;
}

int lind_recv (int sockfd, size_t len, int flags, void *buf)
{
    LIND_API_PART1;
    CHECK_NOT_NULL(buf);
    callArgs = Py_BuildValue("(i[iii])", LIND_safe_net_recv, sockfd, len, flags);
    LIND_API_PART2;
    COPY_DATA(buf, len)
    LIND_API_PART3;
}

int lind_connect (int sockfd, socklen_t addrlen, const struct sockaddr *src_addr)
{
    LIND_API_PART1;
    CHECK_NOT_NULL(src_addr);
    callArgs = Py_BuildValue("(i[iis#])", LIND_safe_net_connect, sockfd, addrlen, src_addr, addrlen);
    LIND_API_PART2;
    LIND_API_PART3;
}

int lind_listen (int sockfd, int backlog)
{
    LIND_API_PART1;
    callArgs = Py_BuildValue("(i[ii])", LIND_safe_net_listen, sockfd, backlog);
    LIND_API_PART2;
    LIND_API_PART3;
}

/* unimplemented */
int lind_sendto (int sockfd, size_t len, int flags, socklen_t addrlen, const struct sockaddr_in *dest_addr, const void *buf)
{
    UNREFERENCED_PARAMETER(sockfd);
    UNREFERENCED_PARAMETER(len);
    UNREFERENCED_PARAMETER(flags);
    UNREFERENCED_PARAMETER(addrlen);
    UNREFERENCED_PARAMETER(dest_addr);
    UNREFERENCED_PARAMETER(buf);
    return 0;
}

int lind_accept (int sockfd, socklen_t addrlen)
{
    LIND_API_PART1;
    callArgs = Py_BuildValue("(i[ii])", LIND_safe_net_accept, sockfd, addrlen);
    LIND_API_PART2;
    LIND_API_PART3;
}

/* unimplemented */
int lind_getpeername (int sockfd, socklen_t addrlen_in, __SOCKADDR_ARG addr, socklen_t *addrlen_out)
{
    UNREFERENCED_PARAMETER(sockfd);
    UNREFERENCED_PARAMETER(addrlen_in);
    UNREFERENCED_PARAMETER(addr);
    UNREFERENCED_PARAMETER(addrlen_out);
    return 0;
}

int lind_setsockopt (int sockfd, int level, int optname, socklen_t optlen, const void *optval)
{
    LIND_API_PART1;
    CHECK_NOT_NULL(optval);
    callArgs = Py_BuildValue("(i[iiiis#])", LIND_safe_net_setsockopt, sockfd, level, optname, optlen, optval, optlen);
    LIND_API_PART2;
    LIND_API_PART3;
}

int lind_getsockopt (int sockfd, int level, int optname, socklen_t optlen, void *optval)
{
    LIND_API_PART1;
    callArgs = Py_BuildValue("(i[iiii])", LIND_safe_net_getsockopt, sockfd, level, optname, optlen);
    LIND_API_PART2;
    COPY_DATA(optval, optlen)
    LIND_API_PART3;
}

int lind_shutdown (int sockfd, int how)
{
    LIND_API_PART1;
    callArgs = Py_BuildValue("(i[ii])", LIND_safe_net_shutdown, sockfd, how);
    LIND_API_PART2;
    LIND_API_PART3;
}

int lind_select (int nfds, fd_set * readfds, fd_set * writefds, fd_set * exceptfds,
        struct timeval *timeout, struct select_results *result)
{
    PyObject *readFdObj = NULL;
    PyObject *writeFdObj = NULL;
    PyObject *exceptFdObj = NULL;
    PyObject *timeValObj = NULL;
    LIND_API_PART1;
    if(readfds) {
        readFdObj = PyString_FromStringAndSize((char*)readfds, sizeof(fd_set));
    } else {
        readFdObj = Py_None;
        Py_INCREF(readFdObj);
    }
    if(writefds) {
        writeFdObj = PyString_FromStringAndSize((char*)writefds, sizeof(fd_set));
    } else {
        writeFdObj = Py_None;
        Py_INCREF(writeFdObj);
    }
    if(exceptfds) {
        exceptFdObj = PyString_FromStringAndSize((char*)exceptfds, sizeof(fd_set));
    } else {
        exceptFdObj = Py_None;
        Py_INCREF(exceptFdObj);
    }
    if(timeout) {
        timeValObj = PyString_FromStringAndSize((char*)timeout, sizeof(struct timeval));
    } else {
        timeValObj = Py_None;
        Py_INCREF(timeValObj);
    }
    callArgs = Py_BuildValue("(i[iOOOO])", LIND_safe_net_select, nfds, readFdObj,
            writeFdObj, exceptFdObj, timeValObj);
    Py_XDECREF(readFdObj);
    Py_XDECREF(writeFdObj);
    Py_XDECREF(exceptFdObj);
    Py_XDECREF(timeValObj);
    LIND_API_PART2;
    COPY_DATA(result, sizeof(*result))
    LIND_API_PART3;
}

int lind_getifaddrs (int ifaddrs_buf_siz, void *ifaddrs)
{
    LIND_API_PART1;
    callArgs = Py_BuildValue("(i[i])", LIND_safe_net_getifaddrs, ifaddrs_buf_siz);
    LIND_API_PART2;
    COPY_DATA(ifaddrs, ifaddrs_buf_siz)
    LIND_API_PART3;
}

int lind_recvfrom (int sockfd, size_t len, int flags, socklen_t addrlen, socklen_t *addrlen_out, void *buf, struct sockaddr *src_addr)
{
    LIND_API_PART1;
    callArgs = Py_BuildValue("(i[iiii])", LIND_safe_net_recvfrom, sockfd, len, flags, addrlen);
    LIND_API_PART2;
    COPY_DATA_OFFSET(addrlen_out, sizeof(*addrlen_out), 3, 0)
    COPY_DATA_OFFSET(buf, len, 3, 1)
    COPY_DATA_OFFSET(src_addr, sizeof(*src_addr), 3, 2)
    LIND_API_PART3;
}

int lind_poll (int nfds, int timeout, struct pollfd *fds_in, struct pollfd *fds_out)
{
    LIND_API_PART1;
    callArgs = Py_BuildValue("(i[iis#])", LIND_safe_net_poll, nfds, timeout, fds_in, sizeof(struct pollfd)*nfds);
    LIND_API_PART2;
    COPY_DATA(fds_out, sizeof(struct pollfd)*nfds)
    LIND_API_PART3;
}

int lind_socketpair (int domain, int type, int protocol, int *fds)
{
    LIND_API_PART1;
    callArgs = Py_BuildValue("(i[iii])", LIND_safe_net_socketpair, domain, type, protocol);
    LIND_API_PART2;
    COPY_DATA(fds, sizeof(int)*2)
    LIND_API_PART3;
}

int lind_getuid (uid_t * buf)
{
    LIND_API_PART1;
    callArgs = Py_BuildValue("(i[])", LIND_safe_sys_getuid);
    LIND_API_PART2;
    COPY_DATA(buf, sizeof(*buf))
    LIND_API_PART3;
}

int lind_geteuid (uid_t * buf)
{
    LIND_API_PART1;
    callArgs = Py_BuildValue("(i[])", LIND_safe_sys_geteuid);
    LIND_API_PART2;
    COPY_DATA(buf, sizeof(*buf))
    LIND_API_PART3;
}

int lind_getgid (gid_t * buf)
{
    LIND_API_PART1;
    callArgs = Py_BuildValue("(i[])", LIND_safe_sys_getgid);
    LIND_API_PART2;
    COPY_DATA(buf, sizeof(*buf))
    LIND_API_PART3;
}

int lind_getegid (gid_t * buf)
{
    LIND_API_PART1;
    callArgs = Py_BuildValue("(i[])", LIND_safe_sys_getegid);
    LIND_API_PART2;
    COPY_DATA(buf, sizeof(*buf))
    LIND_API_PART3;
}

int lind_flock (int fd, int operation)
{
    LIND_API_PART1;
    callArgs = Py_BuildValue("(i[ii])", LIND_safe_fs_flock, fd, operation);
    LIND_API_PART2;
    LIND_API_PART3;
}

