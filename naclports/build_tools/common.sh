# Copyright (c) 2012 The Native Client Authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.
#
# Environment variable NACL_ARCH should be set to one of the following
# values: i686 x86_64 pnacl arm


# NAMING CONVENTION
# =================
#
# This file is source'd by the build_port script.  Functions and variables
# defined here are available in the build script for individual ports.  Only
# variables beginning with "NACL_" are intended to be used by those scripts.

set -o nounset
set -o errexit

unset MAKEFLAGS

readonly TOOLS_DIR=$(cd "$(dirname "${BASH_SOURCE}")" ; pwd)
START_DIR=${PWD}
readonly NACL_SRC=$(dirname "${TOOLS_DIR}")
readonly NACL_PACKAGES=${NACL_SRC}

NACL_DEBUG=${NACL_DEBUG:-0}

WEBPORTS_ENV_IMPORT=1
. "${TOOLS_DIR}/webports-env.sh"

# export tool names for direct use in patches.
export NACLCC
export NACLCXX
export NACLAR
export NACLRANLIB
export NACLLD
export NACLREADELF
export NACLSTRINGS
export NACLSTRIP
export NACL_EXEEXT

# sha1check python script
readonly SHA1CHECK=${TOOLS_DIR}/sha1check.py

readonly NACLPORTS_INCLUDE=${NACL_PREFIX}/include
readonly NACLPORTS_LIBDIR=${NACL_PREFIX}/lib
readonly NACLPORTS_BIN=${NACL_PREFIX}/bin

readonly GTEST_SRC=$NACL_PREFIX/src/gtest

# The prefix used when configuring packages.  Since we want to build re-usable
# re-locatable binary packages, we use a dummy value here and then modify
# at install time certain parts of package (e.g. pkgconfig .pc files) that
# embed this this information.
readonly PREFIX=/webports-dummydir

NACLPORTS_LIBS=""
NACLPORTS_CFLAGS=""
NACLPORTS_CXXFLAGS=""
NACLPORTS_CPPFLAGS="${NACL_CPPFLAGS}"
NACLPORTS_LDFLAGS="${NACL_LDFLAGS}"

# i686-nacl-clang doesn't currently know about i686-nacl/usr/include
# or i686-nacl/usr/lib.  Instead it shared the headers with x86_64
# and uses x86_64-nacl/usr/lib32.
# TODO(sbc): remove this once we fix:
# https://code.google.com/p/nativeclient/issues/detail?id=4108
if [ "${TOOLCHAIN}" = "clang-newlib" -a "${NACL_ARCH}" = "i686" ]; then
  NACLPORTS_CPPFLAGS+=" -isystem ${NACLPORTS_INCLUDE}"
  NACLPORTS_LDFLAGS+=" -L${NACLPORTS_LIBDIR}"
fi

if [ "${TOOLCHAIN}" = "pnacl" -a "${NACL_ARCH}" = "le32" ]; then
  NACLPORTS_CPPFLAGS+=" -isystem ${NACLPORTS_INCLUDE}"
fi

if [ "${TOOLCHAIN}" = "clang-newlib" -o "${TOOLCHAIN}" = "pnacl" -o \
     "${TOOLCHAIN}" = "emscripten" ]; then
  NACLPORTS_CLANG=1
else
  NACLPORTS_CLANG=0
fi

# If stderr is a tty enable clang color compiler diagnostics
if [ -t 1 -a "${NACLPORTS_CLANG}" = "1" ]; then
  NACLPORTS_CPPFLAGS+=" -fcolor-diagnostics"
  NACLPORTS_LDFLAGS+=" -fcolor-diagnostics"
fi

# TODO(sbc): Remove once the toolchainge gets fixed:
# https://code.google.com/p/nativeclient/issues/detail?id=4333
if [[ ${TOOLCHAIN} = pnacl ]]; then
  NACLPORTS_CPPFLAGS+=" -fgnu-inline-asm"
fi

# The new arm-nacl-gcc glibc toolchain supports color diagnostics, but older
# x86 versions do not.
if [ "${TOOLCHAIN}" = "glibc" -a "${NACL_ARCH}" = "arm" ]; then
  NACLPORTS_CPPFLAGS+=" -fdiagnostics-color=auto"
  NACLPORTS_LDFLAGS+=" -fdiagnostics-color=auto"
fi

if [ "${NACL_ARCH}" = "emscripten" ]; then
  NACLPORTS_CFLAGS+=" -Wno-warn-absolute-paths"
  NACLPORTS_CXXFLAGS+=" -Wno-warn-absolute-paths"
fi

# configure spec for if MMX/SSE/SSE2/Assembly should be enabled/disabled
# TODO: Currently only x86-32 will encourage MMX, SSE & SSE2 intrinsics
#       and handcoded assembly.
if [ "${NACL_ARCH}" = "i686" ]; then
  readonly NACL_OPTION="enable"
else
  readonly NACL_OPTION="disable"
fi

# Set NACL_SHARED when we want to build shared libraries.
if [ "${NACL_LIBC}" = "glibc" ]; then
  NACL_SHARED=1
else
  NACL_SHARED=0
fi

# libcli_main.a has a circular dependency which makes static link fail
# (cli_main => nacl_io => ppapi_cpp => cli_main). To break this loop,
# you should use this instead of -lcli_main.
NACL_CLI_MAIN_LDFLAGS="-Xlinker -uPSUserMainGet"
NACL_CLI_MAIN_LIB="-lcli_main -lnacl_spawn -ltar -lppapi_simple \
-lnacl_io -lppapi -l${NACL_CXX_LIB}"
NACL_CLI_MAIN_LIB_CPP="-lcli_main -lnacl_spawn -ltar -lppapi_simple_cpp \
-lnacl_io  -lppapi_cpp -lppapi -l${NACL_CXX_LIB}"

# Python variables
NACL_PYSETUP_ARGS=""
NACL_BUILD_SUBDIR=build
NACL_INSTALL_SUBDIR=install

# output directories
readonly NACL_PACKAGES_OUT=${NACL_SRC}/out
readonly NACL_PACKAGES_ROOT=${NACL_PACKAGES_OUT}/packages
readonly NACL_PACKAGES_BUILD=${NACL_PACKAGES_OUT}/build
readonly NACL_PACKAGES_PUBLISH=${NACL_PACKAGES_OUT}/publish
readonly NACL_PACKAGES_CACHE=${NACL_PACKAGES_OUT}/cache
readonly NACL_PACKAGES_STAMPDIR=${NACL_PACKAGES_OUT}/stamp
readonly NACL_HOST_PYROOT=${NACL_PACKAGES_BUILD}/python-host/install_host
readonly NACL_HOST_PYBUILD=${NACL_PACKAGES_BUILD}/python-host/build_host
readonly NACL_HOST_PYTHON=${NACL_HOST_PYROOT}/bin/python2.7
readonly NACL_DEST_PYROOT=${NACL_PREFIX}
readonly SITE_PACKAGES="lib/python2.7/site-packages/"

# The components of package names cannot contain underscore
# characters so use x86-64 rather then x86_64 for arch component.
if [ "${NACL_ARCH}" = "x86_64" ]; then
  PACKAGE_SUFFIX="_x86-64"
else
  PACKAGE_SUFFIX="_${NACL_ARCH}"
fi

if [ "${NACL_ARCH}" != "pnacl" -a "${NACL_ARCH}" != "emscripten" ]; then
  PACKAGE_SUFFIX+=_${TOOLCHAIN}
fi

if [ "${NACL_DEBUG}" = "1" ]; then
  PACKAGE_SUFFIX+=_debug
fi

NACL_BUILD_SUBDIR+=${PACKAGE_SUFFIX}
NACL_INSTALL_SUBDIR+=${PACKAGE_SUFFIX}
readonly DEST_PYTHON_OBJS=${NACL_PACKAGES_BUILD}/python-modules/${NACL_BUILD_SUBDIR}
PACKAGE_FILE=${NACL_PACKAGES_ROOT}/${NAME}_${VERSION}${PACKAGE_SUFFIX}.tar.bz2

