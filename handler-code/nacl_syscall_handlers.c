/*
 * Copyright (c) 2012 The Native Client Authors. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */


#include <time.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <errno.h>
#include <sched.h>
#include <sys/mman.h>
#include <string.h>
#include <unistd.h>

#include "native_client/src/include/portability.h"
#include "native_client/src/include/nacl_platform.h"
#include "native_client/src/include/nacl_macros.h"

#include "native_client/src/public/imc_types.h"

#include "native_client/src/shared/platform/nacl_check.h"
#include "native_client/src/shared/platform/nacl_log.h"
#include "native_client/src/shared/platform/nacl_sync_checked.h"
#include "native_client/src/shared/platform/nacl_time.h"

#include "native_client/src/trusted/desc/nacl_desc_base.h"
#include "native_client/src/trusted/desc/nacl_desc_conn_cap.h"
#include "native_client/src/trusted/desc/nacl_desc_imc.h"
#include "native_client/src/trusted/desc/nacl_desc_imc_bound_desc.h"
#include "native_client/src/trusted/desc/nacl_desc_imc_shm.h"
#include "native_client/src/trusted/desc/nacl_desc_io.h"

#include "native_client/src/trusted/service_runtime/nacl_app_thread.h"
#include "native_client/src/trusted/service_runtime/nacl_config.h"
#include "native_client/src/trusted/service_runtime/nacl_copy.h"
#include "native_client/src/trusted/service_runtime/nacl_globals.h"
#include "native_client/src/trusted/service_runtime/nacl_syscall_handlers.h"
#include "native_client/src/trusted/service_runtime/nacl_syscall_common.h"
#include "native_client/src/trusted/service_runtime/nacl_text.h"
#include "native_client/src/trusted/service_runtime/sel_ldr.h"
#include "native_client/src/trusted/service_runtime/sel_memory.h"
#include "native_client/src/trusted/service_runtime/sel_util.h"
#include "native_client/src/trusted/service_runtime/sys_list_mappings.h"
#include "native_client/src/trusted/service_runtime/lind_syscalls.h"

#include "native_client/src/trusted/service_runtime/include/bits/mman.h"
#include "native_client/src/trusted/service_runtime/include/bits/nacl_syscalls.h"
#include "native_client/src/trusted/service_runtime/include/machine/_types.h"
#include "native_client/src/trusted/service_runtime/include/sys/errno.h"
#include "native_client/src/trusted/service_runtime/include/sys/fcntl.h"
#include "native_client/src/trusted/service_runtime/include/sys/stat.h"
#include "native_client/src/trusted/service_runtime/include/sys/time.h"
#include "native_client/src/trusted/service_runtime/include/sys/unistd.h"

#include "native_client/src/trusted/service_runtime/linux/nacl_syscall_inl.h"


/*
 * TODO(bsy): REMOVE THIS AND PROVIDE GETRUSAGE.  This is normally
 * not a syscall; instead, it is a library routine on top of
 * getrusage, with appropriate clock tick translation.
 */
int32_t NaClSysClock(struct NaClAppThread *natp) {
  int32_t retval;

  NaClLog(3,
          ("Entered NaClSysClock(%08"NACL_PRIxPTR")\n"),
          (uintptr_t) natp);

  retval = clock();
  return retval;
}

int32_t NaClSysSysconf(struct NaClAppThread *natp,
                       int32_t name,
                       int32_t *result) {
  int32_t         retval = -NACL_ABI_EINVAL;
  int32_t         result_value;

  NaClLog(3,
          ("Entered NaClSysSysconf(%08"NACL_PRIxPTR
           "x, %d, 0x%08"NACL_PRIxPTR")\n"),
          (uintptr_t) natp, name, (uintptr_t) result);

  switch (name) {
    case NACL_ABI__SC_NPROCESSORS_ONLN: {
      if (-1 == natp->nap->sc_nprocessors_onln) {
        /* Unable to get the number of processors at startup. */
        retval = -NACL_ABI_EINVAL;
        goto cleanup;
      }
      result_value = natp->nap->sc_nprocessors_onln;
      break;
    }
    case NACL_ABI__SC_SENDMSG_MAX_SIZE: {
      /* TODO(sehr,bsy): this value needs to be determined at run time. */
      const int32_t kImcSendMsgMaxSize = 1 << 16;
      result_value = kImcSendMsgMaxSize;
      break;
    }
    case NACL_ABI__SC_PAGESIZE: {
      result_value = 1 << 16;  /* always 64k pages */
      break;
    }
    default: {
      retval = -NACL_ABI_EINVAL;
      goto cleanup;
    }
  }
  if (!NaClCopyOutToUser(natp->nap, (uintptr_t) result, &result_value,
                         sizeof result_value)) {
    retval = -NACL_ABI_EFAULT;
    goto cleanup;
  }
  retval = 0;
cleanup:
  return retval;
}

/*
 * WARNING WARNING WARNING WARNING WARNING WARNING WARNING WARNING WARNING
 *
 * Automatically generated code.  See nacl_syscall_handlers_gen.py
 *
 * NaCl Server Runtime Service Call abstractions
 */

/* this function was automagically generated */
static int32_t NaClSysNullDecoder(struct NaClAppThread *natp) {
  #ifdef SYSCALL_TIMING
  int32_t retval;
  clock_t nacl_sys_begin;
  clock_t nacl_sys_finish;
  #endif
  #ifdef NACL_SYSCALL_TRACE_ENABLED
  struct NaClApp *nap = natp->nap;
  int32_t retval;
#if 0
  unsigned int i = 0;
#endif
  #endif
    NaClCopyDropLock(natp->nap);
  #ifdef SYSCALL_TIMING
  nacl_syscall_counter++;
  nacl_syscall_invoked_times[NACL_sys_null]++;
  nacl_sys_begin = clock();
  retval = NaClSysNull(natp);
  nacl_sys_finish = clock();
  nacl_syscall_execution_time[NACL_sys_null] += (double)(nacl_sys_finish - nacl_sys_begin) / CLOCKS_PER_SEC;
  return retval;
  #endif
  #ifdef NACL_SYSCALL_TRACE_ENABLED
  printf("[NaClSysCallInterface] cage id = %d, syscall_num = NACL_sys_null [enter][syscall_depth = %d]\n", nap->cage_id, nacl_syscall_trace_level_counter);
  printf("==> NACL_sys_null(");
#if 0
  for (i = 0; i < sizeof(p)/4; i++) {
    printf("%x,", *((uint32_t *)&p+i));
  }
#endif
  printf(")\n");
  nacl_syscall_trace_level_counter++;
  retval = NaClSysNull(natp);
  nacl_syscall_trace_level_counter--;
  printf("[NaClSysCallInterface] cage id = %d, syscall_num = NACL_sys_null [exit][syscall_depth = %d] \n", nap->cage_id, nacl_syscall_trace_level_counter);
  return retval;
  #endif

  return NaClSysNull(natp);

}

/*
 * Check that the function being wrapped has the same type as the type
 * declared in SYSCALL_LIST.
 */
static INLINE void AssertSameType_NaClSysNull(void) {
  /* This assignment will give an error if the argument types don't match. */
  int32_t (*dummy)(struct NaClAppThread *natp) = NaClSysNull;
  /* 'dummy' is not actually a parameter but this suppresses the warning. */
  UNREFERENCED_PARAMETER(dummy);
}

/* this function was automagically generated */
static int32_t NaClSysNameServiceDecoder(struct NaClAppThread *natp) {
  #ifdef SYSCALL_TIMING
  int32_t retval;
  clock_t nacl_sys_begin;
  clock_t nacl_sys_finish;
  #endif
  #ifdef NACL_SYSCALL_TRACE_ENABLED
  struct NaClApp *nap = natp->nap;
  int32_t retval;
#if 1
  unsigned int i = 0;
#endif
  #endif
    struct NaClSysNameServiceArgs {
    uint32_t desc_in_out;
  } p;
  if (!NaClCopyInFromUserAndDropLock(natp->nap, &p, natp->usr_syscall_args,
                                     sizeof p)) {
    return -NACL_ABI_EFAULT;
  }


  #ifdef SYSCALL_TIMING
  nacl_syscall_counter++;
  nacl_syscall_invoked_times[NACL_sys_nameservice]++;
  nacl_sys_begin = clock();
  retval = NaClSysNameService(natp, (int *) (uintptr_t) p.desc_in_out);
  nacl_sys_finish = clock();
  nacl_syscall_execution_time[NACL_sys_nameservice] += (double)(nacl_sys_finish - nacl_sys_begin) / CLOCKS_PER_SEC;
  return retval;
  #endif
  #ifdef NACL_SYSCALL_TRACE_ENABLED
  printf("[NaClSysCallInterface] cage id = %d, syscall_num = NACL_sys_nameservice [enter][syscall_depth = %d]\n", nap->cage_id, nacl_syscall_trace_level_counter);
  printf("==> NACL_sys_nameservice(");
#if 1
  for (i = 0; i < sizeof(p)/4; i++) {
    printf("%x,", *((uint32_t *)&p+i));
  }
#endif
  printf(")\n");
  nacl_syscall_trace_level_counter++;
  retval = NaClSysNameService(natp, (int *) (uintptr_t) p.desc_in_out);
  nacl_syscall_trace_level_counter--;
  printf("[NaClSysCallInterface] cage id = %d, syscall_num = NACL_sys_nameservice [exit][syscall_depth = %d] \n", nap->cage_id, nacl_syscall_trace_level_counter);
  return retval;
  #endif

  return NaClSysNameService(natp, (int *) (uintptr_t) p.desc_in_out);

}

/*
 * Check that the function being wrapped has the same type as the type
 * declared in SYSCALL_LIST.
 */
static INLINE void AssertSameType_NaClSysNameService(void) {
  /* This assignment will give an error if the argument types don't match. */
  int32_t (*dummy)(struct NaClAppThread *natp, int *desc_in_out) = NaClSysNameService;
  /* 'dummy' is not actually a parameter but this suppresses the warning. */
  UNREFERENCED_PARAMETER(dummy);
}

/* this function was automagically generated */
static int32_t NaClSysDupDecoder(struct NaClAppThread *natp) {
  #ifdef SYSCALL_TIMING
  int32_t retval;
  clock_t nacl_sys_begin;
  clock_t nacl_sys_finish;
  #endif
  #ifdef NACL_SYSCALL_TRACE_ENABLED
  struct NaClApp *nap = natp->nap;
  int32_t retval;
#if 1
  unsigned int i = 0;
#endif
  #endif
    struct NaClSysDupArgs {
    uint32_t oldfd;
  } p;
  if (!NaClCopyInFromUserAndDropLock(natp->nap, &p, natp->usr_syscall_args,
                                     sizeof p)) {
    return -NACL_ABI_EFAULT;
  }


  #ifdef SYSCALL_TIMING
  nacl_syscall_counter++;
  nacl_syscall_invoked_times[NACL_sys_dup]++;
  nacl_sys_begin = clock();
  retval = NaClSysDup(natp, (int)  p.oldfd);
  nacl_sys_finish = clock();
  nacl_syscall_execution_time[NACL_sys_dup] += (double)(nacl_sys_finish - nacl_sys_begin) / CLOCKS_PER_SEC;
  return retval;
  #endif
  #ifdef NACL_SYSCALL_TRACE_ENABLED
  printf("[NaClSysCallInterface] cage id = %d, syscall_num = NACL_sys_dup [enter][syscall_depth = %d]\n", nap->cage_id, nacl_syscall_trace_level_counter);
  printf("==> NACL_sys_dup(");
#if 1
  for (i = 0; i < sizeof(p)/4; i++) {
    printf("%x,", *((uint32_t *)&p+i));
  }
#endif
  printf(")\n");
  nacl_syscall_trace_level_counter++;
  retval = NaClSysDup(natp, (int)  p.oldfd);
  nacl_syscall_trace_level_counter--;
  printf("[NaClSysCallInterface] cage id = %d, syscall_num = NACL_sys_dup [exit][syscall_depth = %d] \n", nap->cage_id, nacl_syscall_trace_level_counter);
  return retval;
  #endif

  return NaClSysDup(natp, (int)  p.oldfd);

}

/*
 * Check that the function being wrapped has the same type as the type
 * declared in SYSCALL_LIST.
 */
static INLINE void AssertSameType_NaClSysDup(void) {
  /* This assignment will give an error if the argument types don't match. */
  int32_t (*dummy)(struct NaClAppThread *natp, int oldfd) = NaClSysDup;
  /* 'dummy' is not actually a parameter but this suppresses the warning. */
  UNREFERENCED_PARAMETER(dummy);
}

/* this function was automagically generated */
static int32_t NaClSysDup2Decoder(struct NaClAppThread *natp) {
  #ifdef SYSCALL_TIMING
  int32_t retval;
  clock_t nacl_sys_begin;
  clock_t nacl_sys_finish;
  #endif
  #ifdef NACL_SYSCALL_TRACE_ENABLED
  struct NaClApp *nap = natp->nap;
  int32_t retval;
#if 1
  unsigned int i = 0;
#endif
  #endif
    struct NaClSysDup2Args {
    uint32_t oldfd;
    uint32_t newfd;
  } p;
  if (!NaClCopyInFromUserAndDropLock(natp->nap, &p, natp->usr_syscall_args,
                                     sizeof p)) {
    return -NACL_ABI_EFAULT;
  }


  #ifdef SYSCALL_TIMING
  nacl_syscall_counter++;
  nacl_syscall_invoked_times[NACL_sys_dup2]++;
  nacl_sys_begin = clock();
  retval = NaClSysDup2(natp, (int)  p.oldfd, (int)  p.newfd);
  nacl_sys_finish = clock();
  nacl_syscall_execution_time[NACL_sys_dup2] += (double)(nacl_sys_finish - nacl_sys_begin) / CLOCKS_PER_SEC;
  return retval;
  #endif
  #ifdef NACL_SYSCALL_TRACE_ENABLED
  printf("[NaClSysCallInterface] cage id = %d, syscall_num = NACL_sys_dup2 [enter][syscall_depth = %d]\n", nap->cage_id, nacl_syscall_trace_level_counter);
  printf("==> NACL_sys_dup2(");
#if 1
  for (i = 0; i < sizeof(p)/4; i++) {
    printf("%x,", *((uint32_t *)&p+i));
  }
#endif
  printf(")\n");
  nacl_syscall_trace_level_counter++;
  retval = NaClSysDup2(natp, (int)  p.oldfd, (int)  p.newfd);
  nacl_syscall_trace_level_counter--;
  printf("[NaClSysCallInterface] cage id = %d, syscall_num = NACL_sys_dup2 [exit][syscall_depth = %d] \n", nap->cage_id, nacl_syscall_trace_level_counter);
  return retval;
  #endif

  return NaClSysDup2(natp, (int)  p.oldfd, (int)  p.newfd);

}

/*
 * Check that the function being wrapped has the same type as the type
 * declared in SYSCALL_LIST.
 */
static INLINE void AssertSameType_NaClSysDup2(void) {
  /* This assignment will give an error if the argument types don't match. */
  int32_t (*dummy)(struct NaClAppThread *natp, int oldfd, int newfd) = NaClSysDup2;
  /* 'dummy' is not actually a parameter but this suppresses the warning. */
  UNREFERENCED_PARAMETER(dummy);
}

/* this function was automagically generated */
static int32_t NaClSysDup3Decoder(struct NaClAppThread *natp) {
  #ifdef SYSCALL_TIMING
  int32_t retval;
  clock_t nacl_sys_begin;
  clock_t nacl_sys_finish;
  #endif
  #ifdef NACL_SYSCALL_TRACE_ENABLED
  struct NaClApp *nap = natp->nap;
  int32_t retval;
#if 1
  unsigned int i = 0;
#endif
  #endif
    struct NaClSysDup3Args {
    uint32_t oldfd;
    uint32_t newfd;
    uint32_t flags;
  } p;
  if (!NaClCopyInFromUserAndDropLock(natp->nap, &p, natp->usr_syscall_args,
                                     sizeof p)) {
    return -NACL_ABI_EFAULT;
  }


  #ifdef SYSCALL_TIMING
  nacl_syscall_counter++;
  nacl_syscall_invoked_times[NACL_sys_dup3]++;
  nacl_sys_begin = clock();
  retval = NaClSysDup3(natp, (int)  p.oldfd, (int)  p.newfd, (int)  p.flags);
  nacl_sys_finish = clock();
  nacl_syscall_execution_time[NACL_sys_dup3] += (double)(nacl_sys_finish - nacl_sys_begin) / CLOCKS_PER_SEC;
  return retval;
  #endif
  #ifdef NACL_SYSCALL_TRACE_ENABLED
  printf("[NaClSysCallInterface] cage id = %d, syscall_num = NACL_sys_dup3 [enter][syscall_depth = %d]\n", nap->cage_id, nacl_syscall_trace_level_counter);
  printf("==> NACL_sys_dup3(");
#if 1
  for (i = 0; i < sizeof(p)/4; i++) {
    printf("%x,", *((uint32_t *)&p+i));
  }
#endif
  printf(")\n");
  nacl_syscall_trace_level_counter++;
  retval = NaClSysDup3(natp, (int)  p.oldfd, (int)  p.newfd, (int)  p.flags);
  nacl_syscall_trace_level_counter--;
  printf("[NaClSysCallInterface] cage id = %d, syscall_num = NACL_sys_dup3 [exit][syscall_depth = %d] \n", nap->cage_id, nacl_syscall_trace_level_counter);
  return retval;
  #endif

  return NaClSysDup3(natp, (int)  p.oldfd, (int)  p.newfd, (int)  p.flags);

}

/*
 * Check that the function being wrapped has the same type as the type
 * declared in SYSCALL_LIST.
 */
static INLINE void AssertSameType_NaClSysDup3(void) {
  /* This assignment will give an error if the argument types don't match. */
  int32_t (*dummy)(struct NaClAppThread *natp, int oldfd, int newfd, int flags) = NaClSysDup3;
  /* 'dummy' is not actually a parameter but this suppresses the warning. */
  UNREFERENCED_PARAMETER(dummy);
}

/* this function was automagically generated */
static int32_t NaClSysOpenDecoder(struct NaClAppThread *natp) {
  #ifdef SYSCALL_TIMING
  int32_t retval;
  clock_t nacl_sys_begin;
  clock_t nacl_sys_finish;
  #endif
  #ifdef NACL_SYSCALL_TRACE_ENABLED
  struct NaClApp *nap = natp->nap;
  int32_t retval;
#if 1
  unsigned int i = 0;
#endif
  #endif
    struct NaClSysOpenArgs {
    uint32_t pathname;
    uint32_t flags;
    uint32_t mode;
  } p;
  if (!NaClCopyInFromUserAndDropLock(natp->nap, &p, natp->usr_syscall_args,
                                     sizeof p)) {
    return -NACL_ABI_EFAULT;
  }


  #ifdef SYSCALL_TIMING
  nacl_syscall_counter++;
  nacl_syscall_invoked_times[NACL_sys_open]++;
  nacl_sys_begin = clock();
  retval = NaClSysOpen(natp, (char *) (uintptr_t) p.pathname, (int)  p.flags, (int)  p.mode);
  nacl_sys_finish = clock();
  nacl_syscall_execution_time[NACL_sys_open] += (double)(nacl_sys_finish - nacl_sys_begin) / CLOCKS_PER_SEC;
  return retval;
  #endif
  #ifdef NACL_SYSCALL_TRACE_ENABLED
  printf("[NaClSysCallInterface] cage id = %d, syscall_num = NACL_sys_open [enter][syscall_depth = %d]\n", nap->cage_id, nacl_syscall_trace_level_counter);
  printf("==> NACL_sys_open(");
#if 1
  for (i = 0; i < sizeof(p)/4; i++) {
    printf("%x,", *((uint32_t *)&p+i));
  }
#endif
  printf(")\n");
  nacl_syscall_trace_level_counter++;
  retval = NaClSysOpen(natp, (char *) (uintptr_t) p.pathname, (int)  p.flags, (int)  p.mode);
  nacl_syscall_trace_level_counter--;
  printf("[NaClSysCallInterface] cage id = %d, syscall_num = NACL_sys_open [exit][syscall_depth = %d] \n", nap->cage_id, nacl_syscall_trace_level_counter);
  return retval;
  #endif

  return NaClSysOpen(natp, (char *) (uintptr_t) p.pathname, (int)  p.flags, (int)  p.mode);

}

/*
 * Check that the function being wrapped has the same type as the type
 * declared in SYSCALL_LIST.
 */
static INLINE void AssertSameType_NaClSysOpen(void) {
  /* This assignment will give an error if the argument types don't match. */
  int32_t (*dummy)(struct NaClAppThread *natp, char *pathname, int flags, int mode) = NaClSysOpen;
  /* 'dummy' is not actually a parameter but this suppresses the warning. */
  UNREFERENCED_PARAMETER(dummy);
}

/* this function was automagically generated */
static int32_t NaClSysCloseDecoder(struct NaClAppThread *natp) {
  #ifdef SYSCALL_TIMING
  int32_t retval;
  clock_t nacl_sys_begin;
  clock_t nacl_sys_finish;
  #endif
  #ifdef NACL_SYSCALL_TRACE_ENABLED
  struct NaClApp *nap = natp->nap;
  int32_t retval;
#if 1
  unsigned int i = 0;
#endif
  #endif
    struct NaClSysCloseArgs {
    uint32_t d;
  } p;
  if (!NaClCopyInFromUserAndDropLock(natp->nap, &p, natp->usr_syscall_args,
                                     sizeof p)) {
    return -NACL_ABI_EFAULT;
  }


  #ifdef SYSCALL_TIMING
  nacl_syscall_counter++;
  nacl_syscall_invoked_times[NACL_sys_close]++;
  nacl_sys_begin = clock();
  retval = NaClSysClose(natp, (int)  p.d);
  nacl_sys_finish = clock();
  nacl_syscall_execution_time[NACL_sys_close] += (double)(nacl_sys_finish - nacl_sys_begin) / CLOCKS_PER_SEC;
  return retval;
  #endif
  #ifdef NACL_SYSCALL_TRACE_ENABLED
  printf("[NaClSysCallInterface] cage id = %d, syscall_num = NACL_sys_close [enter][syscall_depth = %d]\n", nap->cage_id, nacl_syscall_trace_level_counter);
  printf("==> NACL_sys_close(");
#if 1
  for (i = 0; i < sizeof(p)/4; i++) {
    printf("%x,", *((uint32_t *)&p+i));
  }
#endif
  printf(")\n");
  nacl_syscall_trace_level_counter++;
  retval = NaClSysClose(natp, (int)  p.d);
  nacl_syscall_trace_level_counter--;
  printf("[NaClSysCallInterface] cage id = %d, syscall_num = NACL_sys_close [exit][syscall_depth = %d] \n", nap->cage_id, nacl_syscall_trace_level_counter);
  return retval;
  #endif

  return NaClSysClose(natp, (int)  p.d);

}

/*
 * Check that the function being wrapped has the same type as the type
 * declared in SYSCALL_LIST.
 */
static INLINE void AssertSameType_NaClSysClose(void) {
  /* This assignment will give an error if the argument types don't match. */
  int32_t (*dummy)(struct NaClAppThread *natp, int d) = NaClSysClose;
  /* 'dummy' is not actually a parameter but this suppresses the warning. */
  UNREFERENCED_PARAMETER(dummy);
}

/* this function was automagically generated */
static int32_t NaClSysReadDecoder(struct NaClAppThread *natp) {
  #ifdef SYSCALL_TIMING
  int32_t retval;
  clock_t nacl_sys_begin;
  clock_t nacl_sys_finish;
  #endif
  #ifdef NACL_SYSCALL_TRACE_ENABLED
  struct NaClApp *nap = natp->nap;
  int32_t retval;
#if 1
  unsigned int i = 0;
#endif
  #endif
    struct NaClSysReadArgs {
    uint32_t d;
    uint32_t buf;
    uint32_t count;
  } p;
  if (!NaClCopyInFromUserAndDropLock(natp->nap, &p, natp->usr_syscall_args,
                                     sizeof p)) {
    return -NACL_ABI_EFAULT;
  }


  #ifdef SYSCALL_TIMING
  nacl_syscall_counter++;
  nacl_syscall_invoked_times[NACL_sys_read]++;
  nacl_sys_begin = clock();
  retval = NaClSysRead(natp, (int)  p.d, (void *) (uintptr_t) p.buf, (size_t)  p.count);
  nacl_sys_finish = clock();
  nacl_syscall_execution_time[NACL_sys_read] += (double)(nacl_sys_finish - nacl_sys_begin) / CLOCKS_PER_SEC;
  return retval;
  #endif
  #ifdef NACL_SYSCALL_TRACE_ENABLED
  printf("[NaClSysCallInterface] cage id = %d, syscall_num = NACL_sys_read [enter][syscall_depth = %d]\n", nap->cage_id, nacl_syscall_trace_level_counter);
  printf("==> NACL_sys_read(");
#if 1
  for (i = 0; i < sizeof(p)/4; i++) {
    printf("%x,", *((uint32_t *)&p+i));
  }
#endif
  printf(")\n");
  nacl_syscall_trace_level_counter++;
  retval = NaClSysRead(natp, (int)  p.d, (void *) (uintptr_t) p.buf, (size_t)  p.count);
  nacl_syscall_trace_level_counter--;
  printf("[NaClSysCallInterface] cage id = %d, syscall_num = NACL_sys_read [exit][syscall_depth = %d] \n", nap->cage_id, nacl_syscall_trace_level_counter);
  return retval;
  #endif

  return NaClSysRead(natp, (int)  p.d, (void *) (uintptr_t) p.buf, (size_t)  p.count);

}

/*
 * Check that the function being wrapped has the same type as the type
 * declared in SYSCALL_LIST.
 */
static INLINE void AssertSameType_NaClSysRead(void) {
  /* This assignment will give an error if the argument types don't match. */
  int32_t (*dummy)(struct NaClAppThread *natp, int d, void *buf, size_t count) = NaClSysRead;
  /* 'dummy' is not actually a parameter but this suppresses the warning. */
  UNREFERENCED_PARAMETER(dummy);
}

/* this function was automagically generated */
static int32_t NaClSysWriteDecoder(struct NaClAppThread *natp) {
  #ifdef SYSCALL_TIMING
  int32_t retval;
  clock_t nacl_sys_begin;
  clock_t nacl_sys_finish;
  #endif
  #ifdef NACL_SYSCALL_TRACE_ENABLED
  struct NaClApp *nap = natp->nap;
  int32_t retval;
#if 1
  unsigned int i = 0;
#endif
  #endif
    struct NaClSysWriteArgs {
    uint32_t d;
    uint32_t buf;
    uint32_t count;
  } p;
  if (!NaClCopyInFromUserAndDropLock(natp->nap, &p, natp->usr_syscall_args,
                                     sizeof p)) {
    return -NACL_ABI_EFAULT;
  }


  #ifdef SYSCALL_TIMING
  nacl_syscall_counter++;
  nacl_syscall_invoked_times[NACL_sys_write]++;
  nacl_sys_begin = clock();
  retval = NaClSysWrite(natp, (int)  p.d, (void *) (uintptr_t) p.buf, (size_t)  p.count);
  nacl_sys_finish = clock();
  nacl_syscall_execution_time[NACL_sys_write] += (double)(nacl_sys_finish - nacl_sys_begin) / CLOCKS_PER_SEC;
  return retval;
  #endif
  #ifdef NACL_SYSCALL_TRACE_ENABLED
  printf("[NaClSysCallInterface] cage id = %d, syscall_num = NACL_sys_write [enter][syscall_depth = %d]\n", nap->cage_id, nacl_syscall_trace_level_counter);
  printf("==> NACL_sys_write(");
#if 1
  for (i = 0; i < sizeof(p)/4; i++) {
    printf("%x,", *((uint32_t *)&p+i));
  }
#endif
  printf(")\n");
  nacl_syscall_trace_level_counter++;
  retval = NaClSysWrite(natp, (int)  p.d, (void *) (uintptr_t) p.buf, (size_t)  p.count);
  nacl_syscall_trace_level_counter--;
  printf("[NaClSysCallInterface] cage id = %d, syscall_num = NACL_sys_write [exit][syscall_depth = %d] \n", nap->cage_id, nacl_syscall_trace_level_counter);
  return retval;
  #endif

  return NaClSysWrite(natp, (int)  p.d, (void *) (uintptr_t) p.buf, (size_t)  p.count);

}

/*
 * Check that the function being wrapped has the same type as the type
 * declared in SYSCALL_LIST.
 */
static INLINE void AssertSameType_NaClSysWrite(void) {
  /* This assignment will give an error if the argument types don't match. */
  int32_t (*dummy)(struct NaClAppThread *natp, int d, void *buf, size_t count) = NaClSysWrite;
  /* 'dummy' is not actually a parameter but this suppresses the warning. */
  UNREFERENCED_PARAMETER(dummy);
}

