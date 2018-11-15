# Copyright (c) 2011 The Native Client Authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.

# zlib doesn't support custom build directories so we have
# to build directly in the source dir.
BUILD_DIR=${SRC_DIR}
EXECUTABLES="minigzip${NACL_EXEEXT} example${NACL_EXEEXT}"
if [ "${NACL_SHARED}" = "1" ]; then
  EXECUTABLES+=" libz.so.1"
fi

ConfigureStep() {
  local CONFIGURE_FLAGS="--prefix='${PREFIX}'"
  if [ "${TOOLCHAIN}" = "emscripten" ]; then
    # The emscripten toolchain will happily accept -shared (although it
    # emits a warning if the output name ends with .so).  This means that
    # zlib's configure script tries to build shared as well as static
    # libraries until we explicitly disable shared libraries like this.
    CONFIGURE_FLAGS+=" --static"
  fi
  LogExecute rm -f libz.*
  SetupCrossEnvironment
  CFLAGS="${CPPFLAGS} ${CFLAGS}"
  CXXFLAGS="${CPPFLAGS} ${CXXFLAGS}"
  CHOST=${NACL_CROSS_PREFIX} LogExecute ./configure ${CONFIGURE_FLAGS}
}

RunMinigzip() {
  echo "Running minigzip test"
  export SEL_LDR_LIB_PATH=.
  if echo "hello world" | ./minigzip | ./minigzip -d; then
    echo '  *** minigzip test OK ***'
  else
    echo '  *** minigzip test FAILED ***'
    exit 1
  fi
  unset SEL_LDR_LIB_PATH
}

RunExample() {
  echo "Running exmple test"
  export SEL_LDR_LIB_PATH=.
  # This second test does not yet work on nacl (gzopen fails)
  if ./example; then \
    echo '  *** zlib test OK ***'; \
  else \
    echo '  *** zlib test FAILED ***'; \
    exit 1
  fi
  unset SEL_LDR_LIB_PATH
}

TestStep() {
  RunExample
  RunMinigzip
  if [[ ${NACL_ARCH} == pnacl  || ${NACL_ARCH} == le32 ]]; then
    # Run the minigzip tests again but with x86-32 and arm translations
    WriteLauncherScript minigzip minigzip.x86-32.nexe
    RunMinigzip
    if [[ ${SEL_LDR_SUPPORTS_ARM} == 1 ]]; then
      WriteLauncherScript minigzip minigzip.arm.nexe
      RunMinigzip
    fi
  fi
}
