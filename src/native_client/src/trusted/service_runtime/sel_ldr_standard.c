/*
 * Copyright (c) 2012 The Native Client Authors. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

/*
 * NaCl Simple/secure ELF loader (NaCl SEL).
 */

#include "native_client/src/include/portability.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "native_client/src/include/elf_constants.h"
#include "native_client/src/include/elf.h"
#include "native_client/src/include/nacl_macros.h"
#include "native_client/src/include/win/mman.h"
#include "native_client/src/shared/platform/nacl_check.h"
#include "native_client/src/shared/platform/nacl_log.h"
#include "native_client/src/shared/platform/nacl_sync_checked.h"
#include "native_client/src/shared/platform/nacl_time.h"
#include "native_client/src/shared/platform/lind_platform.h"

#include "native_client/src/shared/srpc/nacl_srpc.h"

#include "native_client/src/trusted/manifest_name_service_proxy/manifest_proxy.h"
#include "native_client/src/trusted/perf_counter/nacl_perf_counter.h"

#include "native_client/src/trusted/reverse_service/reverse_control_rpc.h"

#include "native_client/src/trusted/service_runtime/include/sys/errno.h"
#include "native_client/src/trusted/service_runtime/include/sys/fcntl.h"

#include "native_client/src/trusted/service_runtime/arch/sel_ldr_arch.h"
#include "native_client/src/trusted/service_runtime/elf_util.h"
#include "native_client/src/trusted/service_runtime/nacl_app_thread.h"
#include "native_client/src/trusted/service_runtime/nacl_kernel_service.h"
#include "native_client/src/trusted/service_runtime/nacl_signal.h"
#include "native_client/src/trusted/service_runtime/nacl_switch_to_app.h"
#include "native_client/src/trusted/service_runtime/nacl_syscall_common.h"
#include "native_client/src/trusted/service_runtime/nacl_text.h"
#include "native_client/src/trusted/service_runtime/sel_ldr.h"
#include "native_client/src/trusted/service_runtime/sel_ldr_thread_interface.h"
#include "native_client/src/trusted/service_runtime/sel_memory.h"
#include "native_client/src/trusted/service_runtime/sel_util.h"
#include "native_client/src/trusted/service_runtime/sel_addrspace.h"

/*
 * Fill from static_text_end to end of that page with halt
 * instruction, which is at least NACL_HALT_LEN in size when no
 * dynamic text is present.  Does not touch dynamic text region, which
 * should be pre-filled with HLTs.
 *
 * By adding NACL_HALT_SLED_SIZE, we ensure that the code region ends
 * with HLTs, just in case the CPU has a bug in which it fails to
 * check for running off the end of the x86 code segment.
 */
void NaClFillEndOfTextRegion(struct NaClApp *nap) {
  size_t page_pad;

  /*
   * NOTE: make sure we are not silently overwriting data.  It is the
   * toolchain's responsibility to ensure that a NACL_HALT_SLED_SIZE
   * gap exists.
   */
  if (0 != nap->data_start &&
      nap->static_text_end + NACL_HALT_SLED_SIZE >
      NaClTruncAllocPage(nap->data_start)) {
    NaClLog(LOG_FATAL, "Missing gap between text and data for halt_sled\n");
  }
  if (0 != nap->rodata_start &&
      nap->static_text_end + NACL_HALT_SLED_SIZE > nap->rodata_start) {
    NaClLog(LOG_FATAL, "Missing gap between text and rodata for halt_sled\n");
  }

  if (NULL == nap->text_shm) {
    /*
     * No dynamic text exists.  Space for NACL_HALT_SLED_SIZE must
     * exist.
     */
    page_pad = (NaClRoundAllocPage(nap->static_text_end + NACL_HALT_SLED_SIZE)
                - nap->static_text_end);
    CHECK(page_pad >= NACL_HALT_SLED_SIZE);
    CHECK(page_pad < NACL_MAP_PAGESIZE + NACL_HALT_SLED_SIZE);
  } else {
    /*
     * Dynamic text exists; the halt sled resides in the dynamic text
     * region, so all we need to do here is to round out the last
     * static text page with HLT instructions.  It doesn't matter if
     * the size of this region is smaller than NACL_HALT_SLED_SIZE --
     * this is just to fully initialize the page, rather than (later)
     * decoding/validating zero-filled memory as instructions.
     */
    page_pad = NaClRoundAllocPage(nap->static_text_end) - nap->static_text_end;
  }

  NaClLog(4,
          "Filling with halts: %08"NACL_PRIxPTR", %08"NACL_PRIxS" bytes\n",
          nap->mem_start + nap->static_text_end,
          page_pad);

  NaClFillMemoryRegionWithHalt((void *)(nap->mem_start + nap->static_text_end),
                               page_pad);

  nap->static_text_end += page_pad;
}

/*
 * Basic address space layout sanity check.
 */
