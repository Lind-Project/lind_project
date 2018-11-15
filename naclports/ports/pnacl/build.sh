# Copyright (c) 2013 The Native Client Authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.

EnableGlibcCompat
EnableCliMain

PatchStep() {
  DefaultPatchStep
  MakeDir ${SRC_DIR}/toolchain_build/src
  Remove ${SRC_DIR}/toolchain_build/src/llvm
  LogExecute ln -fs ${SRC_DIR}/../../pnacl-llvm-src/llvm \
    ${SRC_DIR}/toolchain_build/src/llvm
  Remove ${SRC_DIR}/toolchain_build/src/binutils
  LogExecute ln -fs ${SRC_DIR}/../../pnacl-binutils-src/binutils \
    ${SRC_DIR}/toolchain_build/src/binutils
  Remove ${SRC_DIR}/toolchain_build/src/clang
  LogExecute ln -fs ${SRC_DIR}/../../pnacl-clang-src/clang \
    ${SRC_DIR}/toolchain_build/src/clang
  Remove ${SRC_DIR}/toolchain_build/src/llvm/tools/clang
  LogExecute ln -fs ${SRC_DIR}/../../pnacl-clang-src/clang \
    ${SRC_DIR}/toolchain_build/src/llvm/tools/clang
  Remove ${SRC_DIR}/toolchain_build/src/binutils-x86
  LogExecute ln -fs ${SRC_DIR}/../../pnacl-binutils-x86-src/binutils \
    ${SRC_DIR}/toolchain_build/src/binutils-x86
}

ConfigureStep() {
  return
}

OUT_DIR=${BUILD_DIR}/out
OUT_INSTALL=${BUILD_DIR}/install

