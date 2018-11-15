# Copyright (c) 2013 The Native Client Authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.

EXECUTABLES=python${NACL_EXEEXT}

# This build relies on certain host binaries and python's configure
# requires us to set --build= as well as --host=.
HOST_BUILD_DIR=${WORK_DIR}/build_host

# Workaround for arm-gcc bug:
# https://code.google.com/p/nativeclient/issues/detail?id=3205
# TODO(sbc): remove this once the issue is fixed
if [ "${NACL_ARCH}" = "arm" ]; then
  NACLPORTS_CPPFLAGS+=" -mfpu=vfp"
fi

SetOptFlags() {
  # Python build system sets its own opt flags
  return
}

ConfigureStep() {
  # We pre-seed configure with certain results that it cannot determine
  # since we are doing a cross compile.  The $CONFIG_SITE file is sourced
  # by configure early on.
  export CROSS_COMPILE=true
  export CONFIG_SITE=${START_DIR}/config.site
  # Disable ipv6 since configure claims it requires a working getaddrinfo
  # which we do not provide.  TODO(sbc): remove this once nacl_io supports
  # getaddrinfo.
  EXTRA_CONFIGURE_ARGS+=" --disable-ipv6"
  EXTRA_CONFIGURE_ARGS+=" --with-suffix=${NACL_EXEEXT}"
  EXTRA_CONFIGURE_ARGS+=" --build=x86_64-linux-gnu"
  if [ "${NACL_DEBUG}" = 1 ]; then
    EXTRA_CONFIGURE_ARGS+=" --with-pydebug"
  fi
  NACLPORTS_LIBS+=" -ltermcap"
  if [ "${NACL_LIBC}" = "newlib" ]; then
    # When python builds with wait3/wait4 support it also expects struct rusage
    # to have certain fields and newlib lacks.
    export ac_cv_func_wait3=no
    export ac_cv_func_wait4=no
  fi
  EnableCliMain
  EnableGlibcCompat
  DefaultConfigureStep
  if [ "${NACL_LIBC}" = "newlib" ]; then
    # For static linking we copy in a pre-baked Setup.local
    LogExecute cp ${START_DIR}/Setup.local Modules/
  fi
}

BuildStep() {
  export CROSS_COMPILE=true
  export MAKEFLAGS="PGEN=${NACL_HOST_PYBUILD}/Parser/pgen"
  SetupCrossEnvironment
  DefaultBuildStep
}

InstallStep() {
  export CROSS_COMPILE=true
  DefaultInstallStep
}

PublishStep() {
  MakeDir ${PUBLISH_DIR}

  PublishMultiArch python${NACL_EXEEXT} python
  ChangeDir ${PUBLISH_DIR}
  if [[ $TOOLCHAIN == pnacl ]]; then
    local tar_file=pydata.tar
  else
    local tar_file=_platform_specific/${NACL_ARCH}/pydata.tar
  fi

  LogExecute tar cf ${tar_file} -C ${INSTALL_DIR}${PREFIX} lib/python2.7
  if [[ $NACL_SHARED == 1 ]]; then
    # Extra shared libraries depedencies requires by python loadable modules
    LogExecute tar rf ${tar_file} -h -C ${NACL_PREFIX} lib/libz.so.1 \
      lib/libreadline.so lib/libncurses.so.5 lib/libbz2.so.1.0 \
      lib/libssl.so.1.0.0 lib/libcrypto.so.1.0.0
  fi
  LogExecute shasum ${tar_file} > ${tar_file}.hash

  LogExecute python ${TOOLS_DIR}/create_term.py python.nmf

  GenerateManifest ${START_DIR}/manifest.json ${PUBLISH_DIR}
  InstallNaClTerm ${PUBLISH_DIR}
  LogExecute cp ${START_DIR}/background.js ${PUBLISH_DIR}
  LogExecute cp ${START_DIR}/python.js ${PUBLISH_DIR}
  LogExecute cp ${START_DIR}/index.html ${PUBLISH_DIR}
  LogExecute cp ${START_DIR}/icon_16.png ${PUBLISH_DIR}
  LogExecute cp ${START_DIR}/icon_48.png ${PUBLISH_DIR}
  LogExecute cp ${START_DIR}/icon_128.png ${PUBLISH_DIR}
  ChangeDir ${PUBLISH_DIR}
  CreateWebStoreZip python-${VERSION}.zip .
}
