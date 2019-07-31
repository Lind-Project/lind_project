/*
 * Copyright (c) 2012 The Native Client Authors. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

/*
 * NaCl service run-time, non-platform specific system call helper routines.
 */

#ifndef NATIVE_CLIENT_SERVICE_RUNTIME_NACL_SYSCALL_COMMON_H__
#define NATIVE_CLIENT_SERVICE_RUNTIME_NACL_SYSCALL_COMMON_H__ 1

#include "native_client/src/include/portability.h"

#include "native_client/src/include/nacl_base.h"
#include "native_client/src/shared/platform/nacl_host_desc.h"
#include "native_client/src/trusted/service_runtime/include/sys/time.h"

EXTERN_C_BEGIN

struct NaClAbiNaClImcMsgHdr;
struct NaClApp;
struct NaClAppThread;
struct NaClSocketAddress;
struct NaClDesc;
struct NaClImcMsgHdr;
struct nacl_abi_stat;
struct rusage;

int32_t NaClSysNotImplementedDecoder(struct NaClAppThread *natp);

void NaClAddSyscall(int num, int32_t (*fn)(struct NaClAppThread *));

int32_t NaClSysNull(struct NaClAppThread *natp);

int32_t NaClSysBrk(struct NaClAppThread *natp,
                   uintptr_t            new_break);

int NaClHighResolutionTimerEnabled(void);

int32_t NaClOpenAclCheck(struct NaClApp *nap,
                         char const     *path,
                         int            flags,
                         int            mode);

int32_t NaClStatAclCheck(struct NaClApp *nap,
                         char const     *path);

int32_t NaClSysGetpid(struct NaClAppThread *natp);
int32_t NaClSysGetppid(struct NaClAppThread *natp);

int32_t NaClSysExit(struct NaClAppThread  *natp,
                    int                   status);

int32_t NaClSysThreadExit(struct NaClAppThread  *natp,
                          int32_t               *stack_flag);

extern int NaClAclBypassChecks;

void NaClInsecurelyBypassAllAclChecks(void);

int32_t NaClSysNameService(struct NaClAppThread *natp,
                           int32_t              *desc_addr);

int32_t NaClSysDup(struct NaClAppThread *natp,
                   int                  oldfd);

int32_t NaClSysDup2(struct NaClAppThread  *natp,
                    int                   oldfd,
                    int                   newfd);

int32_t NaClSysDup3(struct NaClAppThread  *natp,
                    int                   oldfd,
                    int                   newfd,
                    int                   flags);

int32_t NaClSysOpen(struct NaClAppThread  *natp,
                    char                  *pathname,
                    int                   flags,
                    int                   mode);

int32_t NaClSysClose(struct NaClAppThread *natp,
                     int                  d);

int32_t NaClSysRead(struct NaClAppThread  *natp,
                    int                   d,
                    void                  *buf,
                    size_t                count);

int32_t NaClSysWrite(struct NaClAppThread *natp,
                     int                  d,
                     void                 *buf,
                     size_t               count);

int32_t NaClSysLseek(struct NaClAppThread *natp,
                     int                  d,
                     nacl_abi_off_t       *offp,
                     int                  whence);

int32_t NaClSysIoctl(struct NaClAppThread *natp,
                     int                  d,
                     int                  request,
                     void                 *arg);

int32_t NaClSysFstat(struct NaClAppThread *natp,
                     int                  d,
                     struct nacl_abi_stat *nasp);

int32_t NaClSysStat(struct NaClAppThread *natp,
                    const char           *pathname,
                    struct nacl_abi_stat *buf);

int32_t NaClSysLStat(struct NaClAppThread  *natp,
                    const char            *pathname,
                    struct nacl_abi_stat  *buf);

int32_t NaClSysMkdir(struct NaClAppThread *natp,
                     uint32_t             pathname,
                     int                  mode);

int32_t NaClSysRmdir(struct NaClAppThread *natp,
                     uint32_t             pathname);

