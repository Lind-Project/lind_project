# Copyright 2015 The Native Client Authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.

EnableCliMain
EnableGlibcCompat

if [ "${NACL_LIBC}" = "newlib" ]; then
  # setitimer and getitimer not available in newlib, no plan to implement them
  # TODO(dt) remove this flag once this issue is sorted.
  EXTRA_CONFIGURE_ARGS+=" --disable-libevent-regress"
fi
