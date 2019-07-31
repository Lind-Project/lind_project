/*
 * Copyright (c) 2012 The Native Client Authors. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

/*
 * NaCl Server Runtime user thread state.
 */

#include <string.h>

#include "native_client/src/shared/platform/aligned_malloc.h"
#include "native_client/src/shared/platform/nacl_check.h"
#include "native_client/src/shared/platform/nacl_exit.h"
#include "native_client/src/shared/platform/nacl_sync_checked.h"

#include "native_client/src/trusted/service_runtime/arch/sel_ldr_arch.h"
#include "native_client/src/trusted/service_runtime/dyn_array.h"
#include "native_client/src/trusted/service_runtime/nacl_app.h"
#include "native_client/src/trusted/service_runtime/nacl_desc_effector_ldr.h"
#include "native_client/src/trusted/service_runtime/nacl_globals.h"
#include "native_client/src/trusted/service_runtime/nacl_stack_safety.h"
#include "native_client/src/trusted/service_runtime/nacl_switch_to_app.h"
#include "native_client/src/trusted/service_runtime/nacl_syscall_common.h"
#include "native_client/src/trusted/service_runtime/nacl_tls.h"
#include "native_client/src/trusted/service_runtime/osx/mach_thread_map.h"

#include "native_client/src/include/win/mman.h"
#include "native_client/src/trusted/service_runtime/load_file.h"
#include "native_client/src/trusted/service_runtime/sel_memory.h"

#include "native_client/src/trusted/desc/nacl_desc_io.h"
#include "native_client/src/shared/platform/lind_platform.h"
#include "native_client/src/trusted/service_runtime/include/bits/mman.h"
#include "native_client/src/trusted/service_runtime/include/sys/fcntl.h"


/*
 * always points at original program context
 *
 * -jp
 */
struct NaClThreadContext *master_ctx;


/*
 * dynamically allocate and initilize a copy
 * of the parents NaClApp structure which is
 * used in NaClSysFork()
 */
struct NaClApp *NaClChildNapCtor(struct NaClApp *nap) {
  struct NaClApp *nap_child = NaClAlignedMalloc(sizeof(*nap_child), __alignof(struct NaClApp));
  struct NaClApp *nap_master = ((struct NaClAppThread *)master_ctx)->nap;
  struct NaClApp *nap_parent = nap;
  struct NaClApp *nap_arr[] = {nap_master, nap_parent};
  NaClErrorCode *mod_status = NULL;

  CHECK(nap_master);
  CHECK(nap_parent);
  CHECK(nap_child);

  NaClLog(1, "%s\n", "Entered NaClChildNapCtor()");
  memset(nap_child, 0, sizeof(*nap_child));
  if (!NaClAppCtor(nap_child)) {
    NaClLog(LOG_FATAL, "%s\n", "Failed to initialize fork child nap");
  }
  mod_status = &nap_child->module_load_status;
  nap_child->argc = nap_parent->argc;
  nap_child->argv = nap_parent->argv;
  nap_child->binary = nap_parent->binary;
  nap_child->clean_environ = nap->clean_environ;
  nap_child->nacl_file = nap_parent->nacl_file ? nap_parent->nacl_file : LD_FILE;
  nap_child->enable_exception_handling = nap_parent->enable_exception_handling;
  nap_child->validator_stub_out_mode = nap_parent->validator_stub_out_mode;
  nap_child->ignore_validator_result = nap_parent->ignore_validator_result;
  nap_child->skip_validator = nap_parent->skip_validator;
  nap_child->user_entry_pt = nap_parent->user_entry_pt;
  nap_child->parent_id = nap_parent->cage_id;
  nap_child->parent = nap_parent;
  nap_child->master = nap_master;
  nap_child->in_fork = 0;

  /* avoid incrementing child count twice */
  if (nap_master == nap_parent) {
    nap_arr[0] = NULL;
  }

