#!/bin/bash
# Copyright (c) 2012 The Native Client Authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.

set -x
set -e
set -u

declare -r RAGEL_VERSION=6.7

if [[ "$(uname -s)" = "Darwin" ]] ; then
  PLATFORM=mac
else
  case "$(uname -o)" in
    *cygwin* )
      PLATFORM=cygwin ;;
    *Linux* )
      PLATFORM=linux ;;
  esac
fi

cd "$(dirname "$0")"
rm -rf ragel-${RAGEL_VERSION}
tar xSvpf ragel-${RAGEL_VERSION}.tar.gz
(
  cd ragel-${RAGEL_VERSION}
  for patch in ../??-ragel-${RAGEL_VERSION}.*.patch ; do
    patch -p0 < $patch
  done
  ./configure
  make -j16 \
    CXXFLAGS="-m32 -O3" \
    CXXLD='gcc -s' \
    LIBS='-Wl,-Bstatic -lstdc++ -Wl,-Bdynamic'
  cp -fv ragel/ragel ../ragel.${PLATFORM}
)
rm -rf ragel-6.7
