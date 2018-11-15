# Copyright (c) 2011 The Native Client Authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.

NACLPORTS_CFLAGS+=" -std=gnu99"

EXECUTABLES="
checkkeys${NACL_EXEEXT}
controllermap${NACL_EXEEXT}
loopwave${NACL_EXEEXT}
loopwavequeue${NACL_EXEEXT}
testatomic${NACL_EXEEXT}
testaudioinfo${NACL_EXEEXT}
testautomation${NACL_EXEEXT}
testdraw2${NACL_EXEEXT}
testdrawchessboard${NACL_EXEEXT}
testdropfile${NACL_EXEEXT}
testerror${NACL_EXEEXT}
testfile${NACL_EXEEXT}
testfilesystem${NACL_EXEEXT}
testgamecontroller${NACL_EXEEXT}
testgesture${NACL_EXEEXT}
testgl2${NACL_EXEEXT}
testgles2${NACL_EXEEXT}
testgles${NACL_EXEEXT}
testhaptic${NACL_EXEEXT}
testhotplug${NACL_EXEEXT}
testiconv${NACL_EXEEXT}
testime${NACL_EXEEXT}
testintersections${NACL_EXEEXT}
testjoystick${NACL_EXEEXT}
testkeys${NACL_EXEEXT}
testloadso${NACL_EXEEXT}
testlock${NACL_EXEEXT}
testmessage${NACL_EXEEXT}
testmultiaudio${NACL_EXEEXT}
testoverlay2${NACL_EXEEXT}
testplatform${NACL_EXEEXT}
testpower${NACL_EXEEXT}
testrelative${NACL_EXEEXT}
testrendercopyex${NACL_EXEEXT}
testrendertarget${NACL_EXEEXT}
testresample${NACL_EXEEXT}
testrumble${NACL_EXEEXT}
testscale${NACL_EXEEXT}
testsem${NACL_EXEEXT}
testshader${NACL_EXEEXT}
testshape${NACL_EXEEXT}
testsprite2${NACL_EXEEXT}
testspriteminimal${NACL_EXEEXT}
teststreaming${NACL_EXEEXT}
testthread${NACL_EXEEXT}
testtimer${NACL_EXEEXT}
testver${NACL_EXEEXT}
testviewport${NACL_EXEEXT}
testwm2${NACL_EXEEXT}
torturethread${NACL_EXEEXT}
"

ConfigureStep() {
  Banner "Autogen ${PACKAGE_NAME}"
  pushd ${SRC_DIR}/test
  LogExecute ./autogen.sh
  popd

  Banner "Configure ${PACKAGE_NAME}"
  SetupCrossEnvironment

  CFLAGS="${CPPFLAGS} ${CFLAGS}"
  LIBS="${LDFLAGS}"
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
  for NEXE in ${EXECUTABLES}; do
    LogExecute "${NACL_SDK_ROOT}/tools/create_html.py" ${NEXE}
  done
  if [ ${NACL_ARCH} = "pnacl" -o ${NACL_ARCH} = "le32" ]; then
    sed -i.bak 's/x-nacl/x-pnacl/' *.html
  fi
}