  /* don't lock master twice */
  NaClXMutexLock(&nap_master->children_mu);
  if (nap_parent != nap_master) {
    NaClXMutexLock(&nap_parent->children_mu);
  }
  /*
   * increment fork generation count and generate child
   * cage_id (both master and parent mutexes need to be held
   */
  InitializeCage(nap_child, nap_master->cage_id + ++fork_num);
  /* store cage_ids in both master and parent to provide redundancy and avoid orphans */
  for (size_t i = 0; i < sizeof(nap_arr) / sizeof(*nap_arr); i++) {
    if (!nap_arr[i]) {
      continue;
    }
    NaClLog(1, "[nap %d] incrementing num_children\n", nap_arr[i]->cage_id);
    nap_arr[i]->children_ids[nap_arr[i]->num_children++] = nap_child->cage_id;
    if (nap_arr[i]->num_children > CHILD_NUM_MAX) {
      NaClLog(LOG_FATAL, "[nap %u] child_idx > %d\n", nap_arr[i]->cage_id, CHILD_NUM_MAX);
    }
    if (!DynArraySet(&nap_arr[i]->children, nap_child->cage_id, nap_child)) {
      NaClLog(LOG_FATAL, "[nap %u] failed to add cage_id %d\n", nap_arr[i]->cage_id, nap_child->cage_id);
    }
    NaClLog(1, "[nap %d] new child count: %d\n", nap_arr[i]->cage_id, nap_arr[i]->num_children);
  }
  /* don't unlock master twice */
  NaClXMutexUnlock(&nap_master->children_mu);
  if (nap_parent != nap_master) {
    NaClXMutexUnlock(&nap_parent->children_mu);
  }

  NaClAppInitialDescriptorHookup(nap_child);
  NaClLog(1, "fork_num = %d, cage_id = %d\n", fork_num, nap_child->cage_id);
  if ((*mod_status = NaClAppLoadFileFromFilename(nap_child, nap_child->nacl_file)) != LOAD_OK) {
    NaClLog(1, "Error while loading \"%s\": %s\n", nap_child->nacl_file, NaClErrorString(*mod_status));
    NaClLog(LOG_FATAL, "%s\n%s\n",
                       "Using the wrong type of nexe (nacl-x86-32 on an x86-64 or vice versa) ",
                       "or a corrupt nexe file may be responsible for this error.");
  }

  if ((*mod_status = NaClAppPrepareToLaunch(nap_child)) != LOAD_OK) {
    NaClLog(LOG_FATAL, "Failed to prepare child nap_parent for launch\n");
  }
  NaClLog(1, "Loading blob file %s\n", nap_child->nacl_file);
  if (!nap_child->validator->readonly_text_implemented) {
    NaClLog(LOG_FATAL, "fixed_feature_cpu_mode is not supported\n");
  }

  NaClLog(1, "%s\n", "Enabling Fixed-Feature CPU Mode");
  nap_child->fixed_feature_cpu_mode = 1;
  if (!nap_child->validator->FixCPUFeatures(nap_child->cpu_features)) {
    NaClLog(LOG_FATAL, "This CPU lacks features required by fixed-function CPU mode.\n");
  }
  if (!NaClAppLaunchServiceThreads(nap_child)) {
    NaClLog(LOG_FATAL, "Launch service threads failed\n");
  }

  /* duplicate file descriptor table */
  NaClXMutexLock(&nap_parent->mu);
  for (int old_fd = nap_child->fd, new_fd = old_fd; old_fd < nap_parent->fd; new_fd = ++old_fd) {
    struct NaClDesc *old_nd;
    old_nd = NaClGetDesc(nap_parent, old_fd);
    if (!old_nd) {
      continue;
    }
    NaClSetDesc(nap_child, new_fd, old_nd);
    fd_cage_table[nap_child->cage_id][nap_child->fd++] = new_fd;
    NaClLog(1, "NaClGetDesc() copied parent fd [%d] to child fd [%d]\n", old_fd, nap_child->fd - 1);
  }
  NaClXMutexUnlock(&nap_parent->mu);

  return nap_child;
}

