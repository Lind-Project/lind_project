# Copyright (c) 2014 The Native Client Authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.

# NOTE: This build doesn't work in parallel.
OS_JOBS=1

# This build relies on certain host binaries.
HOST_BUILD_DIR=${WORK_DIR}/build_host
HOST_INSTALL_DIR=${WORK_DIR}/install_host

EXECUTABLE="gforth-ditc${NACL_EXEEXT}"
EXECUTABLES="${EXECUTABLE}"
MAKE_TARGETS="${EXECUTABLE}"

EnableCliMain

BuildHostGforth() {
  if [[ -f "${HOST_INSTALL_DIR}/bin/gforth" ]]; then
    return
  fi
  Banner "Building ${PACKAGE_NAME} for host"
  MakeDir ${HOST_BUILD_DIR}
  ChangeDir ${HOST_BUILD_DIR}
  CC="gcc -m32" LogExecute ${SRC_DIR}/configure --prefix=${HOST_INSTALL_DIR}
  LogExecute make -j${OS_JOBS}
  LogExecute make install
}

ConfigureStep() {
  ChangeDir ${SRC_DIR}
  LogExecute ./autogen.sh
  if ! grep '# NOTE: Disabling this, as it prevents sharing' configure; then
    echo "Autoconf failed to properly update configure, delete and retry."
    Remove ./configure
    LogExecute ./autogen.sh
  fi
  BuildHostGforth
  Banner "Building ${PACKAGE_NAME} for NaCl"
  export PATH="${HOST_INSTALL_DIR}/bin:${PATH}"
  host_gforth=$(which gforth)
  if [[ -z $host_gforth ]]; then
    echo "Failed to find host version of gforth"
    exit 1
  else
    echo "Host gforth found at: $(which gforth)"
  fi
  export skipcode=no
  EnableGlibcCompat
  ChangeDir ${BUILD_DIR}
  EXTRA_CONFIGURE_ARGS="--without-check"
  DefaultConfigureStep
}

InstallStep() {
  return
}

PublishStep() {
  MakeDir ${PUBLISH_DIR}
  ChangeDir ${PUBLISH_DIR}

  LogExecute cp ${BUILD_DIR}/${EXECUTABLE} gforth_${NACL_ARCH}${NACL_EXEEXT}

  # TODO(bradnelson): Make this nicer.
  local TAR_DIR=${PUBLISH_DIR}/webports-dummydir
  MakeDir ${TAR_DIR}

  cp -r ${HOST_INSTALL_DIR}/* ${TAR_DIR}/
  rm -rf ${TAR_DIR}/bin
  rm -rf ${TAR_DIR}/share/info
  rm -rf ${TAR_DIR}/share/man
  rm -rf ${TAR_DIR}/include
  rm -f ${TAR_DIR}/lib/gforth/0.7.2/gforth-ditc
  tar cf ${PUBLISH_DIR}/gforth.tar webports-dummydir
  rm -rf ${TAR_DIR}
  shasum ${PUBLISH_DIR}/gforth.tar > ${PUBLISH_DIR}/gforth.tar.hash

  LogExecute python ${NACL_SDK_ROOT}/tools/create_nmf.py \
      gforth_*${NACL_EXEEXT} \
      -s . \
      -o gforth.nmf
  LogExecute python ${TOOLS_DIR}/create_term.py gforth.nmf

  InstallNaClTerm ${PUBLISH_DIR}

  cp ${START_DIR}/gforth.js ${PUBLISH_DIR}/

  ChangeDir ${PUBLISH_DIR}
  Remove gforth.zip
  LogExecute zip -r gforth.zip .
}