NaClErrorCode NaClCheckAddressSpaceLayoutSanity(struct NaClApp *nap,
                                                uintptr_t rodata_end,
                                                uintptr_t data_end,
                                                uintptr_t max_vaddr) {
  if (0 != nap->data_start) {
    if (data_end != max_vaddr) {
      NaClLog(LOG_INFO, "data segment is not last\n");
      return LOAD_DATA_NOT_LAST_SEGMENT;
    }
  } else if (0 != nap->rodata_start) {
    if (NaClRoundAllocPage(rodata_end) != max_vaddr) {
      /*
       * This should be unreachable, but we include it just for
       * completeness.
       *
       * Here is why it is unreachable:
       *
       * NaClPhdrChecks checks the test segment starting address.  The
       * only allowed loaded segments are text, data, and rodata.
       * Thus unless the rodata is in the trampoline region, it must
       * be after the text.  And NaClElfImageValidateProgramHeaders
       * ensures that all segments start after the trampoline region.
       */
      NaClLog(LOG_INFO, "no data segment, but rodata segment is not last\n");
      return LOAD_NO_DATA_BUT_RODATA_NOT_LAST_SEGMENT;
    }
  }
  if (0 != nap->rodata_start && 0 != nap->data_start) {
    if (rodata_end > NaClTruncAllocPage(nap->data_start)) {
      NaClLog(LOG_INFO, "rodata_overlaps data.\n");
      return LOAD_RODATA_OVERLAPS_DATA;
    }
  }
  if (0 != nap->rodata_start) {
    if (NaClRoundAllocPage(NaClEndOfStaticText(nap)) > nap->rodata_start) {
      return LOAD_TEXT_OVERLAPS_RODATA;
    }
  } else if (0 != nap->data_start) {
    if (NaClRoundAllocPage(NaClEndOfStaticText(nap)) >
        NaClTruncAllocPage(nap->data_start)) {
      return LOAD_TEXT_OVERLAPS_DATA;
    }
  }
  if (0 != nap->rodata_start &&
      NaClRoundAllocPage(nap->rodata_start) != nap->rodata_start) {
    NaClLog(LOG_INFO, "rodata_start not a multiple of allocation size\n");
    return LOAD_BAD_RODATA_ALIGNMENT;
  }
  return LOAD_OK;
}

