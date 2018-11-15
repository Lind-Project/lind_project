# Copyright (c) 2014 The Native Client Authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.

EnableCliMain
NACLPORTS_CPPFLAGS+=" -Wall -Werror -Dpipe=nacl_spawn_pipe"
NACLPORTS_CPPFLAGS+=" -isystem ${GTEST_SRC}/include"

EXECUTABLES="tests/devenv_small_test_${NACL_ARCH}${NACL_EXEEXT} \
             jseval/jseval_${NACL_ARCH}${NACL_EXEEXT}"

STORAGE_URL=https://webports.storage.googleapis.com/builds
SDK_VERSION=pepper_51
BUILT_REVISION=trunk-837-gd9eb95d
DEFAULT_SOURCE=${STORAGE_URL}/${SDK_VERSION}/${BUILT_REVISION}/publish
LOCAL_SOURCE=http://localhost:5103

BuildStep() {
  SetupCrossEnvironment

  # Build jseval module.
  MakeDir ${BUILD_DIR}/jseval
  LogExecute ${CC} ${CPPFLAGS} ${CFLAGS} ${LDFLAGS} \
      ${START_DIR}/jseval.c \
      -o ${BUILD_DIR}/jseval/jseval_${NACL_ARCH}${NACL_EXEEXT} \
      ${LIBS}

  # Build test module.
  MakeDir tests
  LogExecute ${CXX} ${CPPFLAGS} ${CXXFLAGS} -o tests/devenv_small_test.o \
      -c ${START_DIR}/tests/devenv_small_test.cc
  LogExecute ${CXX} ${CPPFLAGS} ${CXXFLAGS} -o tests/gtest-all.o \
      -c ${GTEST_SRC}/src/gtest-all.cc -I${GTEST_SRC}
  LogExecute ${CXX} ${LDFLAGS} tests/devenv_small_test.o tests/gtest-all.o \
      -o tests/devenv_small_test_${NACL_ARCH}${NACL_EXEEXT} ${LIBS}
}

InstallStep() {
  return
}

#
# $1: Name name of the repo
# $2: Name of directory in which to create the conf file.
# $3: The http address of repo.
# $4: The priority of the repo (higher number means higher priority).
# $5: enabled
#
CreateRepoConfFile() {
  local name=$1
  local outdir=$2
  local priority=$4
  local enabled=$5
  local PKG_ARCH=${NACL_ARCH}
  if [[ ${PKG_ARCH} == x86_64 ]]; then
    PKG_ARCH=x86-64
  fi
  if [[ ${NACL_ARCH} == ${TOOLCHAIN} ]]; then
    local url="$3/pkg_${PKG_ARCH}"
  else
    local url="$3/pkg_${TOOLCHAIN}_${PKG_ARCH}"
  fi

  MakeDir ${outdir}
  cat > ${outdir}/${name}.conf <<EOF
$name: {
    URL: $url,
    MIRROR_TYPE: HTTP,
    ENABLED: $enabled,
    PRIORITY: $priority,
}
EOF
}

CreateRootFS() {
  local tar_file=$1
  MakeDir root/usr/etc/pkg/repos/
  MakeDir root/etc
  MakeDir root/home/user
  sed "s/@TOOLCHAIN@/${TOOLCHAIN}/g" \
    ${START_DIR}/bash_profile > root/etc/profile
  LogExecute cp ${START_DIR}/bashrc root/home/user/.bashrc
  # Create Nacl.conf file
  CreateRepoConfFile Local root/usr/etc/pkg/repos "${LOCAL_SOURCE}" 1 NO
  CreateRepoConfFile NaCl root/usr/etc/pkg/repos "${DEFAULT_SOURCE}" 0 YES
  LogExecute tar cf ${tar_file} -C root etc usr home
  LogExecute shasum ${tar_file} > ${tar_file}.hash
  rm -rf root
}

