/*
 * Copyright 2008 The Native Client Authors. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can
 * be found in the LICENSE file.
 */

/*
 * NaCl Service Runtime.  Directory descriptor abstraction.
 */

#ifndef NATIVE_CLIENT_SRC_TRUSTED_PLATFORM_OSX_NACL_HOST_DIR_TYPES_H_
#define NATIVE_CLIENT_SRC_TRUSTED_PLATFORM_OSX_NACL_HOST_DIR_TYPES_H_

#include <sys/types.h>
#include <dirent.h>

#include "native_client/src/shared/platform/nacl_sync.h"

#define NACL_DIRENT_BUF_BYTES 4096

struct NaClHostDir {
  struct NaClMutex  mu;
  int               fd;
  size_t            cur_byte;
  size_t            nbytes;
  char              dirent_buf[NACL_DIRENT_BUF_BYTES];
};

#endif  /* NATIVE_CLIENT_SRC_TRUSTED_PLATFORM_OSX_NACL_HOST_DIR_TYPES_H_ */
