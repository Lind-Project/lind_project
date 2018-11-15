# Copyright 2016 The Native Client Authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.

if [[ $TOOLCHAIN == emscripten ]]; then
  EXTRA_CMAKE_ARGS+=" -DBUILD_gflags_LIB=OFF"
fi
