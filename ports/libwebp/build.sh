# Copyright 2014 The Native Client Authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.

if [[ ${NACL_SHARED} != 1 ]]; then
  # Without this the test for libpng fails with undefined math functions
  NACLPORTS_LIBS+=" -lz -lm"
fi

EXECUTABLES="
  examples/dwebp${NACL_EXEEXT}
  examples/cwebp${NACL_EXEEXT}
"

TestStep() {
  if [[ ${TOOLCHAIN} == pnacl ]]; then
    return
  fi

  EXAMPLE_DIR=examples
  if [[ ${NACL_SHARED} == 1 ]]; then
    EXAMPLE_DIR=examples/.libs
    export SEL_LDR_LIB_PATH=${BUILD_DIR}/src/.libs
  fi
  LogExecute ${EXAMPLE_DIR}/dwebp ${SRC_DIR}/examples/test.webp -o out.webp
  LogExecute ${EXAMPLE_DIR}/cwebp out.webp -o out.png
}
