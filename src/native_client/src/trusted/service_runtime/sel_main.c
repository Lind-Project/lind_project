/*
 * Copyright (c) 2012 The Native Client Authors. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

/*
 * NaCl Simple/secure ELF loader (NaCl SEL). The main entry point for the binary.
 */
#include "native_client/src/include/portability.h"
#include "native_client/src/include/portability_io.h"

#if NACL_OSX
#  include <crt_externs.h>
#endif

#if NACL_LINUX
#  include <getopt.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* avoid errors caused by conflicts with feature_test_macros(7) */
#undef _POSIX_C_SOURCE
#undef _XOPEN_SOURCE

#include "native_client/src/shared/gio/gio.h"
#include "native_client/src/shared/imc/nacl_imc_c.h"
#include "native_client/src/shared/platform/nacl_check.h"
#include "native_client/src/shared/platform/nacl_exit.h"
#include "native_client/src/shared/platform/nacl_log.h"
#include "native_client/src/shared/platform/nacl_sync.h"
#include "native_client/src/shared/platform/nacl_sync_checked.h"
#include "native_client/src/shared/platform/lind_platform.h"
#include "native_client/src/shared/srpc/nacl_srpc.h"

#include "native_client/src/trusted/desc/nacl_desc_base.h"
#include "native_client/src/trusted/desc/nacl_desc_io.h"
#include "native_client/src/trusted/fault_injection/fault_injection.h"
#include "native_client/src/trusted/fault_injection/test_injection.h"
#include "native_client/src/trusted/perf_counter/nacl_perf_counter.h"
#include "native_client/src/trusted/service_runtime/env_cleanser.h"
#include "native_client/src/trusted/service_runtime/include/sys/fcntl.h"
#include "native_client/src/trusted/service_runtime/load_file.h"
#include "native_client/src/trusted/service_runtime/nacl_app.h"
#include "native_client/src/trusted/service_runtime/nacl_all_modules.h"
#include "native_client/src/trusted/service_runtime/nacl_bootstrap_channel_error_reporter.h"
#include "native_client/src/trusted/service_runtime/nacl_debug_init.h"
#include "native_client/src/trusted/service_runtime/nacl_error_log_hook.h"
#include "native_client/src/trusted/service_runtime/nacl_globals.h"
#include "native_client/src/trusted/service_runtime/nacl_signal.h"
#include "native_client/src/trusted/service_runtime/nacl_syscall_common.h"
#include "native_client/src/trusted/service_runtime/nacl_valgrind_hooks.h"
#include "native_client/src/trusted/service_runtime/osx/mach_exception_handler.h"
#include "native_client/src/trusted/service_runtime/outer_sandbox.h"
#include "native_client/src/trusted/service_runtime/sel_ldr.h"
#include "native_client/src/trusted/service_runtime/sel_qualify.h"
#include "native_client/src/trusted/service_runtime/win/exception_patch/ntdll_patch.h"
#include "native_client/src/trusted/service_runtime/win/debug_exception_handler.h"


#include "native_client/src/trusted/service_runtime/sel_ldr.h"
#include "native_client/src/trusted/service_runtime/include/bits/nacl_syscalls.h"
#include <time.h>
#include <sys/shm.h>
#include <sys/mman.h>

#if !NACL_OSX
# define NaClEnableOuterSandbox NULL
#endif

static void (*g_enable_outer_sandbox_func)(void) = NaClEnableOuterSandbox;

void NaClSetEnableOuterSandboxFunc(void (*func)(void)) {
  g_enable_outer_sandbox_func = func;
}

static void VmentryPrinter(void *state, struct NaClVmmapEntry *vmep) {
  UNREFERENCED_PARAMETER(state);
  fprintf(stderr, "page num 0x%06x\n", (uint32_t)vmep->page_num);
  fprintf(stderr, "num pages %d\n", (uint32_t)vmep->npages);
  fprintf(stderr, "prot bits %x\n", vmep->prot);
}

static void PrintVmmap(struct NaClApp *nap) {
  NaClXMutexLock(&nap->mu);
  NaClVmmapVisit(&nap->mem_map, VmentryPrinter, NULL);
  NaClXMutexUnlock(&nap->mu);
}

struct redir {
  struct redir                  *next;
  int                           nacl_desc;
  enum { HOST_DESC, IMC_DESC }  tag;
  union {
    struct { int d; int mode; } host;
    NaClHandle                  handle;
    struct NaClSocketAddress    addr;
  } u;
};

int ImportModeMap(char opt) {
  switch (opt) {
    case 'h':
      return O_RDWR;
    case 'r':
      return O_RDONLY;
    case 'w':
      return O_WRONLY;
  }
  NaClLog(1, "option %c not understood as a host descriptor import mode\n", opt);
  exit(1);
  /* NOTREACHED */
}

