# Copyright (c) 2013 The Native Client Authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.

NACLPORTS_CPPFLAGS+=" ${NACL_EXCEPTIONS_FLAG}"
if [ "${NACL_ARCH}" = "pnacl" ]; then
  NACLPORTS_CFLAGS+=" -std=gnu89"
fi

TestStep() {
  return 0

  if [ ${NACL_ARCH} == "pnacl" ]; then
    # Run once for each architecture.

    WriteLauncherScript test/testil testil.x86-32.nexe
    (cd test && make check)

    WriteLauncherScript test/testil testil.x86-64.nexe
    (cd test && make check)
  else
    (cd test && make check)
  fi
}