void WINAPI NaClAppForkThreadLauncher(void *state) {
  struct NaClAppThread *natp = (struct NaClAppThread *) state;
  struct NaClApp *nap = natp->nap;
  struct NaClThreadContext *context = &natp->user;
  uint32_t thread_idx;
  nacl_reg_t secure_stack_ptr;

  NaClLog(1, "%s\n", "NaClAppForkThreadLauncher: entered");

  NaClSignalStackRegister(natp->signal_stack);

  NaClLog(1, "     natp  = 0x%016"NACL_PRIxPTR"\n", (uintptr_t)natp);
  NaClLog(1, " prog_ctr  = 0x%016"NACL_PRIxNACL_REG"\n", natp->user.prog_ctr);
  NaClLog(1, "stack_ptr  = 0x%016"NACL_PRIxPTR"\n", NaClGetThreadCtxSp(&natp->user));

  thread_idx = NaClGetThreadIdx(natp);
  CHECK(thread_idx > 0 && thread_idx < NACL_THREAD_MAX);
  NaClTlsSetCurrentThread(natp);
  nacl_user[thread_idx] = &natp->user;
#if NACL_WINDOWS
  nacl_thread_ids[thread_idx] = GetCurrentThreadId();
#elif NACL_OSX
  NaClSetCurrentMachThreadForThreadIndex(thread_idx);
#endif

  /*
   * We have to hold the threads_mu and children_mu locks until
   * after thread_num field in this thread has been initialized.
   * All other threads can only find and examine this natp through
   * the threads table, so the fact that natp is not consistent (no
   * thread_num) will not be visible.
   */
  NaClXMutexLock(&nap->threads_mu);
  NaClXMutexLock(&nap->children_mu);
  nap->num_threads = thread_idx + 1;
  natp->thread_num = thread_idx + 1;
  if (!DynArraySet(&nap->threads, natp->thread_num, natp)) {
    NaClLog(LOG_FATAL, "NaClAddThreadMu: DynArraySet at position %d failed\n", natp->thread_num);
  }
  NaClXMutexUnlock(&nap->threads_mu);
  NaClXMutexUnlock(&nap->children_mu);

  NaClVmHoleThreadStackIsSafe(natp->nap);

  NaClStackSafetyNowOnUntrustedStack();

  /*
   * Notify the debug stub, that a new thread is availible.
   */
  if (natp->nap->debug_stub_callbacks) {
    natp->nap->debug_stub_callbacks->thread_create_hook(natp);
  }

#if !NACL_WINDOWS
  /*
   * Ensure stack alignment.  Stack pointer must be -8 mod 16 when no
   * __m256 objects are passed (8 mod 32 if __m256), after the call.
   * Note the current doc (as of 2009-12-09) at
   *
   *   https://github.com/Lind-Project/native_client/raw/fork_implementation/documentation/x86-64_ABI.pdf
   *
   * is wrong since it claims (%rsp-8) should be 0 mod 16 or mod 32
   * after the call, and it should be (%rsp+8) == 0 mod 16 or 32.
   * Clearly it makes no difference since -8 and 8 are the same mod
   * 16, but there is a difference when mod 32.
   *
   * This is not suitable for Windows because we do not reserve 32
   * bytes for the shadow space.
   */
  secure_stack_ptr = NaClGetStackPtr();
  NaClLog(1, "NaClStartThreadInApp: secure stack:   0x%"NACL_PRIxNACL_REG"\n",
          secure_stack_ptr);
  secure_stack_ptr = secure_stack_ptr & ~0x1f;
  NaClLog(1, "NaClStartThreadInApp: adjusted stack: 0x%"NACL_PRIxNACL_REG"\n",
          secure_stack_ptr);
  natp->user.trusted_stack_ptr = secure_stack_ptr;
#endif

  NaClLog(1, "NaClStackThreadInApp: user stack: 0x%"NACL_PRIxPTR"\n",
          NaClGetThreadCtxSp(context));
  NaClLog(1, "%s\n", "NaClStartThreadInApp: switching to untrusted code");

  NaClLog(1, "[NaClAppThreadLauncher] Nap %d is ready to launch! child registers: \n", nap->cage_id);
  NaClLogThreadContext(natp);
  NaClAppThreadPrintInfo(natp);
  CHECK(thread_idx == nacl_user[thread_idx]->tls_idx);

  /*
   * After this NaClAppThreadSetSuspendState() call, we should not
   * claim any mutexes, otherwise we risk deadlock.
   */
  NaClAppThreadSetSuspendState(natp, NACL_APP_THREAD_TRUSTED, NACL_APP_THREAD_UNTRUSTED);

#if NACL_WINDOWS
  /* This sets up a stack containing a return address that has unwind info. */
  NaClSwitchSavingStackPtr(context, &context->trusted_stack_ptr, NaClSwitchToApp);
#else
  NaClSwitchToApp(natp);
#endif
}