/* this function was automagically generated */
static int32_t NaClSysLseekDecoder(struct NaClAppThread *natp) {
  #ifdef SYSCALL_TIMING
  int32_t retval;
  clock_t nacl_sys_begin;
  clock_t nacl_sys_finish;
  #endif
  #ifdef NACL_SYSCALL_TRACE_ENABLED
  struct NaClApp *nap = natp->nap;
  int32_t retval;
#if 1
  unsigned int i = 0;
#endif
  #endif
    struct NaClSysLseekArgs {
    uint32_t d;
    uint32_t offp;
    uint32_t whence;
  } p;
  if (!NaClCopyInFromUserAndDropLock(natp->nap, &p, natp->usr_syscall_args,
                                     sizeof p)) {
    return -NACL_ABI_EFAULT;
  }


  #ifdef SYSCALL_TIMING
  nacl_syscall_counter++;
  nacl_syscall_invoked_times[NACL_sys_lseek]++;
  nacl_sys_begin = clock();
  retval = NaClSysLseek(natp, (int)  p.d, (nacl_abi_off_t *) (uintptr_t) p.offp, (int)  p.whence);
  nacl_sys_finish = clock();
  nacl_syscall_execution_time[NACL_sys_lseek] += (double)(nacl_sys_finish - nacl_sys_begin) / CLOCKS_PER_SEC;
  return retval;
  #endif
  #ifdef NACL_SYSCALL_TRACE_ENABLED
  printf("[NaClSysCallInterface] cage id = %d, syscall_num = NACL_sys_lseek [enter][syscall_depth = %d]\n", nap->cage_id, nacl_syscall_trace_level_counter);
  printf("==> NACL_sys_lseek(");
#if 1
  for (i = 0; i < sizeof(p)/4; i++) {
    printf("%x,", *((uint32_t *)&p+i));
  }
#endif
  printf(")\n");
  nacl_syscall_trace_level_counter++;
  retval = NaClSysLseek(natp, (int)  p.d, (nacl_abi_off_t *) (uintptr_t) p.offp, (int)  p.whence);
  nacl_syscall_trace_level_counter--;
  printf("[NaClSysCallInterface] cage id = %d, syscall_num = NACL_sys_lseek [exit][syscall_depth = %d] \n", nap->cage_id, nacl_syscall_trace_level_counter);
  return retval;
  #endif

  return NaClSysLseek(natp, (int)  p.d, (nacl_abi_off_t *) (uintptr_t) p.offp, (int)  p.whence);

}

/*
 * Check that the function being wrapped has the same type as the type
 * declared in SYSCALL_LIST.
 */
static INLINE void AssertSameType_NaClSysLseek(void) {
  /* This assignment will give an error if the argument types don't match. */
  int32_t (*dummy)(struct NaClAppThread *natp, int d, nacl_abi_off_t *offp, int whence) = NaClSysLseek;
  /* 'dummy' is not actually a parameter but this suppresses the warning. */
  UNREFERENCED_PARAMETER(dummy);
}

/* this function was automagically generated */
static int32_t NaClSysIoctlDecoder(struct NaClAppThread *natp) {
  #ifdef SYSCALL_TIMING
  int32_t retval;
  clock_t nacl_sys_begin;
  clock_t nacl_sys_finish;
  #endif
  #ifdef NACL_SYSCALL_TRACE_ENABLED
  struct NaClApp *nap = natp->nap;
  int32_t retval;
#if 1
  unsigned int i = 0;
#endif
  #endif
    struct NaClSysIoctlArgs {
    uint32_t d;
    uint32_t request;
    uint32_t arg;
  } p;
  if (!NaClCopyInFromUserAndDropLock(natp->nap, &p, natp->usr_syscall_args,
                                     sizeof p)) {
    return -NACL_ABI_EFAULT;
  }


  #ifdef SYSCALL_TIMING
  nacl_syscall_counter++;
  nacl_syscall_invoked_times[NACL_sys_ioctl]++;
  nacl_sys_begin = clock();
  retval = NaClSysIoctl(natp, (int)  p.d, (int)  p.request, (void *) (uintptr_t) p.arg);
  nacl_sys_finish = clock();
  nacl_syscall_execution_time[NACL_sys_ioctl] += (double)(nacl_sys_finish - nacl_sys_begin) / CLOCKS_PER_SEC;
  return retval;
  #endif
  #ifdef NACL_SYSCALL_TRACE_ENABLED
  printf("[NaClSysCallInterface] cage id = %d, syscall_num = NACL_sys_ioctl [enter][syscall_depth = %d]\n", nap->cage_id, nacl_syscall_trace_level_counter);
  printf("==> NACL_sys_ioctl(");
#if 1
  for (i = 0; i < sizeof(p)/4; i++) {
    printf("%x,", *((uint32_t *)&p+i));
  }
#endif
  printf(")\n");
  nacl_syscall_trace_level_counter++;
  retval = NaClSysIoctl(natp, (int)  p.d, (int)  p.request, (void *) (uintptr_t) p.arg);
  nacl_syscall_trace_level_counter--;
  printf("[NaClSysCallInterface] cage id = %d, syscall_num = NACL_sys_ioctl [exit][syscall_depth = %d] \n", nap->cage_id, nacl_syscall_trace_level_counter);
  return retval;
  #endif

  return NaClSysIoctl(natp, (int)  p.d, (int)  p.request, (void *) (uintptr_t) p.arg);

}

/*
 * Check that the function being wrapped has the same type as the type
 * declared in SYSCALL_LIST.
 */
static INLINE void AssertSameType_NaClSysIoctl(void) {
  /* This assignment will give an error if the argument types don't match. */
  int32_t (*dummy)(struct NaClAppThread *natp, int d, int request, void *arg) = NaClSysIoctl;
  /* 'dummy' is not actually a parameter but this suppresses the warning. */
  UNREFERENCED_PARAMETER(dummy);
}

/* this function was automagically generated */
static int32_t NaClSysFstatDecoder(struct NaClAppThread *natp) {
  #ifdef SYSCALL_TIMING
  int32_t retval;
  clock_t nacl_sys_begin;
  clock_t nacl_sys_finish;
  #endif
  #ifdef NACL_SYSCALL_TRACE_ENABLED
  struct NaClApp *nap = natp->nap;
  int32_t retval;
#if 1
  unsigned int i = 0;
#endif
  #endif
    struct NaClSysFstatArgs {
    uint32_t d;
    uint32_t nasp;
  } p;
  if (!NaClCopyInFromUserAndDropLock(natp->nap, &p, natp->usr_syscall_args,
                                     sizeof p)) {
    return -NACL_ABI_EFAULT;
  }


  #ifdef SYSCALL_TIMING
  nacl_syscall_counter++;
  nacl_syscall_invoked_times[NACL_sys_fstat]++;
  nacl_sys_begin = clock();
  retval = NaClSysFstat(natp, (int)  p.d, (struct nacl_abi_stat *) (uintptr_t) p.nasp);
  nacl_sys_finish = clock();
  nacl_syscall_execution_time[NACL_sys_fstat] += (double)(nacl_sys_finish - nacl_sys_begin) / CLOCKS_PER_SEC;
  return retval;
  #endif
  #ifdef NACL_SYSCALL_TRACE_ENABLED
  printf("[NaClSysCallInterface] cage id = %d, syscall_num = NACL_sys_fstat [enter][syscall_depth = %d]\n", nap->cage_id, nacl_syscall_trace_level_counter);
  printf("==> NACL_sys_fstat(");
#if 1
  for (i = 0; i < sizeof(p)/4; i++) {
    printf("%x,", *((uint32_t *)&p+i));
  }
#endif
  printf(")\n");
  nacl_syscall_trace_level_counter++;
  retval = NaClSysFstat(natp, (int)  p.d, (struct nacl_abi_stat *) (uintptr_t) p.nasp);
  nacl_syscall_trace_level_counter--;
  printf("[NaClSysCallInterface] cage id = %d, syscall_num = NACL_sys_fstat [exit][syscall_depth = %d] \n", nap->cage_id, nacl_syscall_trace_level_counter);
  return retval;
  #endif

  return NaClSysFstat(natp, (int)  p.d, (struct nacl_abi_stat *) (uintptr_t) p.nasp);

}

/*
 * Check that the function being wrapped has the same type as the type
 * declared in SYSCALL_LIST.
 */
static INLINE void AssertSameType_NaClSysFstat(void) {
  /* This assignment will give an error if the argument types don't match. */
  int32_t (*dummy)(struct NaClAppThread *natp, int d, struct nacl_abi_stat *nasp) = NaClSysFstat;
  /* 'dummy' is not actually a parameter but this suppresses the warning. */
  UNREFERENCED_PARAMETER(dummy);
}

/* this function was automagically generated */
static int32_t NaClSysStatDecoder(struct NaClAppThread *natp) {
  #ifdef SYSCALL_TIMING
  int32_t retval;
  clock_t nacl_sys_begin;
  clock_t nacl_sys_finish;
  #endif
  #ifdef NACL_SYSCALL_TRACE_ENABLED
  struct NaClApp *nap = natp->nap;
  int32_t retval;
#if 1
  unsigned int i = 0;
#endif
  #endif
    struct NaClSysStatArgs {
    uint32_t path;
    uint32_t nasp;
  } p;
  if (!NaClCopyInFromUserAndDropLock(natp->nap, &p, natp->usr_syscall_args,
                                     sizeof p)) {
    return -NACL_ABI_EFAULT;
  }


  #ifdef SYSCALL_TIMING
  nacl_syscall_counter++;
  nacl_syscall_invoked_times[NACL_sys_stat]++;
  nacl_sys_begin = clock();
  retval = NaClSysStat(natp, (const char *) (uintptr_t) p.path, (struct nacl_abi_stat *) (uintptr_t) p.nasp);
  nacl_sys_finish = clock();
  nacl_syscall_execution_time[NACL_sys_stat] += (double)(nacl_sys_finish - nacl_sys_begin) / CLOCKS_PER_SEC;
  return retval;
  #endif
  #ifdef NACL_SYSCALL_TRACE_ENABLED
  printf("[NaClSysCallInterface] cage id = %d, syscall_num = NACL_sys_stat [enter][syscall_depth = %d]\n", nap->cage_id, nacl_syscall_trace_level_counter);
  printf("==> NACL_sys_stat(");
#if 1
  for (i = 0; i < sizeof(p)/4; i++) {
    printf("%x,", *((uint32_t *)&p+i));
  }
#endif
  printf(")\n");
  nacl_syscall_trace_level_counter++;
  retval = NaClSysStat(natp, (const char *) (uintptr_t) p.path, (struct nacl_abi_stat *) (uintptr_t) p.nasp);
  nacl_syscall_trace_level_counter--;
  printf("[NaClSysCallInterface] cage id = %d, syscall_num = NACL_sys_stat [exit][syscall_depth = %d] \n", nap->cage_id, nacl_syscall_trace_level_counter);
  return retval;
  #endif

  return NaClSysStat(natp, (const char *) (uintptr_t) p.path, (struct nacl_abi_stat *) (uintptr_t) p.nasp);

}

/*
 * Check that the function being wrapped has the same type as the type
 * declared in SYSCALL_LIST.
 */
static INLINE void AssertSameType_NaClSysStat(void) {
  /* This assignment will give an error if the argument types don't match. */
  int32_t (*dummy)(struct NaClAppThread *natp, const char *path, struct nacl_abi_stat *nasp) = NaClSysStat;
  /* 'dummy' is not actually a parameter but this suppresses the warning. */
  UNREFERENCED_PARAMETER(dummy);
}

/* this function was automagically generated */
static int32_t NaClSysGetdentsDecoder(struct NaClAppThread *natp) {
  #ifdef SYSCALL_TIMING
  int32_t retval;
  clock_t nacl_sys_begin;
  clock_t nacl_sys_finish;
  #endif
  #ifdef NACL_SYSCALL_TRACE_ENABLED
  struct NaClApp *nap = natp->nap;
  int32_t retval;
#if 1
  unsigned int i = 0;
#endif
  #endif
    struct NaClSysGetdentsArgs {
    uint32_t d;
    uint32_t buf;
    uint32_t count;
  } p;
  if (!NaClCopyInFromUserAndDropLock(natp->nap, &p, natp->usr_syscall_args,
                                     sizeof p)) {
    return -NACL_ABI_EFAULT;
  }


  #ifdef SYSCALL_TIMING
  nacl_syscall_counter++;
  nacl_syscall_invoked_times[NACL_sys_getdents]++;
  nacl_sys_begin = clock();
  retval = NaClSysGetdents(natp, (int)  p.d, (void *) (uintptr_t) p.buf, (size_t)  p.count);
  nacl_sys_finish = clock();
  nacl_syscall_execution_time[NACL_sys_getdents] += (double)(nacl_sys_finish - nacl_sys_begin) / CLOCKS_PER_SEC;
  return retval;
  #endif
  #ifdef NACL_SYSCALL_TRACE_ENABLED
  printf("[NaClSysCallInterface] cage id = %d, syscall_num = NACL_sys_getdents [enter][syscall_depth = %d]\n", nap->cage_id, nacl_syscall_trace_level_counter);
  printf("==> NACL_sys_getdents(");
#if 1
  for (i = 0; i < sizeof(p)/4; i++) {
    printf("%x,", *((uint32_t *)&p+i));
  }
#endif
  printf(")\n");
  nacl_syscall_trace_level_counter++;
  retval = NaClSysGetdents(natp, (int)  p.d, (void *) (uintptr_t) p.buf, (size_t)  p.count);
  nacl_syscall_trace_level_counter--;
  printf("[NaClSysCallInterface] cage id = %d, syscall_num = NACL_sys_getdents [exit][syscall_depth = %d] \n", nap->cage_id, nacl_syscall_trace_level_counter);
  return retval;
  #endif

  return NaClSysGetdents(natp, (int)  p.d, (void *) (uintptr_t) p.buf, (size_t)  p.count);

}

/*
 * Check that the function being wrapped has the same type as the type
 * declared in SYSCALL_LIST.
 */
static INLINE void AssertSameType_NaClSysGetdents(void) {
  /* This assignment will give an error if the argument types don't match. */
  int32_t (*dummy)(struct NaClAppThread *natp, int d, void *buf, size_t count) = NaClSysGetdents;
  /* 'dummy' is not actually a parameter but this suppresses the warning. */
  UNREFERENCED_PARAMETER(dummy);
}

/* this function was automagically generated */
static int32_t NaClSysBrkDecoder(struct NaClAppThread *natp) {
  #ifdef SYSCALL_TIMING
  int32_t retval;
  clock_t nacl_sys_begin;
  clock_t nacl_sys_finish;
  #endif
  #ifdef NACL_SYSCALL_TRACE_ENABLED
  struct NaClApp *nap = natp->nap;
  int32_t retval;
#if 1
  unsigned int i = 0;
#endif
  #endif
    struct NaClSysBrkArgs {
    uint32_t new_break;
  } p;
  if (!NaClCopyInFromUserAndDropLock(natp->nap, &p, natp->usr_syscall_args,
                                     sizeof p)) {
    return -NACL_ABI_EFAULT;
  }


  #ifdef SYSCALL_TIMING
  nacl_syscall_counter++;
  nacl_syscall_invoked_times[NACL_sys_brk]++;
  nacl_sys_begin = clock();
  retval = NaClSysBrk(natp, (uintptr_t)  p.new_break);
  nacl_sys_finish = clock();
  nacl_syscall_execution_time[NACL_sys_brk] += (double)(nacl_sys_finish - nacl_sys_begin) / CLOCKS_PER_SEC;
  return retval;
  #endif
  #ifdef NACL_SYSCALL_TRACE_ENABLED
  printf("[NaClSysCallInterface] cage id = %d, syscall_num = NACL_sys_brk [enter][syscall_depth = %d]\n", nap->cage_id, nacl_syscall_trace_level_counter);
  printf("==> NACL_sys_brk(");
#if 1
  for (i = 0; i < sizeof(p)/4; i++) {
    printf("%x,", *((uint32_t *)&p+i));
  }
#endif
  printf(")\n");
  nacl_syscall_trace_level_counter++;
  retval = NaClSysBrk(natp, (uintptr_t)  p.new_break);
  nacl_syscall_trace_level_counter--;
  printf("[NaClSysCallInterface] cage id = %d, syscall_num = NACL_sys_brk [exit][syscall_depth = %d] \n", nap->cage_id, nacl_syscall_trace_level_counter);
  return retval;
  #endif

  return NaClSysBrk(natp, (uintptr_t)  p.new_break);

}

/*
 * Check that the function being wrapped has the same type as the type
 * declared in SYSCALL_LIST.
 */
static INLINE void AssertSameType_NaClSysBrk(void) {
  /* This assignment will give an error if the argument types don't match. */
  int32_t (*dummy)(struct NaClAppThread *natp, uintptr_t new_break) = NaClSysBrk;
  /* 'dummy' is not actually a parameter but this suppresses the warning. */
  UNREFERENCED_PARAMETER(dummy);
}

/* this function was automagically generated */
static int32_t NaClSysMmapDecoder(struct NaClAppThread *natp) {
  #ifdef SYSCALL_TIMING
  int32_t retval;
  clock_t nacl_sys_begin;
  clock_t nacl_sys_finish;
  #endif
  #ifdef NACL_SYSCALL_TRACE_ENABLED
  struct NaClApp *nap = natp->nap;
  int32_t retval;
#if 1
  unsigned int i = 0;
#endif
  #endif
    struct NaClSysMmapArgs {
    uint32_t start;
    uint32_t length;
    uint32_t prot;
    uint32_t flags;
    uint32_t d;
    uint32_t offp;
  } p;
  if (!NaClCopyInFromUserAndDropLock(natp->nap, &p, natp->usr_syscall_args,
                                     sizeof p)) {
    return -NACL_ABI_EFAULT;
  }


  #ifdef SYSCALL_TIMING
  nacl_syscall_counter++;
  nacl_syscall_invoked_times[NACL_sys_mmap]++;
  nacl_sys_begin = clock();
  retval = NaClSysMmap(natp, (void *) (uintptr_t) p.start, (size_t)  p.length, (int)  p.prot, (int)  p.flags, (int)  p.d, (nacl_abi_off_t *) (uintptr_t) p.offp);
  nacl_sys_finish = clock();
  nacl_syscall_execution_time[NACL_sys_mmap] += (double)(nacl_sys_finish - nacl_sys_begin) / CLOCKS_PER_SEC;
  return retval;
  #endif
  #ifdef NACL_SYSCALL_TRACE_ENABLED
  printf("[NaClSysCallInterface] cage id = %d, syscall_num = NACL_sys_mmap [enter][syscall_depth = %d]\n", nap->cage_id, nacl_syscall_trace_level_counter);
  printf("==> NACL_sys_mmap(");
#if 1
  for (i = 0; i < sizeof(p)/4; i++) {
    printf("%x,", *((uint32_t *)&p+i));
  }
#endif
  printf(")\n");
  nacl_syscall_trace_level_counter++;
  retval = NaClSysMmap(natp, (void *) (uintptr_t) p.start, (size_t)  p.length, (int)  p.prot, (int)  p.flags, (int)  p.d, (nacl_abi_off_t *) (uintptr_t) p.offp);
  nacl_syscall_trace_level_counter--;
  printf("[NaClSysCallInterface] cage id = %d, syscall_num = NACL_sys_mmap [exit][syscall_depth = %d] \n", nap->cage_id, nacl_syscall_trace_level_counter);
  return retval;
  #endif

  return NaClSysMmap(natp, (void *) (uintptr_t) p.start, (size_t)  p.length, (int)  p.prot, (int)  p.flags, (int)  p.d, (nacl_abi_off_t *) (uintptr_t) p.offp);

}

/*
 * Check that the function being wrapped has the same type as the type
 * declared in SYSCALL_LIST.
 */
static INLINE void AssertSameType_NaClSysMmap(void) {
  /* This assignment will give an error if the argument types don't match. */
  int32_t (*dummy)(struct NaClAppThread *natp, void *start, size_t length, int prot, int flags, int d, nacl_abi_off_t *offp) = NaClSysMmap;
  /* 'dummy' is not actually a parameter but this suppresses the warning. */
  UNREFERENCED_PARAMETER(dummy);
}

/* this function was automagically generated */
static int32_t NaClSysMprotectDecoder(struct NaClAppThread *natp) {
  #ifdef SYSCALL_TIMING
  int32_t retval;
  clock_t nacl_sys_begin;
  clock_t nacl_sys_finish;
  #endif
  #ifdef NACL_SYSCALL_TRACE_ENABLED
  struct NaClApp *nap = natp->nap;
  int32_t retval;
#if 1
  unsigned int i = 0;
#endif
  #endif
    struct NaClSysMprotectArgs {
    uint32_t start;
    uint32_t length;
    uint32_t prot;
  } p;
  if (!NaClCopyInFromUserAndDropLock(natp->nap, &p, natp->usr_syscall_args,
                                     sizeof p)) {
    return -NACL_ABI_EFAULT;
  }


  #ifdef SYSCALL_TIMING
  nacl_syscall_counter++;
  nacl_syscall_invoked_times[NACL_sys_mprotect]++;
  nacl_sys_begin = clock();
  retval = NaClSysMprotect(natp, (uint32_t)  p.start, (size_t)  p.length, (int)  p.prot);
  nacl_sys_finish = clock();
  nacl_syscall_execution_time[NACL_sys_mprotect] += (double)(nacl_sys_finish - nacl_sys_begin) / CLOCKS_PER_SEC;
  return retval;
  #endif
  #ifdef NACL_SYSCALL_TRACE_ENABLED
  printf("[NaClSysCallInterface] cage id = %d, syscall_num = NACL_sys_mprotect [enter][syscall_depth = %d]\n", nap->cage_id, nacl_syscall_trace_level_counter);
  printf("==> NACL_sys_mprotect(");
#if 1
  for (i = 0; i < sizeof(p)/4; i++) {
    printf("%x,", *((uint32_t *)&p+i));
  }
#endif
  printf(")\n");
  nacl_syscall_trace_level_counter++;
  retval = NaClSysMprotect(natp, (uint32_t)  p.start, (size_t)  p.length, (int)  p.prot);
  nacl_syscall_trace_level_counter--;
  printf("[NaClSysCallInterface] cage id = %d, syscall_num = NACL_sys_mprotect [exit][syscall_depth = %d] \n", nap->cage_id, nacl_syscall_trace_level_counter);
  return retval;
  #endif

  return NaClSysMprotect(natp, (uint32_t)  p.start, (size_t)  p.length, (int)  p.prot);

}

/*
 * Check that the function being wrapped has the same type as the type
 * declared in SYSCALL_LIST.
 */
static INLINE void AssertSameType_NaClSysMprotect(void) {
  /* This assignment will give an error if the argument types don't match. */
  int32_t (*dummy)(struct NaClAppThread *natp, uint32_t start, size_t length, int prot) = NaClSysMprotect;
  /* 'dummy' is not actually a parameter but this suppresses the warning. */
  UNREFERENCED_PARAMETER(dummy);
}

/* this function was automagically generated */
static int32_t NaClSysListMappingsDecoder(struct NaClAppThread *natp) {
  #ifdef SYSCALL_TIMING
  int32_t retval;
  clock_t nacl_sys_begin;
  clock_t nacl_sys_finish;
  #endif
  #ifdef NACL_SYSCALL_TRACE_ENABLED
  struct NaClApp *nap = natp->nap;
  int32_t retval;
#if 1
  unsigned int i = 0;
#endif
  #endif
    struct NaClSysListMappingsArgs {
    uint32_t regions;
    uint32_t count;
  } p;
  if (!NaClCopyInFromUserAndDropLock(natp->nap, &p, natp->usr_syscall_args,
                                     sizeof p)) {
    return -NACL_ABI_EFAULT;
  }


  #ifdef SYSCALL_TIMING
  nacl_syscall_counter++;
  nacl_syscall_invoked_times[NACL_sys_list_mappings]++;
  nacl_sys_begin = clock();
  retval = NaClSysListMappings(natp, (uint32_t)  p.regions, (uint32_t)  p.count);
  nacl_sys_finish = clock();
  nacl_syscall_execution_time[NACL_sys_list_mappings] += (double)(nacl_sys_finish - nacl_sys_begin) / CLOCKS_PER_SEC;
  return retval;
  #endif
  #ifdef NACL_SYSCALL_TRACE_ENABLED
  printf("[NaClSysCallInterface] cage id = %d, syscall_num = NACL_sys_list_mappings [enter][syscall_depth = %d]\n", nap->cage_id, nacl_syscall_trace_level_counter);
  printf("==> NACL_sys_list_mappings(");
#if 1
  for (i = 0; i < sizeof(p)/4; i++) {
    printf("%x,", *((uint32_t *)&p+i));
  }
#endif
  printf(")\n");
  nacl_syscall_trace_level_counter++;
  retval = NaClSysListMappings(natp, (uint32_t)  p.regions, (uint32_t)  p.count);
  nacl_syscall_trace_level_counter--;
  printf("[NaClSysCallInterface] cage id = %d, syscall_num = NACL_sys_list_mappings [exit][syscall_depth = %d] \n", nap->cage_id, nacl_syscall_trace_level_counter);
  return retval;
  #endif

  return NaClSysListMappings(natp, (uint32_t)  p.regions, (uint32_t)  p.count);

}

/*
 * Check that the function being wrapped has the same type as the type
 * declared in SYSCALL_LIST.
 */
static INLINE void AssertSameType_NaClSysListMappings(void) {
  /* This assignment will give an error if the argument types don't match. */
  int32_t (*dummy)(struct NaClAppThread *natp, uint32_t regions, uint32_t count) = NaClSysListMappings;
  /* 'dummy' is not actually a parameter but this suppresses the warning. */
  UNREFERENCED_PARAMETER(dummy);
}

/* this function was automagically generated */
static int32_t NaClSysMunmapDecoder(struct NaClAppThread *natp) {
  #ifdef SYSCALL_TIMING
  int32_t retval;
  clock_t nacl_sys_begin;
  clock_t nacl_sys_finish;
  #endif
  #ifdef NACL_SYSCALL_TRACE_ENABLED
  struct NaClApp *nap = natp->nap;
  int32_t retval;
#if 1
  unsigned int i = 0;
#endif
  #endif
    struct NaClSysMunmapArgs {
    uint32_t start;
    uint32_t length;
  } p;
  if (!NaClCopyInFromUserAndDropLock(natp->nap, &p, natp->usr_syscall_args,
                                     sizeof p)) {
    return -NACL_ABI_EFAULT;
  }


  #ifdef SYSCALL_TIMING
  nacl_syscall_counter++;
  nacl_syscall_invoked_times[NACL_sys_munmap]++;
  nacl_sys_begin = clock();
  retval = NaClSysMunmap(natp, (void *) (uintptr_t) p.start, (size_t)  p.length);
  nacl_sys_finish = clock();
  nacl_syscall_execution_time[NACL_sys_munmap] += (double)(nacl_sys_finish - nacl_sys_begin) / CLOCKS_PER_SEC;
  return retval;
  #endif
  #ifdef NACL_SYSCALL_TRACE_ENABLED
  printf("[NaClSysCallInterface] cage id = %d, syscall_num = NACL_sys_munmap [enter][syscall_depth = %d]\n", nap->cage_id, nacl_syscall_trace_level_counter);
  printf("==> NACL_sys_munmap(");
#if 1
  for (i = 0; i < sizeof(p)/4; i++) {
    printf("%x,", *((uint32_t *)&p+i));
  }
#endif
  printf(")\n");
  nacl_syscall_trace_level_counter++;
  retval = NaClSysMunmap(natp, (void *) (uintptr_t) p.start, (size_t)  p.length);
  nacl_syscall_trace_level_counter--;
  printf("[NaClSysCallInterface] cage id = %d, syscall_num = NACL_sys_munmap [exit][syscall_depth = %d] \n", nap->cage_id, nacl_syscall_trace_level_counter);
  return retval;
  #endif

  return NaClSysMunmap(natp, (void *) (uintptr_t) p.start, (size_t)  p.length);

}

/*
 * Check that the function being wrapped has the same type as the type
 * declared in SYSCALL_LIST.
 */
static INLINE void AssertSameType_NaClSysMunmap(void) {
  /* This assignment will give an error if the argument types don't match. */
  int32_t (*dummy)(struct NaClAppThread *natp, void *start, size_t length) = NaClSysMunmap;
  /* 'dummy' is not actually a parameter but this suppresses the warning. */
  UNREFERENCED_PARAMETER(dummy);
}

