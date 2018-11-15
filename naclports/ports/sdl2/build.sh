# Copyright (c) 2011 The Native Client Authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.

NACLPORTS_CFLAGS+=" -std=gnu99"

AutogenStep() {
  ChangeDir ${SRC_DIR}
  # For some reason if we don't remove configure before running
  # autoconf it doesn't always get updates correctly.  About half
  # the time the old configure script (with no reference to nacl)
  # will remain after ./autogen.sh
  rm -f configure
  ./autogen.sh
  PatchConfigure
  PatchConfigSub
  cd -
}

ConfigureStep() {
  AutogenStep
  SetupCrossEnvironment

  LogExecute ${SRC_DIR}/configure \
    --host=${CONF_HOST} \
    --build=${CONF_BUILD} \
    --prefix=${PREFIX} \
    --disable-assembly \
    --disable-pthread-sem
}
