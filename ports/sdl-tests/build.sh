# Copyright (c) 2011 The Native Client Authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.

ConfigureStep() {
  Banner "Autogen ${PACKAGE_NAME}"
  pushd ${SRC_DIR}/test
  LogExecute ./autogen.sh
  popd

  Banner "Configuring ${PACKAGE_NAME}"
  SetupCrossEnvironment

  LIBS="$LDFLAGS"
  LogExecute ${SRC_DIR}/test/configure \
    --host=${CONF_HOST} \
    --build=${CONF_BUILD} \
    --prefix=${PREFIX}
}

InstallStep() {
  Remove ${PUBLISH_DIR}
  MakeDir ${PUBLISH_DIR}
  LogExecute cp *${NACL_EXEEXT} ${PUBLISH_DIR}
  ChangeDir ${SRC_DIR}/test
  LogExecute cp *.bmp *.wav *.xbm *.dat *.txt ${PUBLISH_DIR}
  ChangeDir ${PUBLISH_DIR}
  for NEXE in *${NACL_EXEEXT}; do
    LogExecute "${NACL_SDK_ROOT}/tools/create_html.py" ${NEXE}
  done
  if [ ${NACL_ARCH} = "pnacl"  || ${NACL_ARCH} = "le32" ]; then
    sed -i.bak 's/x-nacl/x-pnacl/' *.html
  fi
}