NACLPORTS_QUICKBUILD=${NACLPORTS_QUICKBUILD:-0}

# Number of simultaneous jobs to run during parallel build.
# Setting OS_JOBS=1 in the envrionment can be useful when debugging
# build failures in building system that interleave the output of
# of different jobs.
if [ -z "${OS_JOBS:-}" ]; then
  if [ "${OS_NAME}" = "Darwin" ]; then
    OS_JOBS=4
  elif [ "${OS_NAME}" = "Linux" ]; then
    OS_JOBS=$(nproc)
  else
    OS_JOBS=1
  fi
fi

CONF_BUILD=$(/bin/sh "${SCRIPT_DIR}/config.guess")
CONF_HOST=${NACL_CROSS_PREFIX}
# TODO(gdeepti): Investigate whether emscripten accurately fits this case for
# long term usage.
if [[ ${NACL_ARCH} == pnacl ]]; then
  # The PNaCl tools use "pnacl-" as the prefix, but config.sub
  # does not know about "pnacl".  It only knows about "le32-nacl".
  # Unfortunately, most of the config.subs here are so old that
  # it doesn't know about that "le32" either.  So we just say "nacl".
  CONF_HOST="nacl"
fi

GomaTest() {
  # test the goma compiler
  if [ "${NACL_GOMA_FORCE:-}" = 1 ]; then
    return 0
  fi
  echo 'int foo = 4;' > goma_test.c
  GOMA_USE_LOCAL=false GOMA_FALLBACK=false gomacc "$1" -c \
      goma_test.c -o goma_test.o 2> /dev/null
  local RTN=$?
  rm -f goma_test.c
  rm -f goma_test.o
  return ${RTN}
}

# If NACL_GOMA is defined then we check for goma and use it if its found.
if [ -n "${NACL_GOMA:-}" ]; then
  if [ "${NACL_ARCH}" != "pnacl" -a
    "${NACL_ARCH}" != "arm" -a
    "${NACL_ARCH}" != "emscripten"]; then
    # Assume that if CC is good then so is CXX since GomaTest is actually
    # quite slow
    if GomaTest "${NACLCC}"; then
      NACLCC="gomacc ${NACLCC}"
      NACLCXX="gomacc ${NACLCXX}"
      # There is a bug in goma right now where the i686 compiler wrapper script
      # is not correctly handled and gets confused with the x86_64 version.
      # We need to pass a redundant -m32, to force it to compiler for i686.
      if [ "${NACL_ARCH}" = "i686" ]; then
        NACLPORTS_CFLAGS+=" -m32"
        NACLPORTS_CXXFLAGS+=" -m32"
      fi
      OS_JOBS=100
      echo "Using GOMA!"
    fi
  fi
fi

if [ "${NACL_DEBUG}" = "1" ]; then
  NACL_CONFIG=Debug
else
  NACL_CONFIG=Release
fi

# ARCHIVE_ROOT (the folder contained within that archive) defaults to
# the NAME-VERSION.  Packages with non-standard contents can override
# this before including common.sh
PACKAGE_NAME=${NAME}
ARCHIVE_ROOT=${ARCHIVE_ROOT:-${NAME}-${VERSION}}
WORK_DIR=${NACL_PACKAGES_BUILD}/${NAME}
SRC_DIR=${WORK_DIR}/${ARCHIVE_ROOT}
DEFAULT_BUILD_DIR=${WORK_DIR}/${NACL_BUILD_SUBDIR}
BUILD_DIR=${NACL_BUILD_DIR:-${DEFAULT_BUILD_DIR}}
INSTALL_DIR=${WORK_DIR}/${NACL_INSTALL_SUBDIR}
NACL_CONFIGURE_PATH=${NACL_CONFIGURE_PATH:-${SRC_DIR}/configure}


# DESTDIR is where the headers, libraries, etc. will be installed
# Default to the usr folder within the SDK.
if [ -z "${DESTDIR:-}" ]; then
  readonly DEFAULT_DESTDIR=1
  DESTDIR=${INSTALL_DIR}
fi

DESTDIR_LIB=${DESTDIR}/${PREFIX}/lib
DESTDIR_BIN=${DESTDIR}/${PREFIX}/bin
DESTDIR_INCLUDE=${DESTDIR}/${PREFIX}/include

PUBLISH_DIR="${NACL_PACKAGES_PUBLISH}/${PACKAGE_NAME}/${TOOLCHAIN}"
PUBLISH_CREATE_NMF_ARGS="-L ${DESTDIR_LIB}"

if [[ ${OS_NAME} == Linux ]]; then
  SEL_LDR_SUPPORTS_ARM=1
else
  SEL_LDR_SUPPORTS_ARM=0
fi

SKIP_SEL_LDR_TESTS=0

# Skip sel_ldr tests on ARM, except on linux where we have qemu-arm available.
if [[ ${NACL_ARCH} == arm && ${SEL_LDR_SUPPORTS_ARM} == 0 ]]; then
  SKIP_SEL_LDR_TESTS=1
fi

# Skip sel_ldr tests when building x86_64 targets on a 32-bit host
if [ "${NACL_ARCH}" = "x86_64" -a "${HOST_IS_32BIT}" = "1" ]; then
  echo "WARNING: Building x86_64 targets on i686 host. Cannot run tests."
  SKIP_SEL_LDR_TESTS=1
fi


######################################################################
# Always run
######################################################################

InstallConfigSite() {
  CONFIG_SITE=${NACL_PREFIX}/share/config.site
  MakeDir "${NACL_PREFIX}/share"
  echo "ac_cv_exeext=${NACL_EXEEXT}" > "${CONFIG_SITE}"
}


#
# $1 - src
# $2 - dest
#
InstallHeader() {
  local src=$1
  local dest=$2
  if [ -f "${dest}" ]; then
    if cmp "${src}" "${dest}" > /dev/null; then
      return
    fi
  fi
  MakeDir "$(dirname ${dest})"
  LogExecute install -m 644 "${src}" "${dest}"
}

#
# When configure checks for system headers is doesn't pass CFLAGS
# to the compiler.  This means that any includes that live in paths added
# with -I are not found.  Here we push the additional newlib headers
# into the toolchain itself from ${NACL_SDK_ROOT}/include/<toolchain>.
#
InjectSystemHeaders() {
  if [ ${TOOLCHAIN} = "clang-newlib" ]; then
    local TC_DIR=pnacl
  else
    local TC_DIR=${TOOLCHAIN}
  fi

  if [ ${TOOLCHAIN} = "glibc" ]; then
    InstallHeader "${TOOLS_DIR}/stubs.h" "${NACLPORTS_INCLUDE}/gnu/stubs.h"
  fi

  local TC_INCLUDES=${NACL_SDK_ROOT}/include/${TC_DIR}
  if [ ! -d "${TC_INCLUDES}" ]; then
    return
  fi

  MakeDir ${NACLPORTS_INCLUDE}
  for inc in $(find ${TC_INCLUDES} -type f); do
    inc="${inc#${TC_INCLUDES}}"
    inc="${inc#${TOOLS_DIR}}"
    src="${TC_INCLUDES}${inc}"
    dest="${NACLPORTS_INCLUDE}${inc}"
    InstallHeader $src $dest
  done
}


