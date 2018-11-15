# Copyright (c) 2011 The Native Client Authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.

# Configure requires this variable to be pre-set when cross compiling.
export bash_cv_wcwidth_broken=no

MAKEFLAGS+=" EXEEXT=.${NACL_EXEEXT}"

EnableGlibcCompat

if [[ ${NACL_SHARED} = 0 ]]; then
  EXTRA_CONFIGURE_ARGS="--disable-shared"
fi

if [[ ${TOOLCHAIN} == emscripten ]]; then
  export bash_cv_signal_vintage=posix
  # Emscripten tends to let autoconf thinks things work when they don't.
  # Without this autoconf will detect that -lutil and -ldir are needed which
  # generated a lot of warnings during the build
  export ac_cv_lib_util_openpty=no
  export ac_cv_lib_dir_opendir=no
fi

TestStep() {
  if [ "${NACL_LIBC}" != "glibc" ]; then
    # readline example don't link under sel_ldr
    # TODO(sbc): find a way to add glibc-compat to link line for examples.
    return
  fi
  MAKE_TARGETS=examples
  DefaultBuildStep
  pushd examples
  # TODO(jvoung): PNaCl can't use WriteLauncherScript --
  # It should use TranslateAndWriteLauncherScript instead.
  # It probably shouldn't use .nexe as the extension either.
  for NEXE in *.nexe; do
    WriteLauncherScript ${NEXE%.*} ${NEXE}
  done
  popd
}

InstallStep() {
  DefaultInstallStep
  if [ "${NACL_SHARED}" = "1" ]; then
    cd ${DESTDIR_LIB}
    ln -sf libreadline.so.6 libreadline.so
  fi
}
