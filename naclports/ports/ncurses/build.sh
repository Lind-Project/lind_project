# Copyright (c) 2012 The Native Client Authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.

EXECUTABLES="progs/clear${NACL_EXEEXT}"

EXTRA_CONFIGURE_ARGS+=" --disable-database"
EXTRA_CONFIGURE_ARGS+=" --with-fallbacks=xterm-256color,vt100"
EXTRA_CONFIGURE_ARGS+=" --disable-termcap"
# Without this ncurses headers will be installed include/ncurses
EXTRA_CONFIGURE_ARGS+=" --enable-overwrite"
EXTRA_CONFIGURE_ARGS+=" --without-ada"

if [ "${NACL_SHARED}" = 1 ]; then
  EXTRA_CONFIGURE_ARGS+=" --with-shared"
fi

if [ "${TOOLCHAIN}" = "pnacl" ]; then
  EXTRA_CONFIGURE_ARGS+=" --without-cxx-binding"
fi


EnableGlibcCompat

export cf_cv_ar_flags=${NACL_ARFLAGS}
NACL_ARFLAGS=""

if [[ ${TOOLCHAIN} == emscripten ]]; then
  export cf_cv_posix_c_source=no
fi

if [[ ${TOOLCHAIN} == glibc ]]; then
  export ac_cv_func_sigvec=no
fi

InstallStep() {
  DefaultInstallStep
  ChangeDir ${DESTDIR_LIB}
  LogExecute ln -sf libncurses.a libtermcap.a
}
