#!/usr/bin/env python
# Copyright (c) 2016 The Native Client Authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.

"""Compiler wrapper for injecting extra libs at the end of the link
line.

This is used rather than just setting LDFLAGS/LIBS becuase setting
LIBS/LDFLAGS will effect both host and target builds.
"""

import os
import subprocess
import sys

cmd = sys.argv[1:]

is_configuring = 'conftest.c' in cmd or 'conftest.pexe' in cmd
is_linking = '-c' not in cmd and '-E' not in cmd
is_shared = '-shared' in cmd

# Add extra libs when linking executables
if is_linking and not is_shared:
  cmd += os.environ['WEBPORTS_EXTRA_LIBS'].split()

if is_configuring:
  cmd.remove('-include')
  cmd.remove('spawn.h')

sys.exit(subprocess.call(cmd))
