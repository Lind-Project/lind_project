# Copyright (c) 2014 The Native Client Authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.

ConfigureStep() {
  EnableGlibcCompat
  NACLPORTS_LIBS+=" -l${NACL_CXX_LIB}"
  NACLPORTS_CPPFLAGS+=" -Dpipe=nacl_spawn_pipe"

  if [ "${TOOLCHAIN}" = "glibc" ]; then
    # Glibc's *at functions don't work correctly since they rely on
    # /proc/self/fd/X.  This ensure thats gnulib's replacements are used
    # instead.
    export ac_cv_func_faccessat=no
    export ac_cv_func_fstatat=no
    export ac_cv_func_fchdir=no
    export ac_cv_func_fdopendir=no

    export gl_cv_func_open_directory_works=yes
  fi

  # Grep fails to build NDEBUG defined
  # ib/chdir-long.c:62: error: unused variable 'close_fail'
  NACLPORTS_CFLAGS="${NACLPORTS_CFLAGS/-DNDEBUG/}"
  DefaultConfigureStep
}
