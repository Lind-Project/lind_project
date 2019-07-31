/*
 * Copyright (c) 2012 The Native Client Authors. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#include <string.h>

#include "native_client/src/include/nacl_macros.h"
#include "native_client/src/untrusted/irt/irt.h"
#include "native_client/src/untrusted/irt/irt_interfaces.h"

struct nacl_interface_table {
  const char *name;
  const void *table;
  size_t size;
};

static const struct nacl_interface_table irt_interfaces[] = {
  { NACL_IRT_BASIC_v0_1, &nacl_irt_basic, sizeof(nacl_irt_basic) },
  { NACL_IRT_FDIO_v0_1, &nacl_irt_fdio, sizeof(nacl_irt_fdio) },
  { NACL_IRT_DEV_FDIO_v0_1, &nacl_irt_fdio, sizeof(nacl_irt_fdio) },
  { NACL_IRT_FILENAME_v0_1, &nacl_irt_filename, sizeof(nacl_irt_filename) },
  { NACL_IRT_DEV_FILENAME_v0_2, &nacl_irt_dev_filename,
      sizeof(nacl_irt_dev_filename) },
  { NACL_IRT_MEMORY_v0_1, &nacl_irt_memory_v0_1, sizeof(nacl_irt_memory_v0_1) },
  { NACL_IRT_MEMORY_v0_2, &nacl_irt_memory_v0_2, sizeof(nacl_irt_memory_v0_2) },
  { NACL_IRT_MEMORY_v0_3, &nacl_irt_memory, sizeof(nacl_irt_memory) },
  { NACL_IRT_DYNCODE_v0_1, &nacl_irt_dyncode, sizeof(nacl_irt_dyncode) },
  { NACL_IRT_THREAD_v0_1, &nacl_irt_thread, sizeof(nacl_irt_thread) },
  { NACL_IRT_FUTEX_v0_1, &nacl_irt_futex, sizeof(nacl_irt_futex) },
  { NACL_IRT_MUTEX_v0_1, &nacl_irt_mutex, sizeof(nacl_irt_mutex) },
  { NACL_IRT_COND_v0_1, &nacl_irt_cond, sizeof(nacl_irt_cond) },
  { NACL_IRT_SEM_v0_1, &nacl_irt_sem, sizeof(nacl_irt_sem) },
  { NACL_IRT_TLS_v0_1, &nacl_irt_tls, sizeof(nacl_irt_tls) },
  { NACL_IRT_BLOCKHOOK_v0_1, &nacl_irt_blockhook, sizeof(nacl_irt_blockhook) },
  { NACL_IRT_RESOURCE_OPEN_v0_1, &nacl_irt_resource_open,
      sizeof(nacl_irt_resource_open) },
#ifdef IRT_PPAPI
  { NACL_IRT_PPAPIHOOK_v0_1, &nacl_irt_ppapihook, sizeof(nacl_irt_ppapihook) },
#endif
  { NACL_IRT_RANDOM_v0_1, &nacl_irt_random, sizeof(nacl_irt_random) },
  { NACL_IRT_CLOCK_v0_1, &nacl_irt_clock, sizeof(nacl_irt_clock) },
  { NACL_IRT_DEV_GETPID_v0_1, &nacl_irt_dev_getpid,
    sizeof(nacl_irt_dev_getpid) },
  { NACL_IRT_EXCEPTION_HANDLING_v0_1, &nacl_irt_exception_handling,
    sizeof(nacl_irt_exception_handling) },
  { NACL_IRT_DEV_LIST_MAPPINGS_v0_1, &nacl_irt_dev_list_mappings,
    sizeof(nacl_irt_dev_list_mappings) },
};

size_t nacl_irt_interface(const char *interface_ident,
                          void *table, size_t tablesize) {
  int i;
  for (i = 0; i < NACL_ARRAY_SIZE(irt_interfaces); ++i) {
    if (0 == strcmp(interface_ident, irt_interfaces[i].name)) {
      const size_t size = irt_interfaces[i].size;
      if (size <= tablesize) {
        memcpy(table, irt_interfaces[i].table, size);
        return size;
      }
      break;
    }
  }
  return 0;
}
