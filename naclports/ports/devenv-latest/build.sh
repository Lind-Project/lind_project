# Copyright (c) 2014 The Native Client Authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.

BuildStep() {
  # Build a local package index of pkg files
  Banner "Building pkg for host"
  ${NACL_SRC}/build_tools/build_repo.sh -l
}

InstallStep() {
  # Meta package, no install.
  return
}

PostInstallTestStep() {
  local arches=
  if [[ ${OS_NAME} == Darwin && ${NACL_ARCH} == x86_64 ]]; then
    echo "Skipping devenv tests on unsupported mac + x86_64 configuration."
  elif [[ ${NACL_ARCH} == arm ]]; then
    echo "Skipping devenv tests on arm for now."
  elif [[ ${NACL_ARCH} == pnacl  || ${NACL_ARCH} == le32 ]]; then
    arches="i686 x86_64"
  else
    arches="${NACL_ARCH}"
  fi
  for arch in ${arches}; do
    LogExecute python ${START_DIR}/../devenv/devenv_large_test.py \
      -p latest=1 \
      -C ${NACL_SRC}/out/publish \
      -x -v -a ${arch}
    # TODO(bradnelson): Re-enable.
    #LogExecute python ${START_DIR}/../devenv/demo2014_test.py \
      #-p latest=1 \
      #-C ${NACL_SRC}/out \
      #-x -v -a ${arch}
  done
}
