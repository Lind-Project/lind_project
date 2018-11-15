# Copyright 2014 The Native Client Authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.

from mock import patch, Mock
import os
import tempfile
import unittest

import common
from webports.configuration import Configuration
from webports import util
from webports import error


class TestUtil(unittest.TestCase):

  def setUp(self):
    common.add_patch(self, patch('webports.util.get_sdk_root',
                                 Mock(return_value='/sdk/root')))
    common.add_patch(self, patch('webports.util.get_emscripten_root',
                                 Mock(return_value='/emscripten/root')))
    common.add_patch(self, patch('webports.util.get_platform',
                                 Mock(return_value='linux')))

  @patch('webports.util.hash_file', Mock(return_value='sha1'))
  def test_verify_hash(self):
    util.verify_hash('foo', 'sha1')
    with self.assertRaises(util.HashVerificationError):
      util.verify_hash('foo', 'sha1x')

  @patch.dict('os.environ', {'PATH': '/x/y/z'})
  def test_find_in_path(self):
    with self.assertRaisesRegexp(error.Error, "command not found: foo"):
      util.find_in_path('foo')

    with patch('os.path.exists') as mock_exists:
      with patch('os.path.isfile') as mock_isfile:
        executable = os.path.join('/x/y/z', 'somefile')
        self.assertEqual(util.find_in_path('somefile'), executable)
        mock_exists.assert_called_once_with(executable)
        mock_isfile.assert_called_once_with(executable)

  def test_check_stamp_missing(self):
    with patch('os.path.exists', Mock(return_value=False)):
      self.assertFalse(util.check_stamp('foo.stamp', ''))

  def test_check_stamp_contents(self):
    temp_fd, temp_name = tempfile.mkstemp('webports_test')
    self.addCleanup(os.remove, temp_name)

    stamp_contents = 'stamp file contents'
    with os.fdopen(temp_fd, 'w') as f:
      f.write(stamp_contents)

    self.assertTrue(util.check_stamp(temp_name, stamp_contents))
    self.assertFalse(util.check_stamp(temp_name, stamp_contents + 'x'))

  def test_get_install_root(self):
    expected = '/sdk/root/toolchain/linux_pnacl/le32-nacl/usr'
    self.assertEqual(util.get_install_root(Configuration()), expected)

    expected = '/sdk/root/toolchain/linux_x86_glibc/x86_64-nacl/usr'
    self.assertEqual(util.get_install_root(Configuration(toolchain='glibc')),
                     expected)

    expected = '/sdk/root/toolchain/linux_pnacl/le32-nacl/usr'
    self.assertEqual(util.get_install_root(Configuration('pnacl')), expected)

    expected = '/emscripten/root/system/local'
    self.assertEqual(util.get_install_root(Configuration('emscripten')),
                     expected)

    expected = '/sdk/root/toolchain/linux_pnacl/x86_64-nacl/usr'
    self.assertEqual(
        util.get_install_root(Configuration(toolchain='clang-newlib')),
        expected)

  def test_hash_file(self):
    temp_name = tempfile.mkstemp('webports_test')[1]
    self.addCleanup(os.remove, temp_name)

    with self.assertRaises(IOError):
      util.hash_file('/does/not/exist')

    sha1_empty_string = 'da39a3ee5e6b4b0d3255bfef95601890afd80709'
    self.assertEqual(util.hash_file(temp_name), sha1_empty_string)

  @patch('webports.paths.NACLPORTS_ROOT', '/foo')
  def test_rel_path(self):
    self.assertEqual('bar', util.rel_path('/foo/bar'))
    self.assertEqual('../baz/bar', util.rel_path('/baz/bar'))


class TestCheckSDKRoot(TestUtil):

  def test_missing_sdk_root(self):
    with self.assertRaisesRegexp(error.Error, 'NACL_SDK_ROOT does not exist'):
      util.check_sdk_root()

  @patch('os.path.exists', Mock())
  @patch('os.path.isdir', Mock())
  @patch('webports.util.get_sdk_version', Mock(return_value=10))
  def test_sdk_version_check(self):
    with patch('webports.util.MIN_SDK_VERSION', 9):
      util.check_sdk_root()

    with patch('webports.util.MIN_SDK_VERSION', 10):
      util.check_sdk_root()

    with patch('webports.util.MIN_SDK_VERSION', 11):
      with self.assertRaisesRegexp(error.Error, 'requires at least version 11'):
        util.check_sdk_root()
