# Copyright (c) 2014 The Native Client Authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.

EXECUTABLES="subversion/svn/svn${NACL_EXEEXT}"

# subversion's build system seem to have a bug with out-of-tree builds
# and parallel building that was causing occational flakes on the buildbots.
# The mkdir-init target appears to be required before any object file can be
# built but none of the object files seem to depend on this.
OS_JOBS=1

EXTRA_CONFIGURE_ARGS="--with-apr=${NACL_PREFIX}"
EXTRA_CONFIGURE_ARGS+=" --with-apr-util=${NACL_PREFIX}"
EXTRA_CONFIGURE_ARGS+=" --without-apxs"
EXTRA_CONFIGURE_ARGS+=" --enable-all-static"

EnableCliMain
EnableGlibcCompat

TestStep() {
  if [[ ${OS_NAME} == Darwin ]]; then
    # Tests disabled on mac.  Running svn under sel_ldr on mac produces the
    # following error:
    # svn: E200001: APR: Can't create a character converter from 'UTF-8' to
    # native encoding
    return
  fi
  LogExecute subversion/svn/svn --version
}
