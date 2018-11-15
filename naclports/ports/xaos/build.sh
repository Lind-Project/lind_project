# Copyright (c) 2012 The Native Client Authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.

EXECUTABLES=bin/xaos
NACL_CPPFLAGS+=" -D__NO_MATH_INLINES=1"

# xaos does not work with a build dir which is separate from the src dir
BUILD_DIR=${SRC_DIR}

NACLPORTS_LDFLAGS+=" -Wl,--undefined=PPP_GetInterface \
                -Wl,--undefined=PPP_ShutdownModule \
                -Wl,--undefined=PPP_InitializeModule \
                -Wl,--undefined=original_main"

NACLPORTS_LIBS="-lppapi -lpthread -l${NACL_CXX_LIB} -lm"

PatchStep() {
  DefaultPatchStep
  echo "copy nacl driver"
  cp -r "${START_DIR}/nacl-ui-driver" "${SRC_DIR}/src/ui/ui-drv/nacl"
}

ConfigureStep() {
  # xaos takes care of defining NDEBUG itself
  NACLPORTS_CFLAGS="${NACLPORTS_CFLAGS/-DNDEBUG/}"

  echo "running autoconf"
  LogExecute rm ./configure
  LogExecute autoconf

  SetupCrossEnvironment
  LogExecute ./configure --with-png=no --with-long-double=no \
      --host=nacl --with-x11-driver=no --with-sffe=no
}

BuildStep() {
  SetupCrossEnvironment
  DefaultBuildStep
}

InstallStep() {
  return
}

PublishStep() {
  MakeDir ${PUBLISH_DIR}
  LogExecute install ${START_DIR}/xaos.html ${PUBLISH_DIR}
  LogExecute install ${BUILD_DIR}/bin/xaos \
      ${PUBLISH_DIR}/xaos_${NACL_ARCH}${NACL_EXEEXT}
  LogExecute install ${BUILD_DIR}/help/xaos.hlp ${PUBLISH_DIR}
  ChangeDir ${PUBLISH_DIR}
  LogExecute python ${NACL_SDK_ROOT}/tools/create_nmf.py \
      xaos*${NACL_EXEEXT} -s . -o xaos.nmf
}