NaClErrorCode NaClAppLoadFileAslr(struct NaClDesc *ndp,
                                  struct NaClApp *nap,
                                  enum NaClAslrMode aslr_mode) {
  NaClErrorCode       ret = LOAD_INTERNAL;
  NaClErrorCode       subret = LOAD_INTERNAL;
  uintptr_t           rodata_end;
  uintptr_t           data_end;
  uintptr_t           max_vaddr;
  struct NaClElfImage *image = NULL;
  struct NaClPerfCounter  time_load_file;
  struct NaClElfImageInfo info;

  NaClPerfCounterCtor(&time_load_file, "NaClAppLoadFile");

  /* NACL_MAX_ADDR_BITS < 32 */
  if (nap->addr_bits > NACL_MAX_ADDR_BITS) {
    ret = LOAD_ADDR_SPACE_TOO_BIG;
    goto done;
  }

  nap->stack_size = NaClRoundAllocPage(nap->stack_size);

  /* temporay object will be deleted at end of function */
  image = NaClElfImageNew(ndp, &subret);
  if (NULL == image || LOAD_OK != subret) {
    ret = subret;
    goto done;
  }

  subret = NaClElfImageValidateProgramHeaders(image,
                                              nap->addr_bits,
                                              &info);
  if (LOAD_OK != subret) {
    ret = subret;
    goto done;
  }

  if (nap->initial_nexe_max_code_bytes != 0) {
    size_t code_segment_size = info.static_text_end - NACL_TRAMPOLINE_END;
    if (code_segment_size > nap->initial_nexe_max_code_bytes) {
      NaClLog(LOG_ERROR, "NaClAppLoadFileAslr: "
              "Code segment size (%"NACL_PRIdS" bytes) exceeds limit (%"
              NACL_PRId32" bytes)\n",
              code_segment_size, nap->initial_nexe_max_code_bytes);
      ret = LOAD_CODE_SEGMENT_TOO_LARGE;
      goto done;
    }
  }

  nap->static_text_end = info.static_text_end;
  nap->rodata_start = info.rodata_start;
  rodata_end = info.rodata_end;
  nap->data_start = info.data_start;
  data_end = info.data_end;
  max_vaddr = info.max_vaddr;

  if (0 == nap->data_start) {
    if (0 == nap->rodata_start) {
      if (NaClRoundAllocPage(max_vaddr) - max_vaddr < NACL_HALT_SLED_SIZE) {
        /*
         * if no rodata and no data, we make sure that there is space for
         * the halt sled.
         */
        max_vaddr += NACL_MAP_PAGESIZE;
      }
    } else {
      /*
       * no data, but there is rodata.  this means max_vaddr is just
       * where rodata ends.  this might not be at an allocation
       * boundary, and in this the page would not be writable.  round
       * max_vaddr up to the next allocation boundary so that bss will
       * be at the next writable region.
       */
      ;
    }
    max_vaddr = NaClRoundAllocPage(max_vaddr);
  }
  /*
   * max_vaddr -- the break or the boundary between data (initialized
   * and bss) and the address space hole -- does not have to be at a
   * page boundary.
   *
   * Memory allocation will use NaClRoundPage(nap->break_addr), but
   * the system notion of break is always an exact address.  Even
   * though we must allocate and make accessible multiples of pages,
   * the linux-style brk system call (which returns current break on
   * failure) permits a non-aligned address as argument.
   */
  nap->break_addr = max_vaddr;
  nap->data_end = max_vaddr;

  NaClLog(4, "Values from NaClElfImageValidateProgramHeaders:\n");
  NaClLog(4, "rodata_start = 0x%08"NACL_PRIxPTR"\n", nap->rodata_start);
  NaClLog(4, "rodata_end   = 0x%08"NACL_PRIxPTR"\n", rodata_end);
  NaClLog(4, "data_start   = 0x%08"NACL_PRIxPTR"\n", nap->data_start);
  NaClLog(4, "data_end     = 0x%08"NACL_PRIxPTR"\n", data_end);
  NaClLog(4, "max_vaddr    = 0x%08"NACL_PRIxPTR"\n", max_vaddr);

  /* We now support only one bundle size.  */
  nap->bundle_size = NACL_INSTR_BLOCK_SIZE;

  nap->initial_entry_pt = NaClElfImageGetEntryPoint(image);
  NaClLogAddressSpaceLayout(nap);

  if (!NaClAddrIsValidEntryPt(nap, nap->initial_entry_pt)) {
    ret = LOAD_BAD_ENTRY;
    goto done;
  }

  subret = NaClCheckAddressSpaceLayoutSanity(nap, rodata_end, data_end,
                                             max_vaddr);

  if (LOAD_OK != subret) {
    ret = subret;
    goto done;
  }

  NaClLog(2, "Allocating address space\n");
  NaClPerfCounterMark(&time_load_file, "PreAllocAddrSpace");
  NaClPerfCounterIntervalLast(&time_load_file);
  subret = NaClAllocAddrSpaceAslr(nap, aslr_mode);
  NaClPerfCounterMark(&time_load_file,
                      NACL_PERF_IMPORTANT_PREFIX "AllocAddrSpace");
  NaClPerfCounterIntervalLast(&time_load_file);
  if (LOAD_OK != subret) {
    ret = subret;
    goto done;
  }

  /*
   * Make sure the static image pages are marked writable before we try
   * to write them.
   */
  NaClLog(2, "Loading into memory\n");
  ret = NaClMprotect((void *) (nap->mem_start + NACL_TRAMPOLINE_START),
                     NaClRoundAllocPage(nap->data_end) - NACL_TRAMPOLINE_START,
                     PROT_READ | PROT_WRITE);
  if (0 != ret) {
    NaClLog(LOG_FATAL,
            "NaClAppLoadFile: Failed to make image pages writable. "
            "Error code 0x%x\n",
            ret);
  }
  subret = NaClElfImageLoad(image, ndp, nap);
  if (LOAD_OK != subret) {
    ret = subret;
    goto done;
  }

  /*
   * NB: mem_map object has been initialized, but is empty.
   * NaClMakeDynamicTextShared does not touch it.
   *
   * NaClMakeDynamicTextShared also fills the dynamic memory region
   * with the architecture-specific halt instruction.  If/when we use
   * memory mapping to save paging space for the dynamic region and
   * lazily halt fill the memory as the pages become
   * readable/executable, we must make sure that the *last*
   * NACL_MAP_PAGESIZE chunk is nonetheless mapped and written with
   * halts.
   */
  NaClLog(2,
          ("Replacing gap between static text and"
           " (ro)data with shareable memory\n"));
  subret = NaClMakeDynamicTextShared(nap);
  NaClPerfCounterMark(&time_load_file,
                      NACL_PERF_IMPORTANT_PREFIX "MakeDynText");
  NaClPerfCounterIntervalLast(&time_load_file);
  if (LOAD_OK != subret) {
    ret = subret;
    goto done;
  }
  /*
   * NaClFillEndOfTextRegion will fill with halt instructions the
   * padding space after the static text region.
   *
   * Shm-backed dynamic text space was filled with halt instructions
   * in NaClMakeDynamicTextShared.  This extends to the rodata.  For
   * non-shm-backed text space, this extend to the next page (and not
   * allocation page).  static_text_end is updated to include the
   * padding.
   */
  NaClFillEndOfTextRegion(nap);

  if (nap->main_exe_prevalidated) {
    NaClLog(2, "Main executable segment hit validation cache and mapped in,"
            " skipping validation.\n");
    subret = LOAD_OK;
  } else {
    NaClLog(2, "Validating image\n");
    subret = NaClValidateImage(nap);
  }
  NaClPerfCounterMark(&time_load_file,
                      NACL_PERF_IMPORTANT_PREFIX "ValidateImg");
  NaClPerfCounterIntervalLast(&time_load_file);
  if (LOAD_OK != subret) {
    ret = subret;
    goto done;
  }
  NaClLog(2, "Initializing arch switcher\n");
  NaClInitSwitchToApp(nap);

  NaClLog(2, "Installing trampoline\n");
  NaClLoadTrampoline(nap);

  NaClLog(2, "Installing springboard\n");
  NaClLoadSpringboard(nap);
  /*
   * NaClMemoryProtection also initializes the mem_map w/ information
   * about the memory pages and their current protection value.
   *
   * The contents of the dynamic text region will get remapped as
   * non-writable.
   */
  NaClLog(2, "Applying memory protection\n");
  subret = NaClMemoryProtection(nap);
  if (LOAD_OK != subret) {
    ret = subret;
    goto done;
  }

  NaClLog(2, "NaClAppLoadFile done; ");
  NaClLogAddressSpaceLayout(nap);
  ret = LOAD_OK;
done:
  NaClElfImageDelete(image);
  NaClPerfCounterMark(&time_load_file, "EndLoadFile");
  NaClPerfCounterIntervalTotal(&time_load_file);
  return ret;
}

NaClErrorCode NaClAppLoadFile(struct NaClDesc *ndp,
                              struct NaClApp *nap) {
  return NaClAppLoadFileAslr(ndp, nap, NACL_ENABLE_ASLR);
}

NaClErrorCode NaClAppLoadFileDynamically(struct NaClApp *nap,
                                         struct NaClDesc *ndp,
                                         struct NaClValidationMetadata *metadata) {
  struct NaClElfImage *image = NULL;
  NaClErrorCode ret = LOAD_INTERNAL;

  image = NaClElfImageNew(ndp, &ret);
  if (NULL == image || LOAD_OK != ret) {
    goto done;
  }
  ret = NaClElfImageLoadDynamically(image, nap, ndp, metadata);
  if (LOAD_OK != ret) {
    goto done;
  }
  nap->user_entry_pt = nap->initial_entry_pt;
  nap->initial_entry_pt = NaClElfImageGetEntryPoint(image);

 done:
  NaClElfImageDelete(image);
  return ret;
}