PatchSpecsFile() {
  if [ "${TOOLCHAIN}" = "pnacl" -o \
       "${TOOLCHAIN}" = "clang-newlib" -o \
       "${TOOLCHAIN}" = "emscripten" ]; then
    # The emscripten and PNaCl toolchains already include the required
    # include and library paths by default. No need to patch them.
    return
  fi

  # For the library path we always explicitly add to the link flags
  # otherwise 'libtool' won't find the libraries correctly.  This
  # is because libtool uses 'gcc -print-search-dirs' which does
  # not honor the external specs file.
  NACLPORTS_LDFLAGS+=" -L${NACLPORTS_LIBDIR}"
  NACLPORTS_LDFLAGS+=" -Wl,-rpath-link=${NACLPORTS_LIBDIR}"

  # SPECS_FILE is where nacl-gcc 'specs' file will be installed
  local SPECS_DIR=
  if [ "${NACL_ARCH}" = "arm" ]; then
    SPECS_DIR=${NACL_TOOLCHAIN_ROOT}/lib/gcc/arm-nacl/4.8.3
    if [ ! -d "${SPECS_DIR}" ]; then
      SPECS_DIR=${NACL_TOOLCHAIN_ROOT}/lib/gcc/arm-nacl/4.9.2
    fi
  else
    SPECS_DIR=${NACL_TOOLCHAIN_ROOT}/lib/gcc/x86_64-nacl/4.4.3
  fi
  if [ ! -d "${SPECS_DIR}" ]; then
    echo "error: gcc directory not found: ${SPECS_DIR}"
    exit 1
  fi
  local SPECS_FILE=${SPECS_DIR}/specs

  # NACL_SDK_MULITARCH_USR is a version of NACL_TOOLCHAIN_ROOT that gets passed
  # into the gcc specs file.  It has a gcc spec-file conditional for
  # ${NACL_ARCH}
  local NACL_SDK_MULTIARCH_USR="${NACL_TOOLCHAIN_ROOT}/\%\(nacl_arch\)/usr"
  local NACL_SDK_MULTIARCH_USR_INCLUDE="${NACL_SDK_MULTIARCH_USR}/include"
  local NACL_SDK_MULTIARCH_USR_LIB="${NACL_SDK_MULTIARCH_USR}/lib"
  local ERROR_MSG="Shared libraries are not supported by newlib toolchain"

  # fix up spaces so gcc sees entire path
  local SED_SAFE_SPACES_USR_INCLUDE=${NACL_SDK_MULTIARCH_USR_INCLUDE/ /\ /}
  local SED_SAFE_SPACES_USR_LIB=${NACL_SDK_MULTIARCH_USR_LIB/ /\ /}

  if [ -f ${SPECS_FILE} ]; then
    if grep -q nacl_arch ${SPECS_FILE}; then
      echo "Specs file already patched"
      return
    fi
    echo "Patching existing specs file"
    cp ${SPECS_FILE} ${SPECS_FILE}.current
  else
    echo "Creating new specs file"
    ${NACLCC} -dumpspecs > ${SPECS_FILE}.current
  fi

  # add include & lib search paths to specs file
  if [ "${NACL_ARCH}" = "arm" ]; then
    local ARCH_SUBST='/\*cpp:/ {
        printf("*nacl_arch:\narm-nacl\n\n", $1); }
        { print $0; }'
  else
    local ARCH_SUBST='/\*cpp:/ {
        printf("*nacl_arch:\n%%{m64:x86_64-nacl; m32:i686-nacl; :x86_64-nacl}\n\n", $1); }
        { print $0; }'
  fi

  awk "${ARCH_SUBST}" < ${SPECS_FILE}.current |\
    sed "/*cpp:/{
      N
      s|$| -isystem ${SED_SAFE_SPACES_USR_INCLUDE}|
    }" |\
    sed "/*link_libgcc:/{
      N
      s|$| -rpath-link=${SED_SAFE_SPACES_USR_LIB} -L${SED_SAFE_SPACES_USR_LIB}|
    }" > "${SPECS_FILE}"

  # For static-only toolchains (i.e. pnacl), modify the specs file to give an
  # error when attempting to create a shared object.
  if [ "${NACL_SHARED}" != "1" ]; then
    sed -i.bak "s/%{shared:-shared/%{shared:%e${ERROR_MSG}/" "${SPECS_FILE}"
  fi

}


######################################################################
# Helper functions
######################################################################

Banner() {
  echo "######################################################################"
  echo "$@"
  echo "######################################################################"
}


#
# echo a command to stdout and then execute it.
#
LogExecute() {
  echo "$@"
  "$@"
}


#
# Return 0 if the current port's URL points to a git repo, 1 otherwise.
#
IsGitRepo() {
  if [ -z "${URL:-}" ]; then
    return 1
  fi

  local GIT_URL=${URL%@*}

  if [[ "${#GIT_URL}" -ge "4" ]] && [[ "${GIT_URL:(-4)}" == ".git" ]]; then
    return 0
  else
    return 1
  fi
}


#
# Return 0 if the current port is autoconf-based, 1 otherwise.
# This must be called after the source archive is expanded
# as it inspects the contents of ${SRC_DIR}
#
IsAutoconfProject() {
  if [ -f "${NACL_CONFIGURE_PATH}" ]; then
    return 0
  else
    return 1
  fi
}


#
# Return 0 if the current port is cmake-based, 1 otherwise.
# This must be called after the source archive is expanded
# as it inspects the contents of ${current}
#
IsCMakeProject() {
  if IsAutoconfProject; then
    return 1
  fi
  if [ -f "${SRC_DIR}/CMakeLists.txt" ]; then
    return 0
  else
    return 1
  fi
}


#
# Add optimization flags for either debug or release configuration.
# This is not done for cmake-based projects as cmake adds these
# internally.
#
SetOptFlags() {
  if IsCMakeProject; then
    return
  fi

  if [ "${NACL_DEBUG}" = "1" ]; then
    NACLPORTS_CFLAGS+=" -g -O0"
    NACLPORTS_CXXFLAGS+=" -g -O0"
  else
    NACLPORTS_CFLAGS+=" -DNDEBUG -O2"
    NACLPORTS_CXXFLAGS+=" -DNDEBUG -O2"
    if [ "${NACL_ARCH}" = "pnacl"  -a "${NACL_ARCH}" == "le32" ]; then
      NACLPORTS_LDFLAGS+=" -DNDEBUG -O2"
    fi
  fi
}

EnableCliMain() {
  if [[ ${TOOLCHAIN} == emscripten ]]; then
    return
  fi
  NACLPORTS_LDFLAGS+=" ${NACL_CLI_MAIN_LDFLAGS}"
  NACLPORTS_LIBS+=" ${NACL_CLI_MAIN_LIB}"
}

EnableCliMainCxx() {
  if [[ ${TOOLCHAIN} == emscripten ]]; then
    return
  fi
  NACLPORTS_LDFLAGS+=" ${NACL_CLI_MAIN_LDFLAGS}"
  NACLPORTS_LIBS+=" ${NACL_CLI_MAIN_LIB_CPP}"
}

EnableGlibcCompat() {
  if [ "${NACL_LIBC}" = "newlib" ]; then
    NACLPORTS_CPPFLAGS+=" -I${NACLPORTS_INCLUDE}/glibc-compat"
    NACLPORTS_LIBS+=" -lglibc-compat"
  fi
}

#
# Attempt to download a file from a given URL
# $1 - URL to fetch
# $2 - Filename to write to.
#
TryFetch() {
  local URL=$1
  local FILENAME=$2
  Banner "Fetching ${PACKAGE_NAME} (${FILENAME})"
  # Send curl's status messages to stdout rather then stderr
  CURL_ARGS="--fail --location --stderr -"
  if [ -t 1 ]; then
    # Add --progress-bar but only if stdout is a TTY device.
    CURL_ARGS+=" --progress-bar"
  else
    # otherwise suppress all status output, since curl always
    # assumes a TTY and writes \r and \b characters.
    CURL_ARGS+=" --silent"
  fi
  if which curl > /dev/null ; then
    curl ${CURL_ARGS} -o "${FILENAME}" "${URL}"
  else
    echo "error: could not find 'curl' in your PATH"
    exit 1
  fi
}


#
# Download a file from a given URL
# $1 - URL to fetch
# $2 - Filename to write to.
#
Fetch() {
  local URL=$1
  local FILENAME=$2
  local MIRROR_URL=http://storage.googleapis.com/webports/mirror
  if echo ${URL} | grep -qv http://storage.googleapis.com &> /dev/null; then
    set +o errexit
    # Try mirrored version first
    local BASENAME=${URL_FILENAME:-$(basename ${URL})}
    TryFetch "${MIRROR_URL}/${BASENAME}" "${FILENAME}"
    if [ $? != 0 -a ${FORCE_MIRROR:-no} = "no" ]; then
      # Fall back to original URL
      TryFetch "${URL}" "${FILENAME}"
    fi
    set -o errexit
  else
    # The URL is already on Google Clound Storage do just download it
    TryFetch "${URL}" "${FILENAME}"
  fi

  if [ ! -s "${FILENAME}" ]; then
    echo "ERROR: failed to download ${FILENAME}"
    exit 1
  fi
}


#
# verify the sha1 checksum of given file
# $1 - filename
# $2 - checksum (as hex string)
#
CheckHash() {
  if echo "$2 *$1" | "${SHA1CHECK}"; then
    return 0
  else
    return 1
  fi
}


VerifyPath() {
  # make sure path isn't all slashes (possibly from an unset variable)
  local PATH=$1
  local TRIM=${PATH##/}
  if [ ${#TRIM} -ne 0 ]; then
    return 0
  else
    return 1
  fi
}


ChangeDir() {
  local NAME="$1"
  if VerifyPath "${NAME}"; then
    echo "chdir ${NAME}"
    cd "${NAME}"
  else
    echo "ChangeDir called with bad path."
    exit 1
  fi
}


Remove() {
  for filename in $*; do
    if VerifyPath "${filename}"; then
      rm -rf "${filename}"
    else
      echo "Remove called with bad path: ${filename}"
      exit 1
    fi
  done
}


MakeDir() {
  local NAME="$1"
  if VerifyPath "${NAME}"; then
    mkdir -p "${NAME}"
  else
    echo "MakeDir called with bad path."
    exit 1
  fi
}


MakeDirs() {
  MakeDir "${NACL_PACKAGES_ROOT}"
  MakeDir "${NACL_PACKAGES_BUILD}"
  # If 'tarballs' directory exists then rename it to the new name: 'cache'.
  # TODO(sbc): remove this once the new name as been in existence for
  # a few months.
  if [ ! -d "${NACL_PACKAGES_CACHE}" -a -d "${NACL_PACKAGES_OUT}/tarballs" ]; then
    mv "${NACL_PACKAGES_OUT}/tarballs" "${NACL_PACKAGES_CACHE}"
  fi
  MakeDir "${NACL_PACKAGES_CACHE}"
  MakeDir "${NACL_PACKAGES_PUBLISH}"
  MakeDir "${WORK_DIR}"
}


#
# Assemble a multi-arch version for use in the devenv packaged app.
#
#
PublishMultiArch() {
  local binary=$1
  local target=$2

  if [ $# -gt 2 ]; then
    local assembly_dir="${PUBLISH_DIR}/$3"
  else
    local assembly_dir="${PUBLISH_DIR}"
  fi

  if [[ ${TOOLCHAIN} == emscripten ]]; then
    LogExecute cp ${BUILD_DIR}/${binary} ${target}${NACL_EXEEXT}
    return
  fi

  local platform_dir="${assembly_dir}/_platform_specific/${NACL_ARCH}"
  MakeDir ${platform_dir}
  if [[ ${TOOLCHAIN} == pnacl ]]; then
    # Add something to the per-arch directory there so the store will accept
    # the app even if nothing else ends up there. This currently happens in
    # the pnacl case, where there's nothing that's per architecture.
    touch ${platform_dir}/MARKER

    local exe="${assembly_dir}/${target}${NACL_EXEEXT}"
    LogExecute ${PNACLFINALIZE} ${BUILD_DIR}/${binary} -o ${exe}
    ChangeDir ${assembly_dir}
    LogExecute python ${NACL_SDK_ROOT}/tools/create_nmf.py \
        ${exe} -s . -o ${target}.nmf
  else
    local exe="${platform_dir}/${target}${NACL_EXEEXT}"
    LogExecute cp ${BUILD_DIR}/${binary} ${exe}
    ChangeDir ${assembly_dir}
    LogExecute python ${NACL_SDK_ROOT}/tools/create_nmf.py --no-arch-prefix \
        _platform_specific/*/${target}*${NACL_EXEEXT} \
        -s . -o ${target}.nmf
  fi
}