int32_t NaClSysChdir(struct NaClAppThread *natp,
                     uint32_t             pathname);

int32_t NaClSysGetcwd(struct NaClAppThread *natp,
                      uint32_t             buffer,
                      int                  len);

int32_t NaClSysUnlink(struct NaClAppThread *natp,
                      uint32_t             pathname);

/* bool */
int NaClSysCommonAddrRangeContainsExecutablePages(struct NaClApp *nap,
                                                  uintptr_t usraddr,
                                                  size_t length);

/* bool */
int NaClSysCommonAddrRangeInAllowedDynamicCodeSpace(struct NaClApp *nap,
                                                    uintptr_t usraddr,
                                                    size_t length);

int32_t NaClSysMmap(struct NaClAppThread  *natp,
                    void                  *start,
                    size_t                length,
                    int                   prot,
                    int                   flags,
                    int                   d,
                    nacl_abi_off_t        *offp);

int32_t NaClSysMmapIntern(struct NaClApp  *nap,
                          void            *start,
                          size_t          length,
                          int             prot,
                          int             flags,
                          int             d,
                          nacl_abi_off_t  offset);

int32_t NaClSysMmap(struct NaClAppThread  *natp,
                    void                  *start,
                    size_t                length,
                    int                   prot,
                    int                   flags,
                    int                   d,
                    nacl_abi_off_t        *offp);

int32_t NaClSysMprotectInternal(struct NaClApp  *nap,
                                uint32_t        start,
                                size_t          length,
                                int             prot);

int32_t NaClSysMprotect(struct NaClAppThread  *natp,
                        uint32_t              start,
                        size_t                length,
                        int                   prot);

int32_t NaClSysMunmap(struct NaClAppThread  *natp,
                      void                  *start,
                      size_t                length);

int32_t NaClSysGetdents(struct NaClAppThread  *natp,
                        int                   d,
                        void                  *dirp,
                        size_t                count);

int32_t NaClSysGetTimeOfDay(struct NaClAppThread      *natp,
                            struct nacl_abi_timeval   *tv,
                            struct nacl_abi_timezone  *tz);

int32_t NaClSysClockGetRes(struct NaClAppThread *natp,
                           int                  clk_id,
                           uint32_t             tsp);

int32_t NaClSysClockGetTime(struct NaClAppThread  *natp,
                            int                   clk_id,
                            uint32_t              tsp);

int32_t NaClSysImcMakeBoundSock(struct NaClAppThread *natp,
                                int32_t              *sap);

int32_t NaClSysImcAccept(struct NaClAppThread  *natp,
                         int                   d);

int32_t NaClSysImcConnect(struct NaClAppThread *natp,
                          int                  d);

int32_t NaClSysImcSendmsg(struct NaClAppThread         *natp,
                          int                          d,
                          struct NaClAbiNaClImcMsgHdr  *nanimhp,
                          int                          flags);

int32_t NaClSysImcRecvmsg(struct NaClAppThread         *natp,
                          int                          d,
                          struct NaClAbiNaClImcMsgHdr  *nanimhp,
                          int                          flags);

int32_t NaClSysImcMemObjCreate(struct NaClAppThread  *natp,
                               size_t                size);

int32_t NaClSysTlsInit(struct NaClAppThread  *natp,
                       uint32_t              thread_ptr);

int32_t NaClSysThreadCreate(struct NaClAppThread *natp,
                            void                 *prog_ctr,
                            uint32_t             stack_ptr,
                            uint32_t             thread_ptr,
                            uint32_t             second_thread_ptr);

int32_t NaClSysTlsGet(struct NaClAppThread *natp);

int32_t NaClSysSecondTlsSet(struct NaClAppThread *natp,
                            uint32_t             new_value);

int32_t NaClSysSecondTlsGet(struct NaClAppThread *natp);