PublishStep() {
  MakeDir ${PUBLISH_DIR}

  local APP_DIR=${PUBLISH_DIR}/app
  MakeDir ${APP_DIR}

  # Set up files for bootstrap.
  local BASH_DIR=${NACL_PACKAGES_PUBLISH}/bash/${TOOLCHAIN}
  local PKG_DIR=${NACL_PACKAGES_PUBLISH}/pkg/${TOOLCHAIN}
  local GETURL_DIR=${NACL_PACKAGES_PUBLISH}/geturl/${TOOLCHAIN}
  local UNZIP_DIR=${NACL_PACKAGES_PUBLISH}/unzip/${TOOLCHAIN}

  LogExecute cp -fR ${BASH_DIR}/* ${APP_DIR}
  LogExecute cp -fR ${PKG_DIR}/* ${APP_DIR}
  LogExecute cp -fR ${GETURL_DIR}/* ${APP_DIR}
  LogExecute cp -fR ${UNZIP_DIR}/* ${APP_DIR}

  # Install jseval only for pnacl (as it can't really work otherwise).
  if [[ ${NACL_ARCH} == pnacl || ${NACL_ARCH} == le32 ]]; then
    LogExecute ${PNACLFINALIZE} \
        ${BUILD_DIR}/jseval/jseval_${NACL_ARCH}${NACL_EXEEXT} \
        -o ${APP_DIR}/jseval_${NACL_ARCH}${NACL_EXEEXT}
    cd ${APP_DIR}
    LogExecute python ${NACL_SDK_ROOT}/tools/create_nmf.py \
        jseval_${NACL_ARCH}${NACL_EXEEXT} \
        -s . \
        -o jseval.nmf
  fi

  # Install the HTML/JS for the terminal.
  # TODO(gdeepti): Extend mounter to the other create_term.py apps.
  ChangeDir ${APP_DIR}
  LogExecute python ${TOOLS_DIR}/create_term.py -i whitelist.js \
      -i devenv.js -i mounter.js -s mounter.css bash.nmf
  LogExecute cp bash.nmf sh.nmf
  InstallNaClTerm ${APP_DIR}

  RESOURCES="background.js mounter.css mounter.js bash.js which
      install-base-packages.sh graphical.html devenv.js whitelist.js
      devenv_16.png devenv_48.png devenv_128.png"
  for resource in ${RESOURCES}; do
    LogExecute install -m 644 ${START_DIR}/${resource} ${APP_DIR}/
  done

  # Generate manifest.txt so that nacl_io can list the directory
  rm -f manifest.txt
  (cd ${APP_DIR} && ${NACL_SDK_ROOT}/tools/genhttpfs.py . -r > ../manifest.txt)
  mv ../manifest.txt .

  if [[ $TOOLCHAIN == pnacl ]]; then
    CreateRootFS bash_data.tar
  else
    CreateRootFS _platform_specific/${NACL_ARCH}/bash_data.tar
  fi

  # Generate a manifest.json.
  GenerateManifest ${START_DIR}/manifest.json.template ${APP_DIR} \
    key=$(cat ${START_DIR}/key.txt)

  # Create uploadable version (key not included).
  local APP_UPLOAD_DIR="${PUBLISH_DIR}/devenv_app_upload"
  rm -rf ${APP_UPLOAD_DIR}
  LogExecute cp -r ${APP_DIR} ${APP_UPLOAD_DIR}
  GenerateManifest ${START_DIR}/manifest.json.template \
    ${APP_UPLOAD_DIR} key=

  # Zip the full app for upload.
  ChangeDir ${PUBLISH_DIR}
  CreateWebStoreZip devenv_app_upload.zip devenv_app_upload

  # Copy the files for DevEnvWidget.
  local WIDGET_DIR=${PUBLISH_DIR}/devenvwidget
  MakeDir ${WIDGET_DIR}
  LogExecute cp -r ${START_DIR}/devenvwidget/* ${WIDGET_DIR}

  # Install tests.
  MakeDir tests
  ChangeDir tests
  LogExecute cp -r ${BUILD_DIR}/tests/*${NACL_EXEEXT} .
  LogExecute mv devenv_small_test_${NACL_ARCH}${NACL_EXEEXT} \
      devenv_small_test_${NACL_ARCH}

  Remove devenv_small_test.zip
  LogExecute zip -r devenv_small_test.zip *
}

PostInstallTestStep() {
  local arches=
  if [[ ${OS_NAME} == Darwin && ${NACL_ARCH} == x86_64 ]]; then
    echo "Skipping devenv tests on unsupported mac + x86_64 configuration."
  elif [[ ${NACL_ARCH} == arm ]]; then
    echo "Skipping devenv tests on arm for now."
  elif [[ ${NACL_ARCH} == pnacl || ${NACL_ARCH} == le32 ]]; then
    arches="i686 x86_64"
  else
    arches="${NACL_ARCH}"
  fi
  for arch in ${arches}; do
    LogExecute python ${START_DIR}/devenv_small_test.py -x -v -a ${arch} \
      -p NACL_BOOT_ARCH=${NACL_ARCH}
    if [[ ${NACL_ARCH} == pnacl || ${NACL_ARCH} == le32 ]]; then
      LogExecute python ${START_DIR}/jseval_test.py -x -v -a ${arch}
    fi

    # TODO(anmittal): enable test back once pinned rev is updated for new driver
    # Run large and demo2014 tests only on the buildbots (against pinned revs).
    if [[ ${NACL_ARCH} != le32 ]]; then
      if [[ -n ${BUILDBOT_BUILDERNAME:-} ]]; then
        LogExecute python ${START_DIR}/../devenv/devenv_large_test.py \
          -x -v -a ${arch}
        LogExecute python ${START_DIR}/../devenv/demo2014_test.py \
          -x -v -a ${arch}
      fi
    fi
  done
}