/* this function was automagically generated */
static int32_t NaClSysExitDecoder(struct NaClAppThread *natp) {
  #ifdef SYSCALL_TIMING
  int32_t retval;
  clock_t nacl_sys_begin;
  clock_t nacl_sys_finish;
  #endif
  #ifdef NACL_SYSCALL_TRACE_ENABLED
  struct NaClApp *nap = natp->nap;
  int32_t retval;
#if 1
  unsigned int i = 0;
#endif
  #endif
    struct NaClSysExitArgs {
    uint32_t status;
  } p;
  if (!NaClCopyInFromUserAndDropLock(natp->nap, &p, natp->usr_syscall_args,
                                     sizeof p)) {
    return -NACL_ABI_EFAULT;
  }


  #ifdef SYSCALL_TIMING
  nacl_syscall_counter++;
  nacl_syscall_invoked_times[NACL_sys_exit]++;
  nacl_sys_begin = clock();
  retval = NaClSysExit(natp, (int)  p.status);
  nacl_sys_finish = clock();
  nacl_syscall_execution_time[NACL_sys_exit] += (double)(nacl_sys_finish - nacl_sys_begin) / CLOCKS_PER_SEC;
  return retval;
  #endif
  #ifdef NACL_SYSCALL_TRACE_ENABLED
  printf("[NaClSysCallInterface] cage id = %d, syscall_num = NACL_sys_exit [enter][syscall_depth = %d]\n", nap->cage_id, nacl_syscall_trace_level_counter);
  printf("==> NACL_sys_exit(");
#if 1
  for (i = 0; i < sizeof(p)/4; i++) {
    printf("%x,", *((uint32_t *)&p+i));
  }
#endif
  printf(")\n");
  nacl_syscall_trace_level_counter++;
  retval = NaClSysExit(natp, (int)  p.status);
  nacl_syscall_trace_level_counter--;
  printf("[NaClSysCallInterface] cage id = %d, syscall_num = NACL_sys_exit [exit][syscall_depth = %d] \n", nap->cage_id, nacl_syscall_trace_level_counter);
  return retval;
  #endif

  return NaClSysExit(natp, (int)  p.status);

}

/*
 * Check that the function being wrapped has the same type as the type
 * declared in SYSCALL_LIST.
 */
static INLINE void AssertSameType_NaClSysExit(void) {
  /* This assignment will give an error if the argument types don't match. */
  int32_t (*dummy)(struct NaClAppThread *natp, int status) = NaClSysExit;
  /* 'dummy' is not actually a parameter but this suppresses the warning. */
  UNREFERENCED_PARAMETER(dummy);
}

/* this function was automagically generated */
static int32_t NaClSysGetpidDecoder(struct NaClAppThread *natp) {
  #ifdef SYSCALL_TIMING
  int32_t retval;
  clock_t nacl_sys_begin;
  clock_t nacl_sys_finish;
  #endif
  #ifdef NACL_SYSCALL_TRACE_ENABLED
  struct NaClApp *nap = natp->nap;
  int32_t retval;
#if 0
  unsigned int i = 0;
#endif
  #endif
    NaClCopyDropLock(natp->nap);
  #ifdef SYSCALL_TIMING
  nacl_syscall_counter++;
  nacl_syscall_invoked_times[NACL_sys_getpid]++;
  nacl_sys_begin = clock();
  retval = NaClSysGetpid(natp);
  nacl_sys_finish = clock();
  nacl_syscall_execution_time[NACL_sys_getpid] += (double)(nacl_sys_finish - nacl_sys_begin) / CLOCKS_PER_SEC;
  return retval;
  #endif
  #ifdef NACL_SYSCALL_TRACE_ENABLED
  printf("[NaClSysCallInterface] cage id = %d, syscall_num = NACL_sys_getpid [enter][syscall_depth = %d]\n", nap->cage_id, nacl_syscall_trace_level_counter);
  printf("==> NACL_sys_getpid(");
#if 0
  for (i = 0; i < sizeof(p)/4; i++) {
    printf("%x,", *((uint32_t *)&p+i));
  }
#endif
  printf(")\n");
  nacl_syscall_trace_level_counter++;
  retval = NaClSysGetpid(natp);
  nacl_syscall_trace_level_counter--;
  printf("[NaClSysCallInterface] cage id = %d, syscall_num = NACL_sys_getpid [exit][syscall_depth = %d] \n", nap->cage_id, nacl_syscall_trace_level_counter);
  return retval;
  #endif

  return NaClSysGetpid(natp);

}

/*
 * Check that the function being wrapped has the same type as the type
 * declared in SYSCALL_LIST.
 */
static INLINE void AssertSameType_NaClSysGetpid(void) {
  /* This assignment will give an error if the argument types don't match. */
  int32_t (*dummy)(struct NaClAppThread *natp) = NaClSysGetpid;
  /* 'dummy' is not actually a parameter but this suppresses the warning. */
  UNREFERENCED_PARAMETER(dummy);
}

/* this function was automagically generated */
static int32_t NaClSysThreadExitDecoder(struct NaClAppThread *natp) {
  #ifdef SYSCALL_TIMING
  int32_t retval;
  clock_t nacl_sys_begin;
  clock_t nacl_sys_finish;
  #endif
  #ifdef NACL_SYSCALL_TRACE_ENABLED
  struct NaClApp *nap = natp->nap;
  int32_t retval;
#if 1
  unsigned int i = 0;
#endif
  #endif
    struct NaClSysThreadExitArgs {
    uint32_t stack_flag;
  } p;
  if (!NaClCopyInFromUserAndDropLock(natp->nap, &p, natp->usr_syscall_args,
                                     sizeof p)) {
    return -NACL_ABI_EFAULT;
  }


  #ifdef SYSCALL_TIMING
  nacl_syscall_counter++;
  nacl_syscall_invoked_times[NACL_sys_thread_exit]++;
  nacl_sys_begin = clock();
  retval = NaClSysThreadExit(natp, (int32_t *) (uintptr_t) p.stack_flag);
  nacl_sys_finish = clock();
  nacl_syscall_execution_time[NACL_sys_thread_exit] += (double)(nacl_sys_finish - nacl_sys_begin) / CLOCKS_PER_SEC;
  return retval;
  #endif
  #ifdef NACL_SYSCALL_TRACE_ENABLED
  printf("[NaClSysCallInterface] cage id = %d, syscall_num = NACL_sys_thread_exit [enter][syscall_depth = %d]\n", nap->cage_id, nacl_syscall_trace_level_counter);
  printf("==> NACL_sys_thread_exit(");
#if 1
  for (i = 0; i < sizeof(p)/4; i++) {
    printf("%x,", *((uint32_t *)&p+i));
  }
#endif
  printf(")\n");
  nacl_syscall_trace_level_counter++;
  retval = NaClSysThreadExit(natp, (int32_t *) (uintptr_t) p.stack_flag);
  nacl_syscall_trace_level_counter--;
  printf("[NaClSysCallInterface] cage id = %d, syscall_num = NACL_sys_thread_exit [exit][syscall_depth = %d] \n", nap->cage_id, nacl_syscall_trace_level_counter);
  return retval;
  #endif

  return NaClSysThreadExit(natp, (int32_t *) (uintptr_t) p.stack_flag);

}

/*
 * Check that the function being wrapped has the same type as the type
 * declared in SYSCALL_LIST.
 */
static INLINE void AssertSameType_NaClSysThreadExit(void) {
  /* This assignment will give an error if the argument types don't match. */
  int32_t (*dummy)(struct NaClAppThread *natp, int32_t *stack_flag) = NaClSysThreadExit;
  /* 'dummy' is not actually a parameter but this suppresses the warning. */
  UNREFERENCED_PARAMETER(dummy);
}

/* this function was automagically generated */
static int32_t NaClSysGetTimeOfDayDecoder(struct NaClAppThread *natp) {
  #ifdef SYSCALL_TIMING
  int32_t retval;
  clock_t nacl_sys_begin;
  clock_t nacl_sys_finish;
  #endif
  #ifdef NACL_SYSCALL_TRACE_ENABLED
  struct NaClApp *nap = natp->nap;
  int32_t retval;
#if 1
  unsigned int i = 0;
#endif
  #endif
    struct NaClSysGetTimeOfDayArgs {
    uint32_t tv;
    uint32_t tz;
  } p;
  if (!NaClCopyInFromUserAndDropLock(natp->nap, &p, natp->usr_syscall_args,
                                     sizeof p)) {
    return -NACL_ABI_EFAULT;
  }


  #ifdef SYSCALL_TIMING
  nacl_syscall_counter++;
  nacl_syscall_invoked_times[NACL_sys_gettimeofday]++;
  nacl_sys_begin = clock();
  retval = NaClSysGetTimeOfDay(natp, (struct nacl_abi_timeval *) (uintptr_t) p.tv, (struct nacl_abi_timezone *) (uintptr_t) p.tz);
  nacl_sys_finish = clock();
  nacl_syscall_execution_time[NACL_sys_gettimeofday] += (double)(nacl_sys_finish - nacl_sys_begin) / CLOCKS_PER_SEC;
  return retval;
  #endif
  #ifdef NACL_SYSCALL_TRACE_ENABLED
  printf("[NaClSysCallInterface] cage id = %d, syscall_num = NACL_sys_gettimeofday [enter][syscall_depth = %d]\n", nap->cage_id, nacl_syscall_trace_level_counter);
  printf("==> NACL_sys_gettimeofday(");
#if 1
  for (i = 0; i < sizeof(p)/4; i++) {
    printf("%x,", *((uint32_t *)&p+i));
  }
#endif
  printf(")\n");
  nacl_syscall_trace_level_counter++;
  retval = NaClSysGetTimeOfDay(natp, (struct nacl_abi_timeval *) (uintptr_t) p.tv, (struct nacl_abi_timezone *) (uintptr_t) p.tz);
  nacl_syscall_trace_level_counter--;
  printf("[NaClSysCallInterface] cage id = %d, syscall_num = NACL_sys_gettimeofday [exit][syscall_depth = %d] \n", nap->cage_id, nacl_syscall_trace_level_counter);
  return retval;
  #endif

  return NaClSysGetTimeOfDay(natp, (struct nacl_abi_timeval *) (uintptr_t) p.tv, (struct nacl_abi_timezone *) (uintptr_t) p.tz);

}

/*
 * Check that the function being wrapped has the same type as the type
 * declared in SYSCALL_LIST.
 */
static INLINE void AssertSameType_NaClSysGetTimeOfDay(void) {
  /* This assignment will give an error if the argument types don't match. */
  int32_t (*dummy)(struct NaClAppThread *natp, struct nacl_abi_timeval *tv, struct nacl_abi_timezone *tz) = NaClSysGetTimeOfDay;
  /* 'dummy' is not actually a parameter but this suppresses the warning. */
  UNREFERENCED_PARAMETER(dummy);
}

/* this function was automagically generated */
static int32_t NaClSysClockDecoder(struct NaClAppThread *natp) {
  #ifdef SYSCALL_TIMING
  int32_t retval;
  clock_t nacl_sys_begin;
  clock_t nacl_sys_finish;
  #endif
  #ifdef NACL_SYSCALL_TRACE_ENABLED
  struct NaClApp *nap = natp->nap;
  int32_t retval;
#if 0
  unsigned int i = 0;
#endif
  #endif
    NaClCopyDropLock(natp->nap);
  #ifdef SYSCALL_TIMING
  nacl_syscall_counter++;
  nacl_syscall_invoked_times[NACL_sys_clock]++;
  nacl_sys_begin = clock();
  retval = NaClSysClock(natp);
  nacl_sys_finish = clock();
  nacl_syscall_execution_time[NACL_sys_clock] += (double)(nacl_sys_finish - nacl_sys_begin) / CLOCKS_PER_SEC;
  return retval;
  #endif
  #ifdef NACL_SYSCALL_TRACE_ENABLED
  printf("[NaClSysCallInterface] cage id = %d, syscall_num = NACL_sys_clock [enter][syscall_depth = %d]\n", nap->cage_id, nacl_syscall_trace_level_counter);
  printf("==> NACL_sys_clock(");
#if 0
  for (i = 0; i < sizeof(p)/4; i++) {
    printf("%x,", *((uint32_t *)&p+i));
  }
#endif
  printf(")\n");
  nacl_syscall_trace_level_counter++;
  retval = NaClSysClock(natp);
  nacl_syscall_trace_level_counter--;
  printf("[NaClSysCallInterface] cage id = %d, syscall_num = NACL_sys_clock [exit][syscall_depth = %d] \n", nap->cage_id, nacl_syscall_trace_level_counter);
  return retval;
  #endif

  return NaClSysClock(natp);

}

/*
 * Check that the function being wrapped has the same type as the type
 * declared in SYSCALL_LIST.
 */
static INLINE void AssertSameType_NaClSysClock(void) {
  /* This assignment will give an error if the argument types don't match. */
  int32_t (*dummy)(struct NaClAppThread *natp) = NaClSysClock;
  /* 'dummy' is not actually a parameter but this suppresses the warning. */
  UNREFERENCED_PARAMETER(dummy);
}

/* this function was automagically generated */
static int32_t NaClSysNanosleepDecoder(struct NaClAppThread *natp) {
  #ifdef SYSCALL_TIMING
  int32_t retval;
  clock_t nacl_sys_begin;
  clock_t nacl_sys_finish;
  #endif
  #ifdef NACL_SYSCALL_TRACE_ENABLED
  struct NaClApp *nap = natp->nap;
  int32_t retval;
#if 1
  unsigned int i = 0;
#endif
  #endif
    struct NaClSysNanosleepArgs {
    uint32_t req;
    uint32_t rem;
  } p;
  if (!NaClCopyInFromUserAndDropLock(natp->nap, &p, natp->usr_syscall_args,
                                     sizeof p)) {
    return -NACL_ABI_EFAULT;
  }


  #ifdef SYSCALL_TIMING
  nacl_syscall_counter++;
  nacl_syscall_invoked_times[NACL_sys_nanosleep]++;
  nacl_sys_begin = clock();
  retval = NaClSysNanosleep(natp, (struct nacl_abi_timespec *) (uintptr_t) p.req, (struct nacl_abi_timespec *) (uintptr_t) p.rem);
  nacl_sys_finish = clock();
  nacl_syscall_execution_time[NACL_sys_nanosleep] += (double)(nacl_sys_finish - nacl_sys_begin) / CLOCKS_PER_SEC;
  return retval;
  #endif
  #ifdef NACL_SYSCALL_TRACE_ENABLED
  printf("[NaClSysCallInterface] cage id = %d, syscall_num = NACL_sys_nanosleep [enter][syscall_depth = %d]\n", nap->cage_id, nacl_syscall_trace_level_counter);
  printf("==> NACL_sys_nanosleep(");
#if 1
  for (i = 0; i < sizeof(p)/4; i++) {
    printf("%x,", *((uint32_t *)&p+i));
  }
#endif
  printf(")\n");
  nacl_syscall_trace_level_counter++;
  retval = NaClSysNanosleep(natp, (struct nacl_abi_timespec *) (uintptr_t) p.req, (struct nacl_abi_timespec *) (uintptr_t) p.rem);
  nacl_syscall_trace_level_counter--;
  printf("[NaClSysCallInterface] cage id = %d, syscall_num = NACL_sys_nanosleep [exit][syscall_depth = %d] \n", nap->cage_id, nacl_syscall_trace_level_counter);
  return retval;
  #endif

  return NaClSysNanosleep(natp, (struct nacl_abi_timespec *) (uintptr_t) p.req, (struct nacl_abi_timespec *) (uintptr_t) p.rem);

}

/*
 * Check that the function being wrapped has the same type as the type
 * declared in SYSCALL_LIST.
 */
static INLINE void AssertSameType_NaClSysNanosleep(void) {
  /* This assignment will give an error if the argument types don't match. */
  int32_t (*dummy)(struct NaClAppThread *natp, struct nacl_abi_timespec *req, struct nacl_abi_timespec *rem) = NaClSysNanosleep;
  /* 'dummy' is not actually a parameter but this suppresses the warning. */
  UNREFERENCED_PARAMETER(dummy);
}

/* this function was automagically generated */
static int32_t NaClSysClockGetResDecoder(struct NaClAppThread *natp) {
  #ifdef SYSCALL_TIMING
  int32_t retval;
  clock_t nacl_sys_begin;
  clock_t nacl_sys_finish;
  #endif
  #ifdef NACL_SYSCALL_TRACE_ENABLED
  struct NaClApp *nap = natp->nap;
  int32_t retval;
#if 1
  unsigned int i = 0;
#endif
  #endif
    struct NaClSysClockGetResArgs {
    uint32_t clk_id;
    uint32_t tsp;
  } p;
  if (!NaClCopyInFromUserAndDropLock(natp->nap, &p, natp->usr_syscall_args,
                                     sizeof p)) {
    return -NACL_ABI_EFAULT;
  }


  #ifdef SYSCALL_TIMING
  nacl_syscall_counter++;
  nacl_syscall_invoked_times[NACL_sys_clock_getres]++;
  nacl_sys_begin = clock();
  retval = NaClSysClockGetRes(natp, (int)  p.clk_id, (uint32_t)  p.tsp);
  nacl_sys_finish = clock();
  nacl_syscall_execution_time[NACL_sys_clock_getres] += (double)(nacl_sys_finish - nacl_sys_begin) / CLOCKS_PER_SEC;
  return retval;
  #endif
  #ifdef NACL_SYSCALL_TRACE_ENABLED
  printf("[NaClSysCallInterface] cage id = %d, syscall_num = NACL_sys_clock_getres [enter][syscall_depth = %d]\n", nap->cage_id, nacl_syscall_trace_level_counter);
  printf("==> NACL_sys_clock_getres(");
#if 1
  for (i = 0; i < sizeof(p)/4; i++) {
    printf("%x,", *((uint32_t *)&p+i));
  }
#endif
  printf(")\n");
  nacl_syscall_trace_level_counter++;
  retval = NaClSysClockGetRes(natp, (int)  p.clk_id, (uint32_t)  p.tsp);
  nacl_syscall_trace_level_counter--;
  printf("[NaClSysCallInterface] cage id = %d, syscall_num = NACL_sys_clock_getres [exit][syscall_depth = %d] \n", nap->cage_id, nacl_syscall_trace_level_counter);
  return retval;
  #endif

  return NaClSysClockGetRes(natp, (int)  p.clk_id, (uint32_t)  p.tsp);

}

/*
 * Check that the function being wrapped has the same type as the type
 * declared in SYSCALL_LIST.
 */
static INLINE void AssertSameType_NaClSysClockGetRes(void) {
  /* This assignment will give an error if the argument types don't match. */
  int32_t (*dummy)(struct NaClAppThread *natp, int clk_id, uint32_t tsp) = NaClSysClockGetRes;
  /* 'dummy' is not actually a parameter but this suppresses the warning. */
  UNREFERENCED_PARAMETER(dummy);
}

/* this function was automagically generated */
static int32_t NaClSysClockGetTimeDecoder(struct NaClAppThread *natp) {
  #ifdef SYSCALL_TIMING
  int32_t retval;
  clock_t nacl_sys_begin;
  clock_t nacl_sys_finish;
  #endif
  #ifdef NACL_SYSCALL_TRACE_ENABLED
  struct NaClApp *nap = natp->nap;
  int32_t retval;
#if 1
  unsigned int i = 0;
#endif
  #endif
    struct NaClSysClockGetTimeArgs {
    uint32_t clk_id;
    uint32_t tsp;
  } p;
  if (!NaClCopyInFromUserAndDropLock(natp->nap, &p, natp->usr_syscall_args,
                                     sizeof p)) {
    return -NACL_ABI_EFAULT;
  }


  #ifdef SYSCALL_TIMING
  nacl_syscall_counter++;
  nacl_syscall_invoked_times[NACL_sys_clock_gettime]++;
  nacl_sys_begin = clock();
  retval = NaClSysClockGetTime(natp, (int)  p.clk_id, (uint32_t)  p.tsp);
  nacl_sys_finish = clock();
  nacl_syscall_execution_time[NACL_sys_clock_gettime] += (double)(nacl_sys_finish - nacl_sys_begin) / CLOCKS_PER_SEC;
  return retval;
  #endif
  #ifdef NACL_SYSCALL_TRACE_ENABLED
  printf("[NaClSysCallInterface] cage id = %d, syscall_num = NACL_sys_clock_gettime [enter][syscall_depth = %d]\n", nap->cage_id, nacl_syscall_trace_level_counter);
  printf("==> NACL_sys_clock_gettime(");
#if 1
  for (i = 0; i < sizeof(p)/4; i++) {
    printf("%x,", *((uint32_t *)&p+i));
  }
#endif
  printf(")\n");
  nacl_syscall_trace_level_counter++;
  retval = NaClSysClockGetTime(natp, (int)  p.clk_id, (uint32_t)  p.tsp);
  nacl_syscall_trace_level_counter--;
  printf("[NaClSysCallInterface] cage id = %d, syscall_num = NACL_sys_clock_gettime [exit][syscall_depth = %d] \n", nap->cage_id, nacl_syscall_trace_level_counter);
  return retval;
  #endif

  return NaClSysClockGetTime(natp, (int)  p.clk_id, (uint32_t)  p.tsp);

}

/*
 * Check that the function being wrapped has the same type as the type
 * declared in SYSCALL_LIST.
 */
static INLINE void AssertSameType_NaClSysClockGetTime(void) {
  /* This assignment will give an error if the argument types don't match. */
  int32_t (*dummy)(struct NaClAppThread *natp, int clk_id, uint32_t tsp) = NaClSysClockGetTime;
  /* 'dummy' is not actually a parameter but this suppresses the warning. */
  UNREFERENCED_PARAMETER(dummy);
}

/* this function was automagically generated */
static int32_t NaClSysMkdirDecoder(struct NaClAppThread *natp) {
  #ifdef SYSCALL_TIMING
  int32_t retval;
  clock_t nacl_sys_begin;
  clock_t nacl_sys_finish;
  #endif
  #ifdef NACL_SYSCALL_TRACE_ENABLED
  struct NaClApp *nap = natp->nap;
  int32_t retval;
#if 1
  unsigned int i = 0;
#endif
  #endif
    struct NaClSysMkdirArgs {
    uint32_t path;
    uint32_t mode;
  } p;
  if (!NaClCopyInFromUserAndDropLock(natp->nap, &p, natp->usr_syscall_args,
                                     sizeof p)) {
    return -NACL_ABI_EFAULT;
  }


  #ifdef SYSCALL_TIMING
  nacl_syscall_counter++;
  nacl_syscall_invoked_times[NACL_sys_mkdir]++;
  nacl_sys_begin = clock();
  retval = NaClSysMkdir(natp, (uint32_t)  p.path, (int)  p.mode);
  nacl_sys_finish = clock();
  nacl_syscall_execution_time[NACL_sys_mkdir] += (double)(nacl_sys_finish - nacl_sys_begin) / CLOCKS_PER_SEC;
  return retval;
  #endif
  #ifdef NACL_SYSCALL_TRACE_ENABLED
  printf("[NaClSysCallInterface] cage id = %d, syscall_num = NACL_sys_mkdir [enter][syscall_depth = %d]\n", nap->cage_id, nacl_syscall_trace_level_counter);
  printf("==> NACL_sys_mkdir(");
#if 1
  for (i = 0; i < sizeof(p)/4; i++) {
    printf("%x,", *((uint32_t *)&p+i));
  }
#endif
  printf(")\n");
  nacl_syscall_trace_level_counter++;
  retval = NaClSysMkdir(natp, (uint32_t)  p.path, (int)  p.mode);
  nacl_syscall_trace_level_counter--;
  printf("[NaClSysCallInterface] cage id = %d, syscall_num = NACL_sys_mkdir [exit][syscall_depth = %d] \n", nap->cage_id, nacl_syscall_trace_level_counter);
  return retval;
  #endif

  return NaClSysMkdir(natp, (uint32_t)  p.path, (int)  p.mode);

}

/*
 * Check that the function being wrapped has the same type as the type
 * declared in SYSCALL_LIST.
 */
static INLINE void AssertSameType_NaClSysMkdir(void) {
  /* This assignment will give an error if the argument types don't match. */
  int32_t (*dummy)(struct NaClAppThread *natp, uint32_t path, int mode) = NaClSysMkdir;
  /* 'dummy' is not actually a parameter but this suppresses the warning. */
  UNREFERENCED_PARAMETER(dummy);
}

/* this function was automagically generated */
static int32_t NaClSysRmdirDecoder(struct NaClAppThread *natp) {
  #ifdef SYSCALL_TIMING
  int32_t retval;
  clock_t nacl_sys_begin;
  clock_t nacl_sys_finish;
  #endif
  #ifdef NACL_SYSCALL_TRACE_ENABLED
  struct NaClApp *nap = natp->nap;
  int32_t retval;
#if 1
  unsigned int i = 0;
#endif
  #endif
    struct NaClSysRmdirArgs {
    uint32_t path;
  } p;
  if (!NaClCopyInFromUserAndDropLock(natp->nap, &p, natp->usr_syscall_args,
                                     sizeof p)) {
    return -NACL_ABI_EFAULT;
  }


  #ifdef SYSCALL_TIMING
  nacl_syscall_counter++;
  nacl_syscall_invoked_times[NACL_sys_rmdir]++;
  nacl_sys_begin = clock();
  retval = NaClSysRmdir(natp, (uint32_t)  p.path);
  nacl_sys_finish = clock();
  nacl_syscall_execution_time[NACL_sys_rmdir] += (double)(nacl_sys_finish - nacl_sys_begin) / CLOCKS_PER_SEC;
  return retval;
  #endif
  #ifdef NACL_SYSCALL_TRACE_ENABLED
  printf("[NaClSysCallInterface] cage id = %d, syscall_num = NACL_sys_rmdir [enter][syscall_depth = %d]\n", nap->cage_id, nacl_syscall_trace_level_counter);
  printf("==> NACL_sys_rmdir(");
#if 1
  for (i = 0; i < sizeof(p)/4; i++) {
    printf("%x,", *((uint32_t *)&p+i));
  }
#endif
  printf(")\n");
  nacl_syscall_trace_level_counter++;
  retval = NaClSysRmdir(natp, (uint32_t)  p.path);
  nacl_syscall_trace_level_counter--;
  printf("[NaClSysCallInterface] cage id = %d, syscall_num = NACL_sys_rmdir [exit][syscall_depth = %d] \n", nap->cage_id, nacl_syscall_trace_level_counter);
  return retval;
  #endif

  return NaClSysRmdir(natp, (uint32_t)  p.path);

}

/*
 * Check that the function being wrapped has the same type as the type
 * declared in SYSCALL_LIST.
 */
static INLINE void AssertSameType_NaClSysRmdir(void) {
  /* This assignment will give an error if the argument types don't match. */
  int32_t (*dummy)(struct NaClAppThread *natp, uint32_t path) = NaClSysRmdir;
  /* 'dummy' is not actually a parameter but this suppresses the warning. */
  UNREFERENCED_PARAMETER(dummy);
}

/* this function was automagically generated */
static int32_t NaClSysChdirDecoder(struct NaClAppThread *natp) {
  #ifdef SYSCALL_TIMING
  int32_t retval;
  clock_t nacl_sys_begin;
  clock_t nacl_sys_finish;
  #endif
  #ifdef NACL_SYSCALL_TRACE_ENABLED
  struct NaClApp *nap = natp->nap;
  int32_t retval;
#if 1
  unsigned int i = 0;
#endif
  #endif
    struct NaClSysChdirArgs {
    uint32_t path;
  } p;
  if (!NaClCopyInFromUserAndDropLock(natp->nap, &p, natp->usr_syscall_args,
                                     sizeof p)) {
    return -NACL_ABI_EFAULT;
  }


  #ifdef SYSCALL_TIMING
  nacl_syscall_counter++;
  nacl_syscall_invoked_times[NACL_sys_chdir]++;
  nacl_sys_begin = clock();
  retval = NaClSysChdir(natp, (uint32_t)  p.path);
  nacl_sys_finish = clock();
  nacl_syscall_execution_time[NACL_sys_chdir] += (double)(nacl_sys_finish - nacl_sys_begin) / CLOCKS_PER_SEC;
  return retval;
  #endif
  #ifdef NACL_SYSCALL_TRACE_ENABLED
  printf("[NaClSysCallInterface] cage id = %d, syscall_num = NACL_sys_chdir [enter][syscall_depth = %d]\n", nap->cage_id, nacl_syscall_trace_level_counter);
  printf("==> NACL_sys_chdir(");
#if 1
  for (i = 0; i < sizeof(p)/4; i++) {
    printf("%x,", *((uint32_t *)&p+i));
  }
#endif
  printf(")\n");
  nacl_syscall_trace_level_counter++;
  retval = NaClSysChdir(natp, (uint32_t)  p.path);
  nacl_syscall_trace_level_counter--;
  printf("[NaClSysCallInterface] cage id = %d, syscall_num = NACL_sys_chdir [exit][syscall_depth = %d] \n", nap->cage_id, nacl_syscall_trace_level_counter);
  return retval;
  #endif

  return NaClSysChdir(natp, (uint32_t)  p.path);

}

/*
 * Check that the function being wrapped has the same type as the type
 * declared in SYSCALL_LIST.
 */
static INLINE void AssertSameType_NaClSysChdir(void) {
  /* This assignment will give an error if the argument types don't match. */
  int32_t (*dummy)(struct NaClAppThread *natp, uint32_t path) = NaClSysChdir;
  /* 'dummy' is not actually a parameter but this suppresses the warning. */
  UNREFERENCED_PARAMETER(dummy);
}