static void PrintUsage(void) {
  /* NOTE: this is broken up into multiple statements to work around
           the constant string size limit */
  fprintf(stderr,
          "Usage: sel_ldr [-h d:D] [-r d:D] [-w d:D] [-i d:D]\n"
          "               [-f nacl_file]\n"
          "               [-l log_file]\n"
          "               [-X d] [-acFglQRsSQv]\n"
          "               -- [nacl_file] [args]\n"
          "\n");
  fprintf(stderr,
          " -h\n"
          " -r\n"
          " -w associate a host POSIX descriptor D with app desc d\n"
          "    that was opened in O_RDWR, O_RDONLY, and O_WRONLY modes\n"
          "    respectively\n"
          " -i associates an IMC handle D with app desc d\n"
          " -f file to load; if omitted, 1st arg after \"--\" is loaded\n"
          " -B additional ELF file to load as a blob library\n"
          " -v increases verbosity\n"
          " -X create a bound socket and export the address via an\n"
          "    IMC message to a corresponding inherited IMC app descriptor\n"
          "    (use -1 to create the bound socket / address descriptor\n"
          "    pair, but that no export via IMC should occur)\n");
  fprintf(stderr,
          " -R an RPC supplies the NaCl module.\n"
          "    No nacl_file argument is expected, and the -f flag cannot be\n"
          "    used with this flag.\n"
          "\n"
          " (testing flags)\n"
          " -a allow file access plus some other syscalls! dangerous!\n"
          " -c ignore validator! dangerous! Repeating this option twice skips\n"
          "    validation completely.\n"
          " -F fuzz testing; quit after loading NaCl app\n"
          " -g enable gdb debug stub.  Not secure on x86-64 Windows.\n"
          " -l <file>  write log output to the given file\n"
          " -Q disable platform qualification (dangerous!)\n"
          " -s safely stub out non-validating instructions\n"
          " -S enable signal handling.  Not supported on Windows.\n"
          " -E <name=value>|<name> set an environment variable\n"
          " -Z use fixed feature x86 CPU mode\n"
          );  /* easier to add new flags/lines */
}

static const struct option longopts[] = {
  { "r_debug", required_argument, NULL, 'D' },
  { "reserved_at_zero", required_argument, NULL, 'z' },
  { NULL, 0, NULL, 0 }
};

static int my_getopt(int argc, char *const *argv, const char *shortopts) {
  return getopt_long(argc, argv, shortopts, longopts, NULL);
}

#if NACL_LINUX
# define getopt my_getopt
  static const char *const optstring = "+D:z:aB:ceE:f:Fgh:i:l:Qr:RsSvw:X:Z";
#else
# define NaClHandleRDebug(A, B) do { /* no-op */ } while (0)
# define NaClHandleReservedAtZero(A) do { /* no-op */ } while (0)
  static const char *const optstring = "aB:ceE:f:Fgh:i:l:Qr:RsSvw:X:Z";
#endif

