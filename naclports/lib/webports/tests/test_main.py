# Copyright 2014 The Native Client Authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.

import os
import mock
from mock import patch, Mock
import StringIO

import common
import webports.__main__
from webports import error
from webports.configuration import Configuration


# pylint: disable=no-self-use
class TestMain(common.NaclportsTest):

  def setUp(self):
    super(TestMain, self).setUp()
    self.add_patch(patch('webports.util.check_sdk_root'))

  @patch('webports.util.log', Mock())
  @patch('webports.util.remove_tree')
  def test_clean_all(self, mock_rmtree):
    config = Configuration()
    webports.__main__.clean_all(config)
    mock_rmtree.assert_any_call('/package/install/path')

  @patch('webports.__main__.run_main', Mock(side_effect=error.Error('oops')))
  def test_error_report(self):
    # Verify that exceptions of the type error.Error are printed
    # to stderr and result in a return code of 1
    with patch('sys.stderr', new_callable=StringIO.StringIO) as stderr:
      self.assertEqual(webports.__main__.main(None), 1)
    self.assertRegexpMatches(stderr.getvalue(), '^webports: oops')

  @patch('webports.__main__.cmd_pkg_clean')
  def test_main_command_dispatch(self, cmd_pkg_clean):
    mock_pkg = Mock()
    with patch('webports.source_package.create_package',
               Mock(return_value=mock_pkg)):
      webports.__main__.run_main(['clean', 'foo'])
    cmd_pkg_clean.assert_called_once_with(mock_pkg, mock.ANY)

  @patch('webports.__main__.cmd_pkg_clean',
         Mock(side_effect=error.DisabledError()))
  def test_main_handle_package_disabled(self):
    mock_pkg = Mock()
    with patch('webports.source_package.create_package',
               Mock(return_value=mock_pkg)):
      with self.assertRaises(error.DisabledError):
        webports.__main__.run_main(['clean', 'foo'])

  @patch('webports.__main__.clean_all')
  def test_main_clean_all(self, clean_all_mock):
    webports.__main__.run_main(['clean', '--all'])
    clean_all_mock.assert_called_once_with(Configuration())


class TestCommands(common.NaclportsTest):

  def test_list_command(self):
    config = Configuration()
    pkg = Mock(NAME='foo', VERSION='0.1')
    with patch('webports.installed_package.installed_package_iterator',
               Mock(return_value=[pkg])):
      with patch('sys.stdout', new_callable=StringIO.StringIO) as stdout:
        options = Mock(all=False)
        webports.__main__.cmd_list(config, options, [])
        lines = stdout.getvalue().splitlines()
        self.assertRegexpMatches(lines[0], '^foo\\s+0.1$')
        self.assertEqual(len(lines), 1)

  def test_list_command_verbose(self):
    config = Configuration()
    pkg = Mock(NAME='foo', VERSION='0.1')
    with patch('webports.installed_package.installed_package_iterator',
               Mock(return_value=[pkg])):
      with patch('sys.stdout', new_callable=StringIO.StringIO) as stdout:
        options = Mock(verbosity=0, all=False)
        webports.__main__.cmd_list(config, options, [])
        lines = stdout.getvalue().splitlines()
        self.assertRegexpMatches(lines[0], "^foo$")
        self.assertEqual(len(lines), 1)

  @patch('webports.installed_package.create_installed_package', Mock())
  def test_info_command(self):
    config = Configuration()
    options = Mock()
    file_mock = common.mock_file_object('FOO=bar\n')

    with patch('sys.stdout', new_callable=StringIO.StringIO) as stdout:
      with patch('__builtin__.open', Mock(return_value=file_mock), create=True):
        webports.__main__.cmd_info(config, options, ['foo'])
        self.assertRegexpMatches(stdout.getvalue(), "FOO=bar")

  def test_contents_command(self):
    file_list = ['foo', 'bar']

    options = Mock(verbosity=0, all=False)
    package = Mock(NAME='test', files=Mock(return_value=file_list))

    expected_output = '\n'.join(file_list) + '\n'
    with patch('sys.stdout', new_callable=StringIO.StringIO) as stdout:
      webports.__main__.cmd_pkg_contents(package, options)
      self.assertEqual(stdout.getvalue(), expected_output)

    # when the verbose option is set expect CmdContents to output full paths.
    webports.util.log_level = webports.util.LOG_VERBOSE
    expected_output = [os.path.join('/package/install/path', f)
                       for f in file_list]
    expected_output = '\n'.join(expected_output) + '\n'
    with patch('sys.stdout', new_callable=StringIO.StringIO) as stdout:
      webports.__main__.cmd_pkg_contents(package, options)
      self.assertEqual(stdout.getvalue(), expected_output)
