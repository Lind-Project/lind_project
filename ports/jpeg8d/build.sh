# Copyright (c) 2011 The Native Client Authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.

EXECUTABLES="rdjpgcom${NACL_EXEEXT} wrjpgcom${NACL_EXEEXT} \
      cjpeg${NACL_EXEEXT} djpeg${NACL_EXEEXT} jpegtran${NACL_EXEEXT}"

RunTestsPnacl() {
  local arch=$1
  for exe in ${EXECUTABLES}; do
    local exe_noext=${exe%.*}
    WriteLauncherScript ${exe_noext} ${exe_noext}.${arch}.nexe
  done
  LogExecute make test
}

TestStep() {
  export SEL_LDR_LIB_PATH=$PWD/.libs

  if [[ ${NACL_SHARED} == 1 ]]; then
    for exe in ${EXECUTABLES}; do
     local script=$(basename ${exe%.*})
      WriteLauncherScript ${script} ${exe}
    done
  fi
  LogExecute make test

  if [[ ${NACL_ARCH} == pnacl ]]; then
    RunTestsPnacl x86-32
    if [[ ${SEL_LDR_SUPPORTS_ARM} == 1 ]]; then
      RunTestsPnacl arm
    fi
  fi
}