int NaClAddrIsValidEntryPt(struct NaClApp *nap,
                           uintptr_t      addr) {
#if defined(NACL_TARGET_ARM_THUMB2_MODE)
  /*
   * The entry point needs to be aligned 0xe mod 0x10.  But ARM processors need
   * an odd target address to indicate that the target is in thumb mode.  When
   * control is actually transferred, it is to the target address minus one.
   */
  if (0xf != (addr & (nap->bundle_size - 1))) {
    return 0;
  }
#else
  if (0 != (addr & (nap->bundle_size - 1))) {
    return 0;
  }
#endif

  return addr < nap->static_text_end;
}

int NaClAppLaunchServiceThreads(struct NaClApp *nap) {
  struct NaClManifestProxy                    *manifest_proxy = NULL;
  struct NaClKernelService                    *kernel_service = NULL;
  int                                         rv = 0;
  enum NaClReverseChannelInitializationState  init_state;

  NaClNameServiceLaunch(nap->name_service);

  kernel_service = (struct NaClKernelService *) malloc(sizeof *kernel_service);
  if (NULL == kernel_service) {
    NaClLog(LOG_ERROR,
            "NaClAppLaunchServiceThreads: No memory for kern service\n");
    goto done;
  }

  if (!NaClKernelServiceCtor(kernel_service,
                             NaClAddrSpSquattingThreadIfFactoryFunction,
                             (void *) nap,
                             nap)) {
    NaClLog(LOG_ERROR,
            "NaClAppLaunchServiceThreads: KernServiceCtor failed\n");
    free(kernel_service);
    kernel_service = NULL;
    goto done;
  }

  if (!NaClSimpleServiceStartServiceThread((struct NaClSimpleService *)
                                           kernel_service)) {
    NaClLog(LOG_ERROR,
            "NaClAppLaunchServiceThreads: KernService start service failed\n");
    goto done;
  }
  /*
   * NB: StartServiceThread grabbed another reference to kernel_service,
   * used by the service thread.  Closing the connection capability
   * should cause the service thread to shut down and in turn release
   * that reference.
   */

  /*
   * The locking here isn't really needed.  Here is why:
   * reverse_channel_initialized is written in reverse_setup RPC
   * handler of the secure command channel RPC handler thread.  and
   * the RPC order requires that the plugin invoke reverse_setup prior
   * to invoking start_module, so there will have been plenty of other
   * synchronization operations to force cache coherency
   * (module_may_start, for example, is set in the cache of the secure
   * channel RPC handler (in start_module) and read by the main
   * thread, and the synchronization operations needed to propagate
   * its value properly suffices to propagate
   * reverse_channel_initialized as well).  However, reading it while
   * holding a lock is more obviously correct for tools like tsan.
   * Due to the RPC order, it is impossible for
   * reverse_channel_initialized to get set after the unlock and
   * before the if test.
   */
  NaClXMutexLock(&nap->mu);
  /*
   * If no reverse_setup RPC was made, then we do not set up a
   * manifest proxy.  Otherwise, we make sure that the reverse channel
   * setup is done, so that the application can actually use
   * reverse-channel-based services such as the manifest proxy.
   */
  if (NACL_REVERSE_CHANNEL_UNINITIALIZED !=
      (init_state = nap->reverse_channel_initialization_state)) {
    while (NACL_REVERSE_CHANNEL_INITIALIZED !=
      (init_state = nap->reverse_channel_initialization_state)) {
      NaClXCondVarWait(&nap->cv, &nap->mu);
    }
  }
  NaClXMutexUnlock(&nap->mu);
  if (NACL_REVERSE_CHANNEL_INITIALIZED != init_state) {
    NaClLog(3,
            ("NaClAppLaunchServiceThreads: no reverse channel;"
             " launched kernel services.\n"));
    NaClLog(3,
            ("NaClAppLaunchServiceThreads: no reverse channel;"
             " NOT launching manifest proxy.\n"));
    nap->kernel_service = kernel_service;
    kernel_service = NULL;

    rv = 1;
    goto done;
  }

  /*
   * Allocate/construct the manifest proxy without grabbing global
   * locks.
   */
  NaClLog(3, "NaClAppLaunchServiceThreads: launching manifest proxy\n");

  /*
   * ReverseClientSetup RPC should be done via the command channel
   * prior to the load_module / start_module RPCs, and
   *  occurs after that, so checking
   * nap->reverse_client suffices for determining whether the proxy is
   * exporting reverse services.
   */
  manifest_proxy = (struct NaClManifestProxy *) malloc(sizeof *manifest_proxy);
  if (NULL == manifest_proxy) {
    NaClLog(LOG_ERROR, "No memory for manifest proxy\n");
    NaClDescUnref(kernel_service->base.bound_and_cap[1]);
    goto done;
  }
  if (!NaClManifestProxyCtor(manifest_proxy,
                             NaClAddrSpSquattingThreadIfFactoryFunction,
                             (void *) nap,
                             nap)) {
    NaClLog(LOG_ERROR, "ManifestProxyCtor failed\n");
    /* do not leave a non-NULL pointer to a not-fully constructed object */
    free(manifest_proxy);
    manifest_proxy = NULL;
    NaClDescUnref(kernel_service->base.bound_and_cap[1]);
    goto done;
  }

  /*
   * NaClSimpleServiceStartServiceThread requires the nap->mu lock.
   */
  if (!NaClSimpleServiceStartServiceThread((struct NaClSimpleService *)
                                           manifest_proxy)) {
    NaClLog(LOG_ERROR, "ManifestProxy start service failed\n");
    NaClDescUnref(kernel_service->base.bound_and_cap[1]);
    goto done;
  }

  NaClXMutexLock(&nap->mu);
  CHECK(NULL == nap->manifest_proxy);
  CHECK(NULL == nap->kernel_service);

  nap->manifest_proxy = manifest_proxy;
  manifest_proxy = NULL;
  nap->kernel_service = kernel_service;
  kernel_service = NULL;
  NaClXMutexUnlock(&nap->mu);
  rv = 1;

done:
  NaClXMutexLock(&nap->mu);
  if (NULL != nap->manifest_proxy) {
    NaClLog(3,
            ("NaClAppLaunchServiceThreads: adding manifest proxy to"
             " name service\n"));
    (*NACL_VTBL(NaClNameService, nap->name_service)->
     CreateDescEntry)(nap->name_service,
                      "ManifestNameService", NACL_ABI_O_RDWR,
                      NaClDescRef(nap->manifest_proxy->base.bound_and_cap[1]));
  }
  if (NULL != nap->kernel_service) {
    NaClLog(3,
            ("NaClAppLaunchServiceThreads: adding kernel service to"
             " name service\n"));
    (*NACL_VTBL(NaClNameService, nap->name_service)->
     CreateDescEntry)(nap->name_service,
                      "KernelService", NACL_ABI_O_RDWR,
                      NaClDescRef(nap->kernel_service->base.bound_and_cap[1]));
  }

  NaClXMutexUnlock(&nap->mu);

  /*
   * Single exit path.
   *
   * Error cleanup invariant.  No service thread should be running
   * (modulo asynchronous shutdown).  Automatic variables refer to
   * fully constructed objects if non-NULL, and when ownership is
   * transferred to the NaClApp object the corresponding automatic
   * variable is set to NULL.
   */
  NaClRefCountSafeUnref((struct NaClRefCount *) manifest_proxy);
  NaClRefCountSafeUnref((struct NaClRefCount *) kernel_service);
  return rv;
}