/* this function was automagically generated */
static int32_t NaClSysGetcwdDecoder(struct NaClAppThread *natp) {
  #ifdef SYSCALL_TIMING
  int32_t retval;
  clock_t nacl_sys_begin;
  clock_t nacl_sys_finish;
  #endif
  #ifdef NACL_SYSCALL_TRACE_ENABLED
  struct NaClApp *nap = natp->nap;
  int32_t retval;
#if 1
  unsigned int i = 0;
#endif
  #endif
    struct NaClSysGetcwdArgs {
    uint32_t buffer;
    uint32_t len;
  } p;
  if (!NaClCopyInFromUserAndDropLock(natp->nap, &p, natp->usr_syscall_args,
                                     sizeof p)) {
    return -NACL_ABI_EFAULT;
  }


  #ifdef SYSCALL_TIMING
  nacl_syscall_counter++;
  nacl_syscall_invoked_times[NACL_sys_getcwd]++;
  nacl_sys_begin = clock();
  retval = NaClSysGetcwd(natp, (uint32_t)  p.buffer, (int)  p.len);
  nacl_sys_finish = clock();
  nacl_syscall_execution_time[NACL_sys_getcwd] += (double)(nacl_sys_finish - nacl_sys_begin) / CLOCKS_PER_SEC;
  return retval;
  #endif
  #ifdef NACL_SYSCALL_TRACE_ENABLED
  printf("[NaClSysCallInterface] cage id = %d, syscall_num = NACL_sys_getcwd [enter][syscall_depth = %d]\n", nap->cage_id, nacl_syscall_trace_level_counter);
  printf("==> NACL_sys_getcwd(");
#if 1
  for (i = 0; i < sizeof(p)/4; i++) {
    printf("%x,", *((uint32_t *)&p+i));
  }
#endif
  printf(")\n");
  nacl_syscall_trace_level_counter++;
  retval = NaClSysGetcwd(natp, (uint32_t)  p.buffer, (int)  p.len);
  nacl_syscall_trace_level_counter--;
  printf("[NaClSysCallInterface] cage id = %d, syscall_num = NACL_sys_getcwd [exit][syscall_depth = %d] \n", nap->cage_id, nacl_syscall_trace_level_counter);
  return retval;
  #endif

  return NaClSysGetcwd(natp, (uint32_t)  p.buffer, (int)  p.len);

}

/*
 * Check that the function being wrapped has the same type as the type
 * declared in SYSCALL_LIST.
 */
static INLINE void AssertSameType_NaClSysGetcwd(void) {
  /* This assignment will give an error if the argument types don't match. */
  int32_t (*dummy)(struct NaClAppThread *natp, uint32_t buffer, int len) = NaClSysGetcwd;
  /* 'dummy' is not actually a parameter but this suppresses the warning. */
  UNREFERENCED_PARAMETER(dummy);
}

/* this function was automagically generated */
static int32_t NaClSysUnlinkDecoder(struct NaClAppThread *natp) {
  #ifdef SYSCALL_TIMING
  int32_t retval;
  clock_t nacl_sys_begin;
  clock_t nacl_sys_finish;
  #endif
  #ifdef NACL_SYSCALL_TRACE_ENABLED
  struct NaClApp *nap = natp->nap;
  int32_t retval;
#if 1
  unsigned int i = 0;
#endif
  #endif
    struct NaClSysUnlinkArgs {
    uint32_t path;
  } p;
  if (!NaClCopyInFromUserAndDropLock(natp->nap, &p, natp->usr_syscall_args,
                                     sizeof p)) {
    return -NACL_ABI_EFAULT;
  }


  #ifdef SYSCALL_TIMING
  nacl_syscall_counter++;
  nacl_syscall_invoked_times[NACL_sys_unlink]++;
  nacl_sys_begin = clock();
  retval = NaClSysUnlink(natp, (uint32_t)  p.path);
  nacl_sys_finish = clock();
  nacl_syscall_execution_time[NACL_sys_unlink] += (double)(nacl_sys_finish - nacl_sys_begin) / CLOCKS_PER_SEC;
  return retval;
  #endif
  #ifdef NACL_SYSCALL_TRACE_ENABLED
  printf("[NaClSysCallInterface] cage id = %d, syscall_num = NACL_sys_unlink [enter][syscall_depth = %d]\n", nap->cage_id, nacl_syscall_trace_level_counter);
  printf("==> NACL_sys_unlink(");
#if 1
  for (i = 0; i < sizeof(p)/4; i++) {
    printf("%x,", *((uint32_t *)&p+i));
  }
#endif
  printf(")\n");
  nacl_syscall_trace_level_counter++;
  retval = NaClSysUnlink(natp, (uint32_t)  p.path);
  nacl_syscall_trace_level_counter--;
  printf("[NaClSysCallInterface] cage id = %d, syscall_num = NACL_sys_unlink [exit][syscall_depth = %d] \n", nap->cage_id, nacl_syscall_trace_level_counter);
  return retval;
  #endif

  return NaClSysUnlink(natp, (uint32_t)  p.path);

}

/*
 * Check that the function being wrapped has the same type as the type
 * declared in SYSCALL_LIST.
 */
static INLINE void AssertSameType_NaClSysUnlink(void) {
  /* This assignment will give an error if the argument types don't match. */
  int32_t (*dummy)(struct NaClAppThread *natp, uint32_t path) = NaClSysUnlink;
  /* 'dummy' is not actually a parameter but this suppresses the warning. */
  UNREFERENCED_PARAMETER(dummy);
}

/* this function was automagically generated */
static int32_t NaClSysImcMakeBoundSockDecoder(struct NaClAppThread *natp) {
  #ifdef SYSCALL_TIMING
  int32_t retval;
  clock_t nacl_sys_begin;
  clock_t nacl_sys_finish;
  #endif
  #ifdef NACL_SYSCALL_TRACE_ENABLED
  struct NaClApp *nap = natp->nap;
  int32_t retval;
#if 1
  unsigned int i = 0;
#endif
  #endif
    struct NaClSysImcMakeBoundSockArgs {
    uint32_t sap;
  } p;
  if (!NaClCopyInFromUserAndDropLock(natp->nap, &p, natp->usr_syscall_args,
                                     sizeof p)) {
    return -NACL_ABI_EFAULT;
  }


  #ifdef SYSCALL_TIMING
  nacl_syscall_counter++;
  nacl_syscall_invoked_times[NACL_sys_imc_makeboundsock]++;
  nacl_sys_begin = clock();
  retval = NaClSysImcMakeBoundSock(natp, (int32_t *) (uintptr_t) p.sap);
  nacl_sys_finish = clock();
  nacl_syscall_execution_time[NACL_sys_imc_makeboundsock] += (double)(nacl_sys_finish - nacl_sys_begin) / CLOCKS_PER_SEC;
  return retval;
  #endif
  #ifdef NACL_SYSCALL_TRACE_ENABLED
  printf("[NaClSysCallInterface] cage id = %d, syscall_num = NACL_sys_imc_makeboundsock [enter][syscall_depth = %d]\n", nap->cage_id, nacl_syscall_trace_level_counter);
  printf("==> NACL_sys_imc_makeboundsock(");
#if 1
  for (i = 0; i < sizeof(p)/4; i++) {
    printf("%x,", *((uint32_t *)&p+i));
  }
#endif
  printf(")\n");
  nacl_syscall_trace_level_counter++;
  retval = NaClSysImcMakeBoundSock(natp, (int32_t *) (uintptr_t) p.sap);
  nacl_syscall_trace_level_counter--;
  printf("[NaClSysCallInterface] cage id = %d, syscall_num = NACL_sys_imc_makeboundsock [exit][syscall_depth = %d] \n", nap->cage_id, nacl_syscall_trace_level_counter);
  return retval;
  #endif

  return NaClSysImcMakeBoundSock(natp, (int32_t *) (uintptr_t) p.sap);

}

/*
 * Check that the function being wrapped has the same type as the type
 * declared in SYSCALL_LIST.
 */
static INLINE void AssertSameType_NaClSysImcMakeBoundSock(void) {
  /* This assignment will give an error if the argument types don't match. */
  int32_t (*dummy)(struct NaClAppThread *natp, int32_t *sap) = NaClSysImcMakeBoundSock;
  /* 'dummy' is not actually a parameter but this suppresses the warning. */
  UNREFERENCED_PARAMETER(dummy);
}

/* this function was automagically generated */
static int32_t NaClSysImcAcceptDecoder(struct NaClAppThread *natp) {
  #ifdef SYSCALL_TIMING
  int32_t retval;
  clock_t nacl_sys_begin;
  clock_t nacl_sys_finish;
  #endif
  #ifdef NACL_SYSCALL_TRACE_ENABLED
  struct NaClApp *nap = natp->nap;
  int32_t retval;
#if 1
  unsigned int i = 0;
#endif
  #endif
    struct NaClSysImcAcceptArgs {
    uint32_t d;
  } p;
  if (!NaClCopyInFromUserAndDropLock(natp->nap, &p, natp->usr_syscall_args,
                                     sizeof p)) {
    return -NACL_ABI_EFAULT;
  }


  #ifdef SYSCALL_TIMING
  nacl_syscall_counter++;
  nacl_syscall_invoked_times[NACL_sys_imc_accept]++;
  nacl_sys_begin = clock();
  retval = NaClSysImcAccept(natp, (int)  p.d);
  nacl_sys_finish = clock();
  nacl_syscall_execution_time[NACL_sys_imc_accept] += (double)(nacl_sys_finish - nacl_sys_begin) / CLOCKS_PER_SEC;
  return retval;
  #endif
  #ifdef NACL_SYSCALL_TRACE_ENABLED
  printf("[NaClSysCallInterface] cage id = %d, syscall_num = NACL_sys_imc_accept [enter][syscall_depth = %d]\n", nap->cage_id, nacl_syscall_trace_level_counter);
  printf("==> NACL_sys_imc_accept(");
#if 1
  for (i = 0; i < sizeof(p)/4; i++) {
    printf("%x,", *((uint32_t *)&p+i));
  }
#endif
  printf(")\n");
  nacl_syscall_trace_level_counter++;
  retval = NaClSysImcAccept(natp, (int)  p.d);
  nacl_syscall_trace_level_counter--;
  printf("[NaClSysCallInterface] cage id = %d, syscall_num = NACL_sys_imc_accept [exit][syscall_depth = %d] \n", nap->cage_id, nacl_syscall_trace_level_counter);
  return retval;
  #endif

  return NaClSysImcAccept(natp, (int)  p.d);

}

/*
 * Check that the function being wrapped has the same type as the type
 * declared in SYSCALL_LIST.
 */
static INLINE void AssertSameType_NaClSysImcAccept(void) {
  /* This assignment will give an error if the argument types don't match. */
  int32_t (*dummy)(struct NaClAppThread *natp, int d) = NaClSysImcAccept;
  /* 'dummy' is not actually a parameter but this suppresses the warning. */
  UNREFERENCED_PARAMETER(dummy);
}

/* this function was automagically generated */
static int32_t NaClSysImcConnectDecoder(struct NaClAppThread *natp) {
  #ifdef SYSCALL_TIMING
  int32_t retval;
  clock_t nacl_sys_begin;
  clock_t nacl_sys_finish;
  #endif
  #ifdef NACL_SYSCALL_TRACE_ENABLED
  struct NaClApp *nap = natp->nap;
  int32_t retval;
#if 1
  unsigned int i = 0;
#endif
  #endif
    struct NaClSysImcConnectArgs {
    uint32_t d;
  } p;
  if (!NaClCopyInFromUserAndDropLock(natp->nap, &p, natp->usr_syscall_args,
                                     sizeof p)) {
    return -NACL_ABI_EFAULT;
  }


  #ifdef SYSCALL_TIMING
  nacl_syscall_counter++;
  nacl_syscall_invoked_times[NACL_sys_imc_connect]++;
  nacl_sys_begin = clock();
  retval = NaClSysImcConnect(natp, (int)  p.d);
  nacl_sys_finish = clock();
  nacl_syscall_execution_time[NACL_sys_imc_connect] += (double)(nacl_sys_finish - nacl_sys_begin) / CLOCKS_PER_SEC;
  return retval;
  #endif
  #ifdef NACL_SYSCALL_TRACE_ENABLED
  printf("[NaClSysCallInterface] cage id = %d, syscall_num = NACL_sys_imc_connect [enter][syscall_depth = %d]\n", nap->cage_id, nacl_syscall_trace_level_counter);
  printf("==> NACL_sys_imc_connect(");
#if 1
  for (i = 0; i < sizeof(p)/4; i++) {
    printf("%x,", *((uint32_t *)&p+i));
  }
#endif
  printf(")\n");
  nacl_syscall_trace_level_counter++;
  retval = NaClSysImcConnect(natp, (int)  p.d);
  nacl_syscall_trace_level_counter--;
  printf("[NaClSysCallInterface] cage id = %d, syscall_num = NACL_sys_imc_connect [exit][syscall_depth = %d] \n", nap->cage_id, nacl_syscall_trace_level_counter);
  return retval;
  #endif

  return NaClSysImcConnect(natp, (int)  p.d);

}

/*
 * Check that the function being wrapped has the same type as the type
 * declared in SYSCALL_LIST.
 */
static INLINE void AssertSameType_NaClSysImcConnect(void) {
  /* This assignment will give an error if the argument types don't match. */
  int32_t (*dummy)(struct NaClAppThread *natp, int d) = NaClSysImcConnect;
  /* 'dummy' is not actually a parameter but this suppresses the warning. */
  UNREFERENCED_PARAMETER(dummy);
}

/* this function was automagically generated */
static int32_t NaClSysImcSendmsgDecoder(struct NaClAppThread *natp) {
  #ifdef SYSCALL_TIMING
  int32_t retval;
  clock_t nacl_sys_begin;
  clock_t nacl_sys_finish;
  #endif
  #ifdef NACL_SYSCALL_TRACE_ENABLED
  struct NaClApp *nap = natp->nap;
  int32_t retval;
#if 1
  unsigned int i = 0;
#endif
  #endif
    struct NaClSysImcSendmsgArgs {
    uint32_t d;
    uint32_t nanimhp;
    uint32_t flags;
  } p;
  if (!NaClCopyInFromUserAndDropLock(natp->nap, &p, natp->usr_syscall_args,
                                     sizeof p)) {
    return -NACL_ABI_EFAULT;
  }


  #ifdef SYSCALL_TIMING
  nacl_syscall_counter++;
  nacl_syscall_invoked_times[NACL_sys_imc_sendmsg]++;
  nacl_sys_begin = clock();
  retval = NaClSysImcSendmsg(natp, (int)  p.d, (struct NaClAbiNaClImcMsgHdr *) (uintptr_t) p.nanimhp, (int)  p.flags);
  nacl_sys_finish = clock();
  nacl_syscall_execution_time[NACL_sys_imc_sendmsg] += (double)(nacl_sys_finish - nacl_sys_begin) / CLOCKS_PER_SEC;
  return retval;
  #endif
  #ifdef NACL_SYSCALL_TRACE_ENABLED
  printf("[NaClSysCallInterface] cage id = %d, syscall_num = NACL_sys_imc_sendmsg [enter][syscall_depth = %d]\n", nap->cage_id, nacl_syscall_trace_level_counter);
  printf("==> NACL_sys_imc_sendmsg(");
#if 1
  for (i = 0; i < sizeof(p)/4; i++) {
    printf("%x,", *((uint32_t *)&p+i));
  }
#endif
  printf(")\n");
  nacl_syscall_trace_level_counter++;
  retval = NaClSysImcSendmsg(natp, (int)  p.d, (struct NaClAbiNaClImcMsgHdr *) (uintptr_t) p.nanimhp, (int)  p.flags);
  nacl_syscall_trace_level_counter--;
  printf("[NaClSysCallInterface] cage id = %d, syscall_num = NACL_sys_imc_sendmsg [exit][syscall_depth = %d] \n", nap->cage_id, nacl_syscall_trace_level_counter);
  return retval;
  #endif

  return NaClSysImcSendmsg(natp, (int)  p.d, (struct NaClAbiNaClImcMsgHdr *) (uintptr_t) p.nanimhp, (int)  p.flags);

}

/*
 * Check that the function being wrapped has the same type as the type
 * declared in SYSCALL_LIST.
 */
static INLINE void AssertSameType_NaClSysImcSendmsg(void) {
  /* This assignment will give an error if the argument types don't match. */
  int32_t (*dummy)(struct NaClAppThread *natp, int d, struct NaClAbiNaClImcMsgHdr *nanimhp, int flags) = NaClSysImcSendmsg;
  /* 'dummy' is not actually a parameter but this suppresses the warning. */
  UNREFERENCED_PARAMETER(dummy);
}

/* this function was automagically generated */
static int32_t NaClSysImcRecvmsgDecoder(struct NaClAppThread *natp) {
  #ifdef SYSCALL_TIMING
  int32_t retval;
  clock_t nacl_sys_begin;
  clock_t nacl_sys_finish;
  #endif
  #ifdef NACL_SYSCALL_TRACE_ENABLED
  struct NaClApp *nap = natp->nap;
  int32_t retval;
#if 1
  unsigned int i = 0;
#endif
  #endif
    struct NaClSysImcRecvmsgArgs {
    uint32_t d;
    uint32_t nanimhp;
    uint32_t flags;
  } p;
  if (!NaClCopyInFromUserAndDropLock(natp->nap, &p, natp->usr_syscall_args,
                                     sizeof p)) {
    return -NACL_ABI_EFAULT;
  }


  #ifdef SYSCALL_TIMING
  nacl_syscall_counter++;
  nacl_syscall_invoked_times[NACL_sys_imc_recvmsg]++;
  nacl_sys_begin = clock();
  retval = NaClSysImcRecvmsg(natp, (int)  p.d, (struct NaClAbiNaClImcMsgHdr *) (uintptr_t) p.nanimhp, (int)  p.flags);
  nacl_sys_finish = clock();
  nacl_syscall_execution_time[NACL_sys_imc_recvmsg] += (double)(nacl_sys_finish - nacl_sys_begin) / CLOCKS_PER_SEC;
  return retval;
  #endif
  #ifdef NACL_SYSCALL_TRACE_ENABLED
  printf("[NaClSysCallInterface] cage id = %d, syscall_num = NACL_sys_imc_recvmsg [enter][syscall_depth = %d]\n", nap->cage_id, nacl_syscall_trace_level_counter);
  printf("==> NACL_sys_imc_recvmsg(");
#if 1
  for (i = 0; i < sizeof(p)/4; i++) {
    printf("%x,", *((uint32_t *)&p+i));
  }
#endif
  printf(")\n");
  nacl_syscall_trace_level_counter++;
  retval = NaClSysImcRecvmsg(natp, (int)  p.d, (struct NaClAbiNaClImcMsgHdr *) (uintptr_t) p.nanimhp, (int)  p.flags);
  nacl_syscall_trace_level_counter--;
  printf("[NaClSysCallInterface] cage id = %d, syscall_num = NACL_sys_imc_recvmsg [exit][syscall_depth = %d] \n", nap->cage_id, nacl_syscall_trace_level_counter);
  return retval;
  #endif

  return NaClSysImcRecvmsg(natp, (int)  p.d, (struct NaClAbiNaClImcMsgHdr *) (uintptr_t) p.nanimhp, (int)  p.flags);

}

/*
 * Check that the function being wrapped has the same type as the type
 * declared in SYSCALL_LIST.
 */
static INLINE void AssertSameType_NaClSysImcRecvmsg(void) {
  /* This assignment will give an error if the argument types don't match. */
  int32_t (*dummy)(struct NaClAppThread *natp, int d, struct NaClAbiNaClImcMsgHdr *nanimhp, int flags) = NaClSysImcRecvmsg;
  /* 'dummy' is not actually a parameter but this suppresses the warning. */
  UNREFERENCED_PARAMETER(dummy);
}

/* this function was automagically generated */
static int32_t NaClSysImcMemObjCreateDecoder(struct NaClAppThread *natp) {
  #ifdef SYSCALL_TIMING
  int32_t retval;
  clock_t nacl_sys_begin;
  clock_t nacl_sys_finish;
  #endif
  #ifdef NACL_SYSCALL_TRACE_ENABLED
  struct NaClApp *nap = natp->nap;
  int32_t retval;
#if 1
  unsigned int i = 0;
#endif
  #endif
    struct NaClSysImcMemObjCreateArgs {
    uint32_t size;
  } p;
  if (!NaClCopyInFromUserAndDropLock(natp->nap, &p, natp->usr_syscall_args,
                                     sizeof p)) {
    return -NACL_ABI_EFAULT;
  }


  #ifdef SYSCALL_TIMING
  nacl_syscall_counter++;
  nacl_syscall_invoked_times[NACL_sys_imc_mem_obj_create]++;
  nacl_sys_begin = clock();
  retval = NaClSysImcMemObjCreate(natp, (size_t)  p.size);
  nacl_sys_finish = clock();
  nacl_syscall_execution_time[NACL_sys_imc_mem_obj_create] += (double)(nacl_sys_finish - nacl_sys_begin) / CLOCKS_PER_SEC;
  return retval;
  #endif
  #ifdef NACL_SYSCALL_TRACE_ENABLED
  printf("[NaClSysCallInterface] cage id = %d, syscall_num = NACL_sys_imc_mem_obj_create [enter][syscall_depth = %d]\n", nap->cage_id, nacl_syscall_trace_level_counter);
  printf("==> NACL_sys_imc_mem_obj_create(");
#if 1
  for (i = 0; i < sizeof(p)/4; i++) {
    printf("%x,", *((uint32_t *)&p+i));
  }
#endif
  printf(")\n");
  nacl_syscall_trace_level_counter++;
  retval = NaClSysImcMemObjCreate(natp, (size_t)  p.size);
  nacl_syscall_trace_level_counter--;
  printf("[NaClSysCallInterface] cage id = %d, syscall_num = NACL_sys_imc_mem_obj_create [exit][syscall_depth = %d] \n", nap->cage_id, nacl_syscall_trace_level_counter);
  return retval;
  #endif

  return NaClSysImcMemObjCreate(natp, (size_t)  p.size);

}

/*
 * Check that the function being wrapped has the same type as the type
 * declared in SYSCALL_LIST.
 */
static INLINE void AssertSameType_NaClSysImcMemObjCreate(void) {
  /* This assignment will give an error if the argument types don't match. */
  int32_t (*dummy)(struct NaClAppThread *natp, size_t size) = NaClSysImcMemObjCreate;
  /* 'dummy' is not actually a parameter but this suppresses the warning. */
  UNREFERENCED_PARAMETER(dummy);
}

/* this function was automagically generated */
static int32_t NaClSysTlsInitDecoder(struct NaClAppThread *natp) {
  #ifdef SYSCALL_TIMING
  int32_t retval;
  clock_t nacl_sys_begin;
  clock_t nacl_sys_finish;
  #endif
  #ifdef NACL_SYSCALL_TRACE_ENABLED
  struct NaClApp *nap = natp->nap;
  int32_t retval;
#if 1
  unsigned int i = 0;
#endif
  #endif
    struct NaClSysTlsInitArgs {
    uint32_t thread_ptr;
  } p;
  if (!NaClCopyInFromUserAndDropLock(natp->nap, &p, natp->usr_syscall_args,
                                     sizeof p)) {
    return -NACL_ABI_EFAULT;
  }


  #ifdef SYSCALL_TIMING
  nacl_syscall_counter++;
  nacl_syscall_invoked_times[NACL_sys_tls_init]++;
  nacl_sys_begin = clock();
  retval = NaClSysTlsInit(natp, (uint32_t)  p.thread_ptr);
  nacl_sys_finish = clock();
  nacl_syscall_execution_time[NACL_sys_tls_init] += (double)(nacl_sys_finish - nacl_sys_begin) / CLOCKS_PER_SEC;
  return retval;
  #endif
  #ifdef NACL_SYSCALL_TRACE_ENABLED
  printf("[NaClSysCallInterface] cage id = %d, syscall_num = NACL_sys_tls_init [enter][syscall_depth = %d]\n", nap->cage_id, nacl_syscall_trace_level_counter);
  printf("==> NACL_sys_tls_init(");
#if 1
  for (i = 0; i < sizeof(p)/4; i++) {
    printf("%x,", *((uint32_t *)&p+i));
  }
#endif
  printf(")\n");
  nacl_syscall_trace_level_counter++;
  retval = NaClSysTlsInit(natp, (uint32_t)  p.thread_ptr);
  nacl_syscall_trace_level_counter--;
  printf("[NaClSysCallInterface] cage id = %d, syscall_num = NACL_sys_tls_init [exit][syscall_depth = %d] \n", nap->cage_id, nacl_syscall_trace_level_counter);
  return retval;
  #endif

  return NaClSysTlsInit(natp, (uint32_t)  p.thread_ptr);

}

/*
 * Check that the function being wrapped has the same type as the type
 * declared in SYSCALL_LIST.
 */
static INLINE void AssertSameType_NaClSysTlsInit(void) {
  /* This assignment will give an error if the argument types don't match. */
  int32_t (*dummy)(struct NaClAppThread *natp, uint32_t thread_ptr) = NaClSysTlsInit;
  /* 'dummy' is not actually a parameter but this suppresses the warning. */
  UNREFERENCED_PARAMETER(dummy);
}

/* this function was automagically generated */
static int32_t NaClSysThreadCreateDecoder(struct NaClAppThread *natp) {
  #ifdef SYSCALL_TIMING
  int32_t retval;
  clock_t nacl_sys_begin;
  clock_t nacl_sys_finish;
  #endif
  #ifdef NACL_SYSCALL_TRACE_ENABLED
  struct NaClApp *nap = natp->nap;
  int32_t retval;
#if 1
  unsigned int i = 0;
#endif
  #endif
    struct NaClSysThreadCreateArgs {
    uint32_t prog_ctr;
    uint32_t stack_ptr;
    uint32_t thread_ptr;
    uint32_t second_thread_ptr;
  } p;
  if (!NaClCopyInFromUserAndDropLock(natp->nap, &p, natp->usr_syscall_args,
                                     sizeof p)) {
    return -NACL_ABI_EFAULT;
  }


  #ifdef SYSCALL_TIMING
  nacl_syscall_counter++;
  nacl_syscall_invoked_times[NACL_sys_thread_create]++;
  nacl_sys_begin = clock();
  retval = NaClSysThreadCreate(natp, (void *) (uintptr_t) p.prog_ctr, (uint32_t)  p.stack_ptr, (uint32_t)  p.thread_ptr, (uint32_t)  p.second_thread_ptr);
  nacl_sys_finish = clock();
  nacl_syscall_execution_time[NACL_sys_thread_create] += (double)(nacl_sys_finish - nacl_sys_begin) / CLOCKS_PER_SEC;
  return retval;
  #endif
  #ifdef NACL_SYSCALL_TRACE_ENABLED
  printf("[NaClSysCallInterface] cage id = %d, syscall_num = NACL_sys_thread_create [enter][syscall_depth = %d]\n", nap->cage_id, nacl_syscall_trace_level_counter);
  printf("==> NACL_sys_thread_create(");
#if 1
  for (i = 0; i < sizeof(p)/4; i++) {
    printf("%x,", *((uint32_t *)&p+i));
  }
#endif
  printf(")\n");
  nacl_syscall_trace_level_counter++;
  retval = NaClSysThreadCreate(natp, (void *) (uintptr_t) p.prog_ctr, (uint32_t)  p.stack_ptr, (uint32_t)  p.thread_ptr, (uint32_t)  p.second_thread_ptr);
  nacl_syscall_trace_level_counter--;
  printf("[NaClSysCallInterface] cage id = %d, syscall_num = NACL_sys_thread_create [exit][syscall_depth = %d] \n", nap->cage_id, nacl_syscall_trace_level_counter);
  return retval;
  #endif

  return NaClSysThreadCreate(natp, (void *) (uintptr_t) p.prog_ctr, (uint32_t)  p.stack_ptr, (uint32_t)  p.thread_ptr, (uint32_t)  p.second_thread_ptr);

}

/*
 * Check that the function being wrapped has the same type as the type
 * declared in SYSCALL_LIST.
 */
static INLINE void AssertSameType_NaClSysThreadCreate(void) {
  /* This assignment will give an error if the argument types don't match. */
  int32_t (*dummy)(struct NaClAppThread *natp, void *prog_ctr, uint32_t stack_ptr, uint32_t thread_ptr, uint32_t second_thread_ptr) = NaClSysThreadCreate;
  /* 'dummy' is not actually a parameter but this suppresses the warning. */
  UNREFERENCED_PARAMETER(dummy);
}

