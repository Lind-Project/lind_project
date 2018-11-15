#!/usr/bin/env python
# Copyright (c) 2013 The Native Client Authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.
"""Tool which checks the sha1 sums of all packages.
"""

from __future__ import print_function

import argparse
import os
import sys

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
sys.path.append(os.path.join(os.path.dirname(SCRIPT_DIR), 'lib'))

import webports
import webports.source_package


def main(args):
  parser = argparse.ArgumentParser(description=__doc__)
  parser.add_argument('-v', '--verbose', action='store_true',
                      help='Output extra information.')
  options = parser.parse_args(args)
  if options.verbose:
    webports.set_verbose(True)
  count = 0

  for package in webports.source_package.source_package_iterator():
    package.download()
    count += 1

  webports.log("Verfied checksums for %d packages" % count)
  return 0


if __name__ == '__main__':
  sys.exit(main(sys.argv[1:]))
