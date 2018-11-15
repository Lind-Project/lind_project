# Copyright (c) 2014 The Native Client Authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.

EXECUTABLES="busybox"

EnableCliMain

ConfigureStep() {
  cp "${START_DIR}/defconfig" .

  if [ "${TOOLCHAIN}" = "glibc" -a "${NACL_ARCH}" = "arm" ]; then
   echo "CONFIG_INIT=n" >> defconfig
   echo "CONFIG_LINEEDIT=n" >> defconfig
   echo "CONFIG_FEATURE_UTMP=n" >> defconfig
   echo "CONFIG_FEATURE_VI_USE_SIGNALS=n" >> defconfig
  fi

  echo "CONFIG_EXTRA_CFLAGS=\"${NACLPORTS_CPPFLAGS} ${NACLPORTS_CFLAGS}\"" \
      >> defconfig
  echo "CONFIG_EXTRA_LDFLAGS=\"${NACLPORTS_LDFLAGS}\"" >> defconfig
  echo "CONFIG_EXTRA_LDLIBS=\"${NACLPORTS_LIBS}\"" >> defconfig
  echo "CONFIG_CROSS_COMPILER_PREFIX=\"${NACL_CROSS_PREFIX}-\"" >> defconfig

  SetupCrossEnvironment
  LogExecute make -f ${SRC_DIR}/Makefile defconfig BUILD_LIBBUSYBOX=y \
    KBUILD_SRC=${SRC_DIR} KBUILD_DEFCONFIG=defconfig
}

InstallStep() {
  MakeDir ${PUBLISH_DIR}
  local ASSEMBLY_DIR="${PUBLISH_DIR}/busybox"
  MakeDir ${ASSEMBLY_DIR}

  cp busybox ${ASSEMBLY_DIR}/busybox_${NACL_ARCH}${NACL_EXEEXT}

  ChangeDir ${ASSEMBLY_DIR}
  LogExecute python ${NACL_SDK_ROOT}/tools/create_nmf.py \
      ${ASSEMBLY_DIR}/busybox_*${NACL_EXEEXT} \
      -s . \
      -o busybox.nmf
  LogExecute python ${TOOLS_DIR}/create_term.py busybox.nmf

  InstallNaClTerm ${ASSEMBLY_DIR}
  LogExecute cp ${START_DIR}/manifest.json ${ASSEMBLY_DIR}
  LogExecute cp ${START_DIR}/icon_16.png ${ASSEMBLY_DIR}
  LogExecute cp ${START_DIR}/icon_48.png ${ASSEMBLY_DIR}
  LogExecute cp ${START_DIR}/icon_128.png ${ASSEMBLY_DIR}
  ChangeDir ${PUBLISH_DIR}
  CreateWebStoreZip busybox-${VERSION}.zip busybox
}

TestStep() {
  if [[ ${TOOLCHAIN} = pnacl ]]; then
    return
  fi

  # Simple test of "cat" command to ensure basic functionality
  # TODO(sbc): run the full test suite
  echo "Running ./busybox.sh cat busybox.sh > test.out"
  $(./busybox.sh cat busybox.sh > test.out)
  LogExecute diff -u busybox.sh test.out
}
