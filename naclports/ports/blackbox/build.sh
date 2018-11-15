# Copyright (c) 2014 The Native Client Authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.

EXTRA_CONFIGURE_ARGS+=" --with-x"
EXTRA_CONFIGURE_ARGS+=" --x-includes=${NACLPORTS_INCLUDE}"
EXTRA_CONFIGURE_ARGS+=" --x-libraries=${NACLPORTS_LIBDIR}"

EXECUTABLES="src/blackbox util/bsetroot util/bstyleconvert"

NACLPORTS_LIBS+=" -liconv -lXext -lXmu -lSM -lICE -lXt -lX11 -lxcb -lXau"

if [[ ${NACL_LIBC} == newlib ]]; then
  # Due to missing sys/ipc.h header
  EXTRA_CONFIGURE_ARGS+=" --disable-mitshm"
fi

EnableCliMain
EnableGlibcCompat
