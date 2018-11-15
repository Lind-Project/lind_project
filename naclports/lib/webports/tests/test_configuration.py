# Copyright 2014 The Native Client Authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.

from mock import patch, Mock

import common
from webports import error
from webports.configuration import Configuration


class TestConfiguration(common.NaclportsTest):

  def test_defaults(self):
    config = Configuration()
    self.assertEqual(config.toolchain, 'pnacl')
    self.assertEqual(config.arch, 'pnacl')
    self.assertEqual(config.debug, False)
    self.assertEqual(config.config_name, 'release')
    self.assertEqual(config.libc, 'newlib')

  def test_default_arch(self):
    # We default to x86_64 except in the special case where the build
    # machine is i686 hardware, in which case we default to i686.
    with patch('platform.machine', Mock(return_value='i686')):
      self.assertEqual(Configuration().arch, 'pnacl')
    with patch('platform.machine', Mock(return_value='dummy')):
      self.assertEqual(Configuration().arch, 'pnacl')
    with patch('platform.machine', Mock(return_value='i686')):
      self.assertEqual(Configuration(toolchain='clang-newlib').arch, 'i686')
    with patch('platform.machine', Mock(return_value='dummy')):
      self.assertEqual(Configuration(toolchain='clang-newlib').arch, 'x86_64')

  def test_environment_variables(self):
    with patch.dict('os.environ', {'NACL_ARCH': 'arm'}):
      self.assertEqual(Configuration().arch, 'arm')

    with patch.dict('os.environ', {'NACL_DEBUG': '1'}):
      self.assertEqual(Configuration().debug, True)

  def test_default_toolchain(self):
    self.assertEqual(Configuration(arch='pnacl').toolchain, 'pnacl')
    self.assertEqual(Configuration(arch='arm').libc, 'newlib')

  def test_default_libc(self):
    self.assertEqual(Configuration(toolchain='pnacl').libc, 'newlib')
    self.assertEqual(Configuration(toolchain='clang-newlib').libc, 'newlib')
    self.assertEqual(Configuration(toolchain='glibc').libc, 'glibc')

  def test_config_string_form(self):
    config = Configuration('arm', 'glibc', True)
    self.assertEqual(str(config), 'arm/glibc/debug')
    self.assertRegexpMatches(repr(config), '<Configuration .*>')

  def test_config_equality(self):
    config1 = Configuration('arm', 'glibc', True)
    config2 = Configuration('arm', 'glibc', True)
    config3 = Configuration('arm', 'glibc', False)
    self.assertEqual(config1, config2)
    self.assertNotEqual(config1, config3)

  def test_invalid_arch(self):
    expected_error = 'Invalid arch: not_arch'
    with self.assertRaisesRegexp(error.Error, expected_error):
      Configuration('not_arch')