#
# CheckStamp: checks for the existence of a stamp file
# $1 - Name of stamp file.
#
CheckStamp() {
  local STAMP_DIR="${NACL_PACKAGES_STAMPDIR}/${PACKAGE_NAME}"
  local STAMP_FILE="${STAMP_DIR}/$1"
  # check the stamp file exists and is newer and dependency
  if [ ! -f "${STAMP_FILE}" ]; then
    return 1
  fi
  return 0
}


TouchStamp() {
  local STAMP_DIR=${NACL_PACKAGES_STAMPDIR}/${PACKAGE_NAME}
  MakeDir "${STAMP_DIR}"
  touch "${STAMP_DIR}/$1"
}


InstallNaClTerm() {
  local INSTALL_DIR=$1
  local CHROMEAPPS=${NACL_SRC}/third_party/libapps/
  local LIB_DOT=${CHROMEAPPS}/libdot
  local HTERM=${CHROMEAPPS}/hterm
  LIBDOT_SEARCH_PATH=${CHROMEAPPS} LogExecute "${LIB_DOT}/bin/concat.sh" \
      -i "${HTERM}/concat/hterm_deps.concat" -o "${INSTALL_DIR}/hterm.concat.js"
  LIBDOT_SEARCH_PATH=${CHROMEAPPS} LogExecute ${LIB_DOT}/bin/concat.sh \
      -i "${HTERM}/concat/hterm.concat" -o "${INSTALL_DIR}/hterm2.js"
  chmod +w "${INSTALL_DIR}/hterm.concat.js" "${INSTALL_DIR}/hterm2.js"
  cat "${INSTALL_DIR}/hterm2.js" >> "${INSTALL_DIR}/hterm.concat.js"
  Remove "${INSTALL_DIR}/hterm2.js"

  LogExecute cp "${TOOLS_DIR}/naclterm.js" "${INSTALL_DIR}"
  LogExecute cp "${TOOLS_DIR}/pipeserver.js" "${INSTALL_DIR}"
  if [[ "${NACL_ARCH}" = "pnacl" || "${NACL_ARCH}" = "le32" ]] ; then
    sed 's/x-nacl/x-pnacl/' \
        "${TOOLS_DIR}/naclprocess.js" > "${INSTALL_DIR}/naclprocess.js"
  else
    LogExecute cp "${TOOLS_DIR}/naclprocess.js" "${INSTALL_DIR}"
  fi
}


#
# Build step for projects based on the NaCl SDK build
# system (common.mk).
#
SetupSDKBuildSystem() {
  # We override $(OUTBASE) to force the build system to put
  # all its artifacts in ${SRC_DIR} rather than alongside
  # the Makefile.
  export OUTBASE=${SRC_DIR}
  export CFLAGS="${NACLPORTS_CPPFLAGS} ${NACLPORTS_CFLAGS}"
  export CXXFLAGS="${NACLPORTS_CPPFLAGS} ${NACLPORTS_CXXFLAGS}"
  export LDFLAGS="${NACLPORTS_LDFLAGS} ${NACLPORTS_LIBS}"
  export NACL_PREFIX
  export NACL_PACKAGES_PUBLISH
  export NACL_SRC
  export NACLPORTS_INCLUDE
  export NACLPORTS_REVISION=${REVISION}
  export PKG_CONFIG_LIBDIR="${NACLPORTS_LIBDIR}/pkgconfig"
  export ENABLE_BIONIC=1
  # By default PKG_CONFIG_PATH is set to <libdir>/pkgconfig:<datadir>/pkgconfig.
  # While PKG_CONFIG_LIBDIR overrides <libdir>, <datadir> (/usr/share/) can only
  # be overridden individually when pkg-config is built.
  # Setting PKG_CONFIG_PATH instead to compensate.
  export PKG_CONFIG_PATH="${NACLPORTS_LIBDIR}/pkgconfig"
  PKG_CONFIG_PATH+=":${NACLPORTS_LIBDIR}/../share/pkgconfig"

  MAKEFLAGS+=" TOOLCHAIN=${TOOLCHAIN}"
  MAKEFLAGS+=" NACL_ARCH=${NACL_ARCH_ALT}"
  if [ "${NACL_DEBUG}" = "1" ]; then
    MAKEFLAGS+=" CONFIG=Debug"
  else
    MAKEFLAGS+=" CONFIG=Release"
  fi
  if [ "${VERBOSE:-}" = "1" ]; then
    MAKEFLAGS+=" V=1"
  fi
  export MAKEFLAGS

  BUILD_DIR=${START_DIR}
  echo "LDFLAGS=${LDFLAGS}"
}