/* this function was automagically generated */
static int32_t NaClSysTlsGetDecoder(struct NaClAppThread *natp) {
  #ifdef SYSCALL_TIMING
  int32_t retval;
  clock_t nacl_sys_begin;
  clock_t nacl_sys_finish;
  #endif
  #ifdef NACL_SYSCALL_TRACE_ENABLED
  struct NaClApp *nap = natp->nap;
  int32_t retval;
#if 0
  unsigned int i = 0;
#endif
  #endif
    NaClCopyDropLock(natp->nap);
  #ifdef SYSCALL_TIMING
  nacl_syscall_counter++;
  nacl_syscall_invoked_times[NACL_sys_tls_get]++;
  nacl_sys_begin = clock();
  retval = NaClSysTlsGet(natp);
  nacl_sys_finish = clock();
  nacl_syscall_execution_time[NACL_sys_tls_get] += (double)(nacl_sys_finish - nacl_sys_begin) / CLOCKS_PER_SEC;
  return retval;
  #endif
  #ifdef NACL_SYSCALL_TRACE_ENABLED
  printf("[NaClSysCallInterface] cage id = %d, syscall_num = NACL_sys_tls_get [enter][syscall_depth = %d]\n", nap->cage_id, nacl_syscall_trace_level_counter);
  printf("==> NACL_sys_tls_get(");
#if 0
  for (i = 0; i < sizeof(p)/4; i++) {
    printf("%x,", *((uint32_t *)&p+i));
  }
#endif
  printf(")\n");
  nacl_syscall_trace_level_counter++;
  retval = NaClSysTlsGet(natp);
  nacl_syscall_trace_level_counter--;
  printf("[NaClSysCallInterface] cage id = %d, syscall_num = NACL_sys_tls_get [exit][syscall_depth = %d] \n", nap->cage_id, nacl_syscall_trace_level_counter);
  return retval;
  #endif

  return NaClSysTlsGet(natp);

}

/*
 * Check that the function being wrapped has the same type as the type
 * declared in SYSCALL_LIST.
 */
static INLINE void AssertSameType_NaClSysTlsGet(void) {
  /* This assignment will give an error if the argument types don't match. */
  int32_t (*dummy)(struct NaClAppThread *natp) = NaClSysTlsGet;
  /* 'dummy' is not actually a parameter but this suppresses the warning. */
  UNREFERENCED_PARAMETER(dummy);
}

/* this function was automagically generated */
static int32_t NaClSysThreadNiceDecoder(struct NaClAppThread *natp) {
  #ifdef SYSCALL_TIMING
  int32_t retval;
  clock_t nacl_sys_begin;
  clock_t nacl_sys_finish;
  #endif
  #ifdef NACL_SYSCALL_TRACE_ENABLED
  struct NaClApp *nap = natp->nap;
  int32_t retval;
#if 1
  unsigned int i = 0;
#endif
  #endif
    struct NaClSysThreadNiceArgs {
    uint32_t nice;
  } p;
  if (!NaClCopyInFromUserAndDropLock(natp->nap, &p, natp->usr_syscall_args,
                                     sizeof p)) {
    return -NACL_ABI_EFAULT;
  }


  #ifdef SYSCALL_TIMING
  nacl_syscall_counter++;
  nacl_syscall_invoked_times[NACL_sys_thread_nice]++;
  nacl_sys_begin = clock();
  retval = NaClSysThreadNice(natp, (const int)  p.nice);
  nacl_sys_finish = clock();
  nacl_syscall_execution_time[NACL_sys_thread_nice] += (double)(nacl_sys_finish - nacl_sys_begin) / CLOCKS_PER_SEC;
  return retval;
  #endif
  #ifdef NACL_SYSCALL_TRACE_ENABLED
  printf("[NaClSysCallInterface] cage id = %d, syscall_num = NACL_sys_thread_nice [enter][syscall_depth = %d]\n", nap->cage_id, nacl_syscall_trace_level_counter);
  printf("==> NACL_sys_thread_nice(");
#if 1
  for (i = 0; i < sizeof(p)/4; i++) {
    printf("%x,", *((uint32_t *)&p+i));
  }
#endif
  printf(")\n");
  nacl_syscall_trace_level_counter++;
  retval = NaClSysThreadNice(natp, (const int)  p.nice);
  nacl_syscall_trace_level_counter--;
  printf("[NaClSysCallInterface] cage id = %d, syscall_num = NACL_sys_thread_nice [exit][syscall_depth = %d] \n", nap->cage_id, nacl_syscall_trace_level_counter);
  return retval;
  #endif

  return NaClSysThreadNice(natp, (const int)  p.nice);

}

/*
 * Check that the function being wrapped has the same type as the type
 * declared in SYSCALL_LIST.
 */
static INLINE void AssertSameType_NaClSysThreadNice(void) {
  /* This assignment will give an error if the argument types don't match. */
  int32_t (*dummy)(struct NaClAppThread *natp, const int nice) = NaClSysThreadNice;
  /* 'dummy' is not actually a parameter but this suppresses the warning. */
  UNREFERENCED_PARAMETER(dummy);
}

/* this function was automagically generated */
static int32_t NaClSysMutexCreateDecoder(struct NaClAppThread *natp) {
  #ifdef SYSCALL_TIMING
  int32_t retval;
  clock_t nacl_sys_begin;
  clock_t nacl_sys_finish;
  #endif
  #ifdef NACL_SYSCALL_TRACE_ENABLED
  struct NaClApp *nap = natp->nap;
  int32_t retval;
#if 0
  unsigned int i = 0;
#endif
  #endif
    NaClCopyDropLock(natp->nap);
  #ifdef SYSCALL_TIMING
  nacl_syscall_counter++;
  nacl_syscall_invoked_times[NACL_sys_mutex_create]++;
  nacl_sys_begin = clock();
  retval = NaClSysMutexCreate(natp);
  nacl_sys_finish = clock();
  nacl_syscall_execution_time[NACL_sys_mutex_create] += (double)(nacl_sys_finish - nacl_sys_begin) / CLOCKS_PER_SEC;
  return retval;
  #endif
  #ifdef NACL_SYSCALL_TRACE_ENABLED
  printf("[NaClSysCallInterface] cage id = %d, syscall_num = NACL_sys_mutex_create [enter][syscall_depth = %d]\n", nap->cage_id, nacl_syscall_trace_level_counter);
  printf("==> NACL_sys_mutex_create(");
#if 0
  for (i = 0; i < sizeof(p)/4; i++) {
    printf("%x,", *((uint32_t *)&p+i));
  }
#endif
  printf(")\n");
  nacl_syscall_trace_level_counter++;
  retval = NaClSysMutexCreate(natp);
  nacl_syscall_trace_level_counter--;
  printf("[NaClSysCallInterface] cage id = %d, syscall_num = NACL_sys_mutex_create [exit][syscall_depth = %d] \n", nap->cage_id, nacl_syscall_trace_level_counter);
  return retval;
  #endif

  return NaClSysMutexCreate(natp);

}

/*
 * Check that the function being wrapped has the same type as the type
 * declared in SYSCALL_LIST.
 */
static INLINE void AssertSameType_NaClSysMutexCreate(void) {
  /* This assignment will give an error if the argument types don't match. */
  int32_t (*dummy)(struct NaClAppThread *natp) = NaClSysMutexCreate;
  /* 'dummy' is not actually a parameter but this suppresses the warning. */
  UNREFERENCED_PARAMETER(dummy);
}

/* this function was automagically generated */
static int32_t NaClSysMutexLockDecoder(struct NaClAppThread *natp) {
  #ifdef SYSCALL_TIMING
  int32_t retval;
  clock_t nacl_sys_begin;
  clock_t nacl_sys_finish;
  #endif
  #ifdef NACL_SYSCALL_TRACE_ENABLED
  struct NaClApp *nap = natp->nap;
  int32_t retval;
#if 1
  unsigned int i = 0;
#endif
  #endif
    struct NaClSysMutexLockArgs {
    uint32_t mutex_handle;
  } p;
  if (!NaClCopyInFromUserAndDropLock(natp->nap, &p, natp->usr_syscall_args,
                                     sizeof p)) {
    return -NACL_ABI_EFAULT;
  }


  #ifdef SYSCALL_TIMING
  nacl_syscall_counter++;
  nacl_syscall_invoked_times[NACL_sys_mutex_lock]++;
  nacl_sys_begin = clock();
  retval = NaClSysMutexLock(natp, (int32_t)  p.mutex_handle);
  nacl_sys_finish = clock();
  nacl_syscall_execution_time[NACL_sys_mutex_lock] += (double)(nacl_sys_finish - nacl_sys_begin) / CLOCKS_PER_SEC;
  return retval;
  #endif
  #ifdef NACL_SYSCALL_TRACE_ENABLED
  printf("[NaClSysCallInterface] cage id = %d, syscall_num = NACL_sys_mutex_lock [enter][syscall_depth = %d]\n", nap->cage_id, nacl_syscall_trace_level_counter);
  printf("==> NACL_sys_mutex_lock(");
#if 1
  for (i = 0; i < sizeof(p)/4; i++) {
    printf("%x,", *((uint32_t *)&p+i));
  }
#endif
  printf(")\n");
  nacl_syscall_trace_level_counter++;
  retval = NaClSysMutexLock(natp, (int32_t)  p.mutex_handle);
  nacl_syscall_trace_level_counter--;
  printf("[NaClSysCallInterface] cage id = %d, syscall_num = NACL_sys_mutex_lock [exit][syscall_depth = %d] \n", nap->cage_id, nacl_syscall_trace_level_counter);
  return retval;
  #endif

  return NaClSysMutexLock(natp, (int32_t)  p.mutex_handle);

}

/*
 * Check that the function being wrapped has the same type as the type
 * declared in SYSCALL_LIST.
 */
static INLINE void AssertSameType_NaClSysMutexLock(void) {
  /* This assignment will give an error if the argument types don't match. */
  int32_t (*dummy)(struct NaClAppThread *natp, int32_t mutex_handle) = NaClSysMutexLock;
  /* 'dummy' is not actually a parameter but this suppresses the warning. */
  UNREFERENCED_PARAMETER(dummy);
}

/* this function was automagically generated */
static int32_t NaClSysMutexUnlockDecoder(struct NaClAppThread *natp) {
  #ifdef SYSCALL_TIMING
  int32_t retval;
  clock_t nacl_sys_begin;
  clock_t nacl_sys_finish;
  #endif
  #ifdef NACL_SYSCALL_TRACE_ENABLED
  struct NaClApp *nap = natp->nap;
  int32_t retval;
#if 1
  unsigned int i = 0;
#endif
  #endif
    struct NaClSysMutexUnlockArgs {
    uint32_t mutex_handle;
  } p;
  if (!NaClCopyInFromUserAndDropLock(natp->nap, &p, natp->usr_syscall_args,
                                     sizeof p)) {
    return -NACL_ABI_EFAULT;
  }


  #ifdef SYSCALL_TIMING
  nacl_syscall_counter++;
  nacl_syscall_invoked_times[NACL_sys_mutex_unlock]++;
  nacl_sys_begin = clock();
  retval = NaClSysMutexUnlock(natp, (int32_t)  p.mutex_handle);
  nacl_sys_finish = clock();
  nacl_syscall_execution_time[NACL_sys_mutex_unlock] += (double)(nacl_sys_finish - nacl_sys_begin) / CLOCKS_PER_SEC;
  return retval;
  #endif
  #ifdef NACL_SYSCALL_TRACE_ENABLED
  printf("[NaClSysCallInterface] cage id = %d, syscall_num = NACL_sys_mutex_unlock [enter][syscall_depth = %d]\n", nap->cage_id, nacl_syscall_trace_level_counter);
  printf("==> NACL_sys_mutex_unlock(");
#if 1
  for (i = 0; i < sizeof(p)/4; i++) {
    printf("%x,", *((uint32_t *)&p+i));
  }
#endif
  printf(")\n");
  nacl_syscall_trace_level_counter++;
  retval = NaClSysMutexUnlock(natp, (int32_t)  p.mutex_handle);
  nacl_syscall_trace_level_counter--;
  printf("[NaClSysCallInterface] cage id = %d, syscall_num = NACL_sys_mutex_unlock [exit][syscall_depth = %d] \n", nap->cage_id, nacl_syscall_trace_level_counter);
  return retval;
  #endif

  return NaClSysMutexUnlock(natp, (int32_t)  p.mutex_handle);

}

/*
 * Check that the function being wrapped has the same type as the type
 * declared in SYSCALL_LIST.
 */
static INLINE void AssertSameType_NaClSysMutexUnlock(void) {
  /* This assignment will give an error if the argument types don't match. */
  int32_t (*dummy)(struct NaClAppThread *natp, int32_t mutex_handle) = NaClSysMutexUnlock;
  /* 'dummy' is not actually a parameter but this suppresses the warning. */
  UNREFERENCED_PARAMETER(dummy);
}

/* this function was automagically generated */
static int32_t NaClSysMutexTrylockDecoder(struct NaClAppThread *natp) {
  #ifdef SYSCALL_TIMING
  int32_t retval;
  clock_t nacl_sys_begin;
  clock_t nacl_sys_finish;
  #endif
  #ifdef NACL_SYSCALL_TRACE_ENABLED
  struct NaClApp *nap = natp->nap;
  int32_t retval;
#if 1
  unsigned int i = 0;
#endif
  #endif
    struct NaClSysMutexTrylockArgs {
    uint32_t mutex_handle;
  } p;
  if (!NaClCopyInFromUserAndDropLock(natp->nap, &p, natp->usr_syscall_args,
                                     sizeof p)) {
    return -NACL_ABI_EFAULT;
  }


  #ifdef SYSCALL_TIMING
  nacl_syscall_counter++;
  nacl_syscall_invoked_times[NACL_sys_mutex_trylock]++;
  nacl_sys_begin = clock();
  retval = NaClSysMutexTrylock(natp, (int32_t)  p.mutex_handle);
  nacl_sys_finish = clock();
  nacl_syscall_execution_time[NACL_sys_mutex_trylock] += (double)(nacl_sys_finish - nacl_sys_begin) / CLOCKS_PER_SEC;
  return retval;
  #endif
  #ifdef NACL_SYSCALL_TRACE_ENABLED
  printf("[NaClSysCallInterface] cage id = %d, syscall_num = NACL_sys_mutex_trylock [enter][syscall_depth = %d]\n", nap->cage_id, nacl_syscall_trace_level_counter);
  printf("==> NACL_sys_mutex_trylock(");
#if 1
  for (i = 0; i < sizeof(p)/4; i++) {
    printf("%x,", *((uint32_t *)&p+i));
  }
#endif
  printf(")\n");
  nacl_syscall_trace_level_counter++;
  retval = NaClSysMutexTrylock(natp, (int32_t)  p.mutex_handle);
  nacl_syscall_trace_level_counter--;
  printf("[NaClSysCallInterface] cage id = %d, syscall_num = NACL_sys_mutex_trylock [exit][syscall_depth = %d] \n", nap->cage_id, nacl_syscall_trace_level_counter);
  return retval;
  #endif

  return NaClSysMutexTrylock(natp, (int32_t)  p.mutex_handle);

}

/*
 * Check that the function being wrapped has the same type as the type
 * declared in SYSCALL_LIST.
 */
static INLINE void AssertSameType_NaClSysMutexTrylock(void) {
  /* This assignment will give an error if the argument types don't match. */
  int32_t (*dummy)(struct NaClAppThread *natp, int32_t mutex_handle) = NaClSysMutexTrylock;
  /* 'dummy' is not actually a parameter but this suppresses the warning. */
  UNREFERENCED_PARAMETER(dummy);
}

/* this function was automagically generated */
static int32_t NaClSysCondCreateDecoder(struct NaClAppThread *natp) {
  #ifdef SYSCALL_TIMING
  int32_t retval;
  clock_t nacl_sys_begin;
  clock_t nacl_sys_finish;
  #endif
  #ifdef NACL_SYSCALL_TRACE_ENABLED
  struct NaClApp *nap = natp->nap;
  int32_t retval;
#if 0
  unsigned int i = 0;
#endif
  #endif
    NaClCopyDropLock(natp->nap);
  #ifdef SYSCALL_TIMING
  nacl_syscall_counter++;
  nacl_syscall_invoked_times[NACL_sys_cond_create]++;
  nacl_sys_begin = clock();
  retval = NaClSysCondCreate(natp);
  nacl_sys_finish = clock();
  nacl_syscall_execution_time[NACL_sys_cond_create] += (double)(nacl_sys_finish - nacl_sys_begin) / CLOCKS_PER_SEC;
  return retval;
  #endif
  #ifdef NACL_SYSCALL_TRACE_ENABLED
  printf("[NaClSysCallInterface] cage id = %d, syscall_num = NACL_sys_cond_create [enter][syscall_depth = %d]\n", nap->cage_id, nacl_syscall_trace_level_counter);
  printf("==> NACL_sys_cond_create(");
#if 0
  for (i = 0; i < sizeof(p)/4; i++) {
    printf("%x,", *((uint32_t *)&p+i));
  }
#endif
  printf(")\n");
  nacl_syscall_trace_level_counter++;
  retval = NaClSysCondCreate(natp);
  nacl_syscall_trace_level_counter--;
  printf("[NaClSysCallInterface] cage id = %d, syscall_num = NACL_sys_cond_create [exit][syscall_depth = %d] \n", nap->cage_id, nacl_syscall_trace_level_counter);
  return retval;
  #endif

  return NaClSysCondCreate(natp);

}

/*
 * Check that the function being wrapped has the same type as the type
 * declared in SYSCALL_LIST.
 */
static INLINE void AssertSameType_NaClSysCondCreate(void) {
  /* This assignment will give an error if the argument types don't match. */
  int32_t (*dummy)(struct NaClAppThread *natp) = NaClSysCondCreate;
  /* 'dummy' is not actually a parameter but this suppresses the warning. */
  UNREFERENCED_PARAMETER(dummy);
}

/* this function was automagically generated */
static int32_t NaClSysCondWaitDecoder(struct NaClAppThread *natp) {
  #ifdef SYSCALL_TIMING
  int32_t retval;
  clock_t nacl_sys_begin;
  clock_t nacl_sys_finish;
  #endif
  #ifdef NACL_SYSCALL_TRACE_ENABLED
  struct NaClApp *nap = natp->nap;
  int32_t retval;
#if 1
  unsigned int i = 0;
#endif
  #endif
    struct NaClSysCondWaitArgs {
    uint32_t cond_handle;
    uint32_t mutex_handle;
  } p;
  if (!NaClCopyInFromUserAndDropLock(natp->nap, &p, natp->usr_syscall_args,
                                     sizeof p)) {
    return -NACL_ABI_EFAULT;
  }


  #ifdef SYSCALL_TIMING
  nacl_syscall_counter++;
  nacl_syscall_invoked_times[NACL_sys_cond_wait]++;
  nacl_sys_begin = clock();
  retval = NaClSysCondWait(natp, (int32_t)  p.cond_handle, (int32_t)  p.mutex_handle);
  nacl_sys_finish = clock();
  nacl_syscall_execution_time[NACL_sys_cond_wait] += (double)(nacl_sys_finish - nacl_sys_begin) / CLOCKS_PER_SEC;
  return retval;
  #endif
  #ifdef NACL_SYSCALL_TRACE_ENABLED
  printf("[NaClSysCallInterface] cage id = %d, syscall_num = NACL_sys_cond_wait [enter][syscall_depth = %d]\n", nap->cage_id, nacl_syscall_trace_level_counter);
  printf("==> NACL_sys_cond_wait(");
#if 1
  for (i = 0; i < sizeof(p)/4; i++) {
    printf("%x,", *((uint32_t *)&p+i));
  }
#endif
  printf(")\n");
  nacl_syscall_trace_level_counter++;
  retval = NaClSysCondWait(natp, (int32_t)  p.cond_handle, (int32_t)  p.mutex_handle);
  nacl_syscall_trace_level_counter--;
  printf("[NaClSysCallInterface] cage id = %d, syscall_num = NACL_sys_cond_wait [exit][syscall_depth = %d] \n", nap->cage_id, nacl_syscall_trace_level_counter);
  return retval;
  #endif

  return NaClSysCondWait(natp, (int32_t)  p.cond_handle, (int32_t)  p.mutex_handle);

}

/*
 * Check that the function being wrapped has the same type as the type
 * declared in SYSCALL_LIST.
 */
static INLINE void AssertSameType_NaClSysCondWait(void) {
  /* This assignment will give an error if the argument types don't match. */
  int32_t (*dummy)(struct NaClAppThread *natp, int32_t cond_handle, int32_t mutex_handle) = NaClSysCondWait;
  /* 'dummy' is not actually a parameter but this suppresses the warning. */
  UNREFERENCED_PARAMETER(dummy);
}

/* this function was automagically generated */
static int32_t NaClSysCondSignalDecoder(struct NaClAppThread *natp) {
  #ifdef SYSCALL_TIMING
  int32_t retval;
  clock_t nacl_sys_begin;
  clock_t nacl_sys_finish;
  #endif
  #ifdef NACL_SYSCALL_TRACE_ENABLED
  struct NaClApp *nap = natp->nap;
  int32_t retval;
#if 1
  unsigned int i = 0;
#endif
  #endif
    struct NaClSysCondSignalArgs {
    uint32_t cond_handle;
  } p;
  if (!NaClCopyInFromUserAndDropLock(natp->nap, &p, natp->usr_syscall_args,
                                     sizeof p)) {
    return -NACL_ABI_EFAULT;
  }


  #ifdef SYSCALL_TIMING
  nacl_syscall_counter++;
  nacl_syscall_invoked_times[NACL_sys_cond_signal]++;
  nacl_sys_begin = clock();
  retval = NaClSysCondSignal(natp, (int32_t)  p.cond_handle);
  nacl_sys_finish = clock();
  nacl_syscall_execution_time[NACL_sys_cond_signal] += (double)(nacl_sys_finish - nacl_sys_begin) / CLOCKS_PER_SEC;
  return retval;
  #endif
  #ifdef NACL_SYSCALL_TRACE_ENABLED
  printf("[NaClSysCallInterface] cage id = %d, syscall_num = NACL_sys_cond_signal [enter][syscall_depth = %d]\n", nap->cage_id, nacl_syscall_trace_level_counter);
  printf("==> NACL_sys_cond_signal(");
#if 1
  for (i = 0; i < sizeof(p)/4; i++) {
    printf("%x,", *((uint32_t *)&p+i));
  }
#endif
  printf(")\n");
  nacl_syscall_trace_level_counter++;
  retval = NaClSysCondSignal(natp, (int32_t)  p.cond_handle);
  nacl_syscall_trace_level_counter--;
  printf("[NaClSysCallInterface] cage id = %d, syscall_num = NACL_sys_cond_signal [exit][syscall_depth = %d] \n", nap->cage_id, nacl_syscall_trace_level_counter);
  return retval;
  #endif

  return NaClSysCondSignal(natp, (int32_t)  p.cond_handle);

}

/*
 * Check that the function being wrapped has the same type as the type
 * declared in SYSCALL_LIST.
 */
static INLINE void AssertSameType_NaClSysCondSignal(void) {
  /* This assignment will give an error if the argument types don't match. */
  int32_t (*dummy)(struct NaClAppThread *natp, int32_t cond_handle) = NaClSysCondSignal;
  /* 'dummy' is not actually a parameter but this suppresses the warning. */
  UNREFERENCED_PARAMETER(dummy);
}

/* this function was automagically generated */
static int32_t NaClSysCondBroadcastDecoder(struct NaClAppThread *natp) {
  #ifdef SYSCALL_TIMING
  int32_t retval;
  clock_t nacl_sys_begin;
  clock_t nacl_sys_finish;
  #endif
  #ifdef NACL_SYSCALL_TRACE_ENABLED
  struct NaClApp *nap = natp->nap;
  int32_t retval;
#if 1
  unsigned int i = 0;
#endif
  #endif
    struct NaClSysCondBroadcastArgs {
    uint32_t cond_handle;
  } p;
  if (!NaClCopyInFromUserAndDropLock(natp->nap, &p, natp->usr_syscall_args,
                                     sizeof p)) {
    return -NACL_ABI_EFAULT;
  }


  #ifdef SYSCALL_TIMING
  nacl_syscall_counter++;
  nacl_syscall_invoked_times[NACL_sys_cond_broadcast]++;
  nacl_sys_begin = clock();
  retval = NaClSysCondBroadcast(natp, (int32_t)  p.cond_handle);
  nacl_sys_finish = clock();
  nacl_syscall_execution_time[NACL_sys_cond_broadcast] += (double)(nacl_sys_finish - nacl_sys_begin) / CLOCKS_PER_SEC;
  return retval;
  #endif
  #ifdef NACL_SYSCALL_TRACE_ENABLED
  printf("[NaClSysCallInterface] cage id = %d, syscall_num = NACL_sys_cond_broadcast [enter][syscall_depth = %d]\n", nap->cage_id, nacl_syscall_trace_level_counter);
  printf("==> NACL_sys_cond_broadcast(");
#if 1
  for (i = 0; i < sizeof(p)/4; i++) {
    printf("%x,", *((uint32_t *)&p+i));
  }
#endif
  printf(")\n");
  nacl_syscall_trace_level_counter++;
  retval = NaClSysCondBroadcast(natp, (int32_t)  p.cond_handle);
  nacl_syscall_trace_level_counter--;
  printf("[NaClSysCallInterface] cage id = %d, syscall_num = NACL_sys_cond_broadcast [exit][syscall_depth = %d] \n", nap->cage_id, nacl_syscall_trace_level_counter);
  return retval;
  #endif

  return NaClSysCondBroadcast(natp, (int32_t)  p.cond_handle);

}

/*
 * Check that the function being wrapped has the same type as the type
 * declared in SYSCALL_LIST.
 */
static INLINE void AssertSameType_NaClSysCondBroadcast(void) {
  /* This assignment will give an error if the argument types don't match. */
  int32_t (*dummy)(struct NaClAppThread *natp, int32_t cond_handle) = NaClSysCondBroadcast;
  /* 'dummy' is not actually a parameter but this suppresses the warning. */
  UNREFERENCED_PARAMETER(dummy);
}

/* this function was automagically generated */
static int32_t NaClSysCondTimedWaitAbsDecoder(struct NaClAppThread *natp) {
  #ifdef SYSCALL_TIMING
  int32_t retval;
  clock_t nacl_sys_begin;
  clock_t nacl_sys_finish;
  #endif
  #ifdef NACL_SYSCALL_TRACE_ENABLED
  struct NaClApp *nap = natp->nap;
  int32_t retval;
#if 1
  unsigned int i = 0;
#endif
  #endif
    struct NaClSysCondTimedWaitAbsArgs {
    uint32_t cond_handle;
    uint32_t mutex_handle;
    uint32_t ts;
  } p;
  if (!NaClCopyInFromUserAndDropLock(natp->nap, &p, natp->usr_syscall_args,
                                     sizeof p)) {
    return -NACL_ABI_EFAULT;
  }


  #ifdef SYSCALL_TIMING
  nacl_syscall_counter++;
  nacl_syscall_invoked_times[NACL_sys_cond_timed_wait_abs]++;
  nacl_sys_begin = clock();
  retval = NaClSysCondTimedWaitAbs(natp, (int32_t)  p.cond_handle, (int32_t)  p.mutex_handle, (struct nacl_abi_timespec *) (uintptr_t) p.ts);
  nacl_sys_finish = clock();
  nacl_syscall_execution_time[NACL_sys_cond_timed_wait_abs] += (double)(nacl_sys_finish - nacl_sys_begin) / CLOCKS_PER_SEC;
  return retval;
  #endif
  #ifdef NACL_SYSCALL_TRACE_ENABLED
  printf("[NaClSysCallInterface] cage id = %d, syscall_num = NACL_sys_cond_timed_wait_abs [enter][syscall_depth = %d]\n", nap->cage_id, nacl_syscall_trace_level_counter);
  printf("==> NACL_sys_cond_timed_wait_abs(");
#if 1
  for (i = 0; i < sizeof(p)/4; i++) {
    printf("%x,", *((uint32_t *)&p+i));
  }
#endif
  printf(")\n");
  nacl_syscall_trace_level_counter++;
  retval = NaClSysCondTimedWaitAbs(natp, (int32_t)  p.cond_handle, (int32_t)  p.mutex_handle, (struct nacl_abi_timespec *) (uintptr_t) p.ts);
  nacl_syscall_trace_level_counter--;
  printf("[NaClSysCallInterface] cage id = %d, syscall_num = NACL_sys_cond_timed_wait_abs [exit][syscall_depth = %d] \n", nap->cage_id, nacl_syscall_trace_level_counter);
  return retval;
  #endif

  return NaClSysCondTimedWaitAbs(natp, (int32_t)  p.cond_handle, (int32_t)  p.mutex_handle, (struct nacl_abi_timespec *) (uintptr_t) p.ts);

}

/*
 * Check that the function being wrapped has the same type as the type
 * declared in SYSCALL_LIST.
 */
static INLINE void AssertSameType_NaClSysCondTimedWaitAbs(void) {
  /* This assignment will give an error if the argument types don't match. */
  int32_t (*dummy)(struct NaClAppThread *natp, int32_t cond_handle, int32_t mutex_handle, struct nacl_abi_timespec *ts) = NaClSysCondTimedWaitAbs;
  /* 'dummy' is not actually a parameter but this suppresses the warning. */
  UNREFERENCED_PARAMETER(dummy);
}

