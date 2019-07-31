/*
 * Copyright (c) 2012 The Native Client Authors. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#include "native_client/src/shared/srpc/nacl_srpc.h"
#include "native_client/src/shared/srpc/nacl_srpc_internal.h"

nacl_abi_size_t NaClSrpcMaxImcSendmsgSize = 0;

int NaClSrpcModuleInit(void) {
#ifdef __native_client__
  /* TODO(sehr): add call to sysconf. */
  NaClSrpcMaxImcSendmsgSize = 1 << 16;
#else
  /* TODO(sehr): add call to trusted API. */
  NaClSrpcMaxImcSendmsgSize = 1 << 16;
#endif  /* __native_client__ */
  return NaClSrpcLogInit();
}

void NaClSrpcModuleFini(void) {
  NaClSrpcLogFini();
}
