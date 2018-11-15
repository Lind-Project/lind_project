# Copyright (c) 2014 The Native Client Authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.

from webports.error import Error
from webports import configuration, pkg_info, util

EXTRA_KEYS = ['BUILD_CONFIG', 'BUILD_ARCH', 'BUILD_TOOLCHAIN',
              'BUILD_SDK_VERSION', 'BUILD_NACLPORTS_REVISION']

class Package(object):
  extra_keys = []
  list_props = (
    'DEPENDS',
    'CONFLICTS',
    'DISABLED_ARCH',
    'DISABLED_LIBC',
    'DISABLED_TOOLCHAIN'
  )

  def __init__(self, info_file=None):
    self.info = info_file
    if self.info:
      with open(self.info) as f:
        self.parse_info(f.read())

  def parse_info(self, info_string):
    valid_keys = pkg_info.VALID_KEYS + self.extra_keys
    required_keys = pkg_info.REQUIRED_KEYS + self.extra_keys

    for key in valid_keys:
      if key in self.list_props:
        setattr(self, key, [])
      else:
        setattr(self, key, None)

    # Parse pkg_info file
    info = pkg_info.parse_pkg_info(info_string, self.info, valid_keys,
                                   required_keys)

    # Set attributres based on pkg_info setttings.
    for key, value in info.items():
      setattr(self, key, value)

    self.validate()

  def validate(self):
    for libc in self.DISABLED_LIBC:
      if libc not in configuration.VALID_LIBC:
        raise Error('%s: invalid libc: %s' % (self.info, libc))

    for toolchain in self.DISABLED_TOOLCHAIN:
      if '/' in toolchain:
        toolchain, arch = toolchain.split('/')
        if arch not in util.arch_to_pkgarch:
          raise Error('%s: invalid architecture: %s' % (self.info, arch))
      if toolchain not in configuration.VALID_TOOLCHAINS:
        raise Error('%s: invalid toolchain: %s' % (self.info, toolchain))

    for arch in self.DISABLED_ARCH:
      if arch not in util.arch_to_pkgarch:
        raise Error('%s: invalid architecture: %s' % (self.info, arch))

    if '_' in self.NAME:
      raise Error('%s: package NAME cannot contain underscores' % self.info)

    if self.NAME != self.NAME.lower():
      raise Error('%s: package NAME cannot contain uppercase characters' %
                  self.info)

    if '_' in self.VERSION:
      raise Error('%s: package VERSION cannot contain underscores' % self.info)

    if self.DISABLED_ARCH and self.ARCH is not None:
      raise Error('%s: contains both ARCH and DISABLED_ARCH' % self.info)

  def __cmp__(self, other):
    return cmp((self.NAME, self.VERSION, self.config),
               (other.NAME, other.VERSION, other.config))

  def __hash__(self):
    return hash((self.NAME, self.VERSION, self.config))

  def __str__(self):
    return '<Package %s %s %s>' % (self.NAME, self.VERSION, self.config)

  def info_string(self):
    return "'%s' [%s]" % ((util.colorize(self.NAME, 'yellow'),
                           util.colorize(self.config, 'blue')))

  def log_status(self, message, suffix=''):
    util.log_heading(message, " " + self.info_string())

  def check_deps(self, valid_packages):
    for package in self.DEPENDS:
      if package not in valid_packages:
        util.log('%s: Invalid dependency: %s' % (self.info, package))
        return False

    for package in self.CONFLICTS:
      if package not in valid_packages:
        util.log('%s: Invalid conflict: %s' % (self.info, package))
        return False

    return True

  def is_any_version_installed(self):
    return util.is_installed(self.NAME, self.config)

  def get_install_stamp(self):
    """Returns the name of install stamp for this package."""
    return util.get_install_stamp(self.NAME, self.config)

  def get_list_file(self):
    """Returns the name of the installed file list for this package."""
    return util.get_list_file(self.NAME, self.config)
