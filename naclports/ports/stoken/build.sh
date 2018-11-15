# Copyright 2016 The Native Client Authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.

EnableCliMain
EnableGlibcCompat
EXTRA_CONFIGURE_ARGS+=" --without-gtk --with-nettle"
EXECUTABLES=stoken${NACL_EXEEXT}

# Workaround for pthread link order problem (copied from libarchive).
export LIBS="-lpthread -lm"

TestStep() {
  if [ "${NACL_SHARED}" = "1" ]; then
    EXE=.libs/stoken${NACL_EXEEXT}
    export SEL_LDR_LIB_PATH=${BUILD_DIR}/.libs
  else
    EXE=stoken${NACL_EXEEXT}
  fi

  if [ "${NACL_ARCH}" = "pnacl" -o "${NACL_ARCH}" = "le32" ]; then
    TranslateAndWriteLauncherScript ${EXE} x86-32 stoken.x86-32.nexe stoken
  else
    WriteLauncherScript stoken ${EXE}
  fi

  LogExecute make check
}