/* this function was automagically generated */
static int32_t NaClSysImcSocketPairDecoder(struct NaClAppThread *natp) {
  #ifdef SYSCALL_TIMING
  int32_t retval;
  clock_t nacl_sys_begin;
  clock_t nacl_sys_finish;
  #endif
  #ifdef NACL_SYSCALL_TRACE_ENABLED
  struct NaClApp *nap = natp->nap;
  int32_t retval;
#if 1
  unsigned int i = 0;
#endif
  #endif
    struct NaClSysImcSocketPairArgs {
    uint32_t descs_out;
  } p;
  if (!NaClCopyInFromUserAndDropLock(natp->nap, &p, natp->usr_syscall_args,
                                     sizeof p)) {
    return -NACL_ABI_EFAULT;
  }


  #ifdef SYSCALL_TIMING
  nacl_syscall_counter++;
  nacl_syscall_invoked_times[NACL_sys_imc_socketpair]++;
  nacl_sys_begin = clock();
  retval = NaClSysImcSocketPair(natp, (uint32_t)  p.descs_out);
  nacl_sys_finish = clock();
  nacl_syscall_execution_time[NACL_sys_imc_socketpair] += (double)(nacl_sys_finish - nacl_sys_begin) / CLOCKS_PER_SEC;
  return retval;
  #endif
  #ifdef NACL_SYSCALL_TRACE_ENABLED
  printf("[NaClSysCallInterface] cage id = %d, syscall_num = NACL_sys_imc_socketpair [enter][syscall_depth = %d]\n", nap->cage_id, nacl_syscall_trace_level_counter);
  printf("==> NACL_sys_imc_socketpair(");
#if 1
  for (i = 0; i < sizeof(p)/4; i++) {
    printf("%x,", *((uint32_t *)&p+i));
  }
#endif
  printf(")\n");
  nacl_syscall_trace_level_counter++;
  retval = NaClSysImcSocketPair(natp, (uint32_t)  p.descs_out);
  nacl_syscall_trace_level_counter--;
  printf("[NaClSysCallInterface] cage id = %d, syscall_num = NACL_sys_imc_socketpair [exit][syscall_depth = %d] \n", nap->cage_id, nacl_syscall_trace_level_counter);
  return retval;
  #endif

  return NaClSysImcSocketPair(natp, (uint32_t)  p.descs_out);

}

/*
 * Check that the function being wrapped has the same type as the type
 * declared in SYSCALL_LIST.
 */
static INLINE void AssertSameType_NaClSysImcSocketPair(void) {
  /* This assignment will give an error if the argument types don't match. */
  int32_t (*dummy)(struct NaClAppThread *natp, uint32_t descs_out) = NaClSysImcSocketPair;
  /* 'dummy' is not actually a parameter but this suppresses the warning. */
  UNREFERENCED_PARAMETER(dummy);
}

/* this function was automagically generated */
static int32_t NaClSysSemCreateDecoder(struct NaClAppThread *natp) {
  #ifdef SYSCALL_TIMING
  int32_t retval;
  clock_t nacl_sys_begin;
  clock_t nacl_sys_finish;
  #endif
  #ifdef NACL_SYSCALL_TRACE_ENABLED
  struct NaClApp *nap = natp->nap;
  int32_t retval;
#if 1
  unsigned int i = 0;
#endif
  #endif
    struct NaClSysSemCreateArgs {
    uint32_t init_value;
  } p;
  if (!NaClCopyInFromUserAndDropLock(natp->nap, &p, natp->usr_syscall_args,
                                     sizeof p)) {
    return -NACL_ABI_EFAULT;
  }


  #ifdef SYSCALL_TIMING
  nacl_syscall_counter++;
  nacl_syscall_invoked_times[NACL_sys_sem_create]++;
  nacl_sys_begin = clock();
  retval = NaClSysSemCreate(natp, (int32_t)  p.init_value);
  nacl_sys_finish = clock();
  nacl_syscall_execution_time[NACL_sys_sem_create] += (double)(nacl_sys_finish - nacl_sys_begin) / CLOCKS_PER_SEC;
  return retval;
  #endif
  #ifdef NACL_SYSCALL_TRACE_ENABLED
  printf("[NaClSysCallInterface] cage id = %d, syscall_num = NACL_sys_sem_create [enter][syscall_depth = %d]\n", nap->cage_id, nacl_syscall_trace_level_counter);
  printf("==> NACL_sys_sem_create(");
#if 1
  for (i = 0; i < sizeof(p)/4; i++) {
    printf("%x,", *((uint32_t *)&p+i));
  }
#endif
  printf(")\n");
  nacl_syscall_trace_level_counter++;
  retval = NaClSysSemCreate(natp, (int32_t)  p.init_value);
  nacl_syscall_trace_level_counter--;
  printf("[NaClSysCallInterface] cage id = %d, syscall_num = NACL_sys_sem_create [exit][syscall_depth = %d] \n", nap->cage_id, nacl_syscall_trace_level_counter);
  return retval;
  #endif

  return NaClSysSemCreate(natp, (int32_t)  p.init_value);

}

/*
 * Check that the function being wrapped has the same type as the type
 * declared in SYSCALL_LIST.
 */
static INLINE void AssertSameType_NaClSysSemCreate(void) {
  /* This assignment will give an error if the argument types don't match. */
  int32_t (*dummy)(struct NaClAppThread *natp, int32_t init_value) = NaClSysSemCreate;
  /* 'dummy' is not actually a parameter but this suppresses the warning. */
  UNREFERENCED_PARAMETER(dummy);
}

/* this function was automagically generated */
static int32_t NaClSysSemWaitDecoder(struct NaClAppThread *natp) {
  #ifdef SYSCALL_TIMING
  int32_t retval;
  clock_t nacl_sys_begin;
  clock_t nacl_sys_finish;
  #endif
  #ifdef NACL_SYSCALL_TRACE_ENABLED
  struct NaClApp *nap = natp->nap;
  int32_t retval;
#if 1
  unsigned int i = 0;
#endif
  #endif
    struct NaClSysSemWaitArgs {
    uint32_t sem_handle;
  } p;
  if (!NaClCopyInFromUserAndDropLock(natp->nap, &p, natp->usr_syscall_args,
                                     sizeof p)) {
    return -NACL_ABI_EFAULT;
  }


  #ifdef SYSCALL_TIMING
  nacl_syscall_counter++;
  nacl_syscall_invoked_times[NACL_sys_sem_wait]++;
  nacl_sys_begin = clock();
  retval = NaClSysSemWait(natp, (int32_t)  p.sem_handle);
  nacl_sys_finish = clock();
  nacl_syscall_execution_time[NACL_sys_sem_wait] += (double)(nacl_sys_finish - nacl_sys_begin) / CLOCKS_PER_SEC;
  return retval;
  #endif
  #ifdef NACL_SYSCALL_TRACE_ENABLED
  printf("[NaClSysCallInterface] cage id = %d, syscall_num = NACL_sys_sem_wait [enter][syscall_depth = %d]\n", nap->cage_id, nacl_syscall_trace_level_counter);
  printf("==> NACL_sys_sem_wait(");
#if 1
  for (i = 0; i < sizeof(p)/4; i++) {
    printf("%x,", *((uint32_t *)&p+i));
  }
#endif
  printf(")\n");
  nacl_syscall_trace_level_counter++;
  retval = NaClSysSemWait(natp, (int32_t)  p.sem_handle);
  nacl_syscall_trace_level_counter--;
  printf("[NaClSysCallInterface] cage id = %d, syscall_num = NACL_sys_sem_wait [exit][syscall_depth = %d] \n", nap->cage_id, nacl_syscall_trace_level_counter);
  return retval;
  #endif

  return NaClSysSemWait(natp, (int32_t)  p.sem_handle);

}

/*
 * Check that the function being wrapped has the same type as the type
 * declared in SYSCALL_LIST.
 */
static INLINE void AssertSameType_NaClSysSemWait(void) {
  /* This assignment will give an error if the argument types don't match. */
  int32_t (*dummy)(struct NaClAppThread *natp, int32_t sem_handle) = NaClSysSemWait;
  /* 'dummy' is not actually a parameter but this suppresses the warning. */
  UNREFERENCED_PARAMETER(dummy);
}

/* this function was automagically generated */
static int32_t NaClSysSemPostDecoder(struct NaClAppThread *natp) {
  #ifdef SYSCALL_TIMING
  int32_t retval;
  clock_t nacl_sys_begin;
  clock_t nacl_sys_finish;
  #endif
  #ifdef NACL_SYSCALL_TRACE_ENABLED
  struct NaClApp *nap = natp->nap;
  int32_t retval;
#if 1
  unsigned int i = 0;
#endif
  #endif
    struct NaClSysSemPostArgs {
    uint32_t sem_handle;
  } p;
  if (!NaClCopyInFromUserAndDropLock(natp->nap, &p, natp->usr_syscall_args,
                                     sizeof p)) {
    return -NACL_ABI_EFAULT;
  }


  #ifdef SYSCALL_TIMING
  nacl_syscall_counter++;
  nacl_syscall_invoked_times[NACL_sys_sem_post]++;
  nacl_sys_begin = clock();
  retval = NaClSysSemPost(natp, (int32_t)  p.sem_handle);
  nacl_sys_finish = clock();
  nacl_syscall_execution_time[NACL_sys_sem_post] += (double)(nacl_sys_finish - nacl_sys_begin) / CLOCKS_PER_SEC;
  return retval;
  #endif
  #ifdef NACL_SYSCALL_TRACE_ENABLED
  printf("[NaClSysCallInterface] cage id = %d, syscall_num = NACL_sys_sem_post [enter][syscall_depth = %d]\n", nap->cage_id, nacl_syscall_trace_level_counter);
  printf("==> NACL_sys_sem_post(");
#if 1
  for (i = 0; i < sizeof(p)/4; i++) {
    printf("%x,", *((uint32_t *)&p+i));
  }
#endif
  printf(")\n");
  nacl_syscall_trace_level_counter++;
  retval = NaClSysSemPost(natp, (int32_t)  p.sem_handle);
  nacl_syscall_trace_level_counter--;
  printf("[NaClSysCallInterface] cage id = %d, syscall_num = NACL_sys_sem_post [exit][syscall_depth = %d] \n", nap->cage_id, nacl_syscall_trace_level_counter);
  return retval;
  #endif

  return NaClSysSemPost(natp, (int32_t)  p.sem_handle);

}

/*
 * Check that the function being wrapped has the same type as the type
 * declared in SYSCALL_LIST.
 */
static INLINE void AssertSameType_NaClSysSemPost(void) {
  /* This assignment will give an error if the argument types don't match. */
  int32_t (*dummy)(struct NaClAppThread *natp, int32_t sem_handle) = NaClSysSemPost;
  /* 'dummy' is not actually a parameter but this suppresses the warning. */
  UNREFERENCED_PARAMETER(dummy);
}

/* this function was automagically generated */
static int32_t NaClSysSemGetValueDecoder(struct NaClAppThread *natp) {
  #ifdef SYSCALL_TIMING
  int32_t retval;
  clock_t nacl_sys_begin;
  clock_t nacl_sys_finish;
  #endif
  #ifdef NACL_SYSCALL_TRACE_ENABLED
  struct NaClApp *nap = natp->nap;
  int32_t retval;
#if 1
  unsigned int i = 0;
#endif
  #endif
    struct NaClSysSemGetValueArgs {
    uint32_t sem_handle;
  } p;
  if (!NaClCopyInFromUserAndDropLock(natp->nap, &p, natp->usr_syscall_args,
                                     sizeof p)) {
    return -NACL_ABI_EFAULT;
  }


  #ifdef SYSCALL_TIMING
  nacl_syscall_counter++;
  nacl_syscall_invoked_times[NACL_sys_sem_get_value]++;
  nacl_sys_begin = clock();
  retval = NaClSysSemGetValue(natp, (int32_t)  p.sem_handle);
  nacl_sys_finish = clock();
  nacl_syscall_execution_time[NACL_sys_sem_get_value] += (double)(nacl_sys_finish - nacl_sys_begin) / CLOCKS_PER_SEC;
  return retval;
  #endif
  #ifdef NACL_SYSCALL_TRACE_ENABLED
  printf("[NaClSysCallInterface] cage id = %d, syscall_num = NACL_sys_sem_get_value [enter][syscall_depth = %d]\n", nap->cage_id, nacl_syscall_trace_level_counter);
  printf("==> NACL_sys_sem_get_value(");
#if 1
  for (i = 0; i < sizeof(p)/4; i++) {
    printf("%x,", *((uint32_t *)&p+i));
  }
#endif
  printf(")\n");
  nacl_syscall_trace_level_counter++;
  retval = NaClSysSemGetValue(natp, (int32_t)  p.sem_handle);
  nacl_syscall_trace_level_counter--;
  printf("[NaClSysCallInterface] cage id = %d, syscall_num = NACL_sys_sem_get_value [exit][syscall_depth = %d] \n", nap->cage_id, nacl_syscall_trace_level_counter);
  return retval;
  #endif

  return NaClSysSemGetValue(natp, (int32_t)  p.sem_handle);

}

/*
 * Check that the function being wrapped has the same type as the type
 * declared in SYSCALL_LIST.
 */
static INLINE void AssertSameType_NaClSysSemGetValue(void) {
  /* This assignment will give an error if the argument types don't match. */
  int32_t (*dummy)(struct NaClAppThread *natp, int32_t sem_handle) = NaClSysSemGetValue;
  /* 'dummy' is not actually a parameter but this suppresses the warning. */
  UNREFERENCED_PARAMETER(dummy);
}

/* this function was automagically generated */
static int32_t NaClSysSchedYieldDecoder(struct NaClAppThread *natp) {
  #ifdef SYSCALL_TIMING
  int32_t retval;
  clock_t nacl_sys_begin;
  clock_t nacl_sys_finish;
  #endif
  #ifdef NACL_SYSCALL_TRACE_ENABLED
  struct NaClApp *nap = natp->nap;
  int32_t retval;
#if 0
  unsigned int i = 0;
#endif
  #endif
    NaClCopyDropLock(natp->nap);
  #ifdef SYSCALL_TIMING
  nacl_syscall_counter++;
  nacl_syscall_invoked_times[NACL_sys_sched_yield]++;
  nacl_sys_begin = clock();
  retval = NaClSysSchedYield(natp);
  nacl_sys_finish = clock();
  nacl_syscall_execution_time[NACL_sys_sched_yield] += (double)(nacl_sys_finish - nacl_sys_begin) / CLOCKS_PER_SEC;
  return retval;
  #endif
  #ifdef NACL_SYSCALL_TRACE_ENABLED
  printf("[NaClSysCallInterface] cage id = %d, syscall_num = NACL_sys_sched_yield [enter][syscall_depth = %d]\n", nap->cage_id, nacl_syscall_trace_level_counter);
  printf("==> NACL_sys_sched_yield(");
#if 0
  for (i = 0; i < sizeof(p)/4; i++) {
    printf("%x,", *((uint32_t *)&p+i));
  }
#endif
  printf(")\n");
  nacl_syscall_trace_level_counter++;
  retval = NaClSysSchedYield(natp);
  nacl_syscall_trace_level_counter--;
  printf("[NaClSysCallInterface] cage id = %d, syscall_num = NACL_sys_sched_yield [exit][syscall_depth = %d] \n", nap->cage_id, nacl_syscall_trace_level_counter);
  return retval;
  #endif

  return NaClSysSchedYield(natp);

}

/*
 * Check that the function being wrapped has the same type as the type
 * declared in SYSCALL_LIST.
 */
static INLINE void AssertSameType_NaClSysSchedYield(void) {
  /* This assignment will give an error if the argument types don't match. */
  int32_t (*dummy)(struct NaClAppThread *natp) = NaClSysSchedYield;
  /* 'dummy' is not actually a parameter but this suppresses the warning. */
  UNREFERENCED_PARAMETER(dummy);
}

/* this function was automagically generated */
static int32_t NaClSysSysconfDecoder(struct NaClAppThread *natp) {
  #ifdef SYSCALL_TIMING
  int32_t retval;
  clock_t nacl_sys_begin;
  clock_t nacl_sys_finish;
  #endif
  #ifdef NACL_SYSCALL_TRACE_ENABLED
  struct NaClApp *nap = natp->nap;
  int32_t retval;
#if 1
  unsigned int i = 0;
#endif
  #endif
    struct NaClSysSysconfArgs {
    uint32_t name;
    uint32_t result;
  } p;
  if (!NaClCopyInFromUserAndDropLock(natp->nap, &p, natp->usr_syscall_args,
                                     sizeof p)) {
    return -NACL_ABI_EFAULT;
  }


  #ifdef SYSCALL_TIMING
  nacl_syscall_counter++;
  nacl_syscall_invoked_times[NACL_sys_sysconf]++;
  nacl_sys_begin = clock();
  retval = NaClSysSysconf(natp, (int32_t)  p.name, (int32_t *) (uintptr_t) p.result);
  nacl_sys_finish = clock();
  nacl_syscall_execution_time[NACL_sys_sysconf] += (double)(nacl_sys_finish - nacl_sys_begin) / CLOCKS_PER_SEC;
  return retval;
  #endif
  #ifdef NACL_SYSCALL_TRACE_ENABLED
  printf("[NaClSysCallInterface] cage id = %d, syscall_num = NACL_sys_sysconf [enter][syscall_depth = %d]\n", nap->cage_id, nacl_syscall_trace_level_counter);
  printf("==> NACL_sys_sysconf(");
#if 1
  for (i = 0; i < sizeof(p)/4; i++) {
    printf("%x,", *((uint32_t *)&p+i));
  }
#endif
  printf(")\n");
  nacl_syscall_trace_level_counter++;
  retval = NaClSysSysconf(natp, (int32_t)  p.name, (int32_t *) (uintptr_t) p.result);
  nacl_syscall_trace_level_counter--;
  printf("[NaClSysCallInterface] cage id = %d, syscall_num = NACL_sys_sysconf [exit][syscall_depth = %d] \n", nap->cage_id, nacl_syscall_trace_level_counter);
  return retval;
  #endif

  return NaClSysSysconf(natp, (int32_t)  p.name, (int32_t *) (uintptr_t) p.result);

}

/*
 * Check that the function being wrapped has the same type as the type
 * declared in SYSCALL_LIST.
 */
static INLINE void AssertSameType_NaClSysSysconf(void) {
  /* This assignment will give an error if the argument types don't match. */
  int32_t (*dummy)(struct NaClAppThread *natp, int32_t name, int32_t *result) = NaClSysSysconf;
  /* 'dummy' is not actually a parameter but this suppresses the warning. */
  UNREFERENCED_PARAMETER(dummy);
}

/* this function was automagically generated */
static int32_t NaClSysDyncodeCreateDecoder(struct NaClAppThread *natp) {
  #ifdef SYSCALL_TIMING
  int32_t retval;
  clock_t nacl_sys_begin;
  clock_t nacl_sys_finish;
  #endif
  #ifdef NACL_SYSCALL_TRACE_ENABLED
  struct NaClApp *nap = natp->nap;
  int32_t retval;
#if 1
  unsigned int i = 0;
#endif
  #endif
    struct NaClSysDyncodeCreateArgs {
    uint32_t dest;
    uint32_t src;
    uint32_t size;
  } p;
  if (!NaClCopyInFromUserAndDropLock(natp->nap, &p, natp->usr_syscall_args,
                                     sizeof p)) {
    return -NACL_ABI_EFAULT;
  }


  #ifdef SYSCALL_TIMING
  nacl_syscall_counter++;
  nacl_syscall_invoked_times[NACL_sys_dyncode_create]++;
  nacl_sys_begin = clock();
  retval = NaClSysDyncodeCreate(natp, (uint32_t)  p.dest, (uint32_t)  p.src, (uint32_t)  p.size);
  nacl_sys_finish = clock();
  nacl_syscall_execution_time[NACL_sys_dyncode_create] += (double)(nacl_sys_finish - nacl_sys_begin) / CLOCKS_PER_SEC;
  return retval;
  #endif
  #ifdef NACL_SYSCALL_TRACE_ENABLED
  printf("[NaClSysCallInterface] cage id = %d, syscall_num = NACL_sys_dyncode_create [enter][syscall_depth = %d]\n", nap->cage_id, nacl_syscall_trace_level_counter);
  printf("==> NACL_sys_dyncode_create(");
#if 1
  for (i = 0; i < sizeof(p)/4; i++) {
    printf("%x,", *((uint32_t *)&p+i));
  }
#endif
  printf(")\n");
  nacl_syscall_trace_level_counter++;
  retval = NaClSysDyncodeCreate(natp, (uint32_t)  p.dest, (uint32_t)  p.src, (uint32_t)  p.size);
  nacl_syscall_trace_level_counter--;
  printf("[NaClSysCallInterface] cage id = %d, syscall_num = NACL_sys_dyncode_create [exit][syscall_depth = %d] \n", nap->cage_id, nacl_syscall_trace_level_counter);
  return retval;
  #endif

  return NaClSysDyncodeCreate(natp, (uint32_t)  p.dest, (uint32_t)  p.src, (uint32_t)  p.size);

}

/*
 * Check that the function being wrapped has the same type as the type
 * declared in SYSCALL_LIST.
 */
static INLINE void AssertSameType_NaClSysDyncodeCreate(void) {
  /* This assignment will give an error if the argument types don't match. */
  int32_t (*dummy)(struct NaClAppThread *natp, uint32_t dest, uint32_t src, uint32_t size) = NaClSysDyncodeCreate;
  /* 'dummy' is not actually a parameter but this suppresses the warning. */
  UNREFERENCED_PARAMETER(dummy);
}

/* this function was automagically generated */
static int32_t NaClSysDyncodeModifyDecoder(struct NaClAppThread *natp) {
  #ifdef SYSCALL_TIMING
  int32_t retval;
  clock_t nacl_sys_begin;
  clock_t nacl_sys_finish;
  #endif
  #ifdef NACL_SYSCALL_TRACE_ENABLED
  struct NaClApp *nap = natp->nap;
  int32_t retval;
#if 1
  unsigned int i = 0;
#endif
  #endif
    struct NaClSysDyncodeModifyArgs {
    uint32_t dest;
    uint32_t src;
    uint32_t size;
  } p;
  if (!NaClCopyInFromUserAndDropLock(natp->nap, &p, natp->usr_syscall_args,
                                     sizeof p)) {
    return -NACL_ABI_EFAULT;
  }


  #ifdef SYSCALL_TIMING
  nacl_syscall_counter++;
  nacl_syscall_invoked_times[NACL_sys_dyncode_modify]++;
  nacl_sys_begin = clock();
  retval = NaClSysDyncodeModify(natp, (uint32_t)  p.dest, (uint32_t)  p.src, (uint32_t)  p.size);
  nacl_sys_finish = clock();
  nacl_syscall_execution_time[NACL_sys_dyncode_modify] += (double)(nacl_sys_finish - nacl_sys_begin) / CLOCKS_PER_SEC;
  return retval;
  #endif
  #ifdef NACL_SYSCALL_TRACE_ENABLED
  printf("[NaClSysCallInterface] cage id = %d, syscall_num = NACL_sys_dyncode_modify [enter][syscall_depth = %d]\n", nap->cage_id, nacl_syscall_trace_level_counter);
  printf("==> NACL_sys_dyncode_modify(");
#if 1
  for (i = 0; i < sizeof(p)/4; i++) {
    printf("%x,", *((uint32_t *)&p+i));
  }
#endif
  printf(")\n");
  nacl_syscall_trace_level_counter++;
  retval = NaClSysDyncodeModify(natp, (uint32_t)  p.dest, (uint32_t)  p.src, (uint32_t)  p.size);
  nacl_syscall_trace_level_counter--;
  printf("[NaClSysCallInterface] cage id = %d, syscall_num = NACL_sys_dyncode_modify [exit][syscall_depth = %d] \n", nap->cage_id, nacl_syscall_trace_level_counter);
  return retval;
  #endif

  return NaClSysDyncodeModify(natp, (uint32_t)  p.dest, (uint32_t)  p.src, (uint32_t)  p.size);

}

/*
 * Check that the function being wrapped has the same type as the type
 * declared in SYSCALL_LIST.
 */
static INLINE void AssertSameType_NaClSysDyncodeModify(void) {
  /* This assignment will give an error if the argument types don't match. */
  int32_t (*dummy)(struct NaClAppThread *natp, uint32_t dest, uint32_t src, uint32_t size) = NaClSysDyncodeModify;
  /* 'dummy' is not actually a parameter but this suppresses the warning. */
  UNREFERENCED_PARAMETER(dummy);
}

/* this function was automagically generated */
static int32_t NaClSysDyncodeDeleteDecoder(struct NaClAppThread *natp) {
  #ifdef SYSCALL_TIMING
  int32_t retval;
  clock_t nacl_sys_begin;
  clock_t nacl_sys_finish;
  #endif
  #ifdef NACL_SYSCALL_TRACE_ENABLED
  struct NaClApp *nap = natp->nap;
  int32_t retval;
#if 1
  unsigned int i = 0;
#endif
  #endif
    struct NaClSysDyncodeDeleteArgs {
    uint32_t dest;
    uint32_t size;
  } p;
  if (!NaClCopyInFromUserAndDropLock(natp->nap, &p, natp->usr_syscall_args,
                                     sizeof p)) {
    return -NACL_ABI_EFAULT;
  }


  #ifdef SYSCALL_TIMING
  nacl_syscall_counter++;
  nacl_syscall_invoked_times[NACL_sys_dyncode_delete]++;
  nacl_sys_begin = clock();
  retval = NaClSysDyncodeDelete(natp, (uint32_t)  p.dest, (uint32_t)  p.size);
  nacl_sys_finish = clock();
  nacl_syscall_execution_time[NACL_sys_dyncode_delete] += (double)(nacl_sys_finish - nacl_sys_begin) / CLOCKS_PER_SEC;
  return retval;
  #endif
  #ifdef NACL_SYSCALL_TRACE_ENABLED
  printf("[NaClSysCallInterface] cage id = %d, syscall_num = NACL_sys_dyncode_delete [enter][syscall_depth = %d]\n", nap->cage_id, nacl_syscall_trace_level_counter);
  printf("==> NACL_sys_dyncode_delete(");
#if 1
  for (i = 0; i < sizeof(p)/4; i++) {
    printf("%x,", *((uint32_t *)&p+i));
  }
#endif
  printf(")\n");
  nacl_syscall_trace_level_counter++;
  retval = NaClSysDyncodeDelete(natp, (uint32_t)  p.dest, (uint32_t)  p.size);
  nacl_syscall_trace_level_counter--;
  printf("[NaClSysCallInterface] cage id = %d, syscall_num = NACL_sys_dyncode_delete [exit][syscall_depth = %d] \n", nap->cage_id, nacl_syscall_trace_level_counter);
  return retval;
  #endif

  return NaClSysDyncodeDelete(natp, (uint32_t)  p.dest, (uint32_t)  p.size);

}

/*
 * Check that the function being wrapped has the same type as the type
 * declared in SYSCALL_LIST.
 */
static INLINE void AssertSameType_NaClSysDyncodeDelete(void) {
  /* This assignment will give an error if the argument types don't match. */
  int32_t (*dummy)(struct NaClAppThread *natp, uint32_t dest, uint32_t size) = NaClSysDyncodeDelete;
  /* 'dummy' is not actually a parameter but this suppresses the warning. */
  UNREFERENCED_PARAMETER(dummy);
}

/* this function was automagically generated */
static int32_t NaClSysSecondTlsSetDecoder(struct NaClAppThread *natp) {
  #ifdef SYSCALL_TIMING
  int32_t retval;
  clock_t nacl_sys_begin;
  clock_t nacl_sys_finish;
  #endif
  #ifdef NACL_SYSCALL_TRACE_ENABLED
  struct NaClApp *nap = natp->nap;
  int32_t retval;
#if 1
  unsigned int i = 0;
#endif
  #endif
    struct NaClSysSecondTlsSetArgs {
    uint32_t new_value;
  } p;
  if (!NaClCopyInFromUserAndDropLock(natp->nap, &p, natp->usr_syscall_args,
                                     sizeof p)) {
    return -NACL_ABI_EFAULT;
  }


  #ifdef SYSCALL_TIMING
  nacl_syscall_counter++;
  nacl_syscall_invoked_times[NACL_sys_second_tls_set]++;
  nacl_sys_begin = clock();
  retval = NaClSysSecondTlsSet(natp, (uint32_t)  p.new_value);
  nacl_sys_finish = clock();
  nacl_syscall_execution_time[NACL_sys_second_tls_set] += (double)(nacl_sys_finish - nacl_sys_begin) / CLOCKS_PER_SEC;
  return retval;
  #endif
  #ifdef NACL_SYSCALL_TRACE_ENABLED
  printf("[NaClSysCallInterface] cage id = %d, syscall_num = NACL_sys_second_tls_set [enter][syscall_depth = %d]\n", nap->cage_id, nacl_syscall_trace_level_counter);
  printf("==> NACL_sys_second_tls_set(");
#if 1
  for (i = 0; i < sizeof(p)/4; i++) {
    printf("%x,", *((uint32_t *)&p+i));
  }
#endif
  printf(")\n");
  nacl_syscall_trace_level_counter++;
  retval = NaClSysSecondTlsSet(natp, (uint32_t)  p.new_value);
  nacl_syscall_trace_level_counter--;
  printf("[NaClSysCallInterface] cage id = %d, syscall_num = NACL_sys_second_tls_set [exit][syscall_depth = %d] \n", nap->cage_id, nacl_syscall_trace_level_counter);
  return retval;
  #endif

  return NaClSysSecondTlsSet(natp, (uint32_t)  p.new_value);

}