int NaClReportExitStatus(struct NaClApp *nap, int exit_status) {
  int           rv = 0;
  NaClSrpcError rpc_result;

  NaClXMutexLock(&nap->mu);
  /*
   * If several threads are exiting/reporting signals at once, we should
   * let only one thread to pass through. This way we can use exit code
   * without synchronization once we know that running==0.
   */
  if (!nap->running) {
    NaClXMutexUnlock(&nap->mu);
    return 0;
  }

  if (NACL_REVERSE_CHANNEL_INITIALIZED ==
      nap->reverse_channel_initialization_state) {
    /* TODO(halyavin) update NaCl plugin to accept full exit_status value */
    if (NACL_ABI_WIFEXITED(exit_status)) {
      rpc_result = NaClSrpcInvokeBySignature(&nap->reverse_channel,
                                             NACL_REVERSE_CONTROL_REPORT_STATUS,
                                             NACL_ABI_WEXITSTATUS(exit_status));
      rv = NACL_SRPC_RESULT_OK == rpc_result;
    }
    /*
     * Due to cross-repository checkins, the Cr-side might not yet
     * implement this RPC.  We return whether shutdown was reported.
     */
  }
  nap->exit_status = exit_status;
  nap->running = 0;
  NaClXCondVarSignal(&nap->cv);

  NaClXMutexUnlock(&nap->mu);

  return rv;
}

uintptr_t NaClGetInitialStackTop(struct NaClApp *nap) {
  /*
   * We keep the top of useful memory a page below the top of the
   * sandbox region so that compilers can do tricks like computing a
   * base register of sp + constant and then using a
   * register-minus-constant addressing mode, which comes up at least
   * on ARM where the compiler is trying to optimize given the limited
   * size of immediate offsets available.  The maximum such negative
   * constant on ARM will be -4095, but we use page size (64k) for
   * good measure and do it on all machines just for uniformity.
   */
  return ((uintptr_t) 1U << nap->addr_bits) - NACL_MAP_PAGESIZE;
}

/*
 * preconditions:
 *  * argc is the length of the argv array
 *  * envv may be NULL (this happens on MacOS/Cocoa and in tests)
 *  * if envv is non-NULL it is 'consistent', null terminated etc.
 */