int32_t NaClSysThreadNice(struct NaClAppThread *natp,
                          int                  nice);

/* mutex */

int32_t NaClSysMutexCreate(struct NaClAppThread *natp);

int32_t NaClSysMutexLock(struct NaClAppThread *natp,
                         int32_t              mutex_handle);

int32_t NaClSysMutexUnlock(struct NaClAppThread *natp,
                           int32_t              mutex_handle);

int32_t NaClSysMutexTrylock(struct NaClAppThread *natp,
                            int32_t              mutex_handle);

/* condition variable */

int32_t NaClSysCondCreate(struct NaClAppThread *natp);

int32_t NaClSysCondWait(struct NaClAppThread *natp,
                        int32_t              cond_handle,
                        int32_t              mutex_handle);

int32_t NaClSysCondSignal(struct NaClAppThread *natp,
                          int32_t              cond_handle);

int32_t NaClSysCondBroadcast(struct NaClAppThread *natp,
                             int32_t              cond_handle);

int32_t NaClSysCondTimedWaitRel(struct NaClAppThread     *natp,
                                int32_t                  cond_handle,
                                int32_t                  mutex_handle,
                                struct nacl_abi_timespec *ts);

int32_t NaClSysCondTimedWaitAbs(struct NaClAppThread     *natp,
                                int32_t                  cond_handle,
                                int32_t                  mutex_handle,
                                struct nacl_abi_timespec *ts);

int32_t NaClCommonDescSocketPair(struct NaClDesc      **pair);

int32_t NaClSysImcSocketPair(struct NaClAppThread *natp,
                             uint32_t             descs_out);
/* Semaphores */
int32_t NaClSysSemCreate(struct NaClAppThread *natp,
                         int32_t              init_value);

int32_t NaClSysSemWait(struct NaClAppThread *natp,
                       int32_t              sem_handle);

int32_t NaClSysSemPost(struct NaClAppThread *natp,
                       int32_t              sem_handle);

int32_t NaClSysSemGetValue(struct NaClAppThread *natp,
                           int32_t              sem_handle);

int32_t NaClSysNanosleep(struct NaClAppThread     *natp,
                         struct nacl_abi_timespec *req,
                         struct nacl_abi_timespec *rem);

int32_t NaClSysSchedYield(struct NaClAppThread *natp);

int32_t NaClSysExceptionHandler(struct NaClAppThread *natp,
                                uint32_t             handler_addr,
                                uint32_t             old_handler);

int32_t NaClSysExceptionStack(struct NaClAppThread *natp,
                              uint32_t             stack_addr,
                              uint32_t             stack_size);

int32_t NaClSysExceptionClearFlag(struct NaClAppThread *natp);

int32_t NaClSysTestInfoLeak(struct NaClAppThread *natp);

int32_t NaClSysTestCrash(struct NaClAppThread *natp, int crash_type);

int32_t NaClSysPipe(struct NaClAppThread *natp, uint32_t *pipedes);
int32_t NaClSysPipe2(struct NaClAppThread *natp, uint32_t *pipedes, int flags);
int32_t NaClSysFork(struct NaClAppThread *natp);
int32_t NaClSysExecve(struct NaClAppThread *natp, void* pathname, void* argv, void* envp);
int32_t NaClSysExecv(struct NaClAppThread *natp, void *pathname, void *argv);
int32_t NaClSysWaitpid(struct NaClAppThread *natp, int pid, uint32_t *stat_loc, int options);
int32_t NaClSysWait(struct NaClAppThread *natp, uint32_t *stat_loc);
int32_t NaClSysWait4(struct NaClAppThread *natp, int pid, uint32_t *stat_loc, int options, void *rusage);
int32_t NaClSysSigProcMask(struct NaClAppThread *natp, int how, const void *set, void *oldset);

EXTERN_C_END

#endif  /* NATIVE_CLIENT_SERVICE_RUNTIME_NACL_SYSCALL_COMMON_H__ */
