# Copyright 2016 The Native Client Authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.

EnableGlibcCompat
NACLPORTS_CPPFLAGS+=" ${NACL_EXCEPTIONS_FLAG}"
EXTRA_CONFIGURE_ARGS+="
  --disable-tools
  --disable-doc
  --with-included-libtasn1
  --without-p11-kit
  --disable-hardware-acceleration"

if [ "${NACL_SHARED}" != "1" ]; then
  EXTRA_CONFIGURE_ARGS+=" --disable-shared"
fi