int NaClCreateMainThread(struct NaClApp     *nap,
                         int                argc,
                         char               **argv,
                         char const *const  *envv) {
  /*
   * Compute size of string tables for argv and envv
   */
  int                   retval;
  int                   envc;
  size_t                size;
  int                   auxv_entries;
  size_t                ptr_tbl_size;
  int                   i;
  uint32_t              *p;
  char                  *strp;
  size_t                *argv_len;
  size_t                *envv_len;
  uintptr_t             stack_ptr;

  CHECK(argc >= 0);
  CHECK(argv || !argc);

  retval = 0;
  size = 0;
  envc = 0;

  /* count number of environment strings */
  for (char const *const *pp = envv; pp && *pp; ++pp) {
    envc++;
  }
  /* allocate space to hold length of vectors */
  argv_len = !argc ? NULL : malloc(argc * sizeof *argv_len);
  envv_len = !envc ? NULL : malloc(envc * sizeof *envv_len);
  /* `argvv_len = malloc()` failed or `argc == 0` */
  if (!argv_len) {
    goto cleanup;
  }
  /* `envv_len = malloc()` failed (`envc == 0` is not an error) */
  if (!envv_len && envc) {
    goto cleanup;
  }

  /*
   * The following two loops cannot overflow.  The reason for this is
   * that they are counting the number of bytes used to hold the
   * NUL-terminated strings that comprise the argv and envv tables.
   * If the entire address space consisted of just those strings, then
   * the size variable would overflow; however, since there's the code
   * space required to hold the code below (and we are not targetting
   * Harvard architecture machines), at least one page holds code, not
   * data.  We are assuming that the caller is non-adversarial and the
   * code does not look like string data....
   */
  for (i = 0; i < argc && argv && argv[i]; i++) {
    argv_len[i] = strlen(argv[i]) + 1;
    size += argv_len[i];
  }
  for (i = 0; i < envc && envv && envv[i]; i++) {
    envv_len[i] = strlen(envv[i]) + 1;
    size += envv_len[i];
  }

  /*
   * NaCl modules are ILP32, so the argv, envv pointers, as well as
   * the terminating NULL pointers at the end of the argv/envv tables,
   * are 32-bit values.  We also have the auxv to take into account.
   *
   * The argv and envv pointer tables came from trusted code and is
   * part of memory.  Thus, by the same argument above, adding in
   * "ptr_tbl_size" cannot possibly overflow the "size" variable since
   * it is a size_t object.  However, the extra pointers for auxv and
   * the space for argv could cause an overflow.  The fact that we
   * used stack to get here etc means that ptr_tbl_size could not have
   * overflowed.
   *
   * NB: the underlying OS would have limited the amount of space used
   * for argv and envv -- on linux, it is ARG_MAX, or 128KB -- and
   * hence the overflow check is for obvious audibility rather than
   * for correctness.
   */
  auxv_entries = 1;
  if (nap->user_entry_pt) {
    auxv_entries++;
  }
  ptr_tbl_size = (((NACL_STACK_GETS_ARG ? 1 : 0)
                  + (3 + argc + 1 + envc + 1 + auxv_entries * 2))
                  * sizeof(uint32_t));

  if (SIZE_MAX - size < ptr_tbl_size) {
    NaClLog(LOG_WARNING, "NaClCreateMainThread() ptr_tbl_size caused copy to overflow!?!\n");
    goto cleanup;
  }
  size += ptr_tbl_size;

  size = (size + NACL_STACK_ALIGN_MASK) & ~NACL_STACK_ALIGN_MASK;

  if (size > nap->stack_size) {
    goto cleanup;
  }

  /*
   * Write strings and char * arrays to stack.
   */
  stack_ptr = NaClUserToSysAddrRange(nap, NaClGetInitialStackTop(nap) - size,
                                     size);
  if (stack_ptr == kNaClBadAddress) {
    goto cleanup;
  }

  NaClLog(2, "setting stack to : %016"NACL_PRIxPTR"\n", stack_ptr);

  VCHECK(!(stack_ptr & NACL_STACK_ALIGN_MASK),
         ("stack_ptr not aligned: %016"NACL_PRIxPTR"\n", stack_ptr));

  p = (uint32_t *)stack_ptr;
  strp = (char *)stack_ptr + ptr_tbl_size;

  /*
   * For x86-32, we push an initial argument that is the address of
   * the main argument block.  For other machines, this is passed
   * in a register and that's set in NaClStartThreadInApp.
   */
  if (NACL_STACK_GETS_ARG) {
    uint32_t *argloc = p++;
    *argloc = (uint32_t)NaClSysToUser(nap, (uintptr_t) p);
  }

  *p++ = 0;  /* Cleanup function pointer, always NULL.  */
  *p++ = envc;
  *p++ = argc;

  for (i = 0; i < argc && argv && argv[i]; i++) {
    *p++ = (uint32_t) NaClSysToUser(nap, (uintptr_t)strp);
    NaClLog(2, "copying arg %d  %p -> %p\n",
            i, (void *)argv[i], (void *)strp);
    snprintf(strp, ARG_LIMIT, "%s", argv[i]);
    strp += argv_len[i];
  }
  *p++ = 0;  /* argv[argc] is NULL.  */

  for (i = 0; i < envc && envv && envv[i]; i++) {
    *p++ = (uint32_t) NaClSysToUser(nap, (uintptr_t)strp);
    NaClLog(1, "copying env %d  %p -> %p\n",
            i, (void *)envv[i], (void *)strp);
    snprintf(strp, ARG_LIMIT, "%s", envv[i]);
    strp += envv_len[i];
  }
  *p++ = 0;  /* envp[envc] is NULL.  */

  /* Push an auxv */
  if (nap->user_entry_pt) {
    *p++ = AT_ENTRY;
    *p++ = (uint32_t)nap->user_entry_pt;
  }
  *p++ = AT_NULL;
  *p++ = 0;

  /* TODO: fix failing CHECK() -jp */
  if ((char *)p != (char *)stack_ptr + ptr_tbl_size) {
    NaClLog(1,
            "p (%p) != stack_ptr (%p) + ptr_tbl_size (%#lx) [%#lx]\n",
            (void *)p, (void *)stack_ptr, ptr_tbl_size, stack_ptr + ptr_tbl_size);
  }
  /* CHECK((char *)p == (char *)stack_ptr + ptr_tbl_size); */

  /* now actually spawn the thread */
  NaClXMutexLock(&nap->mu);
  nap->running = 1;
  NaClXMutexUnlock(&nap->mu);

  NaClVmHoleWaitToStartThread(nap);

  /*
   * For x86, we adjust the stack pointer down to push a dummy return
   * address.  This happens after the stack pointer alignment.
   * We avoid the otherwise harmless call for the zero case because
   * _FORTIFY_SOURCE memset can warn about zero-length calls.
   */
  if (NACL_STACK_PAD_BELOW_ALIGN) {
    stack_ptr -= NACL_STACK_PAD_BELOW_ALIGN;
    memset((void *) stack_ptr, 0, NACL_STACK_PAD_BELOW_ALIGN);
  }

  NaClLog(2, "system stack ptr : %016"NACL_PRIxPTR"\n", stack_ptr);
  NaClLog(2, "  user stack ptr : %016"NACL_PRIxPTR"\n",
          NaClSysToUserStackAddr(nap, stack_ptr));

  /* e_entry is user addr */
  retval = NaClAppThreadSpawn(nap,
                              nap->initial_entry_pt,
                              NaClSysToUserStackAddr(nap, stack_ptr),
                              /* user_tls1= */ (uint32_t) nap->break_addr,
                              /* user_tls2= */ 0);

cleanup:
  free(argv_len);
  free(envv_len);

  return retval;
}

