# Copyright 2014 The Native Client Authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.

import mock
from mock import Mock, patch
import StringIO
import unittest

import webports
import patch_configure
import scan_packages
import update_mirror
from find_effected_packages import find_effected_packages


def mock_file_object(contents):
  file_mock = Mock(name="file_mock", spec=file)
  file_mock.read.return_value = contents
  file_mock.__enter__ = lambda s: s
  file_mock.__exit__ = Mock(return_value=False)
  return file_mock


class TestPatchConfigure(unittest.TestCase):

  @patch('sys.stderr', new_callable=StringIO.StringIO)
  def test_missing_file(self, stderr):
    rtn = patch_configure.main(['non-existent/configure-script'])
    self.assertEqual(rtn, 1)
    expected = '^configure script not found: non-existent/configure-script$'
    self.assertRegexpMatches(stderr.getvalue(), expected)


class TestScanPackages(unittest.TestCase):

  def test_check_hash(self):  # pylint: disable=no-self-use
    file_mock = mock_file_object('1234\n')
    md5 = Mock()
    md5.hexdigest.return_value('4321')
    with patch('__builtin__.open', Mock(return_value=file_mock), create=True):
      scan_packages.check_hash('foo', '1234')

  @patch('webports.package_index.PREBUILT_ROOT', 'dummydir')
  @patch('scan_packages.log', Mock())
  @patch('scan_packages.check_hash')
  @patch('os.path.exists', Mock(return_value=True))
  def test_download_files(self, check_hash_mock):  # pylint: disable=no-self-use
    check_hash_mock.return_value = True
    file_info = scan_packages.FileInfo(name='foo', size=10, gsurl='gs://test',
                                       url='http://host/base', md5='hashval')
    scan_packages.download_files([file_info])
    check_hash_mock.assert_called_once_with('dummydir/base', 'hashval')


class TestUpdateMirror(unittest.TestCase):

  @patch('webports.util.find_in_path', Mock())
  def test_check_mirror_check_only(self):
    pkg = webports.source_package.create_package('zlib')
    pkg.get_archive_filename = Mock(return_value='file.tar.gz')
    options = Mock()
    options.check = True
    update_mirror.check_mirror(options, pkg, ['file.tar.gz'])

    with self.assertRaises(SystemExit):
      update_mirror.check_mirror(options, pkg, [])

  @patch('webports.util.find_in_path', Mock())
  @patch('update_mirror.gs_upload')
  def test_check_mirror_with_download(self, upload_mock):
    mock_download = Mock()
    pkg = webports.source_package.create_package('zlib')
    pkg.download = mock_download

    pkg.get_archive_filename = Mock(return_value='file.tar.gz')
    options = Mock()
    options.check = False
    update_mirror.check_mirror(options, pkg, ['file.tar.gz'])
    update_mirror.check_mirror(options, pkg, [])

    upload_mock.assert_called_once_with(
        options, pkg.download_location(),
        update_mirror.MIRROR_GS + '/file.tar.gz')

  @patch('update_mirror.check_mirror')
  def test_check_packages(self, check_mirror):
    mirror_listing = ['foo']
    mock_options = Mock()
    update_mirror.check_packages(mock_options, ['a', 'b', 'c'], mirror_listing)
    check_mirror.assert_calls([mock.call(mock_options, 'a', mirror_listing),
                               mock.call(mock_options, 'b', mirror_listing),
                               mock.call(mock_options, 'c', mirror_listing)])

  @patch('webports.source_package.source_package_iterator')
  @patch('webports.util.find_in_path', Mock())
  @patch('update_mirror.get_mirror_listing', Mock(return_value=['foo']))
  @patch('update_mirror.check_packages')
  def test_main(self, check_packages, source_package_iter):
    mock_iter = Mock()
    source_package_iter.return_value = mock_iter

    update_mirror.main([])
    check_packages.assert_called_once_with(mock.ANY, mock_iter, ['foo'])


class TestFindEffectedPackages(unittest.TestCase):

   def test_non_port_files(self):
     self.assertEqual(find_effected_packages(['foo/bar'], False, None), ['all'])

   def test_deps(self):
     self.assertEqual(
         find_effected_packages(['ports/hello', 'ports/ruby'], False, None),
         ['hello', 'ruby', 'ruby-ppapi'])

     # The common dependencies of vim and nano should only appear once in this
     # list.
     self.assertEqual(
         find_effected_packages(['ports/hello', 'ports/ruby'], True, None),
         ['hello', 'corelibs', 'gtest', 'glibc-compat', 'ncurses', 'readline',
          'zlib', 'ruby', 'libtar', 'nacl-spawn', 'ruby-ppapi'])

   def test_filter(self):
     effected = find_effected_packages(['ports/corelibs'], True,
         ['corelibs', 'glibc-compat'])
     self.assertEqual(effected, ['corelibs', 'glibc-compat'])
