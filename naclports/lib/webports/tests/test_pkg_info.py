# Copyright 2014 The Native Client Authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.

from webports import pkg_info
from webports import error

import common


class TestParsePkgInfo(common.NaclportsTest):

  def test_invalid_line(self):
    expected_error = 'Invalid info line dummy_file:1'
    with self.assertRaisesRegexp(error.Error, expected_error):
      pkg_info.parse_pkg_info('line without equals sign', 'dummy_file')

  def test_blank_line(self):
    result = pkg_info.parse_pkg_info('NAME=foo\n\nVERSION=bar', 'dummy_file')
    self.assertEqual(result, {'NAME': 'foo', 'VERSION': 'bar'})

  def test_comments(self):
    result = pkg_info.parse_pkg_info('NAME=foo # tail\n# line\nVERSION=bar',
                                     'dummy_file')
    self.assertEqual(result, {'NAME': 'foo', 'VERSION': 'bar'})

  def test_valid_keys(self):
    expected_error = "Invalid key 'BAR' in info file dummy_file:2"
    contents = 'FOO=bar\nBAR=baz\n'
    valid = ['FOO']
    required = []
    with self.assertRaisesRegexp(error.Error, expected_error):
      pkg_info.parse_pkg_info(contents, 'dummy_file', valid, required)

  def test_required_keys(self):
    expected_error = "Required key 'BAR' missing from info file: 'dummy_file'"
    contents = 'FOO=bar\n'
    valid = ['FOO']
    required = ['BAR']
    with self.assertRaisesRegexp(error.Error, expected_error):
      pkg_info.parse_pkg_info(contents, 'dummy_file', valid, required)
