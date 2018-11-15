// Copyright 2015 The Native Client Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "gtest/gtest.h"

// These unittests should be run in the sel_ldr.  In this mode
// nacl_io should not be initialized since we want direct access
// to the real filesystem.  Verify this by checking the value
// or getcwd()
TEST(NaClSpawn, test_nacl_io_not_initialized) {
  const char* cwd = getcwd(NULL, 0);
  printf("cwd: %s\n", cwd);
  ASSERT_NE((char*)NULL, strstr(cwd, "out/build/nacl-spawn"));
}

extern bool _cli_main_init;

TEST(NaClSpawn, test_cli_main_called) {
  ASSERT_EQ(true, _cli_main_init);
}

int main(int argc, char** argv) {
  setenv("TERM", "xterm-256color", 0);
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
