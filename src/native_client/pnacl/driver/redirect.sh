#!/bin/sh
# Copyright (c) 2012 The Native Client Authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.

# Keep this script compatible with different shells.
# It has been tested to work with: bash, zsh, ksh93, and dash.

DRIVER_BIN="`dirname "$0"`"
TOOLNAME="`basename "$0"`"
PYDIR="${DRIVER_BIN}/pydir"

# Expect to find python2 in the PATH. It can be overridden with PNACLPYTHON.
PNACLPYTHON="${PNACLPYTHON:-python2}"
${PNACLPYTHON} "${PYDIR}/loader.py" "${TOOLNAME}" "$@"
