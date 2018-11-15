# Copyright (c) 2013 The Native Client Authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.

MAKE_TARGETS="CCLD=\$(CXX) all"
NACLPORTS_CPPFLAGS+=" -DNACL_SDK_VERSION=$NACL_SDK_VERSION"
if [ "${NACL_DEBUG}" = "1" ] ; then
  NACLPORTS_CPPFLAGS+=" -DSQLITE_DEBUG -DSQLITE_LOCK_TRACE"
fi
if [ "${NACL_SHARED}" = "1" ]; then
  EXECUTABLE_DIR=.libs
  NACLPORTS_LIBS+=" -ldl"
else
  EXTRA_CONFIGURE_ARGS=--disable-dynamic-extensions
  EXECUTABLE_DIR=.
fi

EnableCliMain
EXECUTABLES="sqlite3${NACL_EXEEXT}"

PublishStep() {
  MakeDir ${PUBLISH_DIR}

  local exe=${PUBLISH_DIR}/sqlite3_${NACL_ARCH}${NACL_EXEEXT}

  LogExecute cp ${EXECUTABLE_DIR}/sqlite3${NACL_EXEEXT} ${exe}
  if [ "${NACL_ARCH}" = "pnacl" ]; then
    LogExecute ${PNACLFINALIZE} ${exe}
  fi

  pushd ${PUBLISH_DIR}
  LogExecute python ${NACL_SDK_ROOT}/tools/create_nmf.py \
      -L${DESTDIR_LIB} \
      sqlite3*${NACL_EXEEXT} \
      -s . \
      -o sqlite.nmf
  LogExecute python ${TOOLS_DIR}/create_term.py sqlite.nmf
  popd

  InstallNaClTerm ${PUBLISH_DIR}
}

RunTest() {
  naclport_test/test -g
}

TestStep() {
  MakeDir naclport_test

  if [[ ${NACL_ARCH} == "pnacl" ]]; then
    EXT=.bc
  else
    EXT=${NACL_EXEEXT}
  fi

  INCLUDES="-I${SRC_DIR} -I${GTEST_SRC}/include"
  LogExecute ${NACLCXX} ${INCLUDES} ${NACLPORTS_CPPFLAGS} -I${GTEST_SRC} \
    ${NACLPORTS_CFLAGS} -o gtest-all.o -c ${GTEST_SRC}/src/gtest-all.cc

  LogExecute ${NACLCXX} ${INCLUDES} ${NACLPORTS_CPPFLAGS} \
    ${NACLPORTS_CFLAGS} -o test.o -c ${START_DIR}/test.cc

  LogExecute ${NACLCXX} ${NACLPORTS_LDFLAGS} \
    -o naclport_test/test${EXT} test.o gtest-all.o sqlite3.o ${NACLPORTS_LIBS}

  [[ ${NACL_ARCH} == "pnacl" ]] && ${PNACLFINALIZE} \
    -o naclport_test/test${NACL_EXEEXT} naclport_test/test${EXT}

  echo "Running test"

  if [ "${NACL_ARCH}" = "pnacl" ]; then
    local pexe=test${NACL_EXEEXT}
    (cd naclport_test;
     TranslateAndWriteLauncherScript ${pexe} x86-32 test.x86-32${EXT} \
       test)
    RunTest
    (cd naclport_test;
     TranslateAndWriteLauncherScript ${pexe} x86-64 test.x86-64${EXT} \
       test)
    RunTest
    echo "Tests OK"
  elif [ "$(uname -m)" = "${NACL_ARCH_ALT}" ]; then
    WriteLauncherScript naclport_test/test test${EXT}
    RunTest
    echo "Tests OK"
  fi
}
