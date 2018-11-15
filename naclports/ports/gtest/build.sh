# Copyright (c) 2011 The Native Client Authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.

CTEST_EXECUTABLES="
gtest_break_on_failure_unittest_
gtest_catch_exceptions_ex_test_
gtest_catch_exceptions_no_ex_test_
gtest_color_test_
gtest_env_var_test_
gtest_filter_unittest_
gtest_help_test_
gtest_list_tests_unittest_
gtest_output_test_
gtest_shuffle_test_
gtest_throw_on_failure_test_
gtest_uninitialized_test_
gtest_xml_outfile1_test_
gtest_xml_outfile2_test_
gtest_xml_output_unittest_
gtest_main_unittest
gtest_unittest
gtest_no_test_unittest
gtest_no_rtti_unittest
gtest_pred_impl_unittest
gtest-death-test_ex_catch_test
gtest-death-test_ex_nocatch_test
gtest-death-test_test
gtest_environment_test
gtest-filepath_test
gtest-linked_ptr_test
gtest-listener_test
gtest-message_test
gtest-options_test
gtest-param-test_test
gtest-port_test
gtest_premature_exit_test
gtest-printers_test
gtest_prod_test
gtest_repeat_test
gtest_sole_header_test
gtest_stress_test
gtest-test-part_test
gtest_throw_on_failure_ex_test
gtest-tuple_test
gtest-typed-test_test
gtest-unittest-api_test
gtest_use_own_tuple_test
"

if [[ -e "$NACL_SDK_ROOT/include/gtest" ]]; then
  echo "The current NaCl SDK includes its own version of gtest"
  if [[ -z ${BUILDBOT_BUILDERNAME:-} ]]; then
    # normal use case: prompt the user to move the pre-installed gtest headers
    echo "Please remove or rename '$NACL_SDK_ROOT/include/gtest' to continue"
    exit 1
  else
    # on the buildbot simply move the headers
    mv $NACL_SDK_ROOT/include/gtest $NACL_SDK_ROOT/include/gtest-old
  fi
fi

ConfigureStep() {
  if [[ -z ${GTEST_TEST:-} ]]; then
    Banner "Skipping configure step (set GTEST_TEST to enable)"
    return
  fi
  Remove ${SRC_DIR}/configure
  EXTRA_CMAKE_ARGS="-Dgtest_build_tests=1"
  for exe in $CTEST_EXECUTABLES; do
    Remove $exe
  done
  DefaultConfigureStep
}

BuildStep() {
  return
}

InstallStep() {
  local srcdir=${DESTDIR}/${PREFIX}/src
  MakeDir ${srcdir}/gtest/include

  LogExecute cp -r ${SRC_DIR}/include/gtest ${srcdir}/gtest/include/gtest
  LogExecute cp -r ${SRC_DIR}/src ${srcdir}/gtest
}

TestStep() {
  if [[ -z ${GTEST_TEST:-} ]]; then
    Banner "Skipping tests (set GTEST_TEST to enable)"
    return
  fi
  DefaultBuildStep
  if [ "${NACL_ARCH}" = "pnacl" ]; then
    return
  fi
  for exe in $CTEST_EXECUTABLES; do
    mv $exe $exe$NACL_EXEEXT
    WriteLauncherScript $exe $exe$NACL_EXEEXT
  done
  LogExecute make TZ=gmt test
}
