# Copyright 2015 The Native Client Authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.

import unittest

from webports import error
from webports import package

test_info = '''\
NAME=foo
VERSION=0.1
'''


class test_package(unittest.TestCase):

  def test_valid_libc_disabled(self):  # pylint: disable=no-self-use
    pkg = package.Package()
    pkg.parse_info(test_info + 'DISABLED_LIBC=(newlib glibc)')

  def test_invalid_libc_disabled(self):
    pkg = package.Package()
    # clang-newlib is a toolchain, not a libc
    with self.assertRaisesRegexp(error.Error, 'invalid libc: clang-newlib'):
      pkg.parse_info(test_info + 'DISABLED_LIBC=(clang-newlib)')

  def test_valid_toolchain_disabled(self):  # pylint: disable=no-self-use
    pkg = package.Package()
    pkg.parse_info(test_info + 'DISABLED_TOOLCHAIN=(pnacl glibc clang-newlib)')

  def test_invalid_toolchain_disabled(self):
    pkg = package.Package()
    with self.assertRaisesRegexp(error.Error, 'invalid toolchain: foo'):
      pkg.parse_info(test_info + 'DISABLED_TOOLCHAIN=(foo)')

  def test_valid_arch_disabled(self):  # pylint: disable=no-self-use
    pkg = package.Package()
    pkg.parse_info(test_info + 'DISABLED_ARCH=(arm i686 x86_64)')

  def test_invalid_arch_disabled(self):
    pkg = package.Package()
    with self.assertRaisesRegexp(error.Error, 'invalid architecture: foo'):
      pkg.parse_info(test_info + 'DISABLED_ARCH=(foo)')