BuildStep() {
  PNACL_DIR=${NACL_SDK_ROOT}/toolchain/linux_pnacl
  export PATH=${PNACL_DIR}/bin:${PATH}
  export LD_LIBRARY_PATH=${PNACL_DIR}/lib:${LD_LIBRARY_PATH:-}
  export BUILD_CC=clang
  export BUILD_CXX=clang++

  export STRIPPROG=echo

  export HOST_OS=NativeClient
  export KEEP_SYMBOLS=1

  GOLD_LDADD="--with-gold-ldadd="
  GOLD_LDADD+=" -Wl,--undefined=LLVMgold_onload"
  GOLD_LDADD+=" -L%(abs_llvm_le32_nacl)s/lib"
  # TODO(bradnelson): Apply llvm-config to pick this list.
  GOLD_LDADD+=" -Wl,--start-group"
  GOLD_LDADD+=" -lLLVMgold -lLLVMCodeGen -lLTO -lLLVMX86Disassembler"
  GOLD_LDADD+=" -lLLVMX86AsmParser -lLLVMX86CodeGen -lLLVMX86Desc"
  GOLD_LDADD+=" -lLLVMX86Info -lLLVMX86AsmPrinter -lLLVMX86Utils"
  GOLD_LDADD+=" -lLLVMARMDisassembler -lLLVMARMCodeGen"
  GOLD_LDADD+=" -lLLVMNaClTransforms"
  GOLD_LDADD+=" -lLLVMARMAsmParser -lLLVMARMDesc -lLLVMARMInfo"
  GOLD_LDADD+=" -lLLVMARMAsmPrinter -lLLVMMipsDisassembler -lLLVMMipsCodeGen"
  GOLD_LDADD+=" -lLLVMSelectionDAG -lLLVMAsmPrinter -lLLVMCodeGen"
  GOLD_LDADD+=" -lLLVMMipsAsmParser -lLLVMMipsDesc -lLLVMMipsInfo"
  GOLD_LDADD+=" -lLLVMMipsAsmPrinter -lLLVMMCDisassembler -lLLVMLTO"
  GOLD_LDADD+=" -lLLVMMCParser -lLLVMLinker -lLLVMipo -lLLVMObjCARCOpts"
  GOLD_LDADD+=" -lLLVMVectorize -lLLVMScalarOpts -lLLVMInstCombine"
  GOLD_LDADD+=" -lLLVMTransformUtils -lLLVMipa -lLLVMBitWriter"
  GOLD_LDADD+=" -lLLVMBitReader -lLLVMAnalysis -lLLVMTarget -lLLVMMC"
  GOLD_LDADD+=" -lLLVMObject -lLLVMCore -lLLVMSupport"
  GOLD_LDADD+=" -Wl,--end-group"

  EXTRA_CONFIGURE="--extra-configure-arg=--disable-compiler-version-checks"
  EXTRA_CONFIGURE+=" --extra-configure-arg=--enable-libcpp"
  # Without this configure will detect vfork as missing and define
  # vfork to fork which clobbers that define in "spawn.h".
  EXTRA_CONFIGURE+=" --extra-configure-arg=ac_cv_func_vfork_works=yes"
  EXTRA_CONFIGURE+=" --extra-configure-arg=ac_cv_func_getrusage=no"
  if [[ ${NACL_DEBUG} == 1 ]]; then
    EXTRA_CONFIGURE+=" --host-flavor=debug"
  fi

  # Some code in llvm uses intrisics not supported in the pnacl stable abi.
  if [[ ${TOOLCHAIN} == pnacl ]]; then
    EXTRA_CC_ARGS="-fgnu-inline-asm"
    if [[ ${NACL_ARCH} == le32 ]]; then
      GOLD_LDADD+=" -Wl,-plugin-opt=no-abi-verify"
    else
      EXTRA_CC_ARGS+=" --pnacl-disable-abi-check"
    fi
  fi
  if [[ ${TOOLCHAIN} != glibc ]]; then
    EXTRA_CC_ARGS+=" -I${NACLPORTS_INCLUDE}/glibc-compat"
  fi

  EXTRA_CC_ARGS+=" -include spawn.h"
  EXTRA_CC_ARGS+=" -I${NACL_SDK_ROOT}/include"
  EXTRA_CC_ARGS+=" -isystem${NACLPORTS_INCLUDE}"

  # export WEBPORTS_EXTRA_LIBS so that compiler_wapper.py can access it
  export WEBPORTS_EXTRA_LIBS="${NACLPORTS_LDFLAGS} ${NACLPORTS_LIBS}"
  echo "WEBPORTS_EXTRA_LIBS=${WEBPORTS_EXTRA_LIBS}"

  # Inject a shim that speed up pnacl invocations for configure.
  if [ "${NACL_ARCH}" = "pnacl" ]; then
    local PNACL_CONF_SHIM="${TOOLS_DIR}/pnacl-configure-shim.py"
    NACLCC="${PNACL_CONF_SHIM} ${NACLCC}"
    NACLCXX="${PNACL_CONF_SHIM} ${NACLCXX}"
  fi

  NACLCC="${START_DIR}/compiler_wrapper.py ${NACLCC}"
  NACLCXX="${START_DIR}/compiler_wrapper.py ${NACLCXX}"

  Remove ${OUT_INSTALL}
  MakeDir ${OUT_INSTALL}

  export CC=${NACLCC}
  export CXX=${NACLCXX}
  export AR=${NACLAR}
  export RANLIB=${NACLRANLIB}
  LogExecute ${SRC_DIR}/toolchain_build/toolchain_build_pnacl.py -v \
    --no-use-cached-results \
    --no-use-remote-cache \
    --no-annotator \
    --pnacl-in-pnacl \
    --output=${OUT_DIR} \
    --install=${OUT_INSTALL} \
    "--extra-cc-args=${EXTRA_CC_ARGS}" \
    ${EXTRA_CONFIGURE} \
    "--binutils-extra-configure=${GOLD_LDADD}"

  CreateHybridToolchain
}

