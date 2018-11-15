# Copyright 2014 The Native Client Authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.

from mock import patch, Mock
import mock
import tempfile
import textwrap
import shutil
import os

import common
from webports import source_package
from webports import error
from webports import paths
from webports.configuration import Configuration


class TestSourcePackage(common.NaclportsTest):

  def setUp(self):
    super(TestSourcePackage, self).setUp()
    self.tempdir = tempfile.mkdtemp(prefix='webports_test_')
    self.addCleanup(shutil.rmtree, self.tempdir)
    self.temp_ports = os.path.join(self.tempdir, 'ports')

    self.add_patch(patch('webports.paths.NACLPORTS_ROOT', self.tempdir))
    self.add_patch(patch('webports.paths.BUILD_ROOT',
                         os.path.join(self.tempdir, 'build_root')))
    self.add_patch(patch('webports.paths.CACHE_ROOT',
                         os.path.join(self.tempdir, 'cache')))
    self.add_patch(patch('webports.paths.OUT_DIR',
                         os.path.join(self.tempdir, 'out_dir')))
    self.add_patch(patch('webports.paths.STAMP_DIR',
                         os.path.join(self.tempdir, 'stamp_dir')))

  def create_mock_package(self, name, extra_info=''):
    """Creates a source package directory in a temporary directory.

    Args:
      name: The name of the temporary package.
      extra_info: extra information to append to the pkg_info file.

    Returns:
      The new package source directory
    """
    pkg_root = os.path.join(self.temp_ports, name)
    os.makedirs(pkg_root)
    with open(os.path.join(pkg_root, 'pkg_info'), 'w') as info:
      info.write("NAME=%s\nVERSION=1.0\n%s" % (name, extra_info))
    return pkg_root

  def test_stamp_contents_match(self):
    stamp_file = os.path.join(self.tempdir, 'test_stamp')
    # stamp does not exist
    self.assertFalse(source_package.stamp_contents_match(stamp_file, ''))

    open(stamp_file, 'w').close()
    self.assertTrue(source_package.stamp_contents_match(stamp_file, ''))
    self.assertFalse(source_package.stamp_contents_match(stamp_file, 'foo'))

  def test_invalid_source_dir(self):
    """test that invalid source directory generates an error."""
    path = '/bad/path'
    expected_error = 'Invalid package folder: ' + path
    with self.assertRaisesRegexp(error.Error, expected_error):
      source_package.SourcePackage(path)

  def test_valid_source_dir(self):
    """test that valid source directory is loaded correctly."""
    root = self.create_mock_package('foo')
    pkg = source_package.SourcePackage(root)
    self.assertEqual(pkg.NAME, 'foo')
    self.assertEqual(pkg.root, root)

  def test_is_built_malformed_binary(self):
    """test that is_built() can handle malformed package files."""
    root = self.create_mock_package('foo')
    pkg = source_package.SourcePackage(root)
    invalid_binary = os.path.join(self.tempdir, 'package.tar.bz2')
    with open(invalid_binary, 'w') as f:
      f.write('this is not valid package file\n')
    pkg.package_file = Mock(return_value=invalid_binary)
    self.assertFalse(pkg.is_built())

  @patch('webports.source_package.SourcePackage.run_build_sh',
         Mock(return_value=True))
  @patch('webports.source_package.log', Mock())
  def test_build_package(self):
    root = self.create_mock_package('foo')
    pkg = source_package.SourcePackage(root)
    pkg.build(True)

  def test_source_package_iterator(self):
    self.create_mock_package('foo')
    pkgs = [p for p in source_package.source_package_iterator()]
    self.assertEqual(len(pkgs), 1)
    self.assertEqual(pkgs[0].NAME, 'foo')

  def test_get_installed_package(self):
    root = self.create_mock_package('foo')
    pkg = source_package.SourcePackage(root)
    with self.assertRaisesRegexp(error.Error, 'package not installed: foo'):
      pkg.get_installed_package()

  def test_get_build_location(self):
    root = self.create_mock_package('foo')
    pkg = source_package.SourcePackage(root)
    location = pkg.get_build_location()
    self.assertTrue(location.startswith(paths.BUILD_ROOT))
    self.assertEqual(os.path.basename(location),
                     '%s-%s' % (pkg.NAME, pkg.VERSION))

  @patch('webports.util.log', Mock())
  def test_extract(self):
    root = self.create_mock_package('foo', 'URL=someurl.tar.gz\nSHA1=123')
    pkg = source_package.SourcePackage(root)

    def fake_extract(archive, dest):
      os.mkdir(os.path.join(dest, '%s-%s' % (pkg.NAME, pkg.VERSION)))

    with patch('webports.source_package.extract_archive', fake_extract):
      pkg.extract()

  def test_create_package_invalid(self):
    with self.assertRaisesRegexp(error.Error, 'Package not found: foo'):
      source_package.create_package('foo')

  def test_format_time_delta(self):
    expectations = (
       (1, '1s'),
       (60, '1m'),
       (70, '1m10s'),
    )

    for secs, expected_result in expectations:
      self.assertEqual(expected_result, source_package.format_time_delta(secs))

  def test_conflicts(self):
    root = self.create_mock_package('foo', 'CONFLICTS=(bar)')
    pkg = source_package.SourcePackage(root)

    # with no other packages installed
    with patch('webports.util.is_installed', Mock(return_value=False)):
      pkg.check_installable()

    # with all possible packages installed
    with patch('webports.util.is_installed') as is_installed:
      is_installed.return_value = True
      with self.assertRaises(source_package.PkgConflictError):
        pkg.check_installable()
      is_installed.assert_called_once_with('bar', pkg.config)

  def test_disabled(self):
    root = self.create_mock_package('foo', 'DISABLED=1')
    pkg = source_package.SourcePackage(root)
    with self.assertRaisesRegexp(error.DisabledError, 'package is disabled'):
      pkg.check_installable()

  def test_disabled_arch(self):
    self.create_mock_package('bar', 'DISABLED_ARCH=(x86_64)')

    pkg = source_package.create_package(
        'bar', config=Configuration(toolchain='clang-newlib'))
    with self.assertRaisesRegexp(error.DisabledError,
                                 'disabled for architecture: x86_64'):
      pkg.check_installable()

  def test_single_arch(self):
    self.create_mock_package('bar', 'ARCH=(arm)')

    pkg = source_package.create_package('bar')
    with self.assertRaisesRegexp(error.DisabledError,
                                 'disabled for architecture: pnacl$'):
      pkg.check_installable()

  def test_disabled_libc(self):
    self.create_mock_package('bar', 'DISABLED_LIBC=(newlib)')

    pkg = source_package.create_package('bar')
    with self.assertRaisesRegexp(error.DisabledError,
                                 'cannot be built with newlib$'):
      pkg.check_installable()

  def test_disabled_toolchain(self):
    self.create_mock_package('bar', 'DISABLED_TOOLCHAIN=(pnacl)')

    pkg = source_package.create_package('bar')
    with self.assertRaisesRegexp(error.DisabledError,
                                 'cannot be built with pnacl$'):
      pkg.check_installable()

  def test_disabled_toolchain_arch(self):
    self.create_mock_package('bar', 'DISABLED_TOOLCHAIN=(glibc/x86_64)')

    pkg = source_package.create_package('bar',
                                        config=Configuration(toolchain='glibc'))
    with self.assertRaisesRegexp(error.DisabledError,
                                 'cannot be built with glibc for x86_64$'):
      pkg.check_installable()

    self.create_mock_package('bar2', 'DISABLED_TOOLCHAIN=(pnacl/arm)')

    pkg = source_package.create_package('bar2')
    pkg.check_installable()

  def test_check_installable_depends(self):
    self.create_mock_package('foo', 'DEPENDS=(bar)')
    self.create_mock_package('bar', 'DISABLED=1')

    pkg = source_package.create_package('foo')
    with self.assertRaisesRegexp(error.DisabledError,
                                 'bar: package is disabled$'):
      pkg.check_installable()

  def test_check_buildable(self):
    self.create_mock_package('foo', 'BUILD_OS=solaris')

    pkg = source_package.create_package('foo')
    with self.assertRaisesRegexp(error.DisabledError,
                                 'can only be built on solaris$'):
      pkg.check_buildable()

  @patch('webports.util.get_sdk_version', Mock(return_value=123))
  def test_min_sdk_version(self):
    self.create_mock_package('foo', 'MIN_SDK_VERSION=123')
    pkg = source_package.create_package('foo')
    pkg.check_buildable()

    self.create_mock_package('foo2', 'MIN_SDK_VERSION=121')
    pkg = source_package.create_package('foo2')
    pkg.check_buildable()

    self.create_mock_package('foo3', 'MIN_SDK_VERSION=124')
    pkg = source_package.create_package('foo3')
    with self.assertRaisesRegexp(error.DisabledError,
                                 'requires SDK version 124 or above'):
      pkg.check_buildable()

  @patch('webports.util.get_sdk_version', Mock(return_value=1234))
  def test_installed_info_contents(self):
    root = self.create_mock_package('foo')
    pkg = source_package.SourcePackage(root)
    expected_contents = textwrap.dedent('''\
      NAME=foo
      VERSION=1.0
      BUILD_CONFIG=release
      BUILD_ARCH=pnacl
      BUILD_TOOLCHAIN=pnacl
      BUILD_SDK_VERSION=1234
      ''')
    self.assertRegexpMatches(pkg.installed_info_contents(), expected_contents)

  def test_run_git_cmd_bad_repo(self):
    os.mkdir(os.path.join(self.tempdir, '.git'))
    with self.assertRaisesRegexp(error.Error, 'git command failed'):
      source_package.init_git_repo(self.tempdir)

  def test_init_git_repo(self):
    # init a git repo containing a single dummy file
    with open(os.path.join(self.tempdir, 'file'), 'w') as f:
      f.write('bar')
    source_package.init_git_repo(self.tempdir)
    self.assertTrue(os.path.isdir(os.path.join(self.tempdir, '.git')))

    # InitGitRepo should work on existing git repositories too.
    source_package.init_git_repo(self.tempdir)

  @patch('webports.util.download_file')
  @patch('webports.util.verify_hash')
  def test_download(self, mock_verify, mock_download):
    self.create_mock_package('foo', 'URL=foo/bar.tar.gz\nSHA1=X123')
    pkg = source_package.create_package('foo')
    pkg.download()
    expected_filename = os.path.join(paths.CACHE_ROOT, 'bar.tar.gz')
    mock_download.assert_called_once_with(expected_filename, mock.ANY)
    mock_verify.assert_called_once_with(expected_filename, 'X123')

  @patch('webports.util.download_file')
  def test_download_missing_sha1(self, mock_download):
    self.create_mock_package('foo', 'URL=foo/bar')
    pkg = source_package.create_package('foo')
    with self.assertRaisesRegexp(error.Error, 'missing SHA1 attribute'):
      pkg.download()