void WINAPI NaClAppThreadLauncher(void *state) {
  struct NaClAppThread *natp = (struct NaClAppThread *) state;
  uint32_t thread_idx;
  NaClLog(4, "NaClAppThreadLauncher: entered\n");

  NaClSignalStackRegister(natp->signal_stack);

  NaClLog(4, "     natp  = 0x%016"NACL_PRIxPTR"\n", (uintptr_t)natp);
  NaClLog(4, " prog_ctr  = 0x%016"NACL_PRIxNACL_REG"\n", natp->user.prog_ctr);
  NaClLog(4, "stack_ptr  = 0x%016"NACL_PRIxPTR"\n",
          NaClGetThreadCtxSp(&natp->user));

  thread_idx = NaClGetThreadIdx(natp);
  CHECK(0 < thread_idx);
  CHECK(thread_idx < NACL_THREAD_MAX);
  NaClTlsSetCurrentThread(natp);
  nacl_user[thread_idx] = &natp->user;
#if NACL_WINDOWS
  nacl_thread_ids[thread_idx] = GetCurrentThreadId();
#elif NACL_OSX
  NaClSetCurrentMachThreadForThreadIndex(thread_idx);
#endif

  /*
   * We have to hold the threads_mu lock until after thread_num field
   * in this thread has been initialized.  All other threads can only
   * find and examine this natp through the threads table, so the fact
   * that natp is not consistent (no thread_num) will not be visible.
   */
  NaClXMutexLock(&natp->nap->threads_mu);
  natp->thread_num = NaClAddThreadMu(natp->nap, natp);
  NaClXMutexUnlock(&natp->nap->threads_mu);

  NaClVmHoleThreadStackIsSafe(natp->nap);

  NaClStackSafetyNowOnUntrustedStack();

  /*
   * Notify the debug stub, that a new thread is availible.
   */
  if (NULL != natp->nap->debug_stub_callbacks) {
    natp->nap->debug_stub_callbacks->thread_create_hook(natp);
  }

  /*
   * After this NaClAppThreadSetSuspendState() call, we should not
   * claim any mutexes, otherwise we risk deadlock.
   */
  NaClAppThreadSetSuspendState(natp, NACL_APP_THREAD_TRUSTED,
                               NACL_APP_THREAD_UNTRUSTED);

  NaClLog(1, "%s\n", "[NaCl Main Loader] User program about to start running inside the cage!");
  NaClStartThreadInApp(natp, natp->user.prog_ctr);
}

static INLINE int GetChildIdx(const volatile sig_atomic_t *id_list, int nmemb, int cage_id) {
  int ret;
  /* return the index if match found */
  for (ret = 0; ret < nmemb; ret++) {
    if (cage_id == id_list[ret]) {
      return ret;
    }
  }
  /* otherwise return an error value */
  return -1;
}

/*
 * preconditions:
 * * natp must be thread_self(), called while holding no locks.
 */
