# Copyright 2014 The Native Client Authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.

from mock import Mock, patch
import unittest


def mock_file_object(contents=''):
  file_mock = Mock(name="file_mock", spec=file)
  file_mock.read.return_value = contents
  file_mock.__enter__ = lambda s: s
  file_mock.__exit__ = Mock(return_value=False)
  return file_mock


def add_patch(testcase, patcher):
  patcher.start()
  testcase.addCleanup(patcher.stop)


class NaclportsTest(unittest.TestCase):
  """Class that sets up core mocks common to all test cases."""

  add_patch = add_patch

  def setUp(self):
    add_patch(self, patch.dict('os.environ', {'NACL_SDK_ROOT': '/sdk/root'}))
    add_patch(self, patch('webports.util.get_platform',
                          Mock(return_value='linux')))
    add_patch(self, patch('webports.util.get_install_root',
                          Mock(return_value='/package/install/path')))
    add_patch(self, patch('webports.util.get_sdk_root',
                          Mock(return_value='/sdk/root')))

    mock_lock = Mock()
    mock_lock.__enter__ = lambda s: s
    mock_lock.__exit__ = Mock(return_value=False)
    add_patch(self, patch('webports.util.InstallLock',
                          Mock(return_value=mock_lock)))

    mock_lock = Mock()
    mock_lock.__enter__ = lambda s: s
    mock_lock.__exit__ = Mock(return_value=False)
    add_patch(self, patch('webports.util.BuildLock',
                          Mock(return_value=mock_lock)))
