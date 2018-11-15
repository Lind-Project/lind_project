# Copyright (c) 2011 The Native Client Authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.

EXECUTABLES=test/yajl_test
EXTRA_CMAKE_ARGS="-DBUILD_SHARED=${NACL_SHARED}"

TestStep() {
  local script=${BUILD_DIR}/test/yajl_test.sh
  (cd "${SRC_DIR}/test" && ./run_tests.sh "${script}")

  if [[ ${NACL_ARCH} == pnacl ]]; then
    # Re-run the tests with the x86-32 and arm translated binaries
    WriteLauncherScript ${script} yajl_test.x86-32.nexe
    (cd "${SRC_DIR}/test" && ./run_tests.sh "${script}")
    if [[ ${SEL_LDR_SUPPORTS_ARM} == 1 ]]; then
      WriteLauncherScript ${script} yajl_test.arm.nexe
      (cd "${SRC_DIR}/test" && ./run_tests.sh "${script}")
    fi
  fi
}

# Override configure step to force it use CMake.  Without
# this the default configure step will see the ruby ./configure
# script at the top level of yajl (which doesn't work) and
# try to run that.
ConfigureStep() {
  ConfigureStep_CMake
}
