# Copyright (c) 2012 The Native Client Authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.

NACLPORTS_CPPFLAGS+=" ${NACL_EXCEPTIONS_FLAG}"
EXECUTABLES=src/dosbox${NACL_EXEEXT}
MAKE_TARGETS="AR=${NACLAR}"

ConfigureStep() {
  SetupCrossEnvironment

  CONFIG_FLAGS="--host=${CONF_HOST} --build=${CONF_BUILD} \
      --prefix=${PREFIX} \
      --with-sdl-prefix=${NACL_TOOLCHAIN_ROOT} \
      --disable-shared \
      --with-sdl-exec-prefix=${NACL_TOOLCHAIN_ROOT}"

  LogExecute ${SRC_DIR}/configure ${CONFIG_FLAGS}
}

InstallStep(){
  MakeDir ${PUBLISH_DIR}
  LogExecute install ${START_DIR}/dosbox.html ${PUBLISH_DIR}
  LogExecute install src/dosbox${NACL_EXEEXT} \
    ${PUBLISH_DIR}/dosbox_${NACL_ARCH}${NACL_EXEEXT}
  local CREATE_NMF="${NACL_SDK_ROOT}/tools/create_nmf.py"
  LogExecute ${CREATE_NMF} -s ${PUBLISH_DIR} ${PUBLISH_DIR}/dosbox_*${NACL_EXEEXT} -o ${PUBLISH_DIR}/dosbox.nmf

  if [ "${NACL_ARCH}" = "pnacl" ]; then
    sed -i.bak 's/x-nacl/x-pnacl/' ${PUBLISH_DIR}/dosbox.html
  fi
}