void NaClAppThreadTeardown(struct NaClAppThread *natp) {
  struct NaClApp  *nap = natp->nap;
  struct NaClApp  *nap_master = NULL;
  struct NaClApp  *nap_parent = nap->parent;
  size_t          thread_idx;
  int             list_idx;

  if (master_ctx) {
    nap_master = ((struct NaClAppThread *)master_ctx)->nap;
  }

  /*
   * mark this thread as dead; doesn't matter if some other thread is
   * asking us to commit suicide.
   */
  NaClLog(1, "[NaClAppThreadTeardown] cage id: %d\n", nap->cage_id);

    /* remove self from parent's list of children */
  if (nap_master && nap_parent) {
    struct NaClApp *nap_arr[] = {nap_master, nap_parent};
    /* avoid incrementing child count twice */
    if (nap_master == nap_parent) {
      nap_arr[0] = NULL;
    }
    /* don't lock master twice */
    NaClXMutexLock(&nap_master->children_mu);
    if (nap_parent != nap_master) {
      NaClXMutexLock(&nap_parent->children_mu);
    }
    for (size_t i = 0; i < sizeof(nap_arr) / sizeof(*nap_arr); i++) {
      if (!nap_arr[i]) {
        continue;
      }
      list_idx = GetChildIdx(nap_arr[i]->children_ids, nap_arr[i]->num_children, nap->cage_id);
      switch (list_idx) {
      case -1:
        NaClLog(1, "[parent %d] not found in id list: cage_id = %d\n", nap_arr[i]->cage_id, nap->cage_id);
        break;
      default:
        nap_arr[i]->num_children--;
        nap_arr[i]->children_ids[list_idx] = 0;
        NaClLog(1, "[parent %d] new child count: %d\n", nap_arr[i]->cage_id, nap_arr[i]->num_children);
        if (!DynArraySet(&nap_arr[i]->children, nap->cage_id, NULL)) {
          NaClLog(1, "[parent %d] list removal failed: cage_id = %d\n", nap_arr[i]->cage_id, nap->cage_id);
        }
      }
      NaClXCondVarBroadcast(&nap_arr[i]->children_cv);
    }
    /* don't unlock master twice */
    NaClXMutexUnlock(&nap_master->children_mu);
    if (nap_parent != nap_master) {
      NaClXMutexUnlock(&nap_parent->children_mu);
    }
  }

  /* wait for master thread */
  if (nap_master && nap != nap_master) {
    NaClXMutexLock(&nap_master->children_mu);
    NaClLog(1, "Master children count: %d\n", nap_master->num_children);
    while (nap_master->num_children > 0) {
      NaClXCondVarWait(&nap_master->children_cv, &nap_master->children_mu);
    }
    NaClXCondVarBroadcast(&nap_master->children_cv);
    NaClXMutexUnlock(&nap_master->children_mu);
  }

  if (nap->debug_stub_callbacks) {
    NaClLog(3, " notifying the debug stub of the thread exit\n");
    /*
     * This must happen before deallocating the ID natp->thread_num.
     * We have the invariant that debug stub lock should be acquired before
     * nap->threads_mu lock. Hence we must not hold threads_mu lock while
     * calling debug stub hooks.
     */
    nap->debug_stub_callbacks->thread_exit_hook(natp);
  }

  NaClLog(3, " getting thread table lock\n");
  NaClXMutexLock(&nap->threads_mu);
  NaClLog(3, " getting thread lock\n");
  NaClXMutexLock(&natp->mu);

  /*
   * Remove ourselves from the ldt-indexed global tables.  The ldt
   * entry is released as part of NaClAppThreadDelete(), and if
   * another thread is immediately created (from some other running
   * thread) we want to be sure that any ldt-based lookups will not
   * reach this dying thread's data.
   */
  thread_idx = NaClGetThreadIdx(natp);

  /*
   * On x86-64 and ARM, clearing nacl_user entry ensures that we will
   * fault if another syscall is made with this thread_idx.  In
   * particular, thread_idx 0 is never used.
   */
  nacl_user[thread_idx] = NULL;
#if NACL_WINDOWS
  nacl_thread_ids[thread_idx] = 0;
#elif NACL_OSX
  NaClClearMachThreadForThreadIndex(thread_idx);
#endif
  /*
   * Unset the TLS variable so that if a crash occurs during thread
   * teardown, the signal handler does not dereference a dangling
   * NaClAppThread pointer.
   */
  NaClTlsSetCurrentThread(NULL);

  NaClLog(3, " removing thread from thread table\n");
  /* Deallocate the ID natp->thread_num. */
  NaClRemoveThreadMu(nap, natp->thread_num);
  NaClLog(3, " unlocking thread\n");
  NaClXMutexUnlock(&natp->mu);
  NaClLog(3, " unlocking thread table\n");
  NaClXMutexUnlock(&nap->threads_mu);
  NaClLog(3, " unregistering signal stack\n");
  NaClSignalStackUnregister();
  NaClLog(3, " freeing thread object\n");
  NaClAppThreadDelete(natp);
  NaClLog(3, " NaClThreadExit\n");

  NaClThreadExit();
  NaClLog(LOG_FATAL, "NaClAppThreadTeardown: NaClThreadExit() should not return\n");
  /* NOTREACHED */
}