CreateHybridToolchain() {
  Banner "Creating Hybrid Toolchain"

  # Build a full toolchain based on the one in NACL_SDK_ROOT, but overlayed
  # with the one we just compiled.
  Remove toolchain
  MakeDir toolchain

  host_toolchain=${NACL_SDK_ROOT}/toolchain/linux_pnacl
  LogExecute cp -r ${host_toolchain}/* toolchain

  # Drop pyc files.
  LogExecute find toolchain -name "*.pyc" -exec rm {} \;

  # Overlay compiled toolchain
  Remove ${OUT_INSTALL}/x86_64-nacl/lib/32
  Remove ${OUT_INSTALL}/x86_64-nacl/lib64
  LogExecute cp -r ${OUT_INSTALL}/* toolchain/

  # Rename the nacl executables.
  for f in $(cd ${host_toolchain} && find . -executable -type f); do
    if [[ "$(file ${host_toolchain}/${f} | grep ELF)" != "" \
          && ${f} != *pnacl-abicheck ]]; then
      # We are dealing with an executable
      local built_exe="${OUT_INSTALL}/${f}"
      local exe="toolchain/${f}"
      if [[ -f ${built_exe} ]]; then
        LogExecute mv ${exe} ${exe}${NACL_EXEEXT}
      elif [[ $f == *-clang* ]]; then
        Remove ${exe}
        LogExecute ln -sf clang${NACL_EXEEXT} ${exe}${NACL_EXEEXT}
      else
        echo "Warning: dropping ${f} without a nacl replacement."
        LogExecute rm -f ${exe}
      fi
    fi
  done

  # Now create launcher scripts for each executable
  for f in $(find toolchain -name "*${NACL_EXEEXT}"); do
    script=${f%.*}
    if [[ ${TOOLCHAIN} == pnacl ]]; then
      TranslateAndWriteLauncherScript "${f}" x86-64 "${script}.nexe" "${script}"
    else
      WriteLauncherScript "${script}" "$(basename ${f})"
    fi
  done

  # Drop parts we don't care about
  LogExecute rm -rf toolchain/translator
  LogExecute rm -rf toolchain/mipsel-nacl
  LogExecute rm -rf toolchain/*-nacl/usr
  LogExecute rm -f toolchain/bin/mipsel-*
  LogExecute rm -f toolchain/lib/*.so
}

InstallStep() {
  local INSTALL_DIR=${DESTDIR}/${PREFIX}/pnacl
  Remove ${INSTALL_DIR}/
  MakeDir ${INSTALL_DIR}/

  LogExecute cp -r toolchain/* ${INSTALL_DIR}
  for f in $(find ${INSTALL_DIR} -type l -name "*-clang*${NACL_EXEEXT}"); do
    # link to clang binary
    Remove $f ${f%.*}
    LogExecute ln -s clang ${f%.*}
  done
  for f in $(find ${INSTALL_DIR} -type f -name "*${NACL_EXEEXT}"); do
    LogExecute mv $f ${f%.*}
  done
}

TestStep() {
  # Verify that binaries at least load under sel_ldr
  LogExecute toolchain/bin/le32-nacl-clang --version
  LogExecute toolchain/bin/arm-nacl-readelf --version
  LogExecute toolchain/bin/x86_64-nacl-as --version
  LogExecute toolchain/bin/clang --version

  TestNaClClang
}

TestNaClClang() {
  # Try compiling and running a simple hello world program.  We have to
  # use explicit compile, assemble and link commands since sel_ldr doesn't
  # provide fork().

  # currently x86_64 only
  if [[ $NACL_ARCH != x86_64 ]]; then
    return
  fi

  compile_command="toolchain/bin/x86_64-nacl-clang -cc1 -triple x86_64--nacl
  -S -disable-free -main-file-name ${START_DIR}/hello.c -mrelocation-model
  static -mthread-model posix -mdisable-fp-elim -fmath-errno -no-integrated-as
  -mconstructor-aliases -munwind-tables -fuse-init-array -target-cpu x86-64
  -target-linker-version 2.24 -v -dwarf-column-info
  -resource-dir $PWD/toolchain/bin/../lib/clang/3.7.0
  -internal-isystem $PWD/toolchain/bin/../lib/clang/3.7.0/include
  -internal-isystem $PWD/toolchain/bin/../x86_64-nacl/usr/include
  -internal-isystem $PWD/toolchain/bin/../x86_64-nacl/include
  -fno-dwarf-directory-asm -ferror-limit 19 -fmessage-length 0 -mstackrealign
  -fobjc-runtime=gcc -fdiagnostics-show-option -o hello.s -x c
  ${START_DIR}/hello.c
  "
  LogExecute $compile_command

  LogExecute toolchain/bin/x86_64-nacl-as --64 hello.s -o hello.o
  link_command="toolchain/x86_64-nacl/bin/ld --build-id -m
  elf_x86_64_nacl -static -o hello.nexe
  $PWD/toolchain/bin/../x86_64-nacl/lib/crt1.o
  $PWD/toolchain/bin/../x86_64-nacl/lib/crti.o
  $PWD/toolchain/bin/../lib/clang/3.7.0/lib/x86_64-nacl/crtbeginT.o
  -L$PWD/toolchain/bin/../x86_64-nacl/lib
  -L$PWD/toolchain/bin/../x86_64-nacl/usr/lib
  -L$PWD/toolchain/bin/../lib/clang/3.7.0/lib/x86_64-nacl
  ./hello.o --start-group -lc -lgcc --as-needed -lgcc_eh --no-as-needed
  --end-group
  $PWD/toolchain/bin/../lib/clang/3.7.0/lib/x86_64-nacl/crtend.o
  $PWD/toolchain/bin/../x86_64-nacl/lib/crtn.o
  "
  LogExecute $link_command
  RunSelLdrCommand hello.nexe
}
