# Copyright 2015 The Native Client Authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.

HOST_BUILD_DIR=${WORK_DIR}/build_host
HOST_INSTALL_DIR=${WORK_DIR}/install_host

export ac_cv_func_getrlimit=no

EnableCliMain

BuildHostBinutils() {
  MakeDir ${HOST_BUILD_DIR}
  ChangeDir ${HOST_BUILD_DIR}
  LogExecute ${SRC_DIR}/configure --prefix=${HOST_INSTALL_DIR} \
      --target=avr \
      --disable-nls
  LogExecute make
  LogExecute make install
}

ConfigureStep() {
  BuildHostBinutils

  export PATH="${HOST_INSTALL_DIR}/bin:${PATH}"
  ChangeDir ${BUILD_DIR}
  EXTRA_CONFIGURE_ARGS="\
    --target=avr \
    --disable-nls \
    --disable-werror \
    --enable-deterministic-archives \
    --without-zlib"

  export LIBS="${NACLPORTS_LIBS}"
  DefaultConfigureStep
}

BuildStep() {
  export LIBS="${NACLPORTS_LIBS}"
  DefaultBuildStep
}