struct NaClAppThread *NaClAppThreadMake(struct NaClApp *nap,
                                        uintptr_t      usr_entry,
                                        uintptr_t      usr_stack_ptr,
                                        uint32_t       user_tls1,
                                        uint32_t       user_tls2) {
  struct NaClAppThread *natp;
  uint32_t tls_idx;

  natp = NaClAlignedMalloc(sizeof(*natp), __alignof(struct NaClAppThread));
  if (!natp) {
    return NULL;
  }

  NaClLog(4, "         natp = 0x%016"NACL_PRIxPTR"\n", (uintptr_t) natp);
  NaClLog(4, "          nap = 0x%016"NACL_PRIxPTR"\n", (uintptr_t) nap);
  NaClLog(4, "    usr_entry = 0x%016"NACL_PRIxPTR"\n", usr_entry);
  NaClLog(4, "usr_stack_ptr = 0x%016"NACL_PRIxPTR"\n", usr_stack_ptr);

  /*
   * Set these early, in case NaClTlsAllocate() wants to examine them.
   */
  natp->nap = nap;

  natp->thread_num = -1;  /* illegal index */
  natp->host_thread_is_defined = 0;
  memset(&natp->host_thread, 0, sizeof(natp->host_thread));

  /*
   * Even though we don't know what segment base/range should gs/r9/nacl_tls_idx
   * select, we still need one, since it identifies the thread when we context
   * switch back.  This use of a dummy tls is only needed for the main thread,
   * which is expected to invoke the tls_init syscall from its crt code (before
   * main or much of libc can run).  Other threads are spawned with the thread
   * pointer address as a parameter.
   */
  tls_idx = NaClTlsAllocate(natp);
  if (NACL_TLS_INDEX_INVALID == tls_idx) {
    NaClLog(LOG_ERROR, "No tls for thread, num_thread %d\n", nap->num_threads);
    goto cleanup_free;
  }

  NaClThreadContextCtor(&natp->user, nap, usr_entry, usr_stack_ptr, tls_idx);

  NaClTlsSetTlsValue1(natp, user_tls1);
  NaClTlsSetTlsValue2(natp, user_tls2);

  natp->signal_stack = NULL;
  natp->exception_stack = 0;
  natp->exception_flag = 0;

  if (!NaClMutexCtor(&natp->mu)) {
    goto cleanup_free;
  }

  if (!NaClSignalStackAllocate(&natp->signal_stack)) {
    goto cleanup_mu;
  }

  if (!NaClMutexCtor(&natp->suspend_mu)) {
    goto cleanup_mu;
  }
  natp->suspend_state = NACL_APP_THREAD_TRUSTED;
  natp->suspended_registers = NULL;
  natp->fault_signal = 0;

  natp->dynamic_delete_generation = 0;
  return natp;

 cleanup_mu:
  NaClMutexDtor(&natp->mu);
  if (NULL != natp->signal_stack) {
    NaClSignalStackFree(&natp->signal_stack);
    natp->signal_stack = NULL;
  }
 cleanup_free:
  NaClAlignedFree(natp);
  return NULL;
}