SetupCrossPaths() {
  export PKG_CONFIG_LIBDIR="${NACLPORTS_LIBDIR}/pkgconfig"
  # By default PKG_CONFIG_PATH is set to <libdir>/pkgconfig:<datadir>/pkgconfig.
  # While PKG_CONFIG_LIBDIR overrides <libdir>, <datadir> (/usr/share/) can only
  # be overridden individually when pkg-config is built.
  # Setting PKG_CONFIG_PATH instead to compensate.
  export PKG_CONFIG_PATH="${NACLPORTS_LIBDIR}/pkgconfig"
  PKG_CONFIG_PATH+=":${NACLPORTS_LIBDIR}/../share/pkgconfig"
  export SDL_CONFIG=${NACLPORTS_BIN}/sdl-config
  export FREETYPE_CONFIG=${NACLPORTS_BIN}/freetype-config
  export PATH=${NACL_BIN_PATH}:${NACLPORTS_BIN}:${PATH}
}

SetupCrossEnvironment() {
  SetupCrossPaths

  # export the nacl tools
  export CONFIG_SITE
  export EXEEXT=${NACL_EXEEXT}
  export CC=${NACLCC}
  export CXX=${NACLCXX}
  export AR=${NACLAR}
  export RANLIB=${NACLRANLIB}
  export READELF=${NACLREADELF}
  export STRIP=${NACLSTRIP}

  export CFLAGS=${NACLPORTS_CFLAGS}
  export CPPFLAGS=${NACLPORTS_CPPFLAGS}
  export CXXFLAGS=${NACLPORTS_CXXFLAGS}
  export LDFLAGS=${NACLPORTS_LDFLAGS}
  export ARFLAGS=${NACL_ARFLAGS}
  export AR_FLAGS=${NACL_ARFLAGS}
  export LIBS=${LIBS:-${NACLPORTS_LIBS}}

  echo "CPPFLAGS=${CPPFLAGS}"
  echo "CFLAGS=${CFLAGS}"
  echo "CXXFLAGS=${CXXFLAGS}"
  echo "LDFLAGS=${LDFLAGS}"
  echo "LIBS=${LIBS}"
}

GetRevision() {
  cd ${NACL_SRC}
  FULL_REVISION=$(git describe)
  REVISION=$(echo "${FULL_REVISION}" | cut  -f2 -d-)
  cd - > /dev/null
}


GenerateManifest() {
  local SOURCE_FILE=$1
  shift
  local TARGET_DIR=$1
  shift
  local TEMPLATE_EXPAND="${SCRIPT_DIR}/template_expand.py"

  # TODO(sbc): deal with versions greater than 16bit.
  if (( REVISION >= 65536 )); then
    echo "error: Version too great to store in revision field on manifest.json"
    exit 1
  fi

  echo "Expanding ${SOURCE_FILE} > ${TARGET_DIR}/manifest.json"
  # Generate a manifest.json
  "${TEMPLATE_EXPAND}" "${SOURCE_FILE}" \
    version=${REVISION} $* > ${TARGET_DIR}/manifest.json
}


FixupExecutablesList() {
  # Modify EXECUTABLES list for libtool case where actual executables
  # live within the ".libs" folder.
  local executables_modified=
  for nexe in ${EXECUTABLES:-}; do
    local basename=$(basename ${nexe})
    local dirname=$(dirname ${nexe})
    if [ -f "${dirname}/.libs/${basename}" ]; then
      executables_modified+=" ${dirname}/.libs/${basename}"
    else
      executables_modified+=" ${nexe}"
    fi
  done
  EXECUTABLES=${executables_modified}
}


VerifySharedLibraryOrder() {
  if [ "${NACL_LIBC}" != "glibc" ]; then
    return
  fi
  # Check that pthreads comes after nacl_io + nacl_spawn in the needed order.
  # Pthreads has interception hooks that forward directly into glibc.
  # If it gets loaded first, nacl_io doesn't get a chance to intercept.
  for nexe in ${EXECUTABLES:-}; do
    echo "Verifying shared library order for ${nexe}"
    if ! OBJDUMP=${NACLOBJDUMP} ${TOOLS_DIR}/check_needed_order.py ${nexe}; then
      echo "error: glibc shared library order check failed"
      exit 1
    fi
  done
}


######################################################################
# Build Steps
######################################################################

PatchConfigSub() {
  # Replace the package's config.sub one with an up-do-date copy
  # that includes nacl support.  We only do this if the string
  # 'nacl)' is not already contained in the file.
  CONFIG_SUB=${CONFIG_SUB:-config.sub}
  if [ ! -f "${CONFIG_SUB}" ]; then
    CONFIG_SUB=$(find "${SRC_DIR}" -name config.sub -print)
  fi

  for sub in ${CONFIG_SUB}; do
    if grep -q 'nacl)' "${sub}" /dev/null; then
      if grep -q 'emscripten)' "${sub}" /dev/null; then
        echo "${CONFIG_SUB} supports NaCl + emscripten"
        continue
      fi
    fi
    echo "Patching ${sub}"
    /bin/cp -f "${TOOLS_DIR}/config.sub" "${sub}"
  done
}


PatchConfigure() {
  if [ -f configure ]; then
    Banner "Patching configure"
    "${TOOLS_DIR}/patch_configure.py" configure
  fi
}


DefaultPatchStep() {
  # The applicaiton of the nacl.patch file is now done by
  # webports python code.
  # TODO(sbc): migrate auto patching of config sub and configure
  # and remove this function.

  if [ -z "${URL:-}" ] && ! IsGitRepo; then
    return
  fi

  ChangeDir "${SRC_DIR}"

  if CheckStamp patch ; then
    return
  fi

  PatchConfigure
  PatchConfigSub
  if [ -n "$(git diff --no-ext-diff)" ]; then
    git add -u
    git commit -m "Automatic patch generated by webports"
  fi

  TouchStamp patch
}


DefaultConfigureStep() {
  if [ "${NACLPORTS_QUICKBUILD}" = "1" ]; then
    CONFIGURE_SENTINEL=${CONFIGURE_SENTINEL:-Makefile}
  fi

  if [ -n "${CONFIGURE_SENTINEL:-}" -a -f "${CONFIGURE_SENTINEL:-}" ]; then
    return
  fi

  if [ "${TOOLCHAIN}" = "emscripten" ]; then
    # This is a variable the emconfigure sets, presumably to make configure
    # tests do the right thing.
    # TODO(sbc): We should probably call emconfigure instead of trying to
    # duplicate its functionality.
    export EMMAKEN_JUST_CONFIGURE=1
  fi

  if IsAutoconfProject; then
    ConfigureStep_Autoconf
  elif IsCMakeProject; then
    ConfigureStep_CMake
  else
    echo "No configure or CMakeLists.txt script found in ${SRC_DIR}"
  fi
}