/*
 * Check that the function being wrapped has the same type as the type
 * declared in SYSCALL_LIST.
 */
static INLINE void AssertSameType_NaClSysSecondTlsSet(void) {
  /* This assignment will give an error if the argument types don't match. */
  int32_t (*dummy)(struct NaClAppThread *natp, uint32_t new_value) = NaClSysSecondTlsSet;
  /* 'dummy' is not actually a parameter but this suppresses the warning. */
  UNREFERENCED_PARAMETER(dummy);
}

/* this function was automagically generated */
static int32_t NaClSysSecondTlsGetDecoder(struct NaClAppThread *natp) {
  #ifdef SYSCALL_TIMING
  int32_t retval;
  clock_t nacl_sys_begin;
  clock_t nacl_sys_finish;
  #endif
  #ifdef NACL_SYSCALL_TRACE_ENABLED
  struct NaClApp *nap = natp->nap;
  int32_t retval;
#if 0
  unsigned int i = 0;
#endif
  #endif
    NaClCopyDropLock(natp->nap);
  #ifdef SYSCALL_TIMING
  nacl_syscall_counter++;
  nacl_syscall_invoked_times[NACL_sys_second_tls_get]++;
  nacl_sys_begin = clock();
  retval = NaClSysSecondTlsGet(natp);
  nacl_sys_finish = clock();
  nacl_syscall_execution_time[NACL_sys_second_tls_get] += (double)(nacl_sys_finish - nacl_sys_begin) / CLOCKS_PER_SEC;
  return retval;
  #endif
  #ifdef NACL_SYSCALL_TRACE_ENABLED
  printf("[NaClSysCallInterface] cage id = %d, syscall_num = NACL_sys_second_tls_get [enter][syscall_depth = %d]\n", nap->cage_id, nacl_syscall_trace_level_counter);
  printf("==> NACL_sys_second_tls_get(");
#if 0
  for (i = 0; i < sizeof(p)/4; i++) {
    printf("%x,", *((uint32_t *)&p+i));
  }
#endif
  printf(")\n");
  nacl_syscall_trace_level_counter++;
  retval = NaClSysSecondTlsGet(natp);
  nacl_syscall_trace_level_counter--;
  printf("[NaClSysCallInterface] cage id = %d, syscall_num = NACL_sys_second_tls_get [exit][syscall_depth = %d] \n", nap->cage_id, nacl_syscall_trace_level_counter);
  return retval;
  #endif

  return NaClSysSecondTlsGet(natp);

}

/*
 * Check that the function being wrapped has the same type as the type
 * declared in SYSCALL_LIST.
 */
static INLINE void AssertSameType_NaClSysSecondTlsGet(void) {
  /* This assignment will give an error if the argument types don't match. */
  int32_t (*dummy)(struct NaClAppThread *natp) = NaClSysSecondTlsGet;
  /* 'dummy' is not actually a parameter but this suppresses the warning. */
  UNREFERENCED_PARAMETER(dummy);
}

/* this function was automagically generated */
static int32_t NaClSysExceptionHandlerDecoder(struct NaClAppThread *natp) {
  #ifdef SYSCALL_TIMING
  int32_t retval;
  clock_t nacl_sys_begin;
  clock_t nacl_sys_finish;
  #endif
  #ifdef NACL_SYSCALL_TRACE_ENABLED
  struct NaClApp *nap = natp->nap;
  int32_t retval;
#if 1
  unsigned int i = 0;
#endif
  #endif
    struct NaClSysExceptionHandlerArgs {
    uint32_t handler_addr;
    uint32_t old_handler;
  } p;
  if (!NaClCopyInFromUserAndDropLock(natp->nap, &p, natp->usr_syscall_args,
                                     sizeof p)) {
    return -NACL_ABI_EFAULT;
  }


  #ifdef SYSCALL_TIMING
  nacl_syscall_counter++;
  nacl_syscall_invoked_times[NACL_sys_exception_handler]++;
  nacl_sys_begin = clock();
  retval = NaClSysExceptionHandler(natp, (uint32_t)  p.handler_addr, (uint32_t)  p.old_handler);
  nacl_sys_finish = clock();
  nacl_syscall_execution_time[NACL_sys_exception_handler] += (double)(nacl_sys_finish - nacl_sys_begin) / CLOCKS_PER_SEC;
  return retval;
  #endif
  #ifdef NACL_SYSCALL_TRACE_ENABLED
  printf("[NaClSysCallInterface] cage id = %d, syscall_num = NACL_sys_exception_handler [enter][syscall_depth = %d]\n", nap->cage_id, nacl_syscall_trace_level_counter);
  printf("==> NACL_sys_exception_handler(");
#if 1
  for (i = 0; i < sizeof(p)/4; i++) {
    printf("%x,", *((uint32_t *)&p+i));
  }
#endif
  printf(")\n");
  nacl_syscall_trace_level_counter++;
  retval = NaClSysExceptionHandler(natp, (uint32_t)  p.handler_addr, (uint32_t)  p.old_handler);
  nacl_syscall_trace_level_counter--;
  printf("[NaClSysCallInterface] cage id = %d, syscall_num = NACL_sys_exception_handler [exit][syscall_depth = %d] \n", nap->cage_id, nacl_syscall_trace_level_counter);
  return retval;
  #endif

  return NaClSysExceptionHandler(natp, (uint32_t)  p.handler_addr, (uint32_t)  p.old_handler);

}

/*
 * Check that the function being wrapped has the same type as the type
 * declared in SYSCALL_LIST.
 */
static INLINE void AssertSameType_NaClSysExceptionHandler(void) {
  /* This assignment will give an error if the argument types don't match. */
  int32_t (*dummy)(struct NaClAppThread *natp, uint32_t handler_addr, uint32_t old_handler) = NaClSysExceptionHandler;
  /* 'dummy' is not actually a parameter but this suppresses the warning. */
  UNREFERENCED_PARAMETER(dummy);
}

/* this function was automagically generated */
static int32_t NaClSysExceptionStackDecoder(struct NaClAppThread *natp) {
  #ifdef SYSCALL_TIMING
  int32_t retval;
  clock_t nacl_sys_begin;
  clock_t nacl_sys_finish;
  #endif
  #ifdef NACL_SYSCALL_TRACE_ENABLED
  struct NaClApp *nap = natp->nap;
  int32_t retval;
#if 1
  unsigned int i = 0;
#endif
  #endif
    struct NaClSysExceptionStackArgs {
    uint32_t stack_addr;
    uint32_t stack_size;
  } p;
  if (!NaClCopyInFromUserAndDropLock(natp->nap, &p, natp->usr_syscall_args,
                                     sizeof p)) {
    return -NACL_ABI_EFAULT;
  }


  #ifdef SYSCALL_TIMING
  nacl_syscall_counter++;
  nacl_syscall_invoked_times[NACL_sys_exception_stack]++;
  nacl_sys_begin = clock();
  retval = NaClSysExceptionStack(natp, (uint32_t)  p.stack_addr, (uint32_t)  p.stack_size);
  nacl_sys_finish = clock();
  nacl_syscall_execution_time[NACL_sys_exception_stack] += (double)(nacl_sys_finish - nacl_sys_begin) / CLOCKS_PER_SEC;
  return retval;
  #endif
  #ifdef NACL_SYSCALL_TRACE_ENABLED
  printf("[NaClSysCallInterface] cage id = %d, syscall_num = NACL_sys_exception_stack [enter][syscall_depth = %d]\n", nap->cage_id, nacl_syscall_trace_level_counter);
  printf("==> NACL_sys_exception_stack(");
#if 1
  for (i = 0; i < sizeof(p)/4; i++) {
    printf("%x,", *((uint32_t *)&p+i));
  }
#endif
  printf(")\n");
  nacl_syscall_trace_level_counter++;
  retval = NaClSysExceptionStack(natp, (uint32_t)  p.stack_addr, (uint32_t)  p.stack_size);
  nacl_syscall_trace_level_counter--;
  printf("[NaClSysCallInterface] cage id = %d, syscall_num = NACL_sys_exception_stack [exit][syscall_depth = %d] \n", nap->cage_id, nacl_syscall_trace_level_counter);
  return retval;
  #endif

  return NaClSysExceptionStack(natp, (uint32_t)  p.stack_addr, (uint32_t)  p.stack_size);

}

/*
 * Check that the function being wrapped has the same type as the type
 * declared in SYSCALL_LIST.
 */
static INLINE void AssertSameType_NaClSysExceptionStack(void) {
  /* This assignment will give an error if the argument types don't match. */
  int32_t (*dummy)(struct NaClAppThread *natp, uint32_t stack_addr, uint32_t stack_size) = NaClSysExceptionStack;
  /* 'dummy' is not actually a parameter but this suppresses the warning. */
  UNREFERENCED_PARAMETER(dummy);
}

/* this function was automagically generated */
static int32_t NaClSysExceptionClearFlagDecoder(struct NaClAppThread *natp) {
  #ifdef SYSCALL_TIMING
  int32_t retval;
  clock_t nacl_sys_begin;
  clock_t nacl_sys_finish;
  #endif
  #ifdef NACL_SYSCALL_TRACE_ENABLED
  struct NaClApp *nap = natp->nap;
  int32_t retval;
#if 0
  unsigned int i = 0;
#endif
  #endif
    NaClCopyDropLock(natp->nap);
  #ifdef SYSCALL_TIMING
  nacl_syscall_counter++;
  nacl_syscall_invoked_times[NACL_sys_exception_clear_flag]++;
  nacl_sys_begin = clock();
  retval = NaClSysExceptionClearFlag(natp);
  nacl_sys_finish = clock();
  nacl_syscall_execution_time[NACL_sys_exception_clear_flag] += (double)(nacl_sys_finish - nacl_sys_begin) / CLOCKS_PER_SEC;
  return retval;
  #endif
  #ifdef NACL_SYSCALL_TRACE_ENABLED
  printf("[NaClSysCallInterface] cage id = %d, syscall_num = NACL_sys_exception_clear_flag [enter][syscall_depth = %d]\n", nap->cage_id, nacl_syscall_trace_level_counter);
  printf("==> NACL_sys_exception_clear_flag(");
#if 0
  for (i = 0; i < sizeof(p)/4; i++) {
    printf("%x,", *((uint32_t *)&p+i));
  }
#endif
  printf(")\n");
  nacl_syscall_trace_level_counter++;
  retval = NaClSysExceptionClearFlag(natp);
  nacl_syscall_trace_level_counter--;
  printf("[NaClSysCallInterface] cage id = %d, syscall_num = NACL_sys_exception_clear_flag [exit][syscall_depth = %d] \n", nap->cage_id, nacl_syscall_trace_level_counter);
  return retval;
  #endif

  return NaClSysExceptionClearFlag(natp);

}

/*
 * Check that the function being wrapped has the same type as the type
 * declared in SYSCALL_LIST.
 */
static INLINE void AssertSameType_NaClSysExceptionClearFlag(void) {
  /* This assignment will give an error if the argument types don't match. */
  int32_t (*dummy)(struct NaClAppThread *natp) = NaClSysExceptionClearFlag;
  /* 'dummy' is not actually a parameter but this suppresses the warning. */
  UNREFERENCED_PARAMETER(dummy);
}

/* this function was automagically generated */
static int32_t NaClSysTestInfoLeakDecoder(struct NaClAppThread *natp) {
  #ifdef SYSCALL_TIMING
  int32_t retval;
  clock_t nacl_sys_begin;
  clock_t nacl_sys_finish;
  #endif
  #ifdef NACL_SYSCALL_TRACE_ENABLED
  struct NaClApp *nap = natp->nap;
  int32_t retval;
#if 0
  unsigned int i = 0;
#endif
  #endif
    NaClCopyDropLock(natp->nap);
  #ifdef SYSCALL_TIMING
  nacl_syscall_counter++;
  nacl_syscall_invoked_times[NACL_sys_test_infoleak]++;
  nacl_sys_begin = clock();
  retval = NaClSysTestInfoLeak(natp);
  nacl_sys_finish = clock();
  nacl_syscall_execution_time[NACL_sys_test_infoleak] += (double)(nacl_sys_finish - nacl_sys_begin) / CLOCKS_PER_SEC;
  return retval;
  #endif
  #ifdef NACL_SYSCALL_TRACE_ENABLED
  printf("[NaClSysCallInterface] cage id = %d, syscall_num = NACL_sys_test_infoleak [enter][syscall_depth = %d]\n", nap->cage_id, nacl_syscall_trace_level_counter);
  printf("==> NACL_sys_test_infoleak(");
#if 0
  for (i = 0; i < sizeof(p)/4; i++) {
    printf("%x,", *((uint32_t *)&p+i));
  }
#endif
  printf(")\n");
  nacl_syscall_trace_level_counter++;
  retval = NaClSysTestInfoLeak(natp);
  nacl_syscall_trace_level_counter--;
  printf("[NaClSysCallInterface] cage id = %d, syscall_num = NACL_sys_test_infoleak [exit][syscall_depth = %d] \n", nap->cage_id, nacl_syscall_trace_level_counter);
  return retval;
  #endif

  return NaClSysTestInfoLeak(natp);

}

/*
 * Check that the function being wrapped has the same type as the type
 * declared in SYSCALL_LIST.
 */
static INLINE void AssertSameType_NaClSysTestInfoLeak(void) {
  /* This assignment will give an error if the argument types don't match. */
  int32_t (*dummy)(struct NaClAppThread *natp) = NaClSysTestInfoLeak;
  /* 'dummy' is not actually a parameter but this suppresses the warning. */
  UNREFERENCED_PARAMETER(dummy);
}

/* this function was automagically generated */
static int32_t NaClSysTestCrashDecoder(struct NaClAppThread *natp) {
  #ifdef SYSCALL_TIMING
  int32_t retval;
  clock_t nacl_sys_begin;
  clock_t nacl_sys_finish;
  #endif
  #ifdef NACL_SYSCALL_TRACE_ENABLED
  struct NaClApp *nap = natp->nap;
  int32_t retval;
#if 1
  unsigned int i = 0;
#endif
  #endif
    struct NaClSysTestCrashArgs {
    uint32_t crash_type;
  } p;
  if (!NaClCopyInFromUserAndDropLock(natp->nap, &p, natp->usr_syscall_args,
                                     sizeof p)) {
    return -NACL_ABI_EFAULT;
  }


  #ifdef SYSCALL_TIMING
  nacl_syscall_counter++;
  nacl_syscall_invoked_times[NACL_sys_test_crash]++;
  nacl_sys_begin = clock();
  retval = NaClSysTestCrash(natp, (int)  p.crash_type);
  nacl_sys_finish = clock();
  nacl_syscall_execution_time[NACL_sys_test_crash] += (double)(nacl_sys_finish - nacl_sys_begin) / CLOCKS_PER_SEC;
  return retval;
  #endif
  #ifdef NACL_SYSCALL_TRACE_ENABLED
  printf("[NaClSysCallInterface] cage id = %d, syscall_num = NACL_sys_test_crash [enter][syscall_depth = %d]\n", nap->cage_id, nacl_syscall_trace_level_counter);
  printf("==> NACL_sys_test_crash(");
#if 1
  for (i = 0; i < sizeof(p)/4; i++) {
    printf("%x,", *((uint32_t *)&p+i));
  }
#endif
  printf(")\n");
  nacl_syscall_trace_level_counter++;
  retval = NaClSysTestCrash(natp, (int)  p.crash_type);
  nacl_syscall_trace_level_counter--;
  printf("[NaClSysCallInterface] cage id = %d, syscall_num = NACL_sys_test_crash [exit][syscall_depth = %d] \n", nap->cage_id, nacl_syscall_trace_level_counter);
  return retval;
  #endif

  return NaClSysTestCrash(natp, (int)  p.crash_type);

}

/*
 * Check that the function being wrapped has the same type as the type
 * declared in SYSCALL_LIST.
 */
static INLINE void AssertSameType_NaClSysTestCrash(void) {
  /* This assignment will give an error if the argument types don't match. */
  int32_t (*dummy)(struct NaClAppThread *natp, int crash_type) = NaClSysTestCrash;
  /* 'dummy' is not actually a parameter but this suppresses the warning. */
  UNREFERENCED_PARAMETER(dummy);
}

/* this function was automagically generated */
static int32_t NaClSysLindSyscallDecoder(struct NaClAppThread *natp) {
  #ifdef SYSCALL_TIMING
  int32_t retval;
  clock_t nacl_sys_begin;
  clock_t nacl_sys_finish;
  #endif
  #ifdef NACL_SYSCALL_TRACE_ENABLED
  struct NaClApp *nap = natp->nap;
  int32_t retval;
#if 1
  unsigned int i = 0;
#endif
  #endif
    struct NaClSysLindSyscallArgs {
    uint32_t callNum;
    uint32_t inNum;
    uint32_t inArgs;
    uint32_t outNum;
    uint32_t outArgs;
  } p;
  if (!NaClCopyInFromUserAndDropLock(natp->nap, &p, natp->usr_syscall_args,
                                     sizeof p)) {
    return -NACL_ABI_EFAULT;
  }


  #ifdef SYSCALL_TIMING
  nacl_syscall_counter++;
  nacl_syscall_invoked_times[NACL_sys_lind_syscall]++;
  nacl_sys_begin = clock();
  retval = NaClSysLindSyscall(natp, (uint32_t)  p.callNum, (uint32_t)  p.inNum, (void *) (uintptr_t) p.inArgs, (uint32_t)  p.outNum, (void *) (uintptr_t) p.outArgs);
  nacl_sys_finish = clock();
  nacl_syscall_execution_time[NACL_sys_lind_syscall] += (double)(nacl_sys_finish - nacl_sys_begin) / CLOCKS_PER_SEC;
  return retval;
  #endif
  #ifdef NACL_SYSCALL_TRACE_ENABLED
  printf("[NaClSysCallInterface] cage id = %d, syscall_num = NACL_sys_lind_syscall [enter][syscall_depth = %d]\n", nap->cage_id, nacl_syscall_trace_level_counter);
  printf("==> NACL_sys_lind_syscall(");
#if 1
  for (i = 0; i < sizeof(p)/4; i++) {
    printf("%x,", *((uint32_t *)&p+i));
  }
#endif
  printf(")\n");
  nacl_syscall_trace_level_counter++;
  retval = NaClSysLindSyscall(natp, (uint32_t)  p.callNum, (uint32_t)  p.inNum, (void *) (uintptr_t) p.inArgs, (uint32_t)  p.outNum, (void *) (uintptr_t) p.outArgs);
  nacl_syscall_trace_level_counter--;
  printf("[NaClSysCallInterface] cage id = %d, syscall_num = NACL_sys_lind_syscall [exit][syscall_depth = %d] \n", nap->cage_id, nacl_syscall_trace_level_counter);
  return retval;
  #endif

  return NaClSysLindSyscall(natp, (uint32_t)  p.callNum, (uint32_t)  p.inNum, (void *) (uintptr_t) p.inArgs, (uint32_t)  p.outNum, (void *) (uintptr_t) p.outArgs);

}

/*
 * Check that the function being wrapped has the same type as the type
 * declared in SYSCALL_LIST.
 */
static INLINE void AssertSameType_NaClSysLindSyscall(void) {
  /* This assignment will give an error if the argument types don't match. */
  int32_t (*dummy)(struct NaClAppThread *natp, uint32_t callNum, uint32_t inNum, void *inArgs, uint32_t outNum, void *outArgs) = NaClSysLindSyscall;
  /* 'dummy' is not actually a parameter but this suppresses the warning. */
  UNREFERENCED_PARAMETER(dummy);
}

/* this function was automagically generated */
static int32_t NaClSysForkDecoder(struct NaClAppThread *natp) {
  #ifdef SYSCALL_TIMING
  int32_t retval;
  clock_t nacl_sys_begin;
  clock_t nacl_sys_finish;
  #endif
  #ifdef NACL_SYSCALL_TRACE_ENABLED
  struct NaClApp *nap = natp->nap;
  int32_t retval;
#if 0
  unsigned int i = 0;
#endif
  #endif
    NaClCopyDropLock(natp->nap);
  #ifdef SYSCALL_TIMING
  nacl_syscall_counter++;
  nacl_syscall_invoked_times[NACL_sys_fork]++;
  nacl_sys_begin = clock();
  retval = NaClSysFork(natp);
  nacl_sys_finish = clock();
  nacl_syscall_execution_time[NACL_sys_fork] += (double)(nacl_sys_finish - nacl_sys_begin) / CLOCKS_PER_SEC;
  return retval;
  #endif
  #ifdef NACL_SYSCALL_TRACE_ENABLED
  printf("[NaClSysCallInterface] cage id = %d, syscall_num = NACL_sys_fork [enter][syscall_depth = %d]\n", nap->cage_id, nacl_syscall_trace_level_counter);
  printf("==> NACL_sys_fork(");
#if 0
  for (i = 0; i < sizeof(p)/4; i++) {
    printf("%x,", *((uint32_t *)&p+i));
  }
#endif
  printf(")\n");
  nacl_syscall_trace_level_counter++;
  retval = NaClSysFork(natp);
  nacl_syscall_trace_level_counter--;
  printf("[NaClSysCallInterface] cage id = %d, syscall_num = NACL_sys_fork [exit][syscall_depth = %d] \n", nap->cage_id, nacl_syscall_trace_level_counter);
  return retval;
  #endif

  return NaClSysFork(natp);

}

/*
 * Check that the function being wrapped has the same type as the type
 * declared in SYSCALL_LIST.
 */
static INLINE void AssertSameType_NaClSysFork(void) {
  /* This assignment will give an error if the argument types don't match. */
  int32_t (*dummy)(struct NaClAppThread *natp) = NaClSysFork;
  /* 'dummy' is not actually a parameter but this suppresses the warning. */
  UNREFERENCED_PARAMETER(dummy);
}

/* this function was automagically generated */
static int32_t NaClSysExecvDecoder(struct NaClAppThread *natp) {
  #ifdef SYSCALL_TIMING
  int32_t retval;
  clock_t nacl_sys_begin;
  clock_t nacl_sys_finish;
  #endif
  #ifdef NACL_SYSCALL_TRACE_ENABLED
  struct NaClApp *nap = natp->nap;
  int32_t retval;
#if 1
  unsigned int i = 0;
#endif
  #endif
    struct NaClSysExecvArgs {
    uint32_t path;
    uint32_t argv;
  } p;
  if (!NaClCopyInFromUserAndDropLock(natp->nap, &p, natp->usr_syscall_args,
                                     sizeof p)) {
    return -NACL_ABI_EFAULT;
  }


  #ifdef SYSCALL_TIMING
  nacl_syscall_counter++;
  nacl_syscall_invoked_times[NACL_sys_execv]++;
  nacl_sys_begin = clock();
  retval = NaClSysExecv(natp, (void *) (uintptr_t) p.path, (void *) (uintptr_t) p.argv);
  nacl_sys_finish = clock();
  nacl_syscall_execution_time[NACL_sys_execv] += (double)(nacl_sys_finish - nacl_sys_begin) / CLOCKS_PER_SEC;
  return retval;
  #endif
  #ifdef NACL_SYSCALL_TRACE_ENABLED
  printf("[NaClSysCallInterface] cage id = %d, syscall_num = NACL_sys_execv [enter][syscall_depth = %d]\n", nap->cage_id, nacl_syscall_trace_level_counter);
  printf("==> NACL_sys_execv(");
#if 1
  for (i = 0; i < sizeof(p)/4; i++) {
    printf("%x,", *((uint32_t *)&p+i));
  }
#endif
  printf(")\n");
  nacl_syscall_trace_level_counter++;
  retval = NaClSysExecv(natp, (void *) (uintptr_t) p.path, (void *) (uintptr_t) p.argv);
  nacl_syscall_trace_level_counter--;
  printf("[NaClSysCallInterface] cage id = %d, syscall_num = NACL_sys_execv [exit][syscall_depth = %d] \n", nap->cage_id, nacl_syscall_trace_level_counter);
  return retval;
  #endif

  return NaClSysExecv(natp, (void *) (uintptr_t) p.path, (void *) (uintptr_t) p.argv);

}

/*
 * Check that the function being wrapped has the same type as the type
 * declared in SYSCALL_LIST.
 */
static INLINE void AssertSameType_NaClSysExecv(void) {
  /* This assignment will give an error if the argument types don't match. */
  int32_t (*dummy)(struct NaClAppThread *natp, void *path, void *argv) = NaClSysExecv;
  /* 'dummy' is not actually a parameter but this suppresses the warning. */
  UNREFERENCED_PARAMETER(dummy);
}

/* this function was automagically generated */
static int32_t NaClSysExecveDecoder(struct NaClAppThread *natp) {
  #ifdef SYSCALL_TIMING
  int32_t retval;
  clock_t nacl_sys_begin;
  clock_t nacl_sys_finish;
  #endif
  #ifdef NACL_SYSCALL_TRACE_ENABLED
  struct NaClApp *nap = natp->nap;
  int32_t retval;
#if 1
  unsigned int i = 0;
#endif
  #endif
    struct NaClSysExecveArgs {
    uint32_t path;
    uint32_t argv;
    uint32_t envp;
  } p;
  if (!NaClCopyInFromUserAndDropLock(natp->nap, &p, natp->usr_syscall_args,
                                     sizeof p)) {
    return -NACL_ABI_EFAULT;
  }


  #ifdef SYSCALL_TIMING
  nacl_syscall_counter++;
  nacl_syscall_invoked_times[NACL_sys_execve]++;
  nacl_sys_begin = clock();
  retval = NaClSysExecve(natp, (void *) (uintptr_t) p.path, (void *) (uintptr_t) p.argv, (void *) (uintptr_t) p.envp);
  nacl_sys_finish = clock();
  nacl_syscall_execution_time[NACL_sys_execve] += (double)(nacl_sys_finish - nacl_sys_begin) / CLOCKS_PER_SEC;
  return retval;
  #endif
  #ifdef NACL_SYSCALL_TRACE_ENABLED
  printf("[NaClSysCallInterface] cage id = %d, syscall_num = NACL_sys_execve [enter][syscall_depth = %d]\n", nap->cage_id, nacl_syscall_trace_level_counter);
  printf("==> NACL_sys_execve(");
#if 1
  for (i = 0; i < sizeof(p)/4; i++) {
    printf("%x,", *((uint32_t *)&p+i));
  }
#endif
  printf(")\n");
  nacl_syscall_trace_level_counter++;
  retval = NaClSysExecve(natp, (void *) (uintptr_t) p.path, (void *) (uintptr_t) p.argv, (void *) (uintptr_t) p.envp);
  nacl_syscall_trace_level_counter--;
  printf("[NaClSysCallInterface] cage id = %d, syscall_num = NACL_sys_execve [exit][syscall_depth = %d] \n", nap->cage_id, nacl_syscall_trace_level_counter);
  return retval;
  #endif

  return NaClSysExecve(natp, (void *) (uintptr_t) p.path, (void *) (uintptr_t) p.argv, (void *) (uintptr_t) p.envp);

}

/*
 * Check that the function being wrapped has the same type as the type
 * declared in SYSCALL_LIST.
 */
static INLINE void AssertSameType_NaClSysExecve(void) {
  /* This assignment will give an error if the argument types don't match. */
  int32_t (*dummy)(struct NaClAppThread *natp, void *path, void *argv, void *envp) = NaClSysExecve;
  /* 'dummy' is not actually a parameter but this suppresses the warning. */
  UNREFERENCED_PARAMETER(dummy);
}

/* this function was automagically generated */
static int32_t NaClSysPipeDecoder(struct NaClAppThread *natp) {
  #ifdef SYSCALL_TIMING
  int32_t retval;
  clock_t nacl_sys_begin;
  clock_t nacl_sys_finish;
  #endif
  #ifdef NACL_SYSCALL_TRACE_ENABLED
  struct NaClApp *nap = natp->nap;
  int32_t retval;
#if 1
  unsigned int i = 0;
#endif
  #endif
    struct NaClSysPipeArgs {
    uint32_t pipedes;
  } p;
  if (!NaClCopyInFromUserAndDropLock(natp->nap, &p, natp->usr_syscall_args,
                                     sizeof p)) {
    return -NACL_ABI_EFAULT;
  }


  #ifdef SYSCALL_TIMING
  nacl_syscall_counter++;
  nacl_syscall_invoked_times[NACL_sys_pipe]++;
  nacl_sys_begin = clock();
  retval = NaClSysPipe(natp, (uint32_t *) (uintptr_t) p.pipedes);
  nacl_sys_finish = clock();
  nacl_syscall_execution_time[NACL_sys_pipe] += (double)(nacl_sys_finish - nacl_sys_begin) / CLOCKS_PER_SEC;
  return retval;
  #endif
  #ifdef NACL_SYSCALL_TRACE_ENABLED
  printf("[NaClSysCallInterface] cage id = %d, syscall_num = NACL_sys_pipe [enter][syscall_depth = %d]\n", nap->cage_id, nacl_syscall_trace_level_counter);
  printf("==> NACL_sys_pipe(");
#if 1
  for (i = 0; i < sizeof(p)/4; i++) {
    printf("%x,", *((uint32_t *)&p+i));
  }
#endif
  printf(")\n");
  nacl_syscall_trace_level_counter++;
  retval = NaClSysPipe(natp, (uint32_t *) (uintptr_t) p.pipedes);
  nacl_syscall_trace_level_counter--;
  printf("[NaClSysCallInterface] cage id = %d, syscall_num = NACL_sys_pipe [exit][syscall_depth = %d] \n", nap->cage_id, nacl_syscall_trace_level_counter);
  return retval;
  #endif

  return NaClSysPipe(natp, (uint32_t *) (uintptr_t) p.pipedes);

}