int NaClAppForkThreadSpawn(struct NaClApp           *nap_parent,
                           struct NaClAppThread     *natp_parent,
                           struct NaClApp           *nap_child,
                           uintptr_t                usr_entry,
                           uintptr_t                usr_stack_ptr,
                           uint32_t                 user_tls1,
                           uint32_t                 user_tls2) {
  void *stack_ptr_parent;
  void *stack_ptr_child;
  size_t stack_ptr_offset;
  size_t base_ptr_offset;
  struct NaClAppThread *natp_child;
  struct NaClThreadContext child_ctx;
  struct NaClThreadContext parent_ctx;
  static THREAD int ignored_ret;

  if (!nap_parent->running) {
    return 0;
  }

  NaClXMutexLock(&nap_parent->mu);
  NaClXMutexLock(&nap_child->mu);

  /* guard against extra spawned instances */
  if (nap_child->in_fork) {
    goto already_running;
  }
  nap_child->in_fork = 1;

  /* make a copy of parent thread context */
  parent_ctx = natp_parent->user;

  /*
   * make space to copy the parent stack
   */
  nap_child->stack_size = nap_parent->stack_size;
  stack_ptr_parent = (void *)NaClUserToSysAddr(nap_parent, NaClGetInitialStackTop(nap_parent));
  stack_ptr_child = (void *)NaClUserToSysAddr(nap_child, NaClGetInitialStackTop(nap_child));
  stack_ptr_offset = parent_ctx.rsp - (uintptr_t)stack_ptr_parent;
  base_ptr_offset = parent_ctx.rbp - (uintptr_t)stack_ptr_parent;
  usr_stack_ptr = NaClSysToUserStackAddr(nap_child, (uintptr_t)stack_ptr_child);
  natp_child = NaClAppThreadMake(nap_child, usr_entry, usr_stack_ptr, user_tls1, user_tls2);

  if (!natp_child) {
    return 0;
  }

  /* copy parent page tables and execution context */
  child_ctx = natp_child->user;
  NaClCopyExecutionContext(nap_parent, nap_child);
  NaClLog(1, "fork_num: [%d], child cage_id: [%d], parent cage id: [%d]\n",
          fork_num,
          nap_child->cage_id,
          nap_parent->cage_id);
  NaClLog(1, "%s\n", "Thread context of child before copy");
  NaClLogThreadContext(natp_child);
  natp_child->user = natp_parent->user;
  NaClLog(1, "%s\n", "Thread context of child after copy");
  NaClLogThreadContext(natp_child);

  /*
   * adjust trampolines and %rip
   */
  nap_child->mem_start = child_ctx.r15;
  natp_child->user.r15 = nap_child->mem_start;
  natp_child->user.rsp = (uintptr_t)stack_ptr_child + stack_ptr_offset;
  natp_child->user.rbp = (uintptr_t)stack_ptr_child + base_ptr_offset;
  natp_child->user.sysret = 0;

/* examine arbitrary stack values */
#if defined(_DEBUG)
# define NUM_STACK_VALS 16
# define OUTPUT_FMT "0x%016lx"
# define TYPE_TO_EXAMINE uintptr_t
# define EXAMINE_ADDR(TYPE, FMT, ADDR)                                                             \
        do {                                                                                       \
          unsigned char *addr = (unsigned char *)(ADDR);                                           \
          UNREFERENCED_PARAMETER(addr);                                                            \
          NaClLog(2, "[Memory] Memory addr:                   %p\n", (void *)addr);                \
          NaClLog(2, "[Memory] Memory content (byte-swapped): " FMT "\n", (TYPE)OBJ_REP_64(addr)); \
          NaClLog(2, "[Memory] Memory content (raw):          " FMT "\n", *(TYPE *)addr);          \
        } while (0)
  for (size_t i = 0; i < NUM_STACK_VALS; i++) {
    NaClLog(2, "child_stack[%zu]:\n", i);
    EXAMINE_ADDR(TYPE_TO_EXAMINE, OUTPUT_FMT, (TYPE_TO_EXAMINE *)stack_ptr_child + i);
    NaClLog(2, "parent_stack[%zu]:\n", i);
    EXAMINE_ADDR(TYPE_TO_EXAMINE, OUTPUT_FMT, (TYPE_TO_EXAMINE *)stack_ptr_parent + i);
  }
  for (size_t i = 0; i < NUM_STACK_VALS; i++) {
    uintptr_t child_addr = (uintptr_t)((TYPE_TO_EXAMINE *)natp_child->user.rsp + i);
    uintptr_t parent_addr = (uintptr_t)((TYPE_TO_EXAMINE *)parent_ctx.rsp + i);
    NaClLog(2, "child_rsp[%zu]:\n", i);
    EXAMINE_ADDR(TYPE_TO_EXAMINE, OUTPUT_FMT, child_addr);
    NaClLog(2, "parent_rsp[%zu]:\n", i);
    EXAMINE_ADDR(TYPE_TO_EXAMINE, OUTPUT_FMT, parent_addr);
  }
# undef NUM_STACK_VALS
# undef OUTPUT_FMT
# undef TYPE_TO_EXAMINE
# undef EXAMINE_ADDR
#endif /* defined(_DEBUG) */

  /*
   * setup TLS slot in the global nacl_user array
   */
  natp_child->user.tls_idx = nap_child->cage_id;
  if (nacl_user[natp_child->user.tls_idx]) {
    NaClLog(1, "nacl_user[%u] not NULL (%p)\n)",
            natp_child->user.tls_idx,
            (void *)nacl_user[natp_child->user.tls_idx]);
    goto already_running;
  }
  nacl_user[natp_child->user.tls_idx] = &natp_child->user;
  NaClTlsSetTlsValue1(natp_child, user_tls1);
  NaClTlsSetTlsValue2(natp_child, user_tls2);

  /*
   * We set host_thread_is_defined assuming, for now, that
   * NaClThreadCtor() will succeed.
   */
  natp_child->host_thread_is_defined = 1;

  NaClXCondVarBroadcast(&nap_parent->cv);
  NaClXMutexUnlock(&nap_parent->mu);
  NaClXMutexUnlock(&nap_child->mu);

  /* TODO: figure out a better way to avoid extra instance spawns -jp */
  NaClThreadYield();
  NaClXMutexLock(&nap_child->mu);
  nap_child->in_fork = 0;
  NaClXMutexUnlock(&nap_child->mu);

  if (!NaClThreadCtor(&natp_child->host_thread, NaClAppForkThreadLauncher, natp_child, NACL_KERN_STACK_SIZE)) {
    /*
    * No other thread saw the NaClAppThread, so it is OK that
    * host_thread was not initialized despite host_thread_is_defined
    * being set.
    */
    natp_child->host_thread_is_defined = 0;
    NaClAppThreadDelete(natp_child);
    return 0;
  }

  return 1;

already_running:
    NaClXCondVarBroadcast(&nap_parent->cv);
    NaClXMutexUnlock(&nap_parent->mu);
    NaClXMutexUnlock(&nap_child->mu);
    pthread_exit(&ignored_ret);
}

