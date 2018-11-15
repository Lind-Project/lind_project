# Copyright (c) 2014 The Native Client Authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.

EnableGlibcCompat

InstallStep() {
  DefaultInstallStep
  if [ "${NACL_LIBC}" = "newlib" ]; then
    local pkgconfig_file=${INSTALL_DIR}/webports-dummydir/lib/pkgconfig/xcb.pc
    if ! grep -Eq "lglibc-compat" $pkgconfig_file; then
      sed -i.bak 's/-lxcb/-lxcb -lglibc-compat/' $pkgconfig_file
    fi
  fi
}
