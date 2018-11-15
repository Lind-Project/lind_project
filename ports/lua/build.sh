# Copyright (c) 2011 The Native Client Authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.

BUILD_DIR=${SRC_DIR}
EXECUTABLES="src/lua${NACL_EXEEXT} src/luac${NACL_EXEEXT}"

EnableCliMain

if [ ${TOOLCHAIN} == glibc ]; then
  PLAT=nacl-glibc
elif [ ${TOOLCHAIN} == emscripten ]; then
  PLAT=emscripten
else
  PLAT=nacl-newlib
fi

TEST_FILE=lua-5.3.0-tests.tar.gz
TEST_URL=http://www.lua.org/tests/${TEST_FILE}
TEST_SHA1=8fd633ab67edf5e824c2afc62f318de245fce268

DownloadStep() {
  if ! CheckHash ${NACL_PACKAGES_CACHE}/${TEST_FILE} ${TEST_SHA1}; then
    Fetch ${TEST_URL} ${NACL_PACKAGES_CACHE}/${TEST_FILE}
    if ! CheckHash ${NACL_PACKAGES_CACHE}/${TEST_FILE} ${TEST_SHA1} ; then
       Banner "${TEST_FILE} failed checksum!"
       exit -1
    fi
  fi

  ChangeDir ${BUILD_DIR}
  if [ -d lua-5.3.0-tests ]; then
    Remove lua-5.3.0-tests
  fi
  LogExecute tar zxf ${NACL_PACKAGES_CACHE}/${TEST_FILE}
  ChangeDir lua-5.3.0-tests
  LogExecute patch -p1 < ${START_DIR}/lua_tests.patch
}

BuildStep() {
  LogExecute make PLAT=${PLAT} clean
  set -x
  make MYLDFLAGS="${NACLPORTS_LDFLAGS}" MYCFLAGS="${NACLPORTS_CPPFLAGS}" \
      AR="${NACLAR} rcu" RANLIB="${NACLRANLIB}" CC="${NACLCC} -std=gnu99" \
      MYLIBS="${NACLPORTS_LIBS}" \
      PLAT=${PLAT} EXEEXT=${NACL_EXEEXT} -j${OS_JOBS}
  set +x
}

TestStep() {
  # First, run the 'make test' target.  This currently just runs
  # lua -v.
  LogExecute make PLAT=${PLAT} test

  if [[ ${TOOLCHAIN} == emscripten ]]; then
    # TODO(sbc): fix lua tests running under node.js
    return
  fi

  # Second, run the lua unittests. See: http://www.lua.org/tests/
  ChangeDir lua-5.3.0-tests
  LogExecute ../src/lua -e"_U=true" all.lua
}

InstallStep() {
  LogExecute make PLAT=${PLAT} EXEEXT=${NACL_EXEEXT} \
                  INSTALL_TOP=${DESTDIR}/${PREFIX} install
}

PublishStep() {
  MakeDir ${PUBLISH_DIR}
  ChangeDir ${PUBLISH_DIR}

  PublishMultiArch src/lua${NACL_EXEEXT} lua

  LogExecute python ${TOOLS_DIR}/create_term.py lua

  GenerateManifest ${START_DIR}/manifest.json ${PUBLISH_DIR}
  InstallNaClTerm ${PUBLISH_DIR}
  LogExecute cp ${START_DIR}/background.js ${PUBLISH_DIR}
  LogExecute cp ${START_DIR}/lua.js ${PUBLISH_DIR}
  LogExecute cp ${START_DIR}/*.lua ${PUBLISH_DIR}
  LogExecute cp ${START_DIR}/index.html ${PUBLISH_DIR}
  LogExecute cp ${START_DIR}/icon_16.png ${PUBLISH_DIR}
  LogExecute cp ${START_DIR}/icon_48.png ${PUBLISH_DIR}
  LogExecute cp ${START_DIR}/icon_128.png ${PUBLISH_DIR}
  LogExecute rm -rf ${PUBLISH_DIR}/lua-5.3.0-tests
  LogExecute cp -r ${BUILD_DIR}/lua-5.3.0-tests ${PUBLISH_DIR}
  ChangeDir ${PUBLISH_DIR}
  rm -f manifest.txt lua.zip
  ${NACL_SDK_ROOT}/tools/genhttpfs.py . -r > ../manifest.txt
  mv ../manifest.txt .
  CreateWebStoreZip lua.zip .
}
