/*
 * Copyright (c) 2012 The Native Client Authors. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

/*
 * NaCl Server Runtime global scoped objects for handling global resources.
 */

#include "native_client/src/shared/platform/nacl_interruptible_mutex.h"
#include "native_client/src/shared/platform/nacl_log.h"
#include "native_client/src/shared/platform/nacl_sync.h"
#include "native_client/src/shared/platform/nacl_sync_checked.h"
#include "native_client/src/shared/platform/nacl_threads.h"
#include "native_client/src/trusted/service_runtime/arch/sel_ldr_arch.h"
#include "native_client/src/trusted/service_runtime/nacl_app.h"
#include "native_client/src/trusted/service_runtime/nacl_app_thread.h"
#include "native_client/src/trusted/service_runtime/nacl_globals.h"
#include "native_client/src/trusted/service_runtime/include/bits/nacl_syscalls.h"

struct NaClThreadContext    *nacl_user[NACL_THREAD_MAX] = {NULL};
#if NACL_WINDOWS
uint32_t                    nacl_thread_ids[NACL_THREAD_MAX] = {0};
#endif

/*
 * Hack for gdb.  This records xlate_base in a place where (1) gdb can find it,
 * and (2) gdb doesn't need debug info (it just needs symbol info).
 */
uintptr_t                   nacl_global_xlate_base;

int nacl_syscall_counter;
int nacl_syscall_trace_level_counter;
int nacl_syscall_invoked_times[NACL_MAX_SYSCALLS];
double nacl_syscall_execution_time[NACL_MAX_SYSCALLS];

void NaClGlobalModuleInit(void) {
  NaClInitGlobals();
}

void NaClGlobalModuleFini(void) { /* no-op */ }