ConfigureStep_Autoconf() {
  SetupCrossEnvironment

  # Without this autoconf builds will use the same CFLAGS/LDFLAGS for host
  # builds as NaCl builds and not all the flags we use are supported by the
  # host compiler, which could be an older version of gcc
  # (e.g. -fdiagnostics-color=auto).
  export CFLAGS_FOR_BUILD=""
  export LDFLAGS_FOR_BUILD=""

  # Inject a shim that speed up pnacl invocations for configure.
  if [ "${NACL_ARCH}" = "pnacl" ]; then
    local PNACL_CONF_SHIM="${TOOLS_DIR}/pnacl-configure-shim.py"
    CC="${PNACL_CONF_SHIM} ${CC}"
  fi

  if [[ ${TOOLCHAIN} == emscripten ]]; then
    echo "export EMMAKEN_JUST_CONFIGURE=1"
    export EMMAKEN_JUST_CONFIGURE=1
  fi

  # Specify both --build and --host options.  This forces autoconf into cross
  # compile mode.  This is useful since the autodection doesn't always works.
  # For example a trivial PNaCl binary can sometimes run on the linux host if
  # it has the correct LLVM bimfmt support. What is more, autoconf will
  # generate a warning if only --host is specified.
  LogExecute "${NACL_CONFIGURE_PATH}" \
    --build=${CONF_BUILD} \
    --host=${CONF_HOST} \
    --prefix=${PREFIX} \
    --with-http=no \
    --with-ftp=no \
    --${NACL_OPTION}-mmx \
    --${NACL_OPTION}-sse \
    --${NACL_OPTION}-sse2 \
    --${NACL_OPTION}-asm \
    --with-x=no \
    ${EXTRA_CONFIGURE_ARGS:-}
}


ConfigureStep_CMake() {
  if [ "${CMAKE_USE_NINJA:-}" = "1" ]; then
    EXTRA_CMAKE_ARGS+=" -GNinja"
  fi

  if [ $NACL_DEBUG = "1" ]; then
    BUILD_TYPE=DEBUG
  else
    BUILD_TYPE=RELEASE
  fi

  SetupCrossPaths
  export CFLAGS="${NACLPORTS_CPPFLAGS} ${NACLPORTS_CFLAGS}"
  export CXXFLAGS="${NACLPORTS_CPPFLAGS} ${NACLPORTS_CXXFLAGS}"
  export LDFLAGS="${NACLPORTS_LDFLAGS} ${NACLPORTS_LIBS}"
  LogExecute cmake "${SRC_DIR}" \
           -DCMAKE_TOOLCHAIN_FILE=${TOOLS_DIR}/XCompile-nacl.cmake \
           -DNACLAR=${NACLAR} \
           -DNACLLD=${NACLLD} \
           -DNACLCC=${NACLCC} \
           -DNACLCXX=${NACLCXX} \
           -DNACL_CROSS_PREFIX=${NACL_CROSS_PREFIX} \
           -DNACL_ARCH=${NACL_ARCH} \
           -DNACL_SDK_ROOT=${NACL_SDK_ROOT} \
           -DNACL_SDK_LIBDIR=${NACL_SDK_LIBDIR} \
           -DNACL_TOOLCHAIN_ROOT=${NACL_TOOLCHAIN_ROOT} \
           -DNACL_LIBC=${NACL_LIBC} \
           -DCMAKE_PREFIX_PATH=${NACL_PREFIX} \
           -DCMAKE_INSTALL_PREFIX=${PREFIX} \
           -DCMAKE_BUILD_TYPE=${BUILD_TYPE} ${EXTRA_CMAKE_ARGS:-}
}


DefaultBuildStep() {
  if [ "${CMAKE_USE_NINJA:-}" = "1" ]; then
    if [ "${VERBOSE:-}" = "1" ]; then
      NINJA_ARGS="-v"
    fi
    LogExecute ninja ${NINJA_ARGS:-} ${MAKE_TARGETS:-}
    return
  fi

  # Build ${MAKE_TARGETS} or default target if it is not defined
  if [ -n "${MAKEFLAGS:-}" ]; then
    echo "MAKEFLAGS=${MAKEFLAGS}"
    export MAKEFLAGS
  fi
  if [ "${VERBOSE:-}" = "1" ]; then
    MAKE_TARGETS+=" VERBOSE=1 V=1"
  fi
  export PATH=${NACL_BIN_PATH}:${PATH}
  LogExecute make -j${OS_JOBS} ${MAKE_TARGETS:-}
}


DefaultPythonModuleBuildStep() {
  SetupCrossEnvironment
  Banner "Build ${PACKAGE_NAME} python module"
  ChangeDir "${SRC_DIR}"
  LogExecute rm -rf build dist
  MakeDir "${NACL_DEST_PYROOT}/${SITE_PACKAGES}"
  export PYTHONPATH="${NACL_HOST_PYROOT}/${SITE_PACKAGES}"
  export PYTHONPATH="${PYTHONPATH}:${NACL_DEST_PYROOT}/${SITE_PACKAGES}"
  export NACL_PORT_BUILD=${1:-dest}
  export NACL_BUILD_TREE=${NACL_DEST_PYROOT}
  export CFLAGS="${NACLPORTS_CPPFLAGS} ${NACLPORTS_CFLAGS}"
  export CXXFLAGS="${NACLPORTS_CPPFLAGS} ${NACLPORTS_CXXFLAGS}"
  export LDFLAGS="${NACLPORTS_LDFLAGS} ${NACLPORTS_LIBS}"
  export LIBS="${NACLPORTS_LIBS}"
  LogExecute "${NACL_HOST_PYTHON}" setup.py ${NACL_PYSETUP_ARGS} \
    install "--prefix=${NACL_DEST_PYROOT}"
  MakeDir "${DEST_PYTHON_OBJS}/${PACKAGE_NAME}"
  LogExecute find build -name "*.o" -execdir cp -v {} \
    "${DEST_PYTHON_OBJS}/${PACKAGE_NAME}/"{} \;
}


DefaultTestStep() {
  echo "No TestStep defined for ${PACKAGE_NAME}"
}


DefaultPublishStep() {
  echo "No PublishStep defined for ${PACKAGE_NAME}"
}


DefaultPostInstallTestStep() {
  echo "No PostInstallTestStep defined for ${PACKAGE_NAME}"
}


DefaultInstallStep() {
  INSTALL_TARGETS=${INSTALL_TARGETS:-install}

  if [ "${CMAKE_USE_NINJA:-}" = "1" ]; then
    DESTDIR="${DESTDIR}" LogExecute ninja ${INSTALL_TARGETS}
    return
  fi

  # assumes pwd has makefile
  if [ -n "${MAKEFLAGS:-}" ]; then
    echo "MAKEFLAGS=${MAKEFLAGS}"
    export MAKEFLAGS
  fi
  export PATH="${NACL_BIN_PATH}:${PATH}"
  LogExecute make ${INSTALL_TARGETS} "DESTDIR=${DESTDIR}"
}


DefaultPythonModuleInstallStep() {
  Banner "Installing ${PACKAGE_NAME}"
  # We've installed already previously.  We just need to collect our modules.
  MakeDir "${NACL_HOST_PYROOT}/python_modules/"
  if [ -e "${START_DIR}/modules.list" ] ; then
    LogExecute cp "${START_DIR}/modules.list" \
                  "${DEST_PYTHON_OBJS}/${PACKAGE_NAME}.list"
  fi
  if [ -e "${START_DIR}/modules.libs" ] ; then
    LogExecute cp "${START_DIR}/modules.libs" \
                  "${DEST_PYTHON_OBJS}/${PACKAGE_NAME}.libs"
  fi
}


#
# Validate a given NaCl executable (.nexe file)
# $1 - Execuatable file (.nexe)
#
Validate() {
  local binary=$1

  if [[ ${NACL_ARCH} = pnacl || ${NACL_ARCH} = le32
    || ${NACL_ARCH} = emscripten ]]; then
    if [[ ! -f $binary ]]; then
      echo "error: missing binary: ${binary}"
      exit 1
    fi
    return
  fi

  LogExecute "${NACL_SDK_ROOT}/tools/ncval" "${binary}"
  if [[ $? != 0 ]]; then
    exit 1
  fi
}


