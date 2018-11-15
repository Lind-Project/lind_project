# Copyright 2015 The Native Client Authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.

BUILD_DIR=${SRC_DIR}
EXECUTABLES="tree"
INSTALL_TARGETS="install prefix=${DESTDIR}/${PREFIX}"

EnableCliMain

BuildStep() {
  LogExecute make clean
  LogExecute make -j${OS_JOBS} CC="${NACLCC}" CFLAGS=" -c \
    ${NACLPORTS_CFLAGS}" LDFLAGS="${NACLPORTS_LDFLAGS}" tree
}