int NaClAppThreadSpawn(struct NaClApp *nap,
                       uintptr_t      usr_entry,
                       uintptr_t      usr_stack_ptr,
                       uint32_t       user_tls1,
                       uint32_t       user_tls2) {
  struct NaClAppThread *natp = NaClAppThreadMake(nap, usr_entry, usr_stack_ptr,
                                                 user_tls1, user_tls2);

  if (!natp) {
    return 0;
  }

  /*
   * save master thread context pointer
   */
  if (nap->cage_id == 1 || !master_ctx) {
    master_ctx = &natp->user;
  }
  nap->parent = NULL;
  nap->master = ((struct NaClAppThread *)master_ctx)->nap;

  /*
   * We set host_thread_is_defined assuming, for now, that
   * NaClThreadCtor() will succeed.
   */
  natp->host_thread_is_defined = 1;
  if (!NaClThreadCtor(&natp->host_thread, NaClAppThreadLauncher, (void *) natp,
                      NACL_KERN_STACK_SIZE)) {
    /*
     * No other thread saw the NaClAppThread, so it is OK that
     * host_thread was not initialized despite host_thread_is_defined
     * being set.
     */
    natp->host_thread_is_defined = 0;
    NaClAppThreadDelete(natp);
    return 0;
  }
  return 1;
}

/*
 * preconditions:
 *  * natp must _not_ be running
 */
void NaClAppThreadDelete(struct NaClAppThread *natp) {
  if (natp->host_thread_is_defined) {
    NaClThreadDtor(&natp->host_thread);
  }
  free(natp->suspended_registers);
  NaClMutexDtor(&natp->suspend_mu);
  NaClSignalStackFree(natp->signal_stack);
  natp->signal_stack = NULL;
  NaClTlsFree(natp);
  NaClMutexDtor(&natp->mu);
  NaClAlignedFree(natp);
}

void NaClAppThreadPrintInfo(struct NaClAppThread *natp) {
  NaClLog(1, "[NaClAppThreadPrintInfo] "
          "cage id = %d, prog_ctr = %#lx, new_prog_ctr = %#lx, sysret = %#lx\n",
          natp->nap->cage_id,
          (unsigned long)natp->user.prog_ctr,
          (unsigned long)natp->user.new_prog_ctr,
          (unsigned long)natp->user.sysret);
}