int NaClCreateMainForkThread(struct NaClAppThread     *natp_parent,
                             struct NaClApp           *nap_child,
                             int                      argc,
                             char                     **argv,
                             char const *const        *envv) {
  /*
   * Compute size of string tables for argv and envv
   */
  size_t                size;
  size_t                ptr_tbl_size;
  uintptr_t             stack_ptr;
  uint32_t              *p;
  int                   i;
  int                   retval;
  int                   envc;
  int                   auxv_entries;
  char                  *strp;
  size_t                *argv_len;
  size_t                *envv_len;
  static THREAD int     ignored_ret;
  struct NaClApp        *nap_parent;

  CHECK(argc >= 0);
  CHECK(argv || !argc);

  retval = 0;
  size = 0;
  envc = 0;
  nap_parent = natp_parent->nap;

  NaClXMutexLock(&nap_child->mu);

  /* guard against extra spawned instances */
  if (nap_child->running || nap_child->in_fork) {
    goto already_running;
  }
  nap_child->in_fork = 1;

  /* count number of environment strings */
  for (char const *const *pp = envv; pp && *pp; ++pp) {
    envc++;
  }
  /* allocate space to hold length of vectors */
  argv_len = !argc ? NULL : malloc(argc * sizeof *argv_len);
  envv_len = !envc ? NULL : malloc(envc * sizeof *envv_len);
  /* `argvv_len = malloc()` failed or `argc == 0` */
  if (!argv_len) {
    NaClLog(LOG_WARNING, "NaClCreateMainForkThread failed: cage_id %d has argv length 0!\n", nap_child->cage_id);
    goto cleanup;
  }
  /* `envv_len = malloc()` failed (`envc == 0` is not an error) */
  if (!envv_len && envc) {
    NaClLog(LOG_WARNING, "NaClCreateMainForkThread failed: cage_id %d has envv length 0!\n", nap_child->cage_id);
    goto cleanup;
  }

  /*
   * The following two loops cannot overflow.  The reason for this is
   * that they are counting the number of bytes used to hold the
   * NUL-terminated strings that comprise the argv and envv tables.
   * If the entire address space consisted of just those strings, then
   * the size variable would overflow; however, since there's the code
   * space required to hold the code below (and we are not targetting
   * Harvard architecture machines), at least one page holds code, not
   * data.  We are assuming that the caller is non-adversarial and the
   * code does not look like string data....
   */
  for (i = 0; i < argc && argv && argv[i]; i++) {
    argv_len[i] = strlen(argv[i]) + 1;
    size += argv_len[i];
  }
  for (i = 0; i < envc && envv && envv[i]; i++) {
    envv_len[i] = strlen(envv[i]) + 1;
    size += envv_len[i];
  }

  /*
   * NaCl modules are ILP32, so the argv, envv pointers, as well as
   * the terminating NULL pointers at the end of the argv/envv tables,
   * are 32-bit values.  We also have the auxv to take into account.
   *
   * The argv and envv pointer tables came from trusted code and is
   * part of memory.  Thus, by the same argument above, adding in
   * "ptr_tbl_size" cannot possibly overflow the "size" variable since
   * it is a size_t object.  However, the extra pointers for auxv and
   * the space for argv could cause an overflow.  The fact that we
   * used stack to get here etc means that ptr_tbl_size could not have
   * overflowed.
   *
   * NB: the underlying OS would have limited the amount of space used
   * for argv and envv -- on linux, it is ARG_MAX, or 128KB -- and
   * hence the overflow check is for obvious auditability rather than
   * for correctness.
   */
  auxv_entries = 1;
  if (0 != nap_child->user_entry_pt) {
    auxv_entries++;
  }
  ptr_tbl_size = (((NACL_STACK_GETS_ARG ? 1 : 0) +
                   (3 + argc + 1 + envc + 1 + auxv_entries * 2)) *
                  sizeof(uint32_t));

  if (SIZE_T_MAX - size < ptr_tbl_size) {
    NaClLog(LOG_WARNING,
            "NaClCreateMainThread: ptr_tbl_size cause size of"
            " argv / environment copy to overflow!?!\n");
    retval = 0;
    goto cleanup;
  }
  size += ptr_tbl_size;

  size = (size + NACL_STACK_ALIGN_MASK) & ~NACL_STACK_ALIGN_MASK;

  if (size > nap_child->stack_size) {
    NaClLog(LOG_WARNING,
            "NaClCreateMainForkThread failed: cage_id %d stack is too small! [size: %zu > stack_size: %zu]\n",
            nap_child->cage_id,
            size,
            nap_child->stack_size);
    goto cleanup;
  }

  /*
   * Write strings and char * arrays to stack.
   */
  stack_ptr = NaClUserToSysAddrRange(nap_child,
                                     NaClGetInitialStackTop(nap_child) - size,
                                     size);
  if (stack_ptr == kNaClBadAddress) {
    NaClLog(LOG_WARNING, "NaClCreateMainForkThread failed: cage_id %d stack_ptr address bad!\n", nap_child->cage_id);
    goto cleanup;
  }

  NaClLog(2, "setting stack to : %016"NACL_PRIxPTR"\n", stack_ptr);

  VCHECK(!(stack_ptr & NACL_STACK_ALIGN_MASK),
         ("stack_ptr not aligned: %016"NACL_PRIxPTR"\n", stack_ptr));

  p = (uint32_t *)stack_ptr;
  strp = (char *)stack_ptr + ptr_tbl_size;

  /*
   * For x86-32, we push an initial argument that is the address of
   * the main argument block.  For other machines, this is passed
   * in a register and that's set in NaClStartThreadInApp.
   */
  if (NACL_STACK_GETS_ARG) {
    uint32_t *argloc = p++;
    *argloc = (uint32_t) NaClSysToUser(nap_child, (uintptr_t) p);
  }

  *p++ = 0;  /* Cleanup function pointer, always NULL.  */
  *p++ = envc;
  *p++ = argc;

  for (i = 0; i < argc && argv && argv[i]; i++) {
    *p++ = (uint32_t) NaClSysToUser(nap_child, (uintptr_t)strp);
    NaClLog(1, "copying arg %d  %p -> %p\n",
            i, (void *)argv[i], (void *)strp);
    snprintf(strp, ARG_LIMIT, "%s", argv[i]);
    strp += argv_len[i];
  }
  *p++ = 0;  /* argv[argc] is NULL.  */

  for (i = 0; i < envc && envv && envv[i]; i++) {
    *p++ = (uint32_t) NaClSysToUser(nap_child, (uintptr_t)strp);
    NaClLog(1, "copying env %d  %p -> %p\n",
            i, (void *)envv[i], (void *)strp);
    snprintf(strp, ARG_LIMIT, "%s", envv[i]);
    strp += envv_len[i];
  }
  *p++ = 0;  /* envp[envc] is NULL.  */

  /* Push an auxv */
  if (nap_child->user_entry_pt) {
    *p++ = AT_ENTRY;
    *p++ = (uint32_t)nap_child->user_entry_pt;
  }
  *p++ = AT_NULL;
  *p++ = 0;

  /* TODO: fix failing CHECK() -jp */
  if ((char *)p != (char *)stack_ptr + ptr_tbl_size) {
    NaClLog(1,
            "p (%p) != stack_ptr (%p) + ptr_tbl_size (%#lx) [%#lx]\n",
            (void *)p, (void *)stack_ptr, ptr_tbl_size, stack_ptr + ptr_tbl_size);
  }
  /* CHECK((char *)p == (char *)stack_ptr + ptr_tbl_size); */

  /* now actually spawn the thread */
  nap_child->running = 1;
  NaClXCondVarBroadcast(&nap_child->cv);
  NaClXMutexUnlock(&nap_child->mu);

  NaClVmHoleWaitToStartThread(nap_child);

  /*
   * For x86, we adjust the stack pointer down to push a dummy return
   * address.  This happens after the stack pointer alignment.
   * We avoid the otherwise harmless call for the zero case because
   * _FORTIFY_SOURCE memset can warn about zero-length calls.
   */
  if (NACL_STACK_PAD_BELOW_ALIGN) {
    stack_ptr -= NACL_STACK_PAD_BELOW_ALIGN;
    memset((void *)stack_ptr, 0, NACL_STACK_PAD_BELOW_ALIGN);
  }

  NaClLog(1, "   system stack ptr : %016"NACL_PRIxPTR"\n", stack_ptr);
  NaClLog(1, "     user stack ptr : %016"NACL_PRIxPTR"\n", NaClSysToUserStackAddr(nap_child, stack_ptr));
  NaClLog(1, "   initial entry pt : %016"NACL_PRIxPTR"\n", nap_child->initial_entry_pt);
  NaClLog(1, "      user entry pt : %016"NACL_PRIxPTR"\n", nap_child->user_entry_pt);

  /* TODO: figure out a better way to avoid extra instance spawns -jp */
  NaClThreadYield();
  NaClXMutexLock(&nap_child->mu);
  nap_child->in_fork = 0;
  NaClXMutexUnlock(&nap_child->mu);

  /* e_entry is user addr */
  retval = NaClAppForkThreadSpawn(nap_parent,
                                  natp_parent,
                                  nap_child,
                                  nap_child->initial_entry_pt,
                                  NaClSysToUserStackAddr(nap_child, stack_ptr),
                                  (uint32_t)nap_child->break_addr,
                                  0);

cleanup:
  free(argv_len);
  free(envv_len);
  NaClXMutexUnlock(&nap_child->mu);

  return retval;

/* NO RETURN */
already_running:
  NaClXMutexUnlock(&nap_child->mu);
  pthread_exit(&ignored_ret);
}

