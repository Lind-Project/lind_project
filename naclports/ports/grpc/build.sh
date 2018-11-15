# Copyright 2016 The Native Client Authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.

NACLPORTS_CPPFLAGS+=" -D_POSIX_TIMERS"
EnableGlibcCompat

ConfigureStep() {
  LogExecute cp -rfl ${SRC_DIR}/* .
}

SetupEnv() {
  SetupCrossEnvironment
  export DEFAULT_CC=${CC}
  export DEFAULT_CXX=${CXX}
  export SYSTEM=NaCl
  export PATH=${BUILD_DIR}/../../protobuf/build_host/src:$PATH
  export LDLIBS=${LIBS}
  unset LIBS
}

BuildStep() {
  SetupEnv
  DefaultBuildStep
}

TestStep() {
  SetupEnv
  MAKE_ARGS="-j${OS_JOBS}"
  if [[ ${VERBOSE:-} == 1 ]]; then
    MAKE_ARGS+=" VERBOSE=1 V=1"
  fi
  LogExecute make ${MAKE_ARGS} buildtests_c
  # C++ tests not building yet
  #LogExecute make buildtests_cxx -j${OS_JOBS}

  # A fairly random selections of the C tests that currently pass.
  # Most of the failing tests are due to missing pipe() and socket() functions
  # in sel_ldr.
  exes="
bins/opt/uri_parser_test
bins/opt/alloc_test
bins/opt/alpn_test
bins/opt/bin_encoder_test

bins/opt/gpr_avl_test
bins/opt/gpr_cmdline_test
bins/opt/gpr_cpu_test
bins/opt/gpr_env_test
bins/opt/gpr_file_test
bins/opt/gpr_histogram_test
bins/opt/gpr_host_port_test
bins/opt/gpr_log_test
bins/opt/gpr_slice_buffer_test
bins/opt/gpr_slice_test
bins/opt/gpr_string_test
bins/opt/gpr_sync_test
bins/opt/gpr_time_test
bins/opt/gpr_tls_test
bins/opt/gpr_useful_test
"
  if [[ ${NACL_ARCH} != arm ]]; then
    exes+="
bins/opt/gpr_stack_lockfree_test
bins/opt/gpr_thd_test
"
  fi

  for exe in ${exes}; do
    RunSelLdrCommand ${exe}
  done
}

InstallStep() {
  SetupEnv
  LogExecute make install prefix=${DESTDIR}/${PREFIX}
}
