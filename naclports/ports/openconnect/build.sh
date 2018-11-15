# Copyright 2016 The Native Client Authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.

EnableGlibcCompat
EnableCliMain

EXTRA_CONFIGURE_ARGS+="
  --disable-shared
  --enable-static
  --with-vpnc-script=/bin/false
  --with-gnutls
  --without-openssl
  --with-lz4"

if [ "${NACL_LIBC}" != "glibc" ]; then
  # Normally -lglibc-compat appears before -lgnutls, resulting in unresolved
  # symbols.  Hack around this.
  NACLPORTS_LIBS+=" -lgnutls -lglibc-compat"
fi

# Workaround for pthread link order problem (adapted from libarchive).
NACLPORTS_LIBS+=" -lpthread -lm"

EXECUTABLES=openconnect${NACL_EXEEXT}

ConfigureStep() {
  # Required for building from git.
  ChangeDir ${SRC_DIR}
  LogExecute bash autogen.sh
  cd -

  # Force pkg-config to honor Libs.private and Requires.private fields.
  export PKG_CONFIG="${PKG_CONFIG:-pkg-config} --static"

  DefaultConfigureStep
}