int NaClSelLdrMain(int argc, char **argv) {
  int                           opt;
  char                          *rest;
  struct redir                  *entry;
  struct redir                  *redir_queue;
  struct redir                  **redir_qend;
  struct NaClApp                state = {0};
  struct NaClApp                *nap = &state;
  struct NaClDesc               *blob_file = NULL;
  struct GioFile                gout;
  struct DynArray               env_vars;
  struct NaClPerfCounter        time_all_main;
  struct NaClEnvCleanser        env_cleanser;
  NaClErrorCode                 errcode = LOAD_INTERNAL;
  int                           rpc_supplies_nexe = 0;
  int                           export_addr_to = -1;
  int                           ret_code;
  int                           verbosity = 0;
  int                           fuzzing_quit_after_load = 0;
  int                           debug_mode_bypass_acl_checks = 0;
  int                           debug_mode_ignore_validator = 0;
  int                           skip_qualification = 0;
  int                           handle_signals = 0;
  int                           enable_debug_stub = 0;
  char                          *blob_library_file = NULL;
  char                          *log_file = NULL;
  const char                    **envp;
  clock_t                       nacl_main_begin;
  clock_t                       nacl_main_finish;
  clock_t                       nacl_initialization_finish;
  double                        nacl_main_spent;
  double                        nacl_initialization_spent;
  clock_t                       nacl_user_program_begin;
  clock_t                       nacl_user_program_finish;
  double                        nacl_user_program_spent;
  #ifdef SYSCALL_TIMING
  double                        nacl_syscall_total_time;
  double                        lind_syscall_total_time;
  #endif

#if NACL_OSX
  /* Mac dynamic libraries cannot access the environ variable directly. */
  envp = (const char **)*_NSGetEnviron();
#else
  /* Overzealous code style check is overzealous. */
  /* @IGNORE_LINES_FOR_CODE_HYGIENE[1] */
  extern char **environ;
  envp = (const char **)environ;
#endif

  nacl_syscall_counter = 0;
  lind_syscall_counter = 0;
  nacl_syscall_trace_level_counter = 0;
  ret_code = 1;
  redir_queue = NULL;
  redir_qend = &redir_queue;

  nacl_main_begin = clock();

  if (!DynArrayCtor(&nap->children, 16)) {
    NaClLog(1, "%s\n", "Failed to initialize children list");
  }

  NaClAllModulesInit();
  NaClBootstrapChannelErrorReporterInit();
  NaClErrorLogHookInit(NaClBootstrapChannelErrorReporter, &state);

  verbosity = NaClLogGetVerbosity();

  NaClPerfCounterCtor(&time_all_main, "SelMain");
  fflush(NULL);
  NaClDebugExceptionHandlerStandaloneHandleArgs(argc, argv);

  if (!GioFileRefCtor(&gout, stdout)) {
    NaClLog(1, "%s\n", "Could not create general standard output channel");
    exit(1);
  }
  if (!NaClAppCtor(&state)) {
    NaClLog(1, "%s\n", "NaClAppCtor() failed");
  }
  if (!DynArrayCtor(&env_vars, 0)) {
    NaClLog(1, "%s\n", "Failed to allocate env var array");
  }

  /*
   * On platforms with glibc getopt, require POSIXLY_CORRECT behavior,
   * viz, no reordering of the arglist -- stop argument processing as
   * soon as an unrecognized argument is encountered, so that, for
   * example, in the invocation
   *
   *   sel_ldr foo.nexe -vvv
   *
   * the -vvv flags are made available to the nexe, rather than being
   * consumed by getopt.  This makes the behavior of the Linux build
   * of sel_ldr consistent with the Windows and OSX builds.
   */
  while ((opt = getopt(argc, argv, optstring)) != -1) {
    switch (opt) {
      case 'a':
        NaClLog(1, "%s\n", "DEBUG MODE ENABLED (bypass acl)");
        debug_mode_bypass_acl_checks = 1;
        break;
      case 'B':
        blob_library_file = optarg;
        break;
      case 'c':
        ++debug_mode_ignore_validator;
        break;
      case 'D':
        NaClHandleRDebug(optarg, argv[0]);
        break;
      case 'e':
        nap->enable_exception_handling = 1;
        break;
      case 'E':
        /*
         * For simplicity, we treat the environment variables as a
         * list of strings rather than a key/value mapping.  We do not
         * try to prevent duplicate keys or require the strings to be
         * of the form "KEY=VALUE".  This is in line with how execve()
         * works in Unix.
         *
         * We expect that most callers passing "-E" will either pass
         * in a fixed list or will construct the list using a
         * high-level language, in which case de-duplicating keys
         * outside of sel_ldr is easier.  However, we could do
         * de-duplication here if it proves to be worthwhile.
         */
        if (!DynArraySet(&env_vars, env_vars.num_entries, optarg)) {
          NaClLog(1, "%s\n", "Adding item to env_vars failed");
        }
        break;
      case 'f':
        nap->nacl_file = optarg;
        break;
      case 'F':
        fuzzing_quit_after_load = 1;
        break;
      case 'g':
        enable_debug_stub = 1;
        break;
      case 'h': /* fallthrough */
      case 'r': /* fallthrough */
      case 'w':
        /* import host descriptor */
        entry = malloc(sizeof *entry);
        if (!entry) {
          NaClLog(1, "%s\n", "No memory for redirection queue");
          exit(EXIT_FAILURE);
        }
        entry->next = NULL;
        entry->nacl_desc = strtol(optarg, &rest, 0);
        entry->tag = HOST_DESC;
        entry->u.host.d = strtol(rest + 1, NULL, 0);
        entry->u.host.mode = ImportModeMap(opt);
        *redir_qend = entry;
        redir_qend = &entry->next;
        break;
      case 'i':
        /* import IMC handle */
        entry = malloc(sizeof *entry);
        if (NULL == entry) {
          NaClLog(1, "%s\n", "No memory for redirection queue");
          exit(1);
        }
        entry->next = NULL;
        entry->nacl_desc = strtol(optarg, &rest, 0);
        entry->tag = IMC_DESC;
        entry->u.handle = (NaClHandle)strtol(rest + 1, NULL, 0);
        *redir_qend = entry;
        redir_qend = &entry->next;
        break;
      case 'l':
        log_file = optarg;
        break;
      case 'Q':
        NaClLog(1, "%s\n",
                 "PLATFORM QUALIFICATION DISABLED BY -Q - "
                "Native Client's sandbox will be unreliable!\n");
        skip_qualification = 1;
        break;
      case 'R':
        rpc_supplies_nexe = 1;
        break;
      /* case 'r':  with 'h' and 'w' above */
      case 's':
        if (nap->validator->stubout_mode_implemented) {
          nap->validator_stub_out_mode = 1;
        } else {
           NaClLog(1, "%s\n", "stub_out_mode is not supported, disabled");
        }
        break;
      case 'S':
        handle_signals = 1;
        break;
      case 'v':
        ++verbosity;
        NaClLogIncrVerbosity();
        break;
      /* case 'w':  with 'h' and 'r' above */
      case 'X':
        export_addr_to = strtol(optarg, NULL, 0);
        break;
      case 'z':
        NaClHandleReservedAtZero(optarg);
        break;
      case 'Z':
        if (nap->validator->readonly_text_implemented) {
          NaClLog(1, "%s\n", "Enabling Fixed-Feature CPU Mode");
          nap->fixed_feature_cpu_mode = 1;
          if (!nap->validator->FixCPUFeatures(nap->cpu_features)) {
            NaClLog(1, "%s\n", "This CPU lacks features required by fixed-function CPU mode.");
            exit(EXIT_FAILURE);
          }
        } else {
           NaClLog(1, "%s\n", "fixed_feature_cpu_mode is not supported");
           exit(EXIT_FAILURE);
        }
        break;

      default:
        NaClLog(1, "ERROR: unknown option: [%c]\n\n", opt);
        PrintUsage();
        exit(-1);
    }
  }

  if (!LindPythonInit()) {
      fflush(NULL);
      exit(EXIT_FAILURE);
  }

  if (debug_mode_ignore_validator == 1) {
    NaClLog(1, "%s\n", "DEBUG MODE ENABLED (ignore validator)");
  } else if (debug_mode_ignore_validator > 1) {
    NaClLog(1, "%s\n", "DEBUG MODE ENABLED (skip validator)");
  }

  if (verbosity) {
    int        ix;
    char const *separator = "";
    (void)separator;
    NaClLog(1, "%s", "sel_ldr argument list:");
    for (ix = 0; ix < argc; ++ix) {
      NaClLog(1, "%s%s", separator, argv[ix]);
      separator = " ";
      (void)separator;
    }
    NaClLog(1, "%s", "\n");
  }

  if (debug_mode_bypass_acl_checks) {
    NaClInsecurelyBypassAllAclChecks();
  }

  /*
   * change stdout/stderr to log file now, so that subsequent error
   * messages will go there.  unfortunately, error messages that
   * result from getopt processing -- usually out-of-memory, which
   * shouldn't happen -- won't show up.
   */
  if (log_file) {
    NaClLogSetFile(log_file);
  }

  if (rpc_supplies_nexe) {
    if (nap->nacl_file) {
      NaClLog(LOG_FATAL, "%s\n", "sel_ldr: mutually exclusive flags -f and -R both used");
    }
    /* post: NULL == nap->nacl_file */
    if (export_addr_to < 0) {
      NaClLog(LOG_FATAL, "%s\n", "sel_ldr: -R requires -X to set up secure command channel");
    }
  } else {
    if (!nap->nacl_file && optind > argc) {
      NaClLog(LOG_FATAL, "%s\n", "No nacl file specified");
    }
    /* post: NULL != nap->nacl_file */
    if (!nap->nacl_file && optind < argc) {
      nap->nacl_file = argv[optind];
      ++optind;
    }
  }
  /*
   * either nap->nacl_file or rpc_supplies_nexe
   * must be non-NULL, but not both
   */
  CHECK(!!nap->nacl_file ^ !!rpc_supplies_nexe);

  /* to be passed to NaClMain, eventually... */
  argv[--optind] = "NaClMain";
  state.ignore_validator_result = debug_mode_ignore_validator > 0;
  state.skip_validator = debug_mode_ignore_validator > 1;

/*
 * `_HOST_OSX` is defined so that
 * `if (... && _HOST_OSX)` expands
 * to a valid conditional in when
 * run through a linter
 *
 * -jp
 */
#if NACL_OSX
# define _HOST_OSX 1
#else
# define _HOST_OSX 0
#endif
  if (getenv("NACL_UNTRUSTED_EXCEPTION_HANDLING")) {
    state.enable_exception_handling = 1;
  }
  /*
   * TODO(mseaborn): Always enable the Mach exception handler on Mac
   * OS X, and remove handle_signals and sel_ldr's "-S" option.
   */
  if (state.enable_exception_handling || enable_debug_stub || (handle_signals && _HOST_OSX)) {
#if NACL_WINDOWS
    state.attach_debug_exception_handler_func = NaClDebugExceptionHandlerStandaloneAttach;
#elif NACL_LINUX
    /* NaCl's signal handler is always enabled on Linux. */
#elif NACL_OSX
    if (!NaClInterceptMachExceptions()) {
      NaClLog(1, "%s\n", "ERROR setting up Mach exception interception.");
      exit(-1);
    }
#else
# error Unknown host OS
#endif
  }
#undef _HOST_OSX

  errcode = LOAD_OK;

  /*
   * in order to report load error to the browser plugin through the
   * secure command channel, we do not immediate jump to cleanup code
   * on error.  rather, we continue processing (assuming earlier
   * errors do not make it inappropriate) until the secure command
   * channel is set up, and then bail out.
   */

  /*
   * Ensure the platform qualification checks pass.
   *
   * NACL_DANGEROUS_SKIP_QUALIFICATION_TEST is used by tsan / memcheck
   * (see src/third_party/valgrind/).
   */
  if (!skip_qualification && getenv("NACL_DANGEROUS_SKIP_QUALIFICATION_TEST")) {
    NaClLog(1, "%s\n",
            "PLATFORM QUALIFICATION DISABLED BY ENVIRONMENT - "
            "Native Client's sandbox will be unreliable!");
    skip_qualification = 1;
  }

  if (!skip_qualification) {
    /* TODO: fix gdb segfaults caused by this function */
    NaClErrorCode pq_error = LOAD_OK;
    /* NaClErrorCode pq_error = NACL_FI_VAL("pq", NaClErrorCode, NaClRunSelQualificationTests()); */
    if (LOAD_OK != pq_error) {
      errcode = pq_error;
      nap->module_load_status = pq_error;
      NaClLog(1, "%d: Error while loading \"%s\": %s\n",
              __LINE__,
              !nap->nacl_file ? nap->nacl_file : "(no file, to-be-supplied-via-RPC)",
              NaClErrorString(errcode));
    }
  }

#if NACL_LINUX
  NaClSignalHandlerInit();
#endif
  /*
   * Patch the Windows exception dispatcher to be safe in the case of
   * faults inside x86-64 sandboxed code.  The sandbox is not secure
   * on 64-bit Windows without this.
   */
#if (NACL_WINDOWS && NACL_ARCH(NACL_BUILD_ARCH) == NACL_x86 && NACL_BUILD_SUBARCH == 64)
  NaClPatchWindowsExceptionDispatcher();
#endif
  NaClSignalTestCrashOnStartup();

  /*
   * Open both files first because (on Mac OS X at least)
   * NaClAppLoadFile() enables an outer sandbox.
   */
  if (blob_library_file) {
    NaClFileNameForValgrind(blob_library_file);
    blob_file = (struct NaClDesc *) NaClDescIoDescOpen(blob_library_file,
                                                       NACL_ABI_O_RDONLY, 0);
    if (!blob_file) {
      perror("sel_main");
      NaClLog(1, "Cannot open \"%s\".\n", blob_library_file);
      exit(EXIT_FAILURE);
    }
    NaClPerfCounterMark(&time_all_main, "SnapshotBlob");
    NaClPerfCounterIntervalLast(&time_all_main);
  }

  NaClAppInitialDescriptorHookup(nap);

  if (!rpc_supplies_nexe) {
    if (LOAD_OK == errcode) {
      NaClLog(2, "Loading nacl file %s (non-RPC)\n", nap->nacl_file);
      errcode = NaClAppLoadFileFromFilename(nap, nap->nacl_file);

      if (LOAD_OK != errcode) {
        NaClLog(1, "%d: Error while loading \"%s\": %s\n",
                __LINE__,
                nap->nacl_file,
                NaClErrorString(errcode));
        fprintf(stderr,
                ("Using the wrong type of nexe (nacl-x86-32"
                 " on an x86-64 or vice versa)\n"
                 "or a corrupt nexe file may be"
                 " responsible for this error.\n"));
      }

      NaClPerfCounterMark(&time_all_main, "AppLoadEnd");
      NaClPerfCounterIntervalLast(&time_all_main);

      NaClXMutexLock(&nap->mu);
      nap->module_load_status = errcode;
      NaClXCondVarBroadcast(&nap->cv);
      NaClXMutexUnlock(&nap->mu);
    }

    if (fuzzing_quit_after_load) {
      exit(EXIT_SUCCESS);
    }
  }

  /*
   * Execute additional I/O redirections.  NB: since the NaClApp
   * takes ownership of host / IMC socket descriptors, all but
   * the first run will not get access if the NaClApp closes
   * them.  Currently a normal NaClApp process exit does not
   * close descriptors, since the underlying host OS will do so
   * as part of service runtime exit.
   */
  NaClLog(4, "Processing I/O redirection/inheritance from command line\n");
  for (entry = redir_queue; entry && entry->next; entry = entry->next) {
    switch (entry->tag) {
      case HOST_DESC:
        NaClAddHostDescriptor(nap, entry->u.host.d,
                              entry->u.host.mode, entry->nacl_desc);
        break;
      case IMC_DESC:
        NaClAddImcHandle(nap, entry->u.handle, entry->nacl_desc);
        break;
    }
  }
  free(entry);

  /*
   * If export_addr_to is set to a non-negative integer, we create a
   * bound socket and socket address pair and bind the former to
   * descriptor NACL_SERVICE_PORT_DESCRIPTOR (3 [see sel_ldr.h]) and
   * the latter to descriptor NACL_SERVICE_ADDRESS_DESCRIPTOR (4).
   * The socket address is sent to the export_addr_to descriptor.
   *
   * The service runtime also accepts a connection on the bound socket
   * and spawns a secure command channel thread to service it.
   */
  if (0 <= export_addr_to) {
    NaClCreateServiceSocket(nap);
    /*
     * LOG_FATAL errors that occur before NaClSetUpBootstrapChannel will
     * not be reported via the crash log mechanism (for Chromium
     * embedding of NaCl, shown in the JavaScript console).
     *
     * Some errors, such as due to NaClRunSelQualificationTests, do not
     * trigger a LOG_FATAL but instead set module_load_status to be sent
     * in the start_module RPC reply.  Log messages associated with such
     * errors would be seen, since NaClSetUpBootstrapChannel will get
     * called.
     */
    NaClSetUpBootstrapChannel(nap, (NaClHandle) export_addr_to);
    /*
     * NB: spawns a thread that uses the command channel.  we do
     * this after NaClAppLoadFile so that NaClApp object is more
     * fully populated.  Hereafter any changes to nap should be done
     * while holding locks.
     */
    NaClSecureCommandChannel(nap);
  }

  /*
   * May have created a thread, so need to synchronize uses of nap
   * contents henceforth.
   */

  if (rpc_supplies_nexe) {
    errcode = NaClWaitForLoadModuleStatus(nap);
    NaClPerfCounterMark(&time_all_main, "WaitForLoad");
    NaClPerfCounterIntervalLast(&time_all_main);
  } else {
    /**************************************************************************
     * TODO(bsy): This else block should be made unconditional and
     * invoked after the LoadModule RPC completes, eliminating the
     * essentially dulicated code in latter part of NaClLoadModuleRpc.
     * This cannot be done until we have full saucer separation
     * technology, since Chrome currently uses sel_main_chrome.c and
     * relies on the functionality of the duplicated code.
     *************************************************************************/
    if (LOAD_OK == errcode) {
      if (verbosity) {
        gprintf((struct Gio *) &gout, "printing NaClApp details\n");
        NaClAppPrintDetails(nap, (struct Gio *) &gout);
      }

      /*
       * Finish setting up the NaCl App.  On x86-32, this means
       * allocating segment selectors.  On x86-64 and ARM, this is
       * (currently) a no-op.
       */
      errcode = NaClAppPrepareToLaunch(nap);
      if (LOAD_OK != errcode) {
        nap->module_load_status = errcode;
        NaClLog(1, "NaClAppPrepareToLaunch returned %d", errcode);
      }
    }

    /* Give debuggers a well known point at which xlate_base is known.  */
    NaClGdbHook(&state);
  }

/*
 * `_HOST_OSX` is defined so that
 * `if (... && _HOST_OSX)` expands
 * to a valid conditional in when
 * run through a linter
 *
 * -jp
 */
#if NACL_OSX
# define _HOST_OSX 1
#else
# define _HOST_OSX 0
#endif
  /*
   * Tell the debug stub to bind a TCP port before enabling the outer
   * sandbox.  This is only needed on Mac OS X since that is the only
   * platform where we have an outer sandbox in standalone sel_ldr.
   * In principle this call should work on all platforms, but Windows
   * XP seems to have some problems when we do bind()/listen() on a
   * separate thread from accept().
   */
  if (enable_debug_stub && _HOST_OSX) {
    if (!NaClDebugBindSocket()) {
      exit(1);
    }
  }
#undef _HOST_OSX

  /*
   * Enable the outer sandbox, if one is defined.  Do this as soon as
   * possible.
   *
   * This must come after NaClWaitForLoadModuleStatus(), which waits
   * for another thread to have called NaClAppLoadFile().
   * NaClAppLoadFile() does not work inside the Mac outer sandbox in
   * standalone sel_ldr when using a dynamic code area because it uses
   * NaClCreateMemoryObject() which opens a file in /tmp.
   *
   * We cannot enable the sandbox if file access is enabled.
   */
  if (!NaClAclBypassChecks && g_enable_outer_sandbox_func) {
    g_enable_outer_sandbox_func();
  }

  if (blob_library_file) {
    if (nap->irt_loaded) {
      NaClLog(1, "%s\n", "IRT loaded via command channel; ignoring -B irt");
    } else if (LOAD_OK == errcode) {
      NaClLog(2, "Loading blob file %s\n", blob_library_file);
      errcode = NaClAppLoadFileDynamically(nap, blob_file,
                                           NULL);
      if (LOAD_OK == errcode) {
        nap->irt_loaded = 1;
      } else {
        NaClLog(1, "%d: Error while loading \"%s\": %s\n", __LINE__,
                blob_library_file,
                NaClErrorString(errcode));
      }
      NaClPerfCounterMark(&time_all_main, "BlobLoaded");
      NaClPerfCounterIntervalLast(&time_all_main);
    }

    NaClDescUnref(blob_file);
    if (verbosity) {
      gprintf((struct Gio *) &gout, "printing post-IRT NaClApp details\n");
      NaClAppPrintDetails(nap, (struct Gio *) &gout);
    }
  }

  /*
   * Print out a marker for scripts to use to mark the start of app
   * output.
   */
  NaClLog(1, "NACL: Application output follows\n");

  /*
   * Make sure all the file buffers are flushed before entering
   * the application code.
   */
  fflush(NULL);

  if (nap->secure_service) {
    NaClErrorCode start_result;
    /*
     * wait for start_module RPC call on secure channel thread.
     */
    start_result = NaClWaitForStartModuleCommand(nap);
    NaClPerfCounterMark(&time_all_main, "WaitedForStartModuleCommand");
    NaClPerfCounterIntervalLast(&time_all_main);
    if (LOAD_OK == errcode) {
      errcode = start_result;
    }
  }

  /*
   * error reporting done; can quit now if there was an error earlier.
   */
  if (LOAD_OK != errcode) {
    NaClLog(4,
            "Not running app code since errcode is %s (%d)\n",
            NaClErrorString(errcode),
            errcode);
    goto done;
  }

  if (!DynArraySet(&env_vars, env_vars.num_entries, NULL)) {
    NaClLog(1, "%s\n", "Adding env_vars NULL terminator failed");
  }

  NaClEnvCleanserCtor(&env_cleanser, 0);
  if (!NaClEnvCleanserInit(&env_cleanser, envp,
          (char const *const *)env_vars.ptr_array)) {
    NaClLog(1, "%s\n", "Failed to initialise env cleanser");
  }

  if (!NaClAppLaunchServiceThreads(nap)) {
    NaClLog(1, "%s\n", "Launch service threads failed");
    goto done;
  }
  if (enable_debug_stub) {
    if (!NaClDebugInit(nap)) {
      goto done;
    }
  }

  NACL_TEST_INJECTION(BeforeMainThreadLaunches, ());
  InitializeCage(nap, 1);
  NaClLog(1, "[NaCl Main][Cage 1] argv[3]: %s \n\n", (argv + optind)[3]);
  NaClLog(1, "[NaCl Main][Cage 1] argv[4]: %s \n\n", (argv + optind)[4]);
  NaClLog(1, "[NaCl Main][Cage 1] argv num: %d \n\n", argc - optind);

  nap->argc = argc - optind;
  nap->argv = argv + optind;
  nap->binary = argv[optind + 3];

  NaClLog(1, "%s\n", "Initializing pipe table mutexes/conditional variables.");

  for (size_t i = 0; i < PIPE_NUM_MAX; i++) {
    if (!NaClFastMutexCtor(&pipe_table[i].mu)) {
      NaClLog(LOG_ERROR, "%s\n", "pipe mutex ctor failed");
      goto done;
    }
    pipe_table[i].xfer_done = true;
    pipe_table[i].is_closed = false;
  }

  NaClLog(1, "%s\n\n", "[NaCl Main Loader] before creation of the cage to run user program!");
  nap->clean_environ = NaClEnvCleanserEnvironment(&env_cleanser);
  nacl_initialization_finish = clock();
  if (!NaClCreateMainThread(nap,
                            argc - optind,
                            argv + optind,
                            nap->clean_environ)) {
    NaClLog(LOG_ERROR, "%s\n", "creating main thread failed");
    goto done;
  }
  nacl_user_program_begin = clock();

  // ***********************************************************************
  // yiwen: cleanup and exit
  // ***********************************************************************
  NaClEnvCleanserDtor(&env_cleanser);
  NaClPerfCounterMark(&time_all_main, "CreateMainThread");
  NaClPerfCounterIntervalLast(&time_all_main);
  DynArrayDtor(&env_vars);

  /* yiwen: waiting for running cages to exit */
  ret_code = NaClWaitForMainThreadToExit(nap);
  nacl_user_program_finish = clock();
  NaClPerfCounterMark(&time_all_main, "WaitForMainThread");
  NaClPerfCounterIntervalLast(&time_all_main);
  NaClPerfCounterMark(&time_all_main, "SelMainEnd");
  NaClPerfCounterIntervalTotal(&time_all_main);
  NaClEnvCleanserDtor(&env_cleanser);
  DynArrayDtor(&env_vars);

  /*
   * exit_group or equiv kills any still running threads while module
   * addr space is still valid.  otherwise we'd have to kill threads
   * before we clean up the address space.
   */

  nacl_main_finish = clock();

  NaClLog(1, "%s\n", "[NaClMain] End of the program! \n");
  nacl_main_spent = (double)(nacl_main_finish - nacl_main_begin) / CLOCKS_PER_SEC;
  NaClLog(1, "[NaClMain] NaCl main program time spent = %f \n", nacl_main_spent);
  nacl_initialization_spent = (double)(nacl_initialization_finish - nacl_main_begin) / CLOCKS_PER_SEC;
  NaClLog(1, "[NaClMain] NaCl initialization time spent = %f \n", nacl_initialization_spent);
  nacl_user_program_spent = (double)(nacl_user_program_finish - nacl_user_program_begin) / CLOCKS_PER_SEC;
  NaClLog(1, "[NaClMain] NaCl user program time spent = %f \n", nacl_user_program_spent);

#ifdef SYSCALL_TIMING
  NaClLog(1, "%s\n", "[NaClMain] NaCl system call timing enabled! ");
  NaClLog(1, "%s\n", "[NaClMain] Start printing out results now: ");
  NaClLog(1, "[NaClMain] NaCl global system call counter = %d \n", nacl_syscall_counter);
  NaClLog(1, "%s\n", "[NaClMain] Print out system call timing table: ");
  nacl_syscall_total_time = 0.0;
  for (size_t i = 0; i < NACL_MAX_SYSCALLS; i++) {
    NaClLog(1, "sys_num: %d, invoked times: %d, execution time: %f \n", i, nacl_syscall_invoked_times[i], nacl_syscall_execution_time[i]);
    nacl_syscall_total_time +=  nacl_syscall_execution_time[i];
  }

  NaClLog(1, "[NaClMain] NaCl system call total time: %f \n\n", nacl_syscall_total_time);
  NaClLog(1, "[NaClMain] Lind system call counter = %d \n", lind_syscall_counter);
  NaClLog(1, "%s\n", "[NaClMain] Print out Lind system call timing table: ");
  lind_syscall_total_time = 0.0;
  for (size_t i = 0; i < LIND_MAX_SYSCALLS; i++) {
    NaClLog(1, "sys_num: %d, invoked times: %d, execution time: %f \n", i, lind_syscall_invoked_times[i], lind_syscall_execution_time[i]);
    lind_syscall_total_time +=  lind_syscall_execution_time[i];
  }

  NaClLog(1, "[NaClMain] Lind system call total time: %f \n", lind_syscall_total_time);
  NaClLog(1, "%s\n", "[NaClMain] Results printing out: done! ");
#endif

  NaClLog(1, "[Performance results] LindPythonInit(): %f \n", time_counter);
  LindPythonFinalize();
  NaClExit(ret_code);

done:
  fflush(NULL);

  if (verbosity) {
    gprintf((struct Gio *) &gout, "exiting -- printing NaClApp details\n");
    NaClAppPrintDetails(nap, (struct Gio *) &gout);
    printf("Dumping vmmap.\n"); fflush(NULL);
    PrintVmmap(nap);
    fflush(NULL);
  }

  /*
   * If there is a secure command channel, we sent an RPC reply with
   * the reason that the nexe was rejected.  If we exit now, that
   * reply may still be in-flight and the various channel closure (esp
   * reverse channel) may be detected first.  This would result in a
   * crash being reported, rather than the error in the RPC reply.
   * Instead, we wait for the hard-shutdown on the command channel.
   */
  if (LOAD_OK != errcode) {
    NaClBlockIfCommandChannelExists(nap);
  }
  NaClLog(1, "%s\n", "Done.");

#if NACL_LINUX
  NaClSignalHandlerFini();
#endif
  NaClAllModulesFini();

  if(!LindPythonFinalize()) {
      fflush(NULL);
      exit(EXIT_SUCCESS);
  }

  NaClExit(ret_code);

  /* silence unused variable warnings until timing is implemented properly -jp */
  UNREFERENCED_PARAMETER(nacl_main_spent);
  UNREFERENCED_PARAMETER(nacl_initialization_spent);
  UNREFERENCED_PARAMETER(nacl_user_program_begin);
  UNREFERENCED_PARAMETER(nacl_user_program_finish);
  UNREFERENCED_PARAMETER(nacl_user_program_spent);

  /* NOT REACHED */
  return ret_code;
}
