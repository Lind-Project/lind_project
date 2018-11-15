# Copyright 2014 The Native Client Authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.

EXECUTABLES="convert libyuv_unittest"

# Workaround for arm-gcc bug:
# https://code.google.com/p/nativeclient/issues/detail?id=3205
# TODO(sbc): remove this once the issue is fixed
if [[ "${NACL_ARCH}" == arm ]]; then
  NACLPORTS_CPPFLAGS+=" -mfpu=vfp"
fi

EnableGlibcCompat

EXTRA_CMAKE_ARGS="-DTEST=ON"
EXTRA_CMAKE_ARGS+=" -DGTEST_SRC_DIR=${GTEST_SRC}"

TestStep() {
  # TODO(sbc): figure out why these tests fail
  # https://bugs.chromium.org/p/webports/issues/detail?id=216
  if [[ ${NACL_ARCH} == i686 && ${TOOLCHAIN} == glibc ]]; then
    filter="--gtest_filter=-libyuvTest.Psnr:libyuvTest.Ssim"
  elif [[ ${NACL_ARCH} == x86_64 && ${TOOLCHAIN} == glibc ]]; then
    filter="--gtest_filter=-libyuvTest.ARGBRect_Unaligned"
  elif [[ ${NACL_ARCH} == pnacl  || ${NACL_ARCH} == le32 ]]; then
    filter="--gtest_filter="
    filter+="-libyuvTest.MJPGToI420"
    filter+=":libyuvTest.MJPGToARGB"
    filter+=":LibYUVConvertTest.MJPGToI420"
    filter+=":LibYUVConvertTest.MJPGToARGB"
  else
    filter=
  fi

  LogExecute ./libyuv_unittest.sh ${filter}
}
