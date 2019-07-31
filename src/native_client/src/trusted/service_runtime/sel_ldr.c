/*
 * Copyright (c) 2012 The Native Client Authors. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#include <string.h>

/*
 * NaCl Simple/secure ELF loader (NaCl SEL).
 */
#include "native_client/src/include/portability.h"
#include "native_client/src/include/portability_io.h"
#include "native_client/src/include/portability_string.h"
#include "native_client/src/include/nacl_macros.h"

#include "native_client/src/shared/gio/gio.h"
#include "native_client/src/shared/platform/nacl_check.h"
#include "native_client/src/shared/platform/nacl_exit.h"
#include "native_client/src/shared/platform/nacl_log.h"
#include "native_client/src/shared/platform/nacl_sync.h"
#include "native_client/src/shared/platform/nacl_sync_checked.h"
#include "native_client/src/shared/platform/nacl_time.h"
#include "native_client/src/shared/srpc/nacl_srpc.h"

#include "native_client/src/trusted/desc/nacl_desc_base.h"
#include "native_client/src/trusted/desc/nacl_desc_conn_cap.h"
#include "native_client/src/trusted/desc/nacl_desc_imc.h"
#include "native_client/src/trusted/desc/nacl_desc_io.h"
#include "native_client/src/trusted/desc/nrd_xfer.h"
#include "native_client/src/trusted/fault_injection/fault_injection.h"
#include "native_client/src/trusted/fault_injection/test_injection.h"
#include "native_client/src/trusted/gio/gio_nacl_desc.h"
#include "native_client/src/trusted/gio/gio_shm.h"
#include "native_client/src/trusted/interval_multiset/nacl_interval_range_tree_intern.h"
#include "native_client/src/trusted/service_runtime/arch/sel_ldr_arch.h"
#include "native_client/src/trusted/service_runtime/include/bits/mman.h"
#include "native_client/src/trusted/service_runtime/include/bits/nacl_syscalls.h"
#include "native_client/src/trusted/service_runtime/include/sys/fcntl.h"
#include "native_client/src/trusted/service_runtime/include/sys/stat.h"
#include "native_client/src/trusted/service_runtime/include/sys/time.h"
#include "native_client/src/trusted/service_runtime/nacl_app.h"
#include "native_client/src/trusted/service_runtime/nacl_app_thread.h"
#include "native_client/src/trusted/service_runtime/nacl_desc_effector_ldr.h"
#include "native_client/src/trusted/service_runtime/nacl_globals.h"
#include "native_client/src/trusted/service_runtime/nacl_resource.h"
#include "native_client/src/trusted/service_runtime/nacl_reverse_quota_interface.h"
#include "native_client/src/trusted/service_runtime/nacl_switch_to_app.h"
#include "native_client/src/trusted/service_runtime/nacl_syscall_common.h"
#include "native_client/src/trusted/service_runtime/nacl_syscall_handlers.h"
#include "native_client/src/trusted/service_runtime/nacl_text.h"
#include "native_client/src/trusted/service_runtime/nacl_valgrind_hooks.h"
#include "native_client/src/trusted/service_runtime/name_service/default_name_service.h"
#include "native_client/src/trusted/service_runtime/name_service/name_service.h"
#include "native_client/src/trusted/service_runtime/sel_addrspace.h"
#include "native_client/src/trusted/service_runtime/sel_ldr.h"
#include "native_client/src/trusted/service_runtime/sel_memory.h"
#include "native_client/src/trusted/service_runtime/sel_ldr_thread_interface.h"
#include "native_client/src/trusted/simple_service/nacl_simple_rservice.h"
#include "native_client/src/trusted/simple_service/nacl_simple_service.h"
#include "native_client/src/trusted/threading/nacl_thread_interface.h"

double time_counter = 0.0;
double time_start = 0.0;
double time_end = 0.0;

/*
 * `fd_cage_table[cage_id][fd] = real fd`
 *
 * The [fd] idx is the virtual fd visible to the cages.
 *
 * -jp
 */
volatile sig_atomic_t fork_num;
struct Pipe pipe_table[PIPE_NUM_MAX];
int fd_cage_table[CAGING_FD_NUM][CAGING_FD_NUM];
int cached_lib_num;

// yiwen: lookup table for <file_path, mem_addr>
struct CachedLibTable cached_lib_table[CACHED_LIB_NUM_MAX];

static int IsEnvironmentVariableSet(char const *env_name) {
  return !!getenv(env_name);
}

static int ShouldEnableDyncodeSyscalls(void) {
  return !IsEnvironmentVariableSet("NACL_DISABLE_DYNCODE_SYSCALLS");
}

static int ShouldEnableDynamicLoading(void) {
  return !IsEnvironmentVariableSet("NACL_DISABLE_DYNAMIC_LOADING");
}

