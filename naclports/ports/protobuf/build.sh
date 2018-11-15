# Copyright 2014 The Native Client Authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.

EXECUTABLES="src/protoc${NACL_EXEEXT}"
TESTS="protobuf-lite-test${NACL_EXEEXT} protobuf-test${NACL_EXEEXT}"
HOST_BUILD_DIR="${WORK_DIR}/build_host"
EXTRA_CONFIGURE_ARGS="--with-protoc=$HOST_BUILD_DIR/src/protoc"

# The version of gtest embeded in the protobuf distro isn't recent
# enough to know that NaCl has thread support
# TODO(sbc): remove this when protobuf is next updated.
NACLPORTS_CPPFLAGS+=" -DGTEST_HAS_PTHREAD=1"

if [[ ${NACL_LIBC} == newlib ]]; then
  # needed to LLONG_MAX
  NACLPORTS_CXXFLAGS+=" -std=gnu++11"
fi

BuildHostProtoc() {
  if [ ! -f "${HOST_BUILD_DIR}/src/protoc" ]; then
    MakeDir "${HOST_BUILD_DIR}"
    ChangeDir "${HOST_BUILD_DIR}"
    # The mac buildbots fail without -std=c++11
    if [[ ${OS_NAME} == Darwin ]]; then
      HOST_CXXFLAGS="-std=c++11"
    else
      HOST_CXXFLAGS=""
    fi
    CXXFLAGS=${HOST_CXXFLAGS} LogExecute "${SRC_DIR}/configure"
    LogExecute make -C src -j${OS_JOBS} protoc
    ChangeDir ${BUILD_DIR}
  fi
}

ConfigureStep() {
  BuildHostProtoc
  DefaultConfigureStep
}

TestStep() {
  LogExecute make -j${OS_JOBS} -C gmock
  LogExecute make -j${OS_JOBS} -C src ${TESTS}

  # The protobuf-test exectuable expects srcdir to be set so it
  # can find its source data.
  export srcdir=${SRC_DIR}/src
  for test in ${TESTS}; do
    RunSelLdrCommand src/${test}
  done
}