int NaClWaitForMainThreadToExit(struct NaClApp  *nap) {
  NaClLog(3, "NaClWaitForMainThreadToExit: taking NaClApp lock\n");
  NaClXMutexLock(&nap->mu);
  NaClLog(3, " waiting for exit status\n");
  while (nap->running) {
    NaClXCondVarWait(&nap->cv, &nap->mu);
    NaClLog(3, " wakeup, nap->running %d, nap->exit_status %d\n",
            nap->running, nap->exit_status);
  }
  NaClXMutexUnlock(&nap->mu);
  /*
   * Some thread invoked the exit (exit_group) syscall.
   */

  if (NULL != nap->debug_stub_callbacks) {
    nap->debug_stub_callbacks->process_exit_hook();
  }

  return NACL_ABI_WEXITSTATUS(nap->exit_status);
}

/*
 * stack_ptr is from syscall, so a 32-bit address.
 */
int32_t NaClCreateAdditionalThread(struct NaClApp *nap,
                                   uintptr_t      prog_ctr,
                                   uintptr_t      sys_stack_ptr,
                                   uint32_t       user_tls1,
                                   uint32_t       user_tls2) {
  if (!NaClAppThreadSpawn(nap,
                          prog_ctr,
                          NaClSysToUserStackAddr(nap, sys_stack_ptr),
                          user_tls1,
                          user_tls2)) {
    NaClLog(LOG_WARNING,
            ("NaClCreateAdditionalThread: could not allocate thread."
             "  Returning EAGAIN per POSIX specs.\n"));
    return -NACL_ABI_EAGAIN;
  }
  return 0;
}