int NaClAppWithSyscallTableCtor(struct NaClApp               *nap,
                                struct NaClSyscallTableEntry *table) {
  struct NaClDescEffectorLdr  *effp = NULL;

  /* The validation cache will be injected later, if it exists. */
  nap->validation_cache = NULL;

  nap->validator = NaClCreateValidator();

  /* Get the set of features that the CPU we're running on supports. */
  /* These may be adjusted later in sel_main.c for fixed-feature CPU mode. */
  nap->cpu_features = malloc(nap->validator->CPUFeatureSize);
  if (!nap->cpu_features) {
    goto cleanup_none;
  }
  nap->validator->GetCurrentCPUFeatures(nap->cpu_features);
  nap->fixed_feature_cpu_mode = 0;
  nap->addr_bits = NACL_MAX_ADDR_BITS;
  nap->stack_size = NACL_DEFAULT_STACK_MAX;
  nap->initial_nexe_max_code_bytes = 0;
  nap->aux_info = NULL;
  nap->mem_start = 0;

#if NACL_ARCH(NACL_BUILD_ARCH) == NACL_x86 && NACL_BUILD_SUBARCH == 32
  nap->pcrel_thunk = 0;
  nap->pcrel_thunk_end = 0;
#elif NACL_ARCH(NACL_BUILD_ARCH) == NACL_x86 && NACL_BUILD_SUBARCH == 64
  nap->nacl_syscall_addr = 0;
  nap->get_tls_fast_path1_addr = 0;
  nap->get_tls_fast_path2_addr = 0;
#endif

  nap->static_text_end = 0;
  nap->dynamic_text_start = 0;
  nap->dynamic_text_end = 0;
  nap->rodata_start = 0;
  nap->data_start = 0;
  nap->data_end = 0;
  nap->initial_entry_pt = 0;
  nap->user_entry_pt = 0;

  if (!DynArrayCtor(&nap->threads, 2)) {
    goto cleanup_cpu_features;
  }
  if (!DynArrayCtor(&nap->desc_tbl, 2)) {
    goto cleanup_threads;
  }
  if (!DynArrayCtor(&nap->children, 2)) {
    goto cleanup_desc_tbl;
  }
  if (!NaClVmmapCtor(&nap->mem_map)) {
    goto cleanup_children;
  }

  nap->mem_io_regions = malloc(sizeof *nap->mem_io_regions);
  if (!nap->mem_io_regions) {
    goto cleanup_mem_map;
  }

  if (!NaClIntervalRangeTreeCtor((struct NaClIntervalRangeTree *)nap->mem_io_regions)) {
    free(nap->mem_io_regions);
    nap->mem_io_regions = NULL;
    goto cleanup_mem_map;
  }

  effp = malloc(sizeof *effp);
  if (!effp) {
    goto cleanup_mem_io_regions;
  }
  if (!NaClDescEffectorLdrCtor(effp, nap)) {
    goto cleanup_effp_free;
  }
  nap->effp = (struct NaClDescEffector *) effp;
  nap->enable_dyncode_syscalls = ShouldEnableDyncodeSyscalls();
  nap->use_shm_for_dynamic_text = ShouldEnableDynamicLoading();
  nap->text_shm = NULL;

  if (!NaClMutexCtor(&nap->dynamic_load_mutex)) {
    goto cleanup_effp_free;
  }
  if (!NaClMutexCtor(&nap->children_mu)) {
    goto cleanup_dynamic_load_mutex;
  }
  nap->dynamic_page_bitmap = NULL;
  nap->dynamic_regions = NULL;
  nap->num_dynamic_regions = 0;
  nap->dynamic_regions_allocated = 0;
  nap->dynamic_delete_generation = 0;
  nap->dynamic_mapcache_offset = 0;
  nap->dynamic_mapcache_size = 0;
  nap->dynamic_mapcache_ret = 0;
  nap->service_port = NULL;
  nap->service_address = NULL;
  nap->secure_service_port = NULL;
  nap->secure_service_address = NULL;
  nap->bootstrap_channel = NULL;
  nap->secure_service = NULL;
  nap->irt_loaded = 0;
  nap->main_exe_prevalidated = 0;
  nap->manifest_proxy = NULL;
  nap->kernel_service = NULL;
  nap->resource_phase = NACL_RESOURCE_PHASE_START;

  if (!NaClResourceNaClAppInit(&nap->resources, nap)) {
    goto cleanup_dynamic_load_mutex;
  }
  nap->reverse_client = NULL;
  nap->reverse_channel_initialization_state =
      NACL_REVERSE_CHANNEL_UNINITIALIZED;
  if (!NaClMutexCtor(&nap->mu)) {
    goto cleanup_children_mutex;
  }
  if (!NaClCondVarCtor(&nap->cv)) {
    goto cleanup_mu;
  }

#if NACL_WINDOWS
  nap->vm_hole_may_exist = 0;
  nap->threads_launching = 0;
#endif

  nap->syscall_table = table;
  nap->module_load_status = LOAD_STATUS_UNKNOWN;
  nap->module_may_start = 0;  /* only when secure_service != NULL */
  nap->name_service = (struct NaClNameService *) malloc(
      sizeof *nap->name_service);
  if (!nap->name_service) {
    goto cleanup_cv;
  }
  if (!NaClNameServiceCtor(nap->name_service,
                           NaClAddrSpSquattingThreadIfFactoryFunction,
                           (void *) nap)) {
    free(nap->name_service);
    goto cleanup_cv;
  }
  nap->name_service_conn_cap = NaClDescRef(nap->name_service->
                                           base.base.bound_and_cap[1]);
  if (!NaClDefaultNameServiceInit(nap->name_service)) {
    goto cleanup_name_service;
  }

  nap->ignore_validator_result = 0;
  nap->skip_validator = 0;
  nap->validator_stub_out_mode = 0;

  if (IsEnvironmentVariableSet("NACL_DANGEROUS_ENABLE_FILE_ACCESS")) {
    NaClInsecurelyBypassAllAclChecks();
    NaClLog(LOG_INFO, "DANGER: ENABLED FILE ACCESS\n");
  }

  nap->enable_list_mappings = 0;
  if (IsEnvironmentVariableSet("NACL_DANGEROUS_ENABLE_LIST_MAPPINGS")) {
    /*
     * This syscall is not actually know to be dangerous, but is not yet
     * exposed by our public API.
     */
    NaClLog(LOG_INFO, "DANGER: ENABLED LIST_MAPPINGS\n");
    nap->enable_list_mappings = 1;
  }

  if (!NaClMutexCtor(&nap->threads_mu)) {
    goto cleanup_name_service;
  }
  nap->num_threads = 0;
  if (!NaClFastMutexCtor(&nap->desc_mu)) {
    goto cleanup_threads_mu;
  }

  nap->running = 0;
  nap->exit_status = -1;

#if NACL_ARCH(NACL_BUILD_ARCH) == NACL_x86 && NACL_BUILD_SUBARCH == 32
  nap->code_seg_sel = 0;
  nap->data_seg_sel = 0;
#endif

  nap->debug_stub_callbacks = NULL;
  nap->exception_handler = 0;
  if (!NaClMutexCtor(&nap->exception_mu)) {
    goto cleanup_desc_mu;
  }
  nap->enable_exception_handling = 0;
#if NACL_WINDOWS
  nap->debug_exception_handler_state = NACL_DEBUG_EXCEPTION_HANDLER_NOT_STARTED;
  nap->attach_debug_exception_handler_func = NULL;
#endif
  nap->enable_faulted_thread_queue = 0;
  nap->faulted_thread_count = 0;
#if NACL_WINDOWS
  nap->faulted_thread_event = INVALID_HANDLE_VALUE;
#else
  nap->faulted_thread_fd_read = -1;
  nap->faulted_thread_fd_write = -1;
#endif


#if NACL_LINUX || NACL_OSX
  /*
   * Try to pre-cache information that we can't obtain with the outer
   * sandbox on.  If the outer sandbox has already been enabled, this
   * will just set sc_nprocessors_onln to -1, and it is the
   * responsibility of the caller to replace this with a sane value
   * after the Ctor returns.
   */
  nap->sc_nprocessors_onln = sysconf(_SC_NPROCESSORS_ONLN);
#endif

  return 1;

 cleanup_desc_mu:
  NaClFastMutexDtor(&nap->desc_mu);
 cleanup_threads_mu:
  NaClMutexDtor(&nap->threads_mu);
 cleanup_name_service:
  NaClDescUnref(nap->name_service_conn_cap);
  NaClRefCountUnref((struct NaClRefCount *) nap->name_service);
 cleanup_cv:
  NaClCondVarDtor(&nap->cv);
 cleanup_mu:
  NaClMutexDtor(&nap->mu);
 cleanup_children_mutex:
  NaClMutexDtor(&nap->children_mu);
 cleanup_dynamic_load_mutex:
  NaClMutexDtor(&nap->dynamic_load_mutex);
 cleanup_effp_free:
  free(nap->effp);
 cleanup_mem_io_regions:
  NaClIntervalMultisetDelete(nap->mem_io_regions);
  nap->mem_io_regions = NULL;
 cleanup_mem_map:
  NaClVmmapDtor(&nap->mem_map);
 cleanup_children:
  DynArrayDtor(&nap->children);
 cleanup_desc_tbl:
  DynArrayDtor(&nap->desc_tbl);
 cleanup_threads:
  DynArrayDtor(&nap->threads);
 cleanup_cpu_features:
  free(nap->cpu_features);
 cleanup_none:
  return 0;
}

int NaClAppCtor(struct NaClApp *nap) {
  return NaClAppWithSyscallTableCtor(nap, nacl_syscall);
}

/*
 * unaligned little-endian load.  precondition: nbytes should never be
 * more than 8.
 */
static uint64_t NaClLoadMem(uintptr_t addr,
                            size_t    user_nbytes) {
  uint64_t      value = 0;

  CHECK(0 != user_nbytes && user_nbytes <= 8);

  do {
    value = value << 8;
    value |= ((uint8_t *) addr)[--user_nbytes];
  } while (user_nbytes > 0);
  return value;
}

#define GENERIC_LOAD(bits) \
  static uint ## bits ## _t NaClLoad ## bits(uintptr_t addr) { \
    return (uint ## bits ## _t) NaClLoadMem(addr, sizeof (uint ## bits ## _t)); \
  }

#if NACL_TARGET_SUBARCH == 32
GENERIC_LOAD(32)
#endif
GENERIC_LOAD(64)

#undef GENERIC_LOAD

/*
 * unaligned little-endian store
 */
static void NaClStoreMem(uintptr_t  addr,
                         size_t     nbytes,
                         uint64_t   value) {
  size_t i;

  CHECK(nbytes <= 8);

  for (i = 0; i < nbytes; i++) {
    ((uint8_t *) addr)[i] = (uint8_t) value;
    value = value >> 8;
  }
}

