#!/bin/bash
# Copyright (c) 2014 The Native Client Authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.

RESULT=0
MESSAGES=

# SCRIPT_DIR must be defined by the including script
readonly BASE_DIR="$(dirname ${SCRIPT_DIR})"
readonly PYTHON=${SCRIPT_DIR}/python_wrapper
cd ${BASE_DIR}

UPLOAD_PATH=webports/builds/${PEPPER_DIR}/
if [ -d .git ]; then
  UPLOAD_PATH+=$(git describe)
else
  UPLOAD_PATH+=${BUILDBOT_GOT_REVISION}
fi

#
# Signal to buildbot that a step failed.
# $1 - target or package name that failed.
# $2 - architecure for which failure occured.
#
BuildSuccess() {
  local target=$1
  local arch=$2
  echo "webports: Build SUCCEEDED ${target} (${arch}/${TOOLCHAIN})"
}

#
# Signal to buildbot that a step failed.
# $1 - target or package name that failed.
# $2 - architecure for which failure occured.
#
BuildFailure() {
  local target=$1
  local arch=$2
  MESSAGE="webports: Build FAILED for ${target} (${arch}/${TOOLCHAIN})"
  echo ${MESSAGE}
  echo "@@@STEP_FAILURE@@@"
  MESSAGES="${MESSAGES}\n${MESSAGE}"
  RESULT=1
  if [ "${TEST_BUILDBOT:-}" = "1" ]; then
    exit 1
  fi
}

RunCmd() {
  echo "$@"
  "$@"
}

NACLPORTS_ARGS="-v --ignore-disabled --from-source"
export FORCE_MIRROR="yes"

#
# Build a single package for a single architecture
# $1 - Name of package to build
#
BuildPackage() {
  local package=$1
  shift
  if RunCmd bin/webports ${NACLPORTS_ARGS} "$@" install ${package}; then
    BuildSuccess ${PACKAGE} ${NACL_ARCH}
  else
    BuildFailure ${PACKAGE} ${NACL_ARCH}
  fi
}

InstallPackageMultiArch() {
  echo "@@@BUILD_STEP ${TOOLCHAIN} $1@@@"

  if [ "${TOOLCHAIN}" = "pnacl" ]; then
    arch_list="le32"
  elif [ "${TOOLCHAIN}" = "emscripten" ]; then
    arch_list="emscripten"
  else
    arch_list="i686 x86_64 arm"
  fi

  export TOOLCHAIN
  for arch in ${arch_list}; do
    if ! RunCmd bin/webports -a ${arch} uninstall --all ; then
      BuildFailure $1 ${arch}
      return
    fi
  done

  for arch in ${arch_list}; do
    if ! RunCmd bin/webports -a ${arch} ${NACLPORTS_ARGS} install $1 ; then
      # Early exit if one of the architecures fails. This mean the
      # failure is always at the end of the build step.
      BuildFailure $1 ${arch}
      return
    fi
  done
  BuildSuccess $1 all
}

CleanToolchain() {
  # Don't use TOOLCHAIN and NACL_ARCH here as we don't want to
  # clobber the globals.
  TC=$1

  if [ "${TC}" = "pnacl" ]; then
    arch_list="le32 pnacl"
  elif [ "${TC}" = "emscripten" ]; then
    arch_list="emscripten"
  elif [ "${TC}" = "glibc" ]; then
    arch_list="i686 x86_64"
  else
    arch_list="i686 x86_64 arm"
  fi

  for ARCH in ${arch_list}; do
    if ! RunCmd bin/webports -a ${ARCH} -t ${TC} clean --all; then
      TOOLCHAIN=${TC} BuildFailure clean ${ARCH}
      exit 1
    fi
  done
}

CleanCurrentToolchain() {
  echo "@@@BUILD_STEP clean@@@"
  CleanToolchain ${TOOLCHAIN}
}

