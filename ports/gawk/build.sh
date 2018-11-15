# Copyright (c) 2015 The Native Client Authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.

# getopt.c and getopt1.c have been commented for build
if [ ${TOOLCHAIN} != "glibc" ]; then
  NACLPORTS_CFLAGS+=" -D__GNU_LIBRARY__ "
fi

EnableCliMain