#
# PostBuildStep by default will validate (using ncval) any executables
# specified in the ${EXECUTABLES} as well as create wrapper scripts
# for running them in sel_ldr.
#
DefaultPostBuildStep() {
  if [[ -z ${EXECUTABLES} ]]; then
    return
  fi
  if [[ ${NACL_ARCH} == pnacl  || ${NACL_ARCH} == le32 ]]; then
    if [[ ${NACL_ARCH} == pnacl ]]; then
      for pexe in ${EXECUTABLES}; do
        FinalizePexe "${pexe}"
      done
    fi
    if [[ ${TRANSLATE_PEXES:-} == no ]]; then
      return
    fi
    for pexe in ${EXECUTABLES}; do
      TranslatePexe "${pexe}"
    done
  fi
  for nexe in ${EXECUTABLES}; do
    Validate "${nexe}"
    # Create a script which will run the executable in sel_ldr.  The name
    # of the script is the same as the name of the executable, either without
    # any extension or with the .sh extension.

    local script_name="${nexe}.sh"
    if [[ ${nexe} == *${NACL_EXEEXT} && ! -d ${nexe%%${NACL_EXEEXT}} ]]; then
      script_name="${nexe%%${NACL_EXEEXT}}"
    fi

    nexe="$(basename ${nexe})"
    if [[ ${NACL_ARCH} == pnacl || ${NACL_ARCH} == le32 ]]; then
      local basename="${nexe%.*}"
      nexe=${basename}.x86-64.nexe
    fi
    WriteLauncherScript "${script_name}" "${nexe}"
  done

  VerifySharedLibraryOrder
}


#
# Run an executable (under sel_ldr or node.js).
# $1 - Executable (.nexe or .pexe) name
#
RunSelLdrCommand() {
  if [ "${SKIP_SEL_LDR_TESTS}" = "1" ]; then
    return
  fi

  if [ "${NACL_ARCH}" = "pnacl" -o  "${NACL_ARCH}" = "le32" ]; then
    # For PNaCl we translate to each arch where we have sel_ldr, then run it.
    local PEXE=$1
    local NEXE_32=$1_32.nexe
    local NEXE_64=$1_64.nexe
    local SCRIPT_32=$1_32.sh
    local SCRIPT_64=$1_64.sh
    shift
    TranslateAndWriteLauncherScript "${PEXE}" x86-32 "${NEXE_32}" "${SCRIPT_32}"
    echo "[sel_ldr x86-32] ${SCRIPT_32} $*"
    "./${SCRIPT_32}" "$@"
    TranslateAndWriteLauncherScript "${PEXE}" x86-64 "${NEXE_64}" "${SCRIPT_64}"
    echo "[sel_ldr x86-64] ${SCRIPT_64} $*"
    "./${SCRIPT_64}" "$@"
  else
    # Normal NaCl.
    local nexe=$1
    local basename=$(basename ${nexe})
    local dirname=$(dirname ${nexe})
    if [ -f "${dirname}/.libs/${basename}" ]; then
      nexe=${dirname}/.libs/${basename}
    fi

    local script=${nexe}.sh
    WriteLauncherScript "${script}" ${basename}
    shift
    echo "[sel_ldr] ${script} $*"
    "./${script}" "$@"
  fi
}


#
# Write a wrapper script that will run a nexe under sel_ldr
# $1 - Script name
# $2 - Nexe name
#
WriteLauncherScript() {
  local script=$1
  local binary=$2
  if [[ ${SKIP_SEL_LDR_TESTS} == 1 ]]; then
    return
  fi

  local abs_binary="$(dirname $script)/${binary}"
  if [[ ! -f ${abs_binary} ]]; then
    echo "binary not found: ${abs_binary}"
    exit 1
  fi

  if [[ ${TOOLCHAIN} == emscripten ]]; then
    local node=node
    if ! which node > /dev/null ; then
      node=nodejs
      if ! which nodejs > /dev/null ; then
        echo "Failed to find 'node' or 'nodejs' in PATH"
        exit 1
      fi
    fi
    cat > "$script" <<HERE
#!/bin/bash

SCRIPT_DIR=\$(dirname "\${BASH_SOURCE[0]}")
NODE=${node}

exec \${NODE} "\${SCRIPT_DIR}/${binary}" "\$@"
HERE
    chmod 750 "$script"
    echo "Wrote script $script -> $binary"
    return
  fi

  if [[ ${OS_NAME} == Cygwin ]]; then
    local LOGFILE=nul
  else
    local LOGFILE=/dev/null
  fi

  if [[ ${NACL_LIBC} == glibc ]]; then
    cat > "$script" <<HERE
#!/bin/bash
SCRIPT_DIR=\$(dirname "\${BASH_SOURCE[0]}")
if [ \$(uname -s) = CYGWIN* ]; then
  SCRIPT_DIR=\$(cygpath -m \${SCRIPT_DIR})
fi
NACL_SDK_ROOT=${NACL_SDK_ROOT}

NACL_SDK_LIB=${NACL_SDK_LIB}
LIB_PATH_DEFAULT=${NACL_SDK_LIBDIR}:${NACLPORTS_LIBDIR}
LIB_PATH_DEFAULT=\${LIB_PATH_DEFAULT}:\${NACL_SDK_LIB}:\${SCRIPT_DIR}
SEL_LDR_LIB_PATH=\${SEL_LDR_LIB_PATH}:\${LIB_PATH_DEFAULT}

exec "\${NACL_SDK_ROOT}/tools/sel_ldr.py" -p --library-path \
  "\${SEL_LDR_LIB_PATH}" -- "\${SCRIPT_DIR}/$binary" "\$@"
HERE
  else
    cat > "$script" <<HERE
#!/bin/bash
SCRIPT_DIR=\$(dirname "\${BASH_SOURCE[0]}")
if [ \$(uname -s) = CYGWIN* ]; then
  SCRIPT_DIR=\$(cygpath -m \${SCRIPT_DIR})
fi
NACL_SDK_ROOT=${NACL_SDK_ROOT}

exec "\${NACL_SDK_ROOT}/tools/sel_ldr.py" -p -- "\${SCRIPT_DIR}/$binary" "\$@"
HERE
  fi

  chmod 750 "$script"
  echo "Wrote script $script -> $binary"
}


#
# Finalize and translate a .pnexe file and create a launch script
# (PNaCl specific)
# $1 - pnexe file
# $2 - architecture
# $3 - nexe file
# $4 - script name
#
TranslateAndWriteLauncherScript() {
  local pexe=$1
  local arch=$2
  local nexe=$3
  local script=$4
  if [[ ! -f ${pexe} ]]; then
    echo "pexe not found: ${pexe}"
    exit 1
  fi
  if [[ ${pexe} -nt ${nexe} ]]; then
    if [[ ${NACL_ARCH} != le32 ]]; then
      echo "Finalizing -> ${pexe}"
      "${PNACLFINALIZE}" "${pexe}"
    else
      echo "Skipping finalizing: ${pexe} -> ${nexe}"
    fi
    echo "Translating -> ${nexe}"
    "${TRANSLATOR}" "${pexe}" -arch "${arch}" -o "${nexe}"
  else
    echo "Skipping finalization and translation: ${pexe} -> ${nexe}"
  fi
  WriteLauncherScript "${script}" $(basename "${nexe}")
}


#
# Finalize a pexe file in place
#
FinalizePexe() {
  local pexe=$1
  if [[ ! -f ${pexe} ]]; then
    echo "pexe not found: ${pexe}"
    exit 1
  fi
  Banner "Finalizing ${pexe}"
  "${PNACLFINALIZE}" "${pexe}"
}