/*
 * Check that the function being wrapped has the same type as the type
 * declared in SYSCALL_LIST.
 */
static INLINE void AssertSameType_NaClSysPipe(void) {
  /* This assignment will give an error if the argument types don't match. */
  int32_t (*dummy)(struct NaClAppThread *natp, uint32_t *pipedes) = NaClSysPipe;
  /* 'dummy' is not actually a parameter but this suppresses the warning. */
  UNREFERENCED_PARAMETER(dummy);
}

/* this function was automagically generated */
static int32_t NaClSysPipe2Decoder(struct NaClAppThread *natp) {
  #ifdef SYSCALL_TIMING
  int32_t retval;
  clock_t nacl_sys_begin;
  clock_t nacl_sys_finish;
  #endif
  #ifdef NACL_SYSCALL_TRACE_ENABLED
  struct NaClApp *nap = natp->nap;
  int32_t retval;
#if 1
  unsigned int i = 0;
#endif
  #endif
    struct NaClSysPipe2Args {
    uint32_t pipedes;
    uint32_t flags;
  } p;
  if (!NaClCopyInFromUserAndDropLock(natp->nap, &p, natp->usr_syscall_args,
                                     sizeof p)) {
    return -NACL_ABI_EFAULT;
  }


  #ifdef SYSCALL_TIMING
  nacl_syscall_counter++;
  nacl_syscall_invoked_times[NACL_sys_pipe2]++;
  nacl_sys_begin = clock();
  retval = NaClSysPipe2(natp, (uint32_t *) (uintptr_t) p.pipedes, (int)  p.flags);
  nacl_sys_finish = clock();
  nacl_syscall_execution_time[NACL_sys_pipe2] += (double)(nacl_sys_finish - nacl_sys_begin) / CLOCKS_PER_SEC;
  return retval;
  #endif
  #ifdef NACL_SYSCALL_TRACE_ENABLED
  printf("[NaClSysCallInterface] cage id = %d, syscall_num = NACL_sys_pipe2 [enter][syscall_depth = %d]\n", nap->cage_id, nacl_syscall_trace_level_counter);
  printf("==> NACL_sys_pipe2(");
#if 1
  for (i = 0; i < sizeof(p)/4; i++) {
    printf("%x,", *((uint32_t *)&p+i));
  }
#endif
  printf(")\n");
  nacl_syscall_trace_level_counter++;
  retval = NaClSysPipe2(natp, (uint32_t *) (uintptr_t) p.pipedes, (int)  p.flags);
  nacl_syscall_trace_level_counter--;
  printf("[NaClSysCallInterface] cage id = %d, syscall_num = NACL_sys_pipe2 [exit][syscall_depth = %d] \n", nap->cage_id, nacl_syscall_trace_level_counter);
  return retval;
  #endif

  return NaClSysPipe2(natp, (uint32_t *) (uintptr_t) p.pipedes, (int)  p.flags);

}

/*
 * Check that the function being wrapped has the same type as the type
 * declared in SYSCALL_LIST.
 */
static INLINE void AssertSameType_NaClSysPipe2(void) {
  /* This assignment will give an error if the argument types don't match. */
  int32_t (*dummy)(struct NaClAppThread *natp, uint32_t *pipedes, int flags) = NaClSysPipe2;
  /* 'dummy' is not actually a parameter but this suppresses the warning. */
  UNREFERENCED_PARAMETER(dummy);
}

/* this function was automagically generated */
static int32_t NaClSysGetppidDecoder(struct NaClAppThread *natp) {
  #ifdef SYSCALL_TIMING
  int32_t retval;
  clock_t nacl_sys_begin;
  clock_t nacl_sys_finish;
  #endif
  #ifdef NACL_SYSCALL_TRACE_ENABLED
  struct NaClApp *nap = natp->nap;
  int32_t retval;
#if 0
  unsigned int i = 0;
#endif
  #endif
    NaClCopyDropLock(natp->nap);
  #ifdef SYSCALL_TIMING
  nacl_syscall_counter++;
  nacl_syscall_invoked_times[NACL_sys_getppid]++;
  nacl_sys_begin = clock();
  retval = NaClSysGetppid(natp);
  nacl_sys_finish = clock();
  nacl_syscall_execution_time[NACL_sys_getppid] += (double)(nacl_sys_finish - nacl_sys_begin) / CLOCKS_PER_SEC;
  return retval;
  #endif
  #ifdef NACL_SYSCALL_TRACE_ENABLED
  printf("[NaClSysCallInterface] cage id = %d, syscall_num = NACL_sys_getppid [enter][syscall_depth = %d]\n", nap->cage_id, nacl_syscall_trace_level_counter);
  printf("==> NACL_sys_getppid(");
#if 0
  for (i = 0; i < sizeof(p)/4; i++) {
    printf("%x,", *((uint32_t *)&p+i));
  }
#endif
  printf(")\n");
  nacl_syscall_trace_level_counter++;
  retval = NaClSysGetppid(natp);
  nacl_syscall_trace_level_counter--;
  printf("[NaClSysCallInterface] cage id = %d, syscall_num = NACL_sys_getppid [exit][syscall_depth = %d] \n", nap->cage_id, nacl_syscall_trace_level_counter);
  return retval;
  #endif

  return NaClSysGetppid(natp);

}

/*
 * Check that the function being wrapped has the same type as the type
 * declared in SYSCALL_LIST.
 */
static INLINE void AssertSameType_NaClSysGetppid(void) {
  /* This assignment will give an error if the argument types don't match. */
  int32_t (*dummy)(struct NaClAppThread *natp) = NaClSysGetppid;
  /* 'dummy' is not actually a parameter but this suppresses the warning. */
  UNREFERENCED_PARAMETER(dummy);
}

/* this function was automagically generated */
static int32_t NaClSysWaitpidDecoder(struct NaClAppThread *natp) {
  #ifdef SYSCALL_TIMING
  int32_t retval;
  clock_t nacl_sys_begin;
  clock_t nacl_sys_finish;
  #endif
  #ifdef NACL_SYSCALL_TRACE_ENABLED
  struct NaClApp *nap = natp->nap;
  int32_t retval;
#if 1
  unsigned int i = 0;
#endif
  #endif
    struct NaClSysWaitpidArgs {
    uint32_t pid;
    uint32_t stat_loc;
    uint32_t options;
  } p;
  if (!NaClCopyInFromUserAndDropLock(natp->nap, &p, natp->usr_syscall_args,
                                     sizeof p)) {
    return -NACL_ABI_EFAULT;
  }


  #ifdef SYSCALL_TIMING
  nacl_syscall_counter++;
  nacl_syscall_invoked_times[NACL_sys_waitpid]++;
  nacl_sys_begin = clock();
  retval = NaClSysWaitpid(natp, (int)  p.pid, (uint32_t *) (uintptr_t) p.stat_loc, (int)  p.options);
  nacl_sys_finish = clock();
  nacl_syscall_execution_time[NACL_sys_waitpid] += (double)(nacl_sys_finish - nacl_sys_begin) / CLOCKS_PER_SEC;
  return retval;
  #endif
  #ifdef NACL_SYSCALL_TRACE_ENABLED
  printf("[NaClSysCallInterface] cage id = %d, syscall_num = NACL_sys_waitpid [enter][syscall_depth = %d]\n", nap->cage_id, nacl_syscall_trace_level_counter);
  printf("==> NACL_sys_waitpid(");
#if 1
  for (i = 0; i < sizeof(p)/4; i++) {
    printf("%x,", *((uint32_t *)&p+i));
  }
#endif
  printf(")\n");
  nacl_syscall_trace_level_counter++;
  retval = NaClSysWaitpid(natp, (int)  p.pid, (uint32_t *) (uintptr_t) p.stat_loc, (int)  p.options);
  nacl_syscall_trace_level_counter--;
  printf("[NaClSysCallInterface] cage id = %d, syscall_num = NACL_sys_waitpid [exit][syscall_depth = %d] \n", nap->cage_id, nacl_syscall_trace_level_counter);
  return retval;
  #endif

  return NaClSysWaitpid(natp, (int)  p.pid, (uint32_t *) (uintptr_t) p.stat_loc, (int)  p.options);

}

/*
 * Check that the function being wrapped has the same type as the type
 * declared in SYSCALL_LIST.
 */
static INLINE void AssertSameType_NaClSysWaitpid(void) {
  /* This assignment will give an error if the argument types don't match. */
  int32_t (*dummy)(struct NaClAppThread *natp, int pid, uint32_t *stat_loc, int options) = NaClSysWaitpid;
  /* 'dummy' is not actually a parameter but this suppresses the warning. */
  UNREFERENCED_PARAMETER(dummy);
}

/* this function was automagically generated */
static int32_t NaClSysWaitDecoder(struct NaClAppThread *natp) {
  #ifdef SYSCALL_TIMING
  int32_t retval;
  clock_t nacl_sys_begin;
  clock_t nacl_sys_finish;
  #endif
  #ifdef NACL_SYSCALL_TRACE_ENABLED
  struct NaClApp *nap = natp->nap;
  int32_t retval;
#if 1
  unsigned int i = 0;
#endif
  #endif
    struct NaClSysWaitArgs {
    uint32_t stat_loc;
  } p;
  if (!NaClCopyInFromUserAndDropLock(natp->nap, &p, natp->usr_syscall_args,
                                     sizeof p)) {
    return -NACL_ABI_EFAULT;
  }


  #ifdef SYSCALL_TIMING
  nacl_syscall_counter++;
  nacl_syscall_invoked_times[NACL_sys_wait]++;
  nacl_sys_begin = clock();
  retval = NaClSysWait(natp, (uint32_t *) (uintptr_t) p.stat_loc);
  nacl_sys_finish = clock();
  nacl_syscall_execution_time[NACL_sys_wait] += (double)(nacl_sys_finish - nacl_sys_begin) / CLOCKS_PER_SEC;
  return retval;
  #endif
  #ifdef NACL_SYSCALL_TRACE_ENABLED
  printf("[NaClSysCallInterface] cage id = %d, syscall_num = NACL_sys_wait [enter][syscall_depth = %d]\n", nap->cage_id, nacl_syscall_trace_level_counter);
  printf("==> NACL_sys_wait(");
#if 1
  for (i = 0; i < sizeof(p)/4; i++) {
    printf("%x,", *((uint32_t *)&p+i));
  }
#endif
  printf(")\n");
  nacl_syscall_trace_level_counter++;
  retval = NaClSysWait(natp, (uint32_t *) (uintptr_t) p.stat_loc);
  nacl_syscall_trace_level_counter--;
  printf("[NaClSysCallInterface] cage id = %d, syscall_num = NACL_sys_wait [exit][syscall_depth = %d] \n", nap->cage_id, nacl_syscall_trace_level_counter);
  return retval;
  #endif

  return NaClSysWait(natp, (uint32_t *) (uintptr_t) p.stat_loc);

}

/*
 * Check that the function being wrapped has the same type as the type
 * declared in SYSCALL_LIST.
 */
static INLINE void AssertSameType_NaClSysWait(void) {
  /* This assignment will give an error if the argument types don't match. */
  int32_t (*dummy)(struct NaClAppThread *natp, uint32_t *stat_loc) = NaClSysWait;
  /* 'dummy' is not actually a parameter but this suppresses the warning. */
  UNREFERENCED_PARAMETER(dummy);
}

/* this function was automagically generated */
static int32_t NaClSysWait4Decoder(struct NaClAppThread *natp) {
  #ifdef SYSCALL_TIMING
  int32_t retval;
  clock_t nacl_sys_begin;
  clock_t nacl_sys_finish;
  #endif
  #ifdef NACL_SYSCALL_TRACE_ENABLED
  struct NaClApp *nap = natp->nap;
  int32_t retval;
#if 1
  unsigned int i = 0;
#endif
  #endif
    struct NaClSysWait4Args {
    uint32_t pid;
    uint32_t stat_loc;
    uint32_t options;
    uint32_t rusage;
  } p;
  if (!NaClCopyInFromUserAndDropLock(natp->nap, &p, natp->usr_syscall_args,
                                     sizeof p)) {
    return -NACL_ABI_EFAULT;
  }


  #ifdef SYSCALL_TIMING
  nacl_syscall_counter++;
  nacl_syscall_invoked_times[NACL_sys_wait4]++;
  nacl_sys_begin = clock();
  retval = NaClSysWait4(natp, (int)  p.pid, (uint32_t *) (uintptr_t) p.stat_loc, (int)  p.options, (void *) (uintptr_t) p.rusage);
  nacl_sys_finish = clock();
  nacl_syscall_execution_time[NACL_sys_wait4] += (double)(nacl_sys_finish - nacl_sys_begin) / CLOCKS_PER_SEC;
  return retval;
  #endif
  #ifdef NACL_SYSCALL_TRACE_ENABLED
  printf("[NaClSysCallInterface] cage id = %d, syscall_num = NACL_sys_wait4 [enter][syscall_depth = %d]\n", nap->cage_id, nacl_syscall_trace_level_counter);
  printf("==> NACL_sys_wait4(");
#if 1
  for (i = 0; i < sizeof(p)/4; i++) {
    printf("%x,", *((uint32_t *)&p+i));
  }
#endif
  printf(")\n");
  nacl_syscall_trace_level_counter++;
  retval = NaClSysWait4(natp, (int)  p.pid, (uint32_t *) (uintptr_t) p.stat_loc, (int)  p.options, (void *) (uintptr_t) p.rusage);
  nacl_syscall_trace_level_counter--;
  printf("[NaClSysCallInterface] cage id = %d, syscall_num = NACL_sys_wait4 [exit][syscall_depth = %d] \n", nap->cage_id, nacl_syscall_trace_level_counter);
  return retval;
  #endif

  return NaClSysWait4(natp, (int)  p.pid, (uint32_t *) (uintptr_t) p.stat_loc, (int)  p.options, (void *) (uintptr_t) p.rusage);

}

/*
 * Check that the function being wrapped has the same type as the type
 * declared in SYSCALL_LIST.
 */
static INLINE void AssertSameType_NaClSysWait4(void) {
  /* This assignment will give an error if the argument types don't match. */
  int32_t (*dummy)(struct NaClAppThread *natp, int pid, uint32_t *stat_loc, int options, void *rusage) = NaClSysWait4;
  /* 'dummy' is not actually a parameter but this suppresses the warning. */
  UNREFERENCED_PARAMETER(dummy);
}

/* this function was automagically generated */
static int32_t NaClSysSigProcMaskDecoder(struct NaClAppThread *natp) {
  #ifdef SYSCALL_TIMING
  int32_t retval;
  clock_t nacl_sys_begin;
  clock_t nacl_sys_finish;
  #endif
  #ifdef NACL_SYSCALL_TRACE_ENABLED
  struct NaClApp *nap = natp->nap;
  int32_t retval;
#if 1
  unsigned int i = 0;
#endif
  #endif
    struct NaClSysSigProcMaskArgs {
    uint32_t how;
    uint32_t set;
    uint32_t oldset;
  } p;
  if (!NaClCopyInFromUserAndDropLock(natp->nap, &p, natp->usr_syscall_args,
                                     sizeof p)) {
    return -NACL_ABI_EFAULT;
  }


  #ifdef SYSCALL_TIMING
  nacl_syscall_counter++;
  nacl_syscall_invoked_times[NACL_sys_sigprocmask]++;
  nacl_sys_begin = clock();
  retval = NaClSysSigProcMask(natp, (int)  p.how, (const void *) (uintptr_t) p.set, (void *) (uintptr_t) p.oldset);
  nacl_sys_finish = clock();
  nacl_syscall_execution_time[NACL_sys_sigprocmask] += (double)(nacl_sys_finish - nacl_sys_begin) / CLOCKS_PER_SEC;
  return retval;
  #endif
  #ifdef NACL_SYSCALL_TRACE_ENABLED
  printf("[NaClSysCallInterface] cage id = %d, syscall_num = NACL_sys_sigprocmask [enter][syscall_depth = %d]\n", nap->cage_id, nacl_syscall_trace_level_counter);
  printf("==> NACL_sys_sigprocmask(");
#if 1
  for (i = 0; i < sizeof(p)/4; i++) {
    printf("%x,", *((uint32_t *)&p+i));
  }
#endif
  printf(")\n");
  nacl_syscall_trace_level_counter++;
  retval = NaClSysSigProcMask(natp, (int)  p.how, (const void *) (uintptr_t) p.set, (void *) (uintptr_t) p.oldset);
  nacl_syscall_trace_level_counter--;
  printf("[NaClSysCallInterface] cage id = %d, syscall_num = NACL_sys_sigprocmask [exit][syscall_depth = %d] \n", nap->cage_id, nacl_syscall_trace_level_counter);
  return retval;
  #endif

  return NaClSysSigProcMask(natp, (int)  p.how, (const void *) (uintptr_t) p.set, (void *) (uintptr_t) p.oldset);

}

/*
 * Check that the function being wrapped has the same type as the type
 * declared in SYSCALL_LIST.
 */
static INLINE void AssertSameType_NaClSysSigProcMask(void) {
  /* This assignment will give an error if the argument types don't match. */
  int32_t (*dummy)(struct NaClAppThread *natp, int how, const void *set, void *oldset) = NaClSysSigProcMask;
  /* 'dummy' is not actually a parameter but this suppresses the warning. */
  UNREFERENCED_PARAMETER(dummy);
}

/* this function was automagically generated */
static int32_t NaClSysLStatDecoder(struct NaClAppThread *natp) {
  #ifdef SYSCALL_TIMING
  int32_t retval;
  clock_t nacl_sys_begin;
  clock_t nacl_sys_finish;
  #endif
  #ifdef NACL_SYSCALL_TRACE_ENABLED
  struct NaClApp *nap = natp->nap;
  int32_t retval;
#if 1
  unsigned int i = 0;
#endif
  #endif
    struct NaClSysLStatArgs {
    uint32_t path;
    uint32_t nasp;
  } p;
  if (!NaClCopyInFromUserAndDropLock(natp->nap, &p, natp->usr_syscall_args,
                                     sizeof p)) {
    return -NACL_ABI_EFAULT;
  }


  #ifdef SYSCALL_TIMING
  nacl_syscall_counter++;
  nacl_syscall_invoked_times[NACL_sys_lstat]++;
  nacl_sys_begin = clock();
  retval = NaClSysLStat(natp, (const char *) (uintptr_t) p.path, (struct nacl_abi_stat *) (uintptr_t) p.nasp);
  nacl_sys_finish = clock();
  nacl_syscall_execution_time[NACL_sys_lstat] += (double)(nacl_sys_finish - nacl_sys_begin) / CLOCKS_PER_SEC;
  return retval;
  #endif
  #ifdef NACL_SYSCALL_TRACE_ENABLED
  printf("[NaClSysCallInterface] cage id = %d, syscall_num = NACL_sys_lstat [enter][syscall_depth = %d]\n", nap->cage_id, nacl_syscall_trace_level_counter);
  printf("==> NACL_sys_lstat(");
#if 1
  for (i = 0; i < sizeof(p)/4; i++) {
    printf("%x,", *((uint32_t *)&p+i));
  }
#endif
  printf(")\n");
  nacl_syscall_trace_level_counter++;
  retval = NaClSysLStat(natp, (const char *) (uintptr_t) p.path, (struct nacl_abi_stat *) (uintptr_t) p.nasp);
  nacl_syscall_trace_level_counter--;
  printf("[NaClSysCallInterface] cage id = %d, syscall_num = NACL_sys_lstat [exit][syscall_depth = %d] \n", nap->cage_id, nacl_syscall_trace_level_counter);
  return retval;
  #endif

  return NaClSysLStat(natp, (const char *) (uintptr_t) p.path, (struct nacl_abi_stat *) (uintptr_t) p.nasp);

}

/*
 * Check that the function being wrapped has the same type as the type
 * declared in SYSCALL_LIST.
 */
static INLINE void AssertSameType_NaClSysLStat(void) {
  /* This assignment will give an error if the argument types don't match. */
  int32_t (*dummy)(struct NaClAppThread *natp, const char *path, struct nacl_abi_stat *nasp) = NaClSysLStat;
  /* 'dummy' is not actually a parameter but this suppresses the warning. */
  UNREFERENCED_PARAMETER(dummy);
}


/* auto generated */

void NaClSyscallTableInit() {
  int i;
  for (i = 0; i < NACL_MAX_SYSCALLS; ++i) {
    nacl_syscall[i].handler = &NaClSysNotImplementedDecoder;
  }

  NaClAddSyscall(NACL_sys_null, &NaClSysNullDecoder);
  NaClAddSyscall(NACL_sys_nameservice, &NaClSysNameServiceDecoder);
  NaClAddSyscall(NACL_sys_dup, &NaClSysDupDecoder);
  NaClAddSyscall(NACL_sys_dup2, &NaClSysDup2Decoder);
  NaClAddSyscall(NACL_sys_dup3, &NaClSysDup3Decoder);
  NaClAddSyscall(NACL_sys_open, &NaClSysOpenDecoder);
  NaClAddSyscall(NACL_sys_close, &NaClSysCloseDecoder);
  NaClAddSyscall(NACL_sys_read, &NaClSysReadDecoder);
  NaClAddSyscall(NACL_sys_write, &NaClSysWriteDecoder);
  NaClAddSyscall(NACL_sys_lseek, &NaClSysLseekDecoder);
  NaClAddSyscall(NACL_sys_ioctl, &NaClSysIoctlDecoder);
  NaClAddSyscall(NACL_sys_fstat, &NaClSysFstatDecoder);
  NaClAddSyscall(NACL_sys_stat, &NaClSysStatDecoder);
  NaClAddSyscall(NACL_sys_getdents, &NaClSysGetdentsDecoder);
  NaClAddSyscall(NACL_sys_brk, &NaClSysBrkDecoder);
  NaClAddSyscall(NACL_sys_mmap, &NaClSysMmapDecoder);
  NaClAddSyscall(NACL_sys_mprotect, &NaClSysMprotectDecoder);
  NaClAddSyscall(NACL_sys_list_mappings, &NaClSysListMappingsDecoder);
  NaClAddSyscall(NACL_sys_munmap, &NaClSysMunmapDecoder);
  NaClAddSyscall(NACL_sys_exit, &NaClSysExitDecoder);
  NaClAddSyscall(NACL_sys_getpid, &NaClSysGetpidDecoder);
  NaClAddSyscall(NACL_sys_thread_exit, &NaClSysThreadExitDecoder);
  NaClAddSyscall(NACL_sys_gettimeofday, &NaClSysGetTimeOfDayDecoder);
  NaClAddSyscall(NACL_sys_clock, &NaClSysClockDecoder);
  NaClAddSyscall(NACL_sys_nanosleep, &NaClSysNanosleepDecoder);
  NaClAddSyscall(NACL_sys_clock_getres, &NaClSysClockGetResDecoder);
  NaClAddSyscall(NACL_sys_clock_gettime, &NaClSysClockGetTimeDecoder);
  NaClAddSyscall(NACL_sys_mkdir, &NaClSysMkdirDecoder);
  NaClAddSyscall(NACL_sys_rmdir, &NaClSysRmdirDecoder);
  NaClAddSyscall(NACL_sys_chdir, &NaClSysChdirDecoder);
  NaClAddSyscall(NACL_sys_getcwd, &NaClSysGetcwdDecoder);
  NaClAddSyscall(NACL_sys_unlink, &NaClSysUnlinkDecoder);
  NaClAddSyscall(NACL_sys_imc_makeboundsock, &NaClSysImcMakeBoundSockDecoder);
  NaClAddSyscall(NACL_sys_imc_accept, &NaClSysImcAcceptDecoder);
  NaClAddSyscall(NACL_sys_imc_connect, &NaClSysImcConnectDecoder);
  NaClAddSyscall(NACL_sys_imc_sendmsg, &NaClSysImcSendmsgDecoder);
  NaClAddSyscall(NACL_sys_imc_recvmsg, &NaClSysImcRecvmsgDecoder);
  NaClAddSyscall(NACL_sys_imc_mem_obj_create, &NaClSysImcMemObjCreateDecoder);
  NaClAddSyscall(NACL_sys_tls_init, &NaClSysTlsInitDecoder);
  NaClAddSyscall(NACL_sys_thread_create, &NaClSysThreadCreateDecoder);
  NaClAddSyscall(NACL_sys_tls_get, &NaClSysTlsGetDecoder);
  NaClAddSyscall(NACL_sys_thread_nice, &NaClSysThreadNiceDecoder);
  NaClAddSyscall(NACL_sys_mutex_create, &NaClSysMutexCreateDecoder);
  NaClAddSyscall(NACL_sys_mutex_lock, &NaClSysMutexLockDecoder);
  NaClAddSyscall(NACL_sys_mutex_unlock, &NaClSysMutexUnlockDecoder);
  NaClAddSyscall(NACL_sys_mutex_trylock, &NaClSysMutexTrylockDecoder);
  NaClAddSyscall(NACL_sys_cond_create, &NaClSysCondCreateDecoder);
  NaClAddSyscall(NACL_sys_cond_wait, &NaClSysCondWaitDecoder);
  NaClAddSyscall(NACL_sys_cond_signal, &NaClSysCondSignalDecoder);
  NaClAddSyscall(NACL_sys_cond_broadcast, &NaClSysCondBroadcastDecoder);
  NaClAddSyscall(NACL_sys_cond_timed_wait_abs, &NaClSysCondTimedWaitAbsDecoder);
  NaClAddSyscall(NACL_sys_imc_socketpair, &NaClSysImcSocketPairDecoder);
  NaClAddSyscall(NACL_sys_sem_create, &NaClSysSemCreateDecoder);
  NaClAddSyscall(NACL_sys_sem_wait, &NaClSysSemWaitDecoder);
  NaClAddSyscall(NACL_sys_sem_post, &NaClSysSemPostDecoder);
  NaClAddSyscall(NACL_sys_sem_get_value, &NaClSysSemGetValueDecoder);
  NaClAddSyscall(NACL_sys_sched_yield, &NaClSysSchedYieldDecoder);
  NaClAddSyscall(NACL_sys_sysconf, &NaClSysSysconfDecoder);
  NaClAddSyscall(NACL_sys_dyncode_create, &NaClSysDyncodeCreateDecoder);
  NaClAddSyscall(NACL_sys_dyncode_modify, &NaClSysDyncodeModifyDecoder);
  NaClAddSyscall(NACL_sys_dyncode_delete, &NaClSysDyncodeDeleteDecoder);
  NaClAddSyscall(NACL_sys_second_tls_set, &NaClSysSecondTlsSetDecoder);
  NaClAddSyscall(NACL_sys_second_tls_get, &NaClSysSecondTlsGetDecoder);
  NaClAddSyscall(NACL_sys_exception_handler, &NaClSysExceptionHandlerDecoder);
  NaClAddSyscall(NACL_sys_exception_stack, &NaClSysExceptionStackDecoder);
  NaClAddSyscall(NACL_sys_exception_clear_flag, &NaClSysExceptionClearFlagDecoder);
  NaClAddSyscall(NACL_sys_test_infoleak, &NaClSysTestInfoLeakDecoder);
  NaClAddSyscall(NACL_sys_test_crash, &NaClSysTestCrashDecoder);
  NaClAddSyscall(NACL_sys_lind_syscall, &NaClSysLindSyscallDecoder);
  NaClAddSyscall(NACL_sys_fork, &NaClSysForkDecoder);
  NaClAddSyscall(NACL_sys_execv, &NaClSysExecvDecoder);
  NaClAddSyscall(NACL_sys_execve, &NaClSysExecveDecoder);
  NaClAddSyscall(NACL_sys_pipe, &NaClSysPipeDecoder);
  NaClAddSyscall(NACL_sys_pipe2, &NaClSysPipe2Decoder);
  NaClAddSyscall(NACL_sys_getppid, &NaClSysGetppidDecoder);
  NaClAddSyscall(NACL_sys_waitpid, &NaClSysWaitpidDecoder);
  NaClAddSyscall(NACL_sys_wait, &NaClSysWaitDecoder);
  NaClAddSyscall(NACL_sys_wait4, &NaClSysWait4Decoder);
  NaClAddSyscall(NACL_sys_sigprocmask, &NaClSysSigProcMaskDecoder);
  NaClAddSyscall(NACL_sys_lstat, &NaClSysLStatDecoder);
}

