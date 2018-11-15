# Copyright (c) 2013 The Native Client Authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.

NACLPORTS_LIBS+=" -lncurses"
EXECUTABLES=src/nano${NACL_EXEEXT}

EnableGlibcCompat
EnableCliMain

if [ "${NACL_LIBC}" = "newlib" ]; then
  EXTRA_CONFIGURE_ARGS="--enable-tiny"
fi

InstallStep() {
  DefaultInstallStep
  # The nano build results in a dangling symlink (symlink doesn't honor the
  # EXEEXT).   We don't care about rnano anyway, so just remove it.
  LogExecute rm ${DESTDIR}${PREFIX}/bin/rnano
}

PublishStep() {
  MakeDir ${PUBLISH_DIR}

  LogExecute cp src/nano${NACL_EXEEXT} \
    "${PUBLISH_DIR}/nano_${NACL_ARCH}${NACL_EXEEXT}"

  rm -rf ${PUBLISH_DIR}/nanotar
  MakeDir ${PUBLISH_DIR}/nanotar/usr
  ChangeDir ${PUBLISH_DIR}/nanotar
  LogExecute cp -a ${DESTDIR}${PREFIX}/share usr/
  tar cf ${PUBLISH_DIR}/nano.tar .
  shasum ${PUBLISH_DIR}/nano.tar > ${PUBLISH_DIR}/nano.tar.hash
  rm -rf ${PUBLISH_DIR}/nanotar

  cd ${PUBLISH_DIR}
  LogExecute python ${NACL_SDK_ROOT}/tools/create_nmf.py \
      nano_*${NACL_EXEEXT} \
      -s . \
      -o nano.nmf
  LogExecute python ${TOOLS_DIR}/create_term.py nano.nmf

  InstallNaClTerm ${PUBLISH_DIR}

  GenerateManifest ${START_DIR}/manifest.json ${PUBLISH_DIR}
  LogExecute cp ${START_DIR}/icon_16.png ${PUBLISH_DIR}
  LogExecute cp ${START_DIR}/icon_48.png ${PUBLISH_DIR}
  LogExecute cp ${START_DIR}/icon_128.png ${PUBLISH_DIR}
  ChangeDir ${PUBLISH_DIR}
  CreateWebStoreZip nano-${VERSION}.zip .
}
