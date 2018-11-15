# Copyright 2015 The Native Client Authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.

export fu_cv_sys_mounted_fread=yes
NACLPORTS_CPPFLAGS+=" -Dpipe=nacl_spawn_pipe"
EnableCliMain

BuildStep() {
  export AR=${NACLAR}
  export RANLIB=${NACLRANLIB}
  DefaultBuildStep
}