#
# Translate a PNaCl executable (.pexe) into one or more
# native NaCl executables (.nexe).
# $1 - pexe file
#
TranslatePexe() {
  local pexe=$1
  local basename="${pexe%.*}"
  local arches="arm x86-32 x86-64"
  if [[ ${NACLPORTS_QUICKBUILD} == 1 ]]; then
    arches="x86-64"
  fi

  Banner "Translating ${pexe}"

  for a in ${arches} ; do
    echo "translating pexe -O0 [${a}]"
    nexe=${basename}.${a}.nexe
    if [ "${pexe}" -nt "${nexe}" ]; then
      "${TRANSLATOR}" -O0 -arch "${a}" "${pexe}" -o "${nexe}"
    fi
  done

  # Now the same spiel with -O2

  if [[ ${NACLPORTS_QUICKBUILD} != 1 ]]; then
    for a in ${arches} ; do
      echo "translating pexe -O2 [${a}]"
      nexe=${basename}.opt.${a}.nexe
      if [ "${pexe}" -nt "${nexe}" ]; then
        "${TRANSLATOR}" -O2 -arch "${a}" "${pexe}" -o "${nexe}"
      fi
    done
  fi

  local dirname=$(dirname "${pexe}")
  ls -l ${pexe} ${basename}*.nexe
}


#
# Create a zip file for uploading to the chrome web store.
# $1 - zipfile to create
# $2 - directory to zip
#
CreateWebStoreZip() {
  if [ "${NACLPORTS_QUICKBUILD}" = "1" ]; then
    echo "Skipping Web Store package create: $1"
    return
  fi
  Banner "Creating Web Store package: $1"
  Remove $1
  LogExecute zip -r $1 $2/
}


PackageStep() {
  local basename=$(basename "${PACKAGE_FILE}")
  Banner "Packaging ${basename}"
  if [ -d "${INSTALL_DIR}${PREFIX}" ]; then
    for item in "${INSTALL_DIR}"/*; do
      if [ "$item" != "${INSTALL_DIR}${PREFIX}" ]; then
        echo "INSTALL_DIR contains unexpected file or directory: $item"
        echo "INSTALL_DIR should contain only '${PREFIX}'"
        exit 1
      fi
    done
    mv "${INSTALL_DIR}${PREFIX}" "${INSTALL_DIR}/payload"
  fi
  local excludes="usr/doc share/man share/info info/
                  share/doc lib/charset.alias"
  for exclude in ${excludes}; do
    if [ -e "${INSTALL_DIR}/payload/${exclude}" ]; then
      echo "Pruning ${exclude}"
      rm -rf "${INSTALL_DIR}/payload/${exclude}"
    fi
  done
  LogExecute cp "${START_DIR}/pkg_info" "${INSTALL_DIR}"
  if [ "${NACL_DEBUG}" = "1" ]; then
    echo "BUILD_CONFIG=debug" >> "${INSTALL_DIR}/pkg_info"
  else
    echo "BUILD_CONFIG=release" >> "${INSTALL_DIR}/pkg_info"
  fi
  echo "BUILD_ARCH=${NACL_ARCH}" >> "${INSTALL_DIR}/pkg_info"
  echo "BUILD_TOOLCHAIN=${TOOLCHAIN}" >> "${INSTALL_DIR}/pkg_info"
  echo "BUILD_SDK_VERSION=${NACL_SDK_VERSION}" >> "${INSTALL_DIR}/pkg_info"
  echo "BUILD_NACLPORTS_REVISION=${FULL_REVISION}" >> "${INSTALL_DIR}/pkg_info"
  if [ "${OS_NAME}" = "Darwin" ]; then
    # OSX likes to create files starting with ._. We don't want to package
    # these.
    local args="--exclude ._*"
  else
    local args=""
  fi
  args+=" pkg_info"
  if [[ -d ${INSTALL_DIR}/payload ]]; then
    args+=" payload"
  fi
  # Create packge in temporary location and move into place once
  # done.  This prevents partially created packages from being
  # left lying around if this process is interrupted.
  LogExecute tar cjf "${PACKAGE_FILE}.tmp" -C "${INSTALL_DIR}" ${args}
  LogExecute mv -f "${PACKAGE_FILE}.tmp" "${PACKAGE_FILE}"
}


PackageInstall() {
  RunDownloadStep
  RunPatchStep
  RunConfigureStep
  RunBuildStep
  RunPostBuildStep
  RunTestStep
  RunInstallStep
  RunPublishStep
  RunPostInstallTestStep
  PackageStep
}


NaclportsMain() {
  local COMMAND=PackageInstall
  if [[ $# -gt 0 ]]; then
    COMMAND=Run$1
  fi
  if [ -d "${BUILD_DIR}" ]; then
    ChangeDir "${BUILD_DIR}"
  fi
  ${COMMAND}
}


RunStep() {
  local STEP_FUNCTION=$1
  local DIR=''
  shift
  if [ $# -gt 0 ]; then
    local TITLE=$1
    shift
    Banner "${TITLE} ${PACKAGE_NAME}"
  fi
  if [ $# -gt 0 ]; then
    DIR=$1
    shift
  fi
  if [ -n "${DIR}" ]; then
    if [ ! -d "${DIR}" ]; then
      MakeDir "${DIR}"
    fi
    ChangeDir "${DIR}"
  fi
  # Step functions are run in sub-shell so that they are independent
  # from each other.
  ( ${STEP_FUNCTION} )
}


# Function entry points that packages should override in order
# to customize the build process.
DownloadStep()        { return;                     }
PatchStep()           { DefaultPatchStep;           }
ConfigureStep()       { DefaultConfigureStep;       }
BuildStep()           { DefaultBuildStep;           }
PostBuildStep()       { DefaultPostBuildStep;       }
TestStep()            { DefaultTestStep;            }
InstallStep()         { DefaultInstallStep;         }
PublishStep()         { DefaultPublishStep;         }
PostInstallTestStep() { DefaultPostInstallTestStep; }

RunDownloadStep()   { RunStep DownloadStep; }
RunPatchStep()      { RunStep PatchStep; }


RunConfigureStep() {
  SetOptFlags
  RunStep ConfigureStep "Configuring" "${BUILD_DIR}"
}


RunBuildStep() {
  RunStep BuildStep "Building" "${BUILD_DIR}"
  FixupExecutablesList
}


RunPostBuildStep() {
  RunStep PostBuildStep "PostBuild" "${BUILD_DIR}"
}


RunTestStep() {
  if [[ ${SKIP_SEL_LDR_TESTS} == 1 ]]; then
    Banner "sel_ldr based tested disavled on this platform"
    return
  fi
  if [[ ${NACLPORTS_QUICKBUILD} == 1 ]]; then
    Banner "Tests disabled (\$NACLPORTS_QUICKBUILD is set)"
    return
  fi
  if [[ ${TESTS_DISABLED:-} == 1 && -n ${BUILDBOT_BUILDERNAME:-} ]]; then
    Banner "Tests for ${PACKAGE_NAME} are currently disabled on the bots"
    return
  fi
  RunStep TestStep "Testing" "${BUILD_DIR}"
}


RunPostInstallTestStep() {
  if [[ ${NACLPORTS_QUICKBUILD} == 1 ]]; then
    Banner "Post-install tests disabled (\$NACLPORTS_QUICKBUILD is set)"
    return
  fi
  RunStep PostInstallTestStep "Testing (post-install)"
}


RunInstallStep() {
  Remove "${INSTALL_DIR}"
  MakeDir "${INSTALL_DIR}"
  RunStep InstallStep "Installing" "${BUILD_DIR}"
}


RunPublishStep() {
  RunStep PublishStep "Publishing" "${BUILD_DIR}"
}


######################################################################
# Always run
# These functions are called when this script is imported to do
# any essential checking/setup operations.
######################################################################
PatchSpecsFile
InjectSystemHeaders
InstallConfigSite
GetRevision
MakeDirs