#define GENERIC_STORE(bits) \
  static void NaClStore ## bits(uintptr_t addr, \
                                uint ## bits ## _t v) { \
    NaClStoreMem(addr, sizeof (uint ## bits ## _t), v); \
  }

GENERIC_STORE(16)
GENERIC_STORE(32)
GENERIC_STORE(64)

#undef GENERIC_STORE

struct NaClPatchInfo *NaClPatchInfoCtor(struct NaClPatchInfo *self) {
  if (self) {
    memset(self, 0, sizeof *self);
  }
  return self;
}

/*
 * This function is called by NaClLoadTrampoline and NaClLoadSpringboard to
 * patch a single memory location specified in NaClPatchInfo structure.
 */
void  NaClApplyPatchToMemory(struct NaClPatchInfo  *patch) {
  size_t    i;
  size_t    offset;
  int64_t   reloc;
  uintptr_t target_addr;

  memcpy((void *) patch->dst, (void *) patch->src, patch->nbytes);

  reloc = patch->dst - patch->src;


  for (i = 0; i < patch->num_abs64; i++) {
    offset = patch->abs64[i].target - patch->src;
    target_addr = patch->dst + offset;
    NaClStore64(target_addr, patch->abs64[i].value);
  }

  for (i = 0; i < patch->num_abs32; i++) {
    offset = patch->abs32[i].target - patch->src;
    target_addr = patch->dst + offset;
    NaClStore32(target_addr, (uint32_t) patch->abs32[i].value);
  }

  for (i = 0; i < patch->num_abs16; i++) {
    offset = patch->abs16[i].target - patch->src;
    target_addr = patch->dst + offset;
    NaClStore16(target_addr, (uint16_t) patch->abs16[i].value);
  }

  for (i = 0; i < patch->num_rel64; i++) {
    offset = patch->rel64[i] - patch->src;
    target_addr = patch->dst + offset;
    NaClStore64(target_addr, NaClLoad64(target_addr) - reloc);
  }

  /*
   * rel32 is only supported on 32-bit architectures. The range of a relative
   * relocation in untrusted space is +/- 4GB. This can be represented as
   * an unsigned 32-bit value mod 2^32, which is handy on a 32 bit system since
   * all 32-bit pointer arithmetic is implicitly mod 2^32. On a 64 bit system,
   * however, pointer arithmetic is implicitly modulo 2^64, which isn't as
   * helpful for our purposes. We could simulate the 32-bit behavior by
   * explicitly modding all relative addresses by 2^32, but that seems like an
   * expensive way to save a few bytes per reloc.
   */
#if NACL_TARGET_SUBARCH == 32
  for (i = 0; i < patch->num_rel32; i++) {
    offset = patch->rel32[i] - patch->src;
    target_addr = patch->dst + offset;
    NaClStore32(target_addr,
      (uint32_t) NaClLoad32(target_addr) - (int32_t) reloc);
  }
#endif
}


/*
 * Install syscall trampolines at all possible well-formed entry
 * points within the trampoline pages.  Many of these syscalls will
 * correspond to unimplemented system calls and will just abort the
 * program.
 */
void  NaClLoadTrampoline(struct NaClApp *nap) {
  int         num_syscalls;
  int         i;
  uintptr_t   addr;

#if NACL_ARCH(NACL_BUILD_ARCH) == NACL_x86 && NACL_BUILD_SUBARCH == 32
  if (!NaClMakePcrelThunk(nap)) {
    NaClLog(LOG_FATAL, "NaClMakePcrelThunk failed!\n");
  }
#endif
#if NACL_ARCH(NACL_BUILD_ARCH) == NACL_x86 && NACL_BUILD_SUBARCH == 64
  if (!NaClMakeDispatchAddrs(nap)) {
    NaClLog(LOG_FATAL, "NaClMakeDispatchAddrs failed!\n");
  }
#endif
  NaClFillTrampolineRegion(nap);

  /*
   * Do not bother to fill in the contents of page 0, since we make it
   * inaccessible later (see sel_addrspace.c, NaClMemoryProtection)
   * anyway to help detect NULL pointer errors, and we might as well
   * not dirty the page.
   *
   * The last syscall entry point is used for springboard code.
   */
  num_syscalls = ((NACL_TRAMPOLINE_END - NACL_SYSCALL_START_ADDR)
                  / NACL_SYSCALL_BLOCK_SIZE) - 1;

  NaClLog(2, "num_syscalls = %d (0x%x)\n", num_syscalls, num_syscalls);

#if defined(NACL_TARGET_ARM_THUMB2_MODE)
  CHECK(0 != ((nap->user_entry_pt | nap->initial_entry_pt) & 0x1));
  /*
   * Thumb trampolines start 2 bytes before the aligned syscall address used
   * by ordinary ARM.  We initialize this by adding 0xe to the start address
   * of each trampoline.  Because the last start address would actually start
   * into user code above, this allows one fewer trampolines than in ARM.
   */
  for (i = 0, addr = nap->mem_start + NACL_SYSCALL_START_ADDR + 0xe;
       i < num_syscalls - 1;
       ++i, addr += NACL_SYSCALL_BLOCK_SIZE) {
    NaClPatchOneTrampoline(nap, addr);
  }
#else
  for (i = 0, addr = nap->mem_start + NACL_SYSCALL_START_ADDR;
       i < num_syscalls;
       ++i, addr += NACL_SYSCALL_BLOCK_SIZE) {
    NaClPatchOneTrampoline(nap, addr);
  }
#endif
#if NACL_ARCH(NACL_BUILD_ARCH) == NACL_x86 && NACL_BUILD_SUBARCH == 64
  NaClPatchOneTrampolineCall(nap->get_tls_fast_path1_addr,
                             nap->mem_start + NACL_SYSCALL_START_ADDR
                             + NACL_SYSCALL_BLOCK_SIZE * NACL_sys_tls_get);
  NaClPatchOneTrampolineCall(nap->get_tls_fast_path2_addr,
                             nap->mem_start + NACL_SYSCALL_START_ADDR
                             + (NACL_SYSCALL_BLOCK_SIZE *
                                NACL_sys_second_tls_get));
#endif

  NACL_TEST_INJECTION(ChangeTrampolines, (nap));
}

void  NaClMemRegionPrinter(void                   *state,
                           struct NaClVmmapEntry  *entry) {
  struct Gio *gp = (struct Gio *) state;

  gprintf(gp, "\nPage   %"NACL_PRIdPTR" (0x%"NACL_PRIxPTR")\n",
          entry->page_num, entry->page_num);
  gprintf(gp,   "npages %"NACL_PRIdS" (0x%"NACL_PRIxS")\n", entry->npages,
          entry->npages);
  gprintf(gp,   "start vaddr 0x%"NACL_PRIxPTR"\n",
          entry->page_num << NACL_PAGESHIFT);
  gprintf(gp,   "end vaddr   0x%"NACL_PRIxPTR"\n",
          (entry->page_num + entry->npages) << NACL_PAGESHIFT);
  gprintf(gp,   "prot   0x%08x\n", entry->prot);
  gprintf(gp,   "%sshared/backed by a file\n",
          (!entry->desc) ? "not " : "");
}

void  NaClAppPrintDetails(struct NaClApp  *nap,
                          struct Gio      *gp) {
  NaClXMutexLock(&nap->mu);
  gprintf(gp,
          "NaClAppPrintDetails((struct NaClApp *) 0x%08"NACL_PRIxPTR","
          "(struct Gio *) 0x%08"NACL_PRIxPTR")\n", (uintptr_t) nap,
          (uintptr_t) gp);
  gprintf(gp, "addr space size:  2**%"NACL_PRId32"\n", nap->addr_bits);
  gprintf(gp, "stack size:       0x%08"NACL_PRIx32"\n", nap->stack_size);

  gprintf(gp, "mem start addr:   0x%08"NACL_PRIxPTR"\n", nap->mem_start);
  /*           123456789012345678901234567890 */

  gprintf(gp, "static_text_end:   0x%08"NACL_PRIxPTR"\n", nap->static_text_end);
  gprintf(gp, "end-of-text:       0x%08"NACL_PRIxPTR"\n",
          NaClEndOfStaticText(nap));
  gprintf(gp, "rodata:            0x%08"NACL_PRIxPTR"\n", nap->rodata_start);
  gprintf(gp, "data:              0x%08"NACL_PRIxPTR"\n", nap->data_start);
  gprintf(gp, "data_end:          0x%08"NACL_PRIxPTR"\n", nap->data_end);
  gprintf(gp, "break_addr:        0x%08"NACL_PRIxPTR"\n", nap->break_addr);

  gprintf(gp, "ELF initial entry point:  0x%08x\n", nap->initial_entry_pt);
  gprintf(gp, "ELF user entry point:  0x%08x\n", nap->user_entry_pt);
  gprintf(gp, "memory map:\n");
  NaClVmmapVisit(&nap->mem_map,
                 NaClMemRegionPrinter,
                 gp);
  NaClXMutexUnlock(&nap->mu);
}

struct NaClDesc *NaClGetDescMu(struct NaClApp *nap,
                               int            d) {
  struct NaClDesc *result;

  result = (struct NaClDesc *) DynArrayGet(&nap->desc_tbl, d);
  if (result) {
    NaClDescRef(result);
  }

  return result;
}

void NaClSetDescMu(struct NaClApp   *nap,
                   int              d,
                   struct NaClDesc  *ndp) {
  struct NaClDesc *result;

  result = (struct NaClDesc *) DynArrayGet(&nap->desc_tbl, d);
  NaClDescSafeUnref(result);

  if (!DynArraySet(&nap->desc_tbl, d, ndp)) {
    NaClLog(LOG_FATAL,
            "NaClSetDesc: could not set descriptor %d to 0x%#08"
            NACL_PRIxPTR"\n",
            d,
            (uintptr_t) ndp);
  }
}

int32_t NaClSetAvailMu(struct NaClApp  *nap,
                       struct NaClDesc *ndp) {
  size_t pos;

  pos = DynArrayFirstAvail(&nap->desc_tbl);

  if (pos > INT32_MAX) {
    NaClLog(LOG_FATAL,
            ("NaClSetAvailMu: DynArrayFirstAvail returned a value"
             " that is greather than 2**31-1.\n"));
  }

  NaClSetDescMu(nap, (int) pos, ndp);

  return (int32_t) pos;
}

struct NaClDesc *NaClGetDesc(struct NaClApp *nap,
                             int            d) {
  struct NaClDesc *res;

  NaClFastMutexLock(&nap->desc_mu);
  res = NaClGetDescMu(nap, d);
  NaClFastMutexUnlock(&nap->desc_mu);
  return res;
}

void NaClSetDesc(struct NaClApp   *nap,
                 int              d,
                 struct NaClDesc  *ndp) {
  NaClFastMutexLock(&nap->desc_mu);
  NaClSetDescMu(nap, d, ndp);
  NaClFastMutexUnlock(&nap->desc_mu);
}

int32_t NaClSetAvail(struct NaClApp  *nap,
                     struct NaClDesc *ndp) {
  int32_t pos;

  NaClFastMutexLock(&nap->desc_mu);
  pos = NaClSetAvailMu(nap, ndp);
  NaClFastMutexUnlock(&nap->desc_mu);

  return pos;
}

int NaClAddThreadMu(struct NaClApp        *nap,
                    struct NaClAppThread  *natp) {
  size_t pos;

  pos = DynArrayFirstAvail(&nap->threads);

  if (!DynArraySet(&nap->threads, pos, natp)) {
    NaClLog(LOG_FATAL,
            "NaClAddThreadMu: DynArraySet at position %"NACL_PRIuS" failed\n",
            pos);
  }
  ++nap->num_threads;

  return (int) pos;
}

int NaClAddThread(struct NaClApp        *nap,
                  struct NaClAppThread  *natp) {
  int pos;

  NaClXMutexLock(&nap->threads_mu);
  pos = NaClAddThreadMu(nap, natp);
  NaClXMutexUnlock(&nap->threads_mu);

  return pos;
}

void NaClRemoveThreadMu(struct NaClApp  *nap,
                        int             thread_num) {
  if (!DynArrayGet(&nap->threads, thread_num)) {
     NaClLog(LOG_FATAL,
            "NaClRemoveThreadMu:: thread to be removed is not in the table\n");
  }
  if (nap->num_threads == 0) {
     NaClLog(LOG_FATAL,
            "NaClRemoveThreadMu:: num_threads cannot be 0!!!\n");
  }
  --nap->num_threads;
  if (!DynArraySet(&nap->threads, thread_num, (struct NaClAppThread *) NULL)) {
     NaClLog(LOG_FATAL,
            "NaClRemoveThreadMu:: DynArraySet at position %d failed\n",
            thread_num);
  }
}

void NaClRemoveThread(struct NaClApp  *nap,
                      int             thread_num) {
  NaClXMutexLock(&nap->threads_mu);
  NaClRemoveThreadMu(nap, thread_num);
  NaClXMutexUnlock(&nap->threads_mu);
}

struct NaClAppThread *NaClGetThreadMu(struct NaClApp  *nap,
                                      int             thread_num) {
  return (struct NaClAppThread *) DynArrayGet(&nap->threads, thread_num);
}

void NaClAddHostDescriptor(struct NaClApp *nap,
                           int            host_os_desc,
                           int            flag,
                           int            nacl_desc) {
  struct NaClDescIoDesc *dp;

  NaClLog(4,
          "NaClAddHostDescriptor: host %d as nacl desc %d, flag %#x\n",
          host_os_desc,
          nacl_desc,
          flag);
  dp = NaClDescIoDescMake(NaClHostDescPosixMake(host_os_desc, flag));
  if (!dp) {
    NaClLog(LOG_FATAL, "NaClAddHostDescriptor: NaClDescIoDescMake failed\n");
  }
  NaClSetDesc(nap, nacl_desc, (struct NaClDesc *)dp);
  if (host_os_desc >= FILE_DESC_MAX) {
    NaClLog(LOG_FATAL, "NaClAddHostDescriptor: fd %d is too large for fd_maps\n", host_os_desc);
    return;
  }
  nap->fd_maps[host_os_desc] = (struct NaClDesc *)dp;
}

void NaClAddImcHandle(struct NaClApp  *nap,
                      NaClHandle      h,
                      int             nacl_desc) {
  struct NaClDescImcDesc  *dp;

  NaClLog(4,
          ("NaClAddImcHandle: importing NaClHandle %"NACL_PRIxPTR
           " as nacl desc %d\n"),
          (uintptr_t) h,
          nacl_desc);
  dp = (struct NaClDescImcDesc *) malloc(sizeof *dp);
  if (NACL_FI_ERROR_COND("NaClAddImcHandle__malloc", !dp)) {
    NaClLog(LOG_FATAL, "NaClAddImcHandle: no memory\n");
  }
  if (NACL_FI_ERROR_COND("NaClAddImcHandle__ctor",
                         !NaClDescImcDescCtor(dp, h))) {
    NaClLog(LOG_FATAL, ("NaClAddImcHandle: cannot construct"
                        " IMC descriptor object\n"));
  }
  NaClSetDesc(nap, nacl_desc, (struct NaClDesc *) dp);
}


static struct {
  int         d;
  char const  *env_name;
  int         nacl_flags;
  int         mode;
} const g_nacl_redir_control[] = {
  { 0, "NACL_EXE_STDIN",
    NACL_ABI_O_RDONLY, 0, },
  { 1, "NACL_EXE_STDOUT",
    NACL_ABI_O_WRONLY | NACL_ABI_O_APPEND | NACL_ABI_O_CREAT, 0777, },
  { 2, "NACL_EXE_STDERR",
    NACL_ABI_O_WRONLY | NACL_ABI_O_APPEND | NACL_ABI_O_CREAT, 0777, },
};

/*
 * File redirection is impossible if an outer sandbox is in place.
 * For the command-line embedding, we sometimes have an outer sandbox:
 * on OSX, it is enabled after loading the file is loaded.  On the
 * other hand, device redirection (DEBUG_ONLY:dev://postmessage) is
 * impossible until the reverse channel setup has occurred.
 *
 * Because of this, we run NaClProcessRedirControl twice: once to
 * process default inheritance, file redirection early on, and once
 * after the reverse channel is in place to handle the device
 * redirection.  We try to hide knowledge about which redirection
 * control values can be handled in which phases by allowing the
 * NaClResourceOpen to fail, and only in the last phase do we check
 * that the redirection succeeded in *some* phase.
 */
static void NaClProcessRedirControl(struct NaClApp *nap) {
  char const      *env = NULL;
  struct NaClDesc *ndp = NULL;
  int d = 0;
  char const *env_name = NULL;
  int nacl_flags = 0;
  int mode = 0;

  for (size_t ix = 0; ix < NACL_ARRAY_SIZE(g_nacl_redir_control); ix++, ndp = NULL) {
    CHECK(ix < INT_MAX);
    d = g_nacl_redir_control[ix].d;
    env_name = g_nacl_redir_control[ix].env_name;
    nacl_flags = g_nacl_redir_control[ix].nacl_flags;
    mode = g_nacl_redir_control[ix].mode;

    if ((env = getenv(env_name))) {
      NaClLog(1, "getenv(%s) -> %s\n", env_name, env);
      ndp = NaClResourceOpen((struct NaClResource *)&nap->resources,
                             env,
                             nacl_flags,
                             mode);
      NaClLog(1, " NaClResourceOpen returned %"NACL_PRIxPTR"\n", (uintptr_t) ndp);
    }

    if (ndp) {
      NaClLog(1, "Setting descriptor %d\n", (int)ix);
      NaClSetDesc(nap, (int)ix, ndp);
      continue;
    }

     /*
      * Environment not set or redirect failed -- handle default inheritance.
      */
    if (NACL_RESOURCE_PHASE_START == nap->resource_phase)
      NaClAddHostDescriptor(nap, d, nacl_flags, (int)ix);
  }
}

/*
 * Process default descriptor inheritance.  This means dup'ing
 * descriptors 0-2 and making them available to the NaCl App.
 *
 * When standard input is inherited, this could result in a NaCl
 * module competing for input from the terminal; for graphical /
 * browser plugin environments, this never is allowed to happen, and
 * having this is useful for debugging, and for potential standalone
 * text-mode applications of NaCl.
 *
 * TODO(bsy): consider whether default inheritance should occur only
 * in debug mode.
 */
void NaClAppInitialDescriptorHookup(struct NaClApp  *nap) {

  NaClLog(4, "Processing I/O redirection/inheritance from environment\n");
  nap->resource_phase = NACL_RESOURCE_PHASE_START;
  NaClProcessRedirControl(nap);
  NaClLog(4, "... done.\n");
}

void NaClCreateServiceSocket(struct NaClApp *nap) {
  struct NaClDesc *secure_pair[2] = {0};
  struct NaClDesc *pair[2] = {0};

  NaClLog(3, "Entered NaClCreateServiceSocket\n");

  if (NACL_FI_ERROR_COND("NaClCreateServiceSocket__secure_boundsock",
                         0 != NaClCommonDescMakeBoundSock(secure_pair))) {
    NaClLog(LOG_FATAL, "Cound not create secure service socket\n");
  }
  NaClLog(1, "got bound socket at %p, addr at %p\n", (void *)secure_pair[0], (void *)secure_pair[1]);
  NaClDescSafeUnref(nap->secure_service_port);
  nap->secure_service_port = secure_pair[0];

  NaClDescSafeUnref(nap->secure_service_address);
  nap->secure_service_address = secure_pair[1];

  if (NACL_FI_ERROR_COND("NaClCreateServiceSocket__boundsock",
                         0 != NaClCommonDescMakeBoundSock(pair))) {
    NaClLog(LOG_FATAL, "Cound not create service socket\n");
  }
  NaClLog(4,
          "got bound socket at 0x%08"NACL_PRIxPTR", "
          "addr at 0x%08"NACL_PRIxPTR"\n",
          (uintptr_t) pair[0],
          (uintptr_t) pair[1]);
  NaClSetDesc(nap, NACL_SERVICE_PORT_DESCRIPTOR, pair[0]);
  NaClSetDesc(nap, NACL_SERVICE_ADDRESS_DESCRIPTOR, pair[1]);

  NaClDescSafeUnref(nap->service_port);

  nap->service_port = pair[0];
  NaClDescRef(nap->service_port);

  NaClDescSafeUnref(nap->service_address);

  nap->service_address = pair[1];
  NaClDescRef(nap->service_address);

  NaClLog(4, "Leaving NaClCreateServiceSocket\n");
}

/*
 * Import the |inherited_desc| descriptor as an IMC handle, save a
 * reference to it at nap->bootstrap_channel, then send the
 * service_address over that channel.
 */
void NaClSetUpBootstrapChannel(struct NaClApp  *nap,
                               NaClHandle      inherited_desc) {
  struct NaClDescImcDesc      *channel = NULL;
  struct NaClImcTypedMsgHdr   hdr = {0};
  struct NaClDesc             *descs[2] = {0};
  ssize_t                     rv = 0;

  NaClLog(1, "NaClSetUpBootstrapChannel(0x%08"NACL_PRIxPTR", %"NACL_PRIdPTR")\n",
          (uintptr_t) nap,
          (uintptr_t) inherited_desc);

  channel = malloc(sizeof *channel);
  if (!channel) {
    NaClLog(LOG_FATAL, "NaClSetUpBootstrapChannel: no memory\n");
    return;
  }
  if (!NaClDescImcDescCtor(channel, inherited_desc)) {
    NaClLog(LOG_FATAL,
            ("NaClSetUpBootstrapChannel: cannot construct IMC descriptor"
             " object for inherited descriptor %"NACL_PRIdPTR"\n"),
            (uintptr_t) inherited_desc);
    return;
  }
  if (!nap->secure_service_address) {
    NaClLog(LOG_FATAL,
            "NaClSetUpBootstrapChannel: secure service address not set\n");
    return;
  }
  if (!nap->service_address) {
    NaClLog(LOG_FATAL,
            "NaClSetUpBootstrapChannel: service address not set\n");
    return;
  }
  /*
   * service_address and service_port are set together.
   */
  descs[0] = nap->secure_service_address;
  descs[1] = nap->service_address;

  hdr.iov = (struct NaClImcMsgIoVec *)NULL;
  hdr.iov_length = 0;
  hdr.ndescv = descs;
  hdr.ndesc_length = NACL_ARRAY_SIZE(descs);

  rv = NACL_VTBL(NaClDesc, channel)->SendMsg((struct NaClDesc *)channel, &hdr, 0);
  NaClXMutexLock(&nap->mu);
  if (nap->bootstrap_channel) {
    NaClLog(LOG_FATAL,
            "NaClSetUpBootstrapChannel: cannot have two bootstrap channels\n");
  }
  nap->bootstrap_channel = (struct NaClDesc *)channel;
  channel = NULL;
  NaClXMutexUnlock(&nap->mu);

  NaClLog(1,
          ("NaClSetUpBootstrapChannel: descriptor %"NACL_PRIdPTR
           ", error %"NACL_PRIdS"\n"),
          (uintptr_t) inherited_desc,
          rv);
  if (NACL_FI_ERROR_COND("NaClSetUpBootstrapChannel__SendMsg", 0 != rv)) {
    NaClLog(LOG_FATAL,
            "NaClSetUpBootstrapChannel: SendMsg failed, rv = %"NACL_PRIdS"\n",
            rv);
  }
}

static void NaClSecureChannelShutdownRpc(
    struct NaClSrpcRpc      *rpc,
    struct NaClSrpcArg      **in_args,
    struct NaClSrpcArg      **out_args,
    struct NaClSrpcClosure  *done) {
  UNREFERENCED_PARAMETER(rpc);
  UNREFERENCED_PARAMETER(in_args);
  UNREFERENCED_PARAMETER(out_args);
  UNREFERENCED_PARAMETER(done);

  NaClLog(4, "NaClSecureChannelShutdownRpc (hard_shutdown), exiting\n");
  NaClExit(0);
  /* Return is never reached, so no need to invoke (*done->Run)(done). */
}

/*
 * This RPC is invoked by the plugin when the nexe is downloaded as a
 * stream and not as a file. The only arguments are a handle to a
 * shared memory object that contains the nexe.
 */
static void NaClLoadModuleRpc(struct NaClSrpcRpc      *rpc,
                              struct NaClSrpcArg      **in_args,
                              struct NaClSrpcArg      **out_args,
                              struct NaClSrpcClosure  *done) {
  struct NaClApp          *nap =
      (struct NaClApp *) rpc->channel->server_instance_data;
  struct NaClDesc         *nexe_binary = in_args[0]->u.hval;
  char                    *aux;
  NaClErrorCode           suberr = LOAD_INTERNAL;

  UNREFERENCED_PARAMETER(out_args);

  NaClLog(4, "NaClLoadModuleRpc: entered\n");

  rpc->result = NACL_SRPC_RESULT_INTERNAL;

  aux = strdup(in_args[1]->arrays.str);
  if (!aux) {
    rpc->result = NACL_SRPC_RESULT_NO_MEMORY;
    goto cleanup;
  }
  NaClLog(4, "Received aux_info: %s\n", aux);

  /*
   * TODO(bsy): consider doing the processing below after sending the
   * RPC reply to increase parallelism.
   */

  NaClXMutexLock(&nap->mu);

  if (LOAD_STATUS_UNKNOWN != nap->module_load_status) {
    NaClLog(LOG_ERROR, "Repeated LoadModule RPC, or platform qual error?!?\n");
    if (LOAD_OK == nap->module_load_status) {
      NaClLog(LOG_ERROR, "LoadModule when module_load_status is LOAD_OK?!?\n");
      suberr = LOAD_DUP_LOAD_MODULE;
      nap->module_load_status = suberr;
    } else {
      suberr = nap->module_load_status;
    }
    rpc->result = NACL_SRPC_RESULT_OK;
    NaClXCondVarBroadcast(&nap->cv);
    goto cleanup_status_mu;
  }

  free(nap->aux_info);
  nap->aux_info = aux;

  /*
   * Check / Mark the nexe binary as OK to attempt memory mapping.
   *
   * TODO(bsy): change needed to get NaClFileToken and resolve to file
   * path information, set NaClRichFileInfo, and stash via
   * NaClSetFileOriginInfo, then set NACL_DESC_FLAGS_MMAP_EXEC_OK.
   */

  suberr = NACL_FI_VAL("load_module", NaClErrorCode,
                       NaClAppLoadFile(nexe_binary, nap));

  if (LOAD_OK != suberr) {
    nap->module_load_status = suberr;
    rpc->result = NACL_SRPC_RESULT_OK;
    NaClXCondVarBroadcast(&nap->cv);
  }

 cleanup_status_mu:
  NaClXMutexUnlock(&nap->mu);  /* NaClAppPrepareToLaunch takes mu */
  if (LOAD_OK != suberr) {
    goto cleanup;
  }

  /***************************************************************************
   * TODO(bsy): Remove/merge the code invoking NaClAppPrepareToLaunch
   * and NaClGdbHook below with sel_main's main function.  See comment
   * there.
   ***************************************************************************/

  /*
   * Finish setting up the NaCl App.
   */
  suberr = NaClAppPrepareToLaunch(nap);

  NaClXMutexLock(&nap->mu);

  nap->module_load_status = suberr;
  rpc->result = NACL_SRPC_RESULT_OK;

  NaClXCondVarBroadcast(&nap->cv);
  NaClXMutexUnlock(&nap->mu);

  /* Give debuggers a well known point at which xlate_base is known.  */
  NaClGdbHook(nap);

 cleanup:
  NaClDescUnref(nexe_binary);
  nexe_binary = NULL;
  (*done->Run)(done);
}

NaClErrorCode NaClWaitForLoadModuleStatus(struct NaClApp *nap) {
  NaClErrorCode status;

  NaClXMutexLock(&nap->mu);
  while (LOAD_STATUS_UNKNOWN == (status = nap->module_load_status)) {
    NaClXCondVarWait(&nap->cv, &nap->mu);
  }
  NaClXMutexUnlock(&nap->mu);
  return status;
}

static void NaClSecureChannelStartModuleRpc(struct NaClSrpcRpc     *rpc,
                                            struct NaClSrpcArg     **in_args,
                                            struct NaClSrpcArg     **out_args,
                                            struct NaClSrpcClosure *done) {
  /*
   * let module start if module is okay; otherwise report error (e.g.,
   * ABI version mismatch).
   */
  struct NaClApp  *nap = (struct NaClApp *) rpc->channel->server_instance_data;
  NaClErrorCode   status;

  UNREFERENCED_PARAMETER(in_args);

  NaClLog(4,
          "NaClSecureChannelStartModuleRpc started, nap 0x%"NACL_PRIxPTR"\n",
          (uintptr_t) nap);

  status = NaClWaitForLoadModuleStatus(nap);

  NaClLog(4, "NaClSecureChannelStartModuleRpc: load status %d\n", status);

  out_args[0]->u.ival = status;
  rpc->result = NACL_SRPC_RESULT_OK;

  /*
   * When reverse setup is being used, we have to block and wait for reverse
   * channel to become initialized before we can proceed with start module.
   */
  NaClXMutexLock(&nap->mu);
  if (NACL_REVERSE_CHANNEL_UNINITIALIZED !=
      nap->reverse_channel_initialization_state) {
    while (NACL_REVERSE_CHANNEL_INITIALIZED !=
           nap->reverse_channel_initialization_state) {
      NaClXCondVarWait(&nap->cv, &nap->mu);
    }
  }
  NaClXMutexUnlock(&nap->mu);

  NaClLog(4, "NaClSecureChannelStartModuleRpc running closure\n");
  (*done->Run)(done);
  /*
   * The RPC reply is now sent.  This has to occur before we signal
   * the main thread to possibly start, since in the case of a failure
   * the main thread may quickly exit.  If the main thread does this
   * before we sent the RPC reply, then the plugin will be left
   * without an answer.
   */

  NaClXMutexLock(&nap->mu);
  if (nap->module_may_start) {
    status = LOAD_DUP_START_MODULE;
    NaClLog(LOG_ERROR, "Duplicate StartModule RPC?!? status: [%u]\n", status);
  } else {
    nap->module_may_start = 1;
  }
  NaClLog(1, "%s\n", "NaClSecureChannelStartModuleRpc: broadcasting");
  NaClXCondVarBroadcast(&nap->cv);
  NaClXMutexUnlock(&nap->mu);

  NaClLog(4, "NaClSecureChannelStartModuleRpc exiting\n");
}

static void NaClSecureChannelLog(struct NaClSrpcRpc      *rpc,
                                 struct NaClSrpcArg      **in_args,
                                 struct NaClSrpcArg      **out_args,
                                 struct NaClSrpcClosure  *done) {
  int severity = in_args[0]->u.ival;
  char *msg = in_args[1]->arrays.str;

  UNREFERENCED_PARAMETER(out_args);

  NaClLog(5, "NaClSecureChannelLog started\n");
  NaClLog(severity, "%s\n", msg);
  NaClLog(5, "NaClSecureChannelLog finished\n");
  rpc->result = NACL_SRPC_RESULT_OK;
  (*done->Run)(done);
}

NaClErrorCode NaClWaitForStartModuleCommand(struct NaClApp *nap) {
  NaClErrorCode status;

  NaClLog(4, "NaClWaitForStartModuleCommand started\n");
  NaClXMutexLock(&nap->mu);
  while (!nap->module_may_start) {
    NaClXCondVarWait(&nap->cv, &nap->mu);
    NaClLog(4,
            "NaClWaitForStartModuleCommand: awaken, module_may_start %d\n",
            nap->module_may_start);
  }
  status = nap->module_load_status;
  NaClXMutexUnlock(&nap->mu);
  NaClLog(4, "NaClWaitForStartModuleCommand finished\n");

  return status;
}

void NaClBlockIfCommandChannelExists(struct NaClApp *nap) {
  if (nap->secure_service) {
    for (;;) {
      struct nacl_abi_timespec req;
      req.tv_sec = 1000;
      req.tv_nsec = 0;
      NaClNanosleep(&req, (struct nacl_abi_timespec *) NULL);
    }
  }
}

/*
 * The first connection is performed by this callback handler.  This
 * spawns a client thread that will bootstrap the other connections by
 * stashing the connection represented by |conn| to make reverse RPCs
 * to ask the peer to connect to us.  No thread is spawned; we just
 * wrap access to the connection with a lock.
 *
 * Subsequent connection callbacks will pass the connection to the
 * actual thread that made the connection request using |conn|
 * received in the first connection.
 */
static void NaClSecureReverseClientCallback(
    void                        *state,
    struct NaClThreadInterface  *tif,
    struct NaClDesc             *new_conn) {
  struct NaClSecureReverseClient *self =
      (struct NaClSecureReverseClient *) state;
  struct NaClApp *nap = self->nap;

  UNREFERENCED_PARAMETER(tif);

  NaClLog(4, "Entered NaClSecureReverseClientCallback\n");

  NaClLog(4, " self=0x%"NACL_PRIxPTR"\n", (uintptr_t) self);
  NaClLog(4, " nap=0x%"NACL_PRIxPTR"\n", (uintptr_t) nap);
  NaClXMutexLock(&nap->mu);

  if (NACL_REVERSE_CHANNEL_INITIALIZATION_STARTED !=
      nap->reverse_channel_initialization_state) {
    /*
     * The reverse channel connection capability is used to make the
     * RPC that invokes this callback (this callback is invoked on a
     * reverse channel connect), so the plugin wants to initialize the
     * reverse channel and in particular the state must be either be
     * in-progress or finished.
     */
    NaClLog(LOG_FATAL, "Reverse channel already initialized\n");
  }
  if (!NaClSrpcClientCtor(&nap->reverse_channel, new_conn)) {
    NaClLog(LOG_FATAL, "Reverse channel SRPC Client Ctor failed\n");
  }
  nap->reverse_quota_interface = (struct NaClReverseQuotaInterface *)
      malloc(sizeof *nap->reverse_quota_interface);
  if (!nap->reverse_quota_interface ||
      NACL_FI_ERROR_COND(
          ("NaClSecureReverseClientCallback"
           "__NaClReverseQuotaInterfaceCtor"),
          !NaClReverseQuotaInterfaceCtor(nap->reverse_quota_interface,
                                         nap))) {
    NaClLog(LOG_FATAL, "Reverse quota interface Ctor failed\n");
  }
  nap->reverse_channel_initialization_state = NACL_REVERSE_CHANNEL_INITIALIZED;

  NaClXCondVarBroadcast(&nap->cv);
  NaClXMutexUnlock(&nap->mu);

  NaClLog(4, "Leaving NaClSecureReverseClientCallback\n");
}

static void NaClSecureReverseClientSetup(struct NaClSrpcRpc     *rpc,
                                         struct NaClSrpcArg     **in_args,
                                         struct NaClSrpcArg     **out_args,
                                         struct NaClSrpcClosure *done) {
  struct NaClApp                  *nap =
      (struct NaClApp *) rpc->channel->server_instance_data;
  struct NaClSecureReverseClient  *rev;

  UNREFERENCED_PARAMETER(in_args);
  NaClLog(4, "Entered NaClSecureReverseClientSetup\n");

  NaClXMutexLock(&nap->mu);
  if (nap->reverse_client) {
    NaClLog(LOG_FATAL, "Double reverse setup RPC\n");
  }
  if (NACL_REVERSE_CHANNEL_UNINITIALIZED !=
      nap->reverse_channel_initialization_state) {
    NaClLog(LOG_FATAL,
            "Reverse channel initialization state not uninitialized\n");
  }
  nap->reverse_channel_initialization_state =
      NACL_REVERSE_CHANNEL_INITIALIZATION_STARTED;
  /* the reverse connection is still coming */
  rev = (struct NaClSecureReverseClient *) malloc(sizeof *rev);
  if (!rev) {
    rpc->result = NACL_SRPC_RESULT_APP_ERROR;
    goto done;
  }
  NaClLog(4,
          "NaClSecureReverseClientSetup: invoking"
          " NaClSecureReverseClientCtor\n");
  if (!NaClSecureReverseClientCtor(rev,
                                   NaClSecureReverseClientCallback,
                                   (void *) rev,
                                   nap)) {
    free(rev);
    rpc->result = NACL_SRPC_RESULT_APP_ERROR;
    goto done;
  }
  nap->reverse_client = (struct NaClSecureReverseClient *) NaClRefCountRef(
      (struct NaClRefCount *) rev);
  out_args[0]->u.hval = NaClDescRef(rev->base.bound_and_cap[1]);
  rpc->result = NACL_SRPC_RESULT_OK;

  /*
   * Hook up reverse-channel enabled resources, e.g.,
   * DEBUG_ONLY:dev://postmessage.  NB: Resources specified by
   * file:path should have been taken care of earlier, in
   * NaClAppInitialDescriptorHookup.
   */
  nap->resource_phase = NACL_RESOURCE_PHASE_REV_CHAN;
  NaClLog(4, "Processing dev I/O redirection/inheritance from environment\n");
  NaClProcessRedirControl(nap);
  NaClLog(4, "... done.\n");

  /*
   * Service thread takes the reference rev.
   */
  if (!NaClSimpleRevClientStartServiceThread(&rev->base)) {
    NaClLog(LOG_FATAL, "Could not start reverse service thread\n");
  }

done:
  NaClXMutexUnlock(&nap->mu);
  (*done->Run)(done);
  NaClLog(4, "Leaving NaClSecureReverseClientSetup\n");
}

struct NaClSrpcHandlerDesc const secure_handlers[]; /* fwd */

void NaClSecureCommandChannel(struct NaClApp *nap) {
  struct NaClSecureService *secure_command_server;

  NaClLog(4, "Entered NaClSecureCommandChannel\n");

  secure_command_server = (struct NaClSecureService *) malloc(
      sizeof *secure_command_server);
  if (NACL_FI_ERROR_COND("NaClSecureCommandChannel__malloc",
                         !secure_command_server)) {
    NaClLog(LOG_FATAL, "Out of memory for secure command channel\n");
  }
  if (NACL_FI_ERROR_COND("NaClSecureCommandChannel__NaClSecureServiceCtor",
                         !NaClSecureServiceCtor(secure_command_server,
                                                secure_handlers,
                                                nap,
                                                nap->secure_service_port,
                                                nap->secure_service_address))) {
    NaClLog(LOG_FATAL, "NaClSecureServiceCtor failed\n");
  }
  nap->secure_service = secure_command_server;

  NaClLog(4, "NaClSecureCommandChannel: starting service thread\n");
  if (NACL_FI_ERROR_COND(
          "NaClSecureCommandChannel__NaClSimpleServiceStartServiceThread",
          !NaClSimpleServiceStartServiceThread((struct NaClSimpleService *)
                                               secure_command_server))) {
    NaClLog(LOG_FATAL,
            "Could not start secure command channel service thread\n");
  }

  NaClLog(4, "Leaving NaClSecureCommandChannel\n");
}

struct NaClSrpcHandlerDesc const secure_handlers[] = {
  { "hard_shutdown::", NaClSecureChannelShutdownRpc, },
  { "start_module::i", NaClSecureChannelStartModuleRpc, },
  { "log:is:", NaClSecureChannelLog, },
  { "load_module:hs:", NaClLoadModuleRpc, },
  { "reverse_setup::h", NaClSecureReverseClientSetup, },
  /* add additional calls here.  upcall set up?  start module signal? */
  { (char const *) NULL, (NaClSrpcMethod) NULL, },
};

/*
 * It is fine to have multiple I/O operations read from memory in Write
 * or SendMsg like operations.
 */
void NaClVmIoWillStart(struct NaClApp *nap,
                       uint32_t addr_first_usr,
                       uint32_t addr_last_usr) {
  NaClXMutexLock(&nap->mu);
  (*nap->mem_io_regions->vtbl->AddInterval)(nap->mem_io_regions,
                                            addr_first_usr,
                                            addr_last_usr);
  NaClXMutexUnlock(&nap->mu);
}


void NaClVmIoHasEnded(struct NaClApp *nap,
                      uint32_t addr_first_usr,
                      uint32_t addr_last_usr) {
  NaClXMutexLock(&nap->mu);
  (*nap->mem_io_regions->vtbl->RemoveInterval)(nap->mem_io_regions,
                                               addr_first_usr,
                                               addr_last_usr);
  NaClXMutexUnlock(&nap->mu);
}

void NaClVmIoPendingCheck_mu(struct NaClApp *nap,
                             uint32_t addr_first_usr,
                             uint32_t addr_last_usr) {
  if ((*nap->mem_io_regions->vtbl->OverlapsWith)(nap->mem_io_regions,
                                                 addr_first_usr,
                                                 addr_last_usr)) {
    NaClLog(LOG_FATAL,
            "NaClVmIoWillStart: program mem write race detected. ABORTING\n");
  }
}

/*
 * GDB's canonical overlay managment routine.
 * We need its symbol in the symbol table so don't inline it.
 * TODO(dje): add some explanation for the non-GDB person.
 */
#if NACL_WINDOWS
__declspec(dllexport noinline)
#endif
#ifdef __GNUC__
__attribute__((noinline))
#endif
void _ovly_debug_event (void) {
#ifdef __GNUC__
  /*
   * The asm volatile is here as instructed by the GCC docs.
   * It's not enough to declare a function noinline.
   * GCC will still look inside the function to see if it's worth calling.
   */
  __asm__ volatile ("");
#elif NACL_WINDOWS
  /*
   * Visual Studio inlines empty functions even with noinline attribute,
   * so we need a compile memory barrier to make this function not to be
   * inlined. Also, it guarantees that nacl_global_xlate_base initialization
   * is not reordered. This is important for gdb since it sets breakpoint on
   * this function and reads nacl_global_xlate_base value.
   */
  _ReadWriteBarrier();
#endif
}

static void StopForDebuggerInit (uintptr_t mem_start) {
  /* Put xlate_base in a place where gdb can find it.  */
  nacl_global_xlate_base = mem_start;

  NaClSandboxMemoryStartForValgrind(mem_start);

  _ovly_debug_event();
}

void NaClGdbHook(struct NaClApp const *nap) {
  StopForDebuggerInit(nap->mem_start);
}

/*
 * Passed to NaClVmmapVisit in order to copy a memory region from
 * an NaClApp to a child process (used when forking).
 *
 * -jp
 *
 * preconditions:
 * * target_state must be a pointer to a valid, initialized NaClApp.
 *
 */
static void NaClVmCopyEntry(void *target_state, struct NaClVmmapEntry *entry) {
  struct NaClApp *target = target_state;
  struct NaClApp *parent = target->parent ? target->parent : target;
  uintptr_t offset = target->mem_start;
  uintptr_t parent_offset = parent ? parent->mem_start : 0;
  uintptr_t page_addr_child = (entry->page_num << NACL_PAGESHIFT) | offset;
  uintptr_t page_addr_parent = (entry->page_num << NACL_PAGESHIFT) | parent_offset;
  size_t copy_size = entry->npages << NACL_PAGESHIFT;

  /* don't copy pages if nap has no parent */
  if (!parent_offset) {
    return;
  }
  NaClLog(2, "copying %zu page(s) at %zu [%#lx] from (%p) to (%p)\n",
          entry->npages,
          entry->page_num,
          copy_size,
          (void *)page_addr_parent,
          (void *)page_addr_child);
  NaClVmmapAddWithOverwrite(&target->mem_map,
                            entry->page_num,
                            entry->npages,
                            entry->prot,
                            (entry->flags | MAP_ANON_PRIV) & ~NACL_ABI_MAP_SHARED,
                            entry->desc,
                            entry->offset,
                            entry->file_size);
  if (!NaClPageAllocFlags((void **)&page_addr_child, copy_size, 0)) {
    NaClLog(LOG_FATAL, "%s\n", "child vmmap NaClPageAllocAtAddr failed!");
  }

  /* temporarily set RW page permissions for copy */
  NaClVmmapChangeProt(&target->mem_map, entry->page_num, entry->npages, entry->prot | PROT_RW);
  NaClVmmapChangeProt(&parent->mem_map, entry->page_num, entry->npages, entry->prot | PROT_RW);
  if (NaClMprotect((void *)page_addr_child, copy_size, PROT_RW) == -1) {
    NaClLog(LOG_FATAL, "%s\n", "child vmmap page NaClMprotect failed!");
  }
  if (NaClMprotect((void *)page_addr_parent, copy_size, PROT_RW) == -1) {
    NaClLog(LOG_FATAL, "%s\n", "parent vmmap page NaClMprotect failed!");
  }

  /* copy data pages point to */
  memcpy((void *)page_addr_child, (void *)page_addr_parent, copy_size);
  NaClPatchAddr(offset, parent_offset, (uintptr_t *)page_addr_child, copy_size);

  /* reset to original page permissions */
  NaClVmmapChangeProt(&target->mem_map, entry->page_num, entry->npages, entry->prot);
  NaClVmmapChangeProt(&parent->mem_map, entry->page_num, entry->npages, entry->prot);
  if (NaClMprotect((void *)page_addr_child, copy_size, entry->prot) == -1) {
    NaClLog(LOG_FATAL, "%s\n", "child vmmap page NaClMprotect failed!");
  }
  if (NaClMprotect((void *)page_addr_parent, copy_size, entry->prot) == -1) {
    NaClLog(LOG_FATAL, "%s\n", "parent vmmap page NaClMprotect failed!");
  }
}

/*
 * Passed to NaClDyncodeVisit in order to copy a dynamic region from
 * an NaClApp to a child process (used when forking).
 *
 * -jp
 *
 * preconditions:
 * * target_state must be a pointer to a valid, initialized NaClApp.
 *
 */
static void NaClCopyDynamicRegion(void *target_state, struct NaClDynamicRegion *region) {
  struct NaClApp *target = target_state;
  uintptr_t start = region->start & UNTRUSTED_ADDR_MASK;
  uintptr_t offset = target->mem_start;
  uintptr_t parent_offset = region->start - start;
  void *dyncode_addr = (void *)(start | target->mem_start);
  NaClVmmapAddWithOverwrite(&target->mem_map,
                            start >> NACL_PAGESHIFT,
                            region->size >> NACL_PAGESHIFT,
                            PROT_RX,
                            NACL_ABI_MAP_PRIVATE,
                            target->text_shm,
                            (region->start & UNTRUSTED_ADDR_MASK) - target->dynamic_text_start,
                            region->size);
  if (NaClMprotect(dyncode_addr, region->size, PROT_RW) == -1) {
    NaClLog(LOG_FATAL, "%s\n", "cbild dynamic text NaClMprotect failed!");
  }
  NaClLog(1, "copying dynamic code from (%p) to (%p)\n", dyncode_addr, (void *)region->start);
  if (!NaClDynamicRegionCreate(target, (uintptr_t)dyncode_addr, region->size, 1)) {
    NaClLog(LOG_FATAL, "%s\n", "cbild dynamic text NaClTextDyncodeCreate failed!");
  }
  memcpy(dyncode_addr, (void *)region->start, region->size);
  NaClPatchAddr(offset, parent_offset, dyncode_addr, region->size);
  if (NaClMprotect(dyncode_addr, region->size, PROT_RX) == -1) {
    NaClLog(LOG_FATAL, "%s\n", "cbild dynamic text NaClMprotect failed!");
  }
}

/*
 * Copy the entire dynamic text section in an NaClApp to a child process.
 *
 * preconditions:
 * * `nap_parent` and `nap_child` must both be pointers to valid, initialized NaClApps
 * * Caller must hold both the nap_parent->mu and the nap_child->mu mutexes
 */
void NaClCopyDynamicText(struct NaClApp *nap_parent, struct NaClApp *nap_child) {
  size_t dyncode_size = NaClRoundPage(nap_child->dynamic_text_end - nap_parent->dynamic_text_start);
  size_t dyncode_npages = dyncode_size >> NACL_PAGESHIFT;
  void *dyncode_parent = (void *)NaClUserToSys(nap_parent, nap_parent->dynamic_text_start);
  void *dyncode_child = (void *)NaClUserToSys(nap_child, nap_child->dynamic_text_start);
  uintptr_t dyncode_pnum_parent = NaClSysToUser(nap_parent, (uintptr_t)dyncode_parent) >> NACL_PAGESHIFT;
  uintptr_t dyncode_pnum_child = NaClSysToUser(nap_child, (uintptr_t)dyncode_child) >> NACL_PAGESHIFT;

  UNREFERENCED_PARAMETER(dyncode_npages);
  UNREFERENCED_PARAMETER(dyncode_pnum_parent);
  UNREFERENCED_PARAMETER(dyncode_pnum_child);

  NaClLog(1, "dyncode [parent: %p] [child: %p]\n", dyncode_parent, dyncode_child);
  NaClLog(1, "cage_id [nap_parent: %d] [nap_child: %d]\n", nap_parent->cage_id, nap_child->cage_id);
  NaClPrintAddressSpaceLayout(nap_parent);
  NaClPrintAddressSpaceLayout(nap_child);

  /* copy dynamic text regions */
  NaClXMutexLock(&nap_child->dynamic_load_mutex);
  /* NaClDyncodeVisit() handles parent dynamic_load_mutex lock */
  nap_child->text_shm = nap_parent->text_shm;
  NaClDyncodeVisit(nap_parent, NaClCopyDynamicRegion, nap_child);
  NaClXMutexUnlock(&nap_child->dynamic_load_mutex);

  /* copy page mappings */
  NaClVmmapVisit(&nap_parent->mem_map, NaClVmCopyEntry, nap_child);

  NaClLog(1, "copied page tables from (%p) to (%p)\n", (void *)nap_parent, (void *)nap_child);
  NaClLog(1, "%s\n", "nap_parent_parent address space after copy:");
  NaClPrintAddressSpaceLayout(nap_parent);
  NaClLog(1, "%s\n", "nap_child address space after copy:");
  NaClPrintAddressSpaceLayout(nap_child);
}

/*
 * Copy the entire address execution context of an NaClApp to a child
 * process.
 *
 * preconditions:
 * * `nap_parent` and `nap_child` must both be pointers to valid, initialized NaClApps
 * * Caller must hold both the nap_parent->mu and the nap_child->mu mutexes
 */
void NaClCopyExecutionContext(struct NaClApp *nap_parent, struct NaClApp *nap_child) {
  size_t stack_size = nap_parent->stack_size;
  size_t stack_npages = stack_size >> NACL_PAGESHIFT;
  size_t tramp_size = NaClRoundPage(nap_parent->static_text_end - NACL_SYSCALL_START_ADDR);
  size_t tramp_npages = tramp_size >> NACL_PAGESHIFT;
  void *stackaddr_parent = (void *)NaClUserToSysAddrRange(nap_parent,
                                                          NaClGetInitialStackTop(nap_parent) - stack_size,
                                                          stack_size);
  void *stackaddr_child = (void *)NaClUserToSysAddrRange(nap_child,
                                                         NaClGetInitialStackTop(nap_child) - stack_size,
                                                         stack_size);
  uintptr_t stack_pnum_parent = NaClSysToUser(nap_parent, (uintptr_t)stackaddr_parent) >> NACL_PAGESHIFT;
  uintptr_t stack_pnum_child = NaClSysToUser(nap_child, (uintptr_t)stackaddr_child) >> NACL_PAGESHIFT;
  uintptr_t parent_start_addr = nap_parent->mem_start + NACL_SYSCALL_START_ADDR;
  uintptr_t child_start_addr = nap_child->mem_start + NACL_SYSCALL_START_ADDR;
  uintptr_t tramp_pnum = NaClSysToUser(nap_parent, parent_start_addr) >> NACL_PAGESHIFT;

  UNREFERENCED_PARAMETER(stack_pnum_parent);

  NaClLog(1, "stack [parent: %p] [child: %p]\n", stackaddr_parent, stackaddr_child);
  NaClLog(1, "cage_id [nap_parent: %d] [nap_child: %d]\n", nap_parent->cage_id, nap_child->cage_id);
  NaClPrintAddressSpaceLayout(nap_parent);
  NaClPrintAddressSpaceLayout(nap_child);

  /* add stack mapping */
  if (NaClMprotect(stackaddr_parent, stack_size, PROT_RW) == -1) {
      NaClLog(LOG_FATAL, "%s\n", "parent stack address NaClMprotect failed!");
  }
  if (NaClMprotect(stackaddr_child, stack_size, PROT_RW) == -1) {
      NaClLog(LOG_FATAL, "%s\n", "child stack address NaClMprotect failed!");
  }
  NaClVmmapAddWithOverwrite(&nap_child->mem_map,
                            stack_pnum_child,
                            stack_npages,
                            PROT_RW,
                            MAP_ANON_PRIV,
                            NULL,
                            0,
                            0);

  /* copy stack */
  NaClLog(1, "Copying parent stack (%zu [%#lx] bytes) from (%p) to (%p)\n",
          stack_size,
          stack_size,
          stackaddr_parent,
          stackaddr_child);
  memcpy(stackaddr_child, stackaddr_parent, stack_size);
  NaClPatchAddr(nap_child->mem_start, nap_parent->mem_start, stackaddr_child, stack_size);

  /* and dynamic text mappings */
  NaClCopyDynamicText(nap_parent, nap_child);

  /* add guard page mapping */
  NaClVmmapAddWithOverwrite(&nap_child->mem_map,
                            0,
                            NACL_SYSCALL_START_ADDR >> NACL_PAGESHIFT,
                            NACL_ABI_PROT_NONE,
                            NACL_ABI_MAP_PRIVATE,
                            NULL,
                            0,
                            0);

  /*
   * The next pages up to NACL_TRAMPOLINE_END are the trampolines.
   * Immediately following that is the loaded text section.
   * These are collectively marked as PROT_READ | PROT_EXEC.
   */
  NaClLog(3,
          ("Trampoline/text region start 0x%08"NACL_PRIxPTR","
           " size 0x%08"NACL_PRIxS", end 0x%08"NACL_PRIxPTR"\n"),
          child_start_addr,
          tramp_size,
          child_start_addr + tramp_size);
  if (NaClMprotect((void *)child_start_addr, tramp_size, PROT_RW)) {
    NaClLog(LOG_FATAL, "NaClMemoryProtection: "
            "NaClMprotect(0x%08"NACL_PRIxPTR", "
            "0x%08"NACL_PRIxS", 0x%x) failed\n",
            child_start_addr,
            tramp_size,
            PROT_RW);
  }

  /* map child trampoline pages */
  NaClVmmapAddWithOverwrite(&nap_child->mem_map,
                            tramp_pnum,
                            tramp_npages,
                            PROT_RW,
                            MAP_ANON_PRIV,
                            NULL,
                            0,
                            0);
  if (!NaClPageAllocFlags((void **)&child_start_addr, tramp_size, 0)) {
    NaClLog(LOG_FATAL, "%s\n", "child vmmap NaClPageAllocAtAddr failed!");
  }

  /* temporarily set RW page permissions for copy */
  NaClVmmapChangeProt(&nap_child->mem_map, tramp_pnum, tramp_npages, PROT_RW);
  NaClVmmapChangeProt(&nap_parent->mem_map, tramp_pnum, tramp_npages, PROT_RW);
  if (NaClMprotect((void *)child_start_addr, tramp_size, PROT_RW) == -1) {
    NaClLog(LOG_FATAL, "%s\n", "child vmmap page NaClMprotect failed!");
  }
  if (NaClMprotect((void *)parent_start_addr, tramp_size, PROT_RW) == -1) {
    NaClLog(LOG_FATAL, "%s\n", "parent vmmap page NaClMprotect failed!");
  }

  /* setup trampolines */
  nap_child->nacl_syscall_addr = 0;
  NaClLog(2, "Initializing arch switcher\n");
  NaClInitSwitchToApp(nap_child);
  NaClLog(2, "Installing trampoline\n");
  NaClLoadTrampoline(nap_child);
  NaClLog(2, "Installing springboard\n");
  NaClLoadSpringboard(nap_child);
  /* copy the trampolines from parent */
  memcpy((void *)child_start_addr, (void *)parent_start_addr, tramp_size);
  NaClPatchAddr(nap_child->mem_start, nap_parent->mem_start, (uintptr_t *)child_start_addr, tramp_size);

  /*
   * NaClMemoryProtection also initializes the mem_map w/ information
   * about the memory pages and their current protection value.
   *
   * The contents of the dynamic text region will get remapped as
   * non-writable.
   */
  NaClLog(2, "Applying memory protection\n");
  if (NaClMemoryProtection(nap_child) != LOAD_OK) {
    NaClLog(LOG_FATAL, "%s\n", "child NaClMemoryProtection failed!");
  }

  /* reset permissions to executable */
  NaClVmmapChangeProt(&nap_child->mem_map, tramp_pnum, tramp_npages, PROT_RX);
  NaClVmmapChangeProt(&nap_parent->mem_map, tramp_pnum, tramp_npages, PROT_RX);
  if (NaClMprotect((void *)child_start_addr, tramp_size, PROT_RX) == -1) {
    NaClLog(LOG_FATAL, "%s\n", "child vmmap page NaClMprotect failed!");
  }
  if (NaClMprotect((void *)parent_start_addr, tramp_size, PROT_RX) == -1) {
    NaClLog(LOG_FATAL, "%s\n", "parent vmmap page NaClMprotect failed!");
  }
}

/* set up the fd table for each cage */
void InitializeCage(struct NaClApp *nap, int cage_id) {
  fd_cage_table[cage_id][0] = 0;
  fd_cage_table[cage_id][1] = 1;
  fd_cage_table[cage_id][2] = 2;
  /* set to the next unused (available for dup() etc.) file descriptor */
  nap->fd = 3;
  nap->num_lib = 3;
  nap->num_children = 0;
  nap->cage_id = cage_id;
}

