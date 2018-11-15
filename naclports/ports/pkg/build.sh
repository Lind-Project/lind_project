# Copyright 2015 The Native Client Authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.

EXECUTABLES="src/pkg-static${NACL_EXEEXT}"
NACLPORTS_LIBS+=" -lbsd -pthread"

EXTRA_CONFIGURE_ARGS+=" --prefix=/usr --exec-prefix=/usr"

if [[ ${NACL_SHARED} == 1 ]]; then
  EXECUTABLES+=" src/pkg${NACL_EXEEXT}"
  NACLPORTS_LIBS+=" -lresolv -ldl -lrt"
  EXTRA_CONFIGURE_ARGS+=" --enable-shared=yes --with-staticonly=no"
  NACLPORTS_CPPFLAGS+=" -D_GNU_SOURCE"
else
  EXTRA_CONFIGURE_ARGS+=" --enable-shared=no --with-staticonly=yes"
fi

EnableCliMain
EnableGlibcCompat

ConfigureStep() {
  ChangeDir ${SRC_DIR}
  ./autogen.sh
  PatchConfigure
  ChangeDir ${BUILD_DIR}
  DefaultConfigureStep
}

BuildHost() {
  HOST_BUILD_DIR=${WORK_DIR}/build_host
  if [[ ! -f ${HOST_BUILD_DIR}/src/pkg ]]; then
    MakeDir ${HOST_BUILD_DIR}
    Banner "Build host pkg"

    local libarchive_install=${WORK_DIR}/../libarchive-dev/install_host
    local libbsd_install=${WORK_DIR}/../libbsd/install_host
    export CPPFLAGS="-I${libarchive_install}/usr/local/include"
    export LDFLAGS="-L${libarchive_install}/usr/local/lib"
    CPPFLAGS+=" -I${libbsd_install}/usr/local/include"
    LDFLAGS+=" -L${libbsd_install}/usr/local/lib"

    cd ${HOST_BUILD_DIR}
    LogExecute ${SRC_DIR}/configure
    LogExecute make -j${OS_JOBS}
    cd -
  fi
}

BuildStep() {
  (BuildHost)
  DefaultBuildStep
}

TestStep() {
  LogExecute ${BUILD_DIR}/src/pkg-static -v
}

InstallStep() {
  DefaultInstallStep
  LogExecute mv ${DESTDIR}/usr ${DESTDIR}/${PREFIX}
  if [[ ${NACL_SHARED} == 0 ]]; then
    LogExecute mv ${DESTDIR}/${PREFIX}/sbin/pkg-static${NACL_EXEEXT} \
        ${DESTDIR}/${PREFIX}/sbin/pkg${NACL_EXEEXT}
  fi
}

PublishStep() {
  PublishMultiArch src/pkg-static${NACL_EXEEXT} pkg
}
