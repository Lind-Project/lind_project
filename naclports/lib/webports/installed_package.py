# Copyright 2015 The Native Client Authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.

import os

from webports import package, configuration, util, error


def remove_empty_dirs(dirname):
  """Recursively remove a directoy and its parents if they are empty."""
  while not os.listdir(dirname):
    os.rmdir(dirname)
    dirname = os.path.dirname(dirname)


def remove_file(filename):
  os.remove(filename)
  remove_empty_dirs(os.path.dirname(filename))


class InstalledPackage(package.Package):
  extra_keys = package.EXTRA_KEYS

  def __init__(self, info_file):
    super(InstalledPackage, self).__init__(info_file)
    self.config = configuration.Configuration(self.BUILD_ARCH,
                                              self.BUILD_TOOLCHAIN,
                                              self.BUILD_CONFIG == 'debug')

  def uninstall(self):
    self.log_status('Uninstalling')
    self.do_uninstall(force=False)

  def files(self):
    """Yields the list of files currently installed by this package."""
    file_list = self.get_list_file()
    if not os.path.exists(file_list):
      return
    with open(self.get_list_file()) as f:
      for line in f:
        yield line.strip()

  def do_uninstall(self, force):
    with util.InstallLock(self.config):
      if not force:
        for pkg in installed_package_iterator(self.config):
          if self.NAME in pkg.DEPENDS:
            raise error.Error("Unable to uninstall '%s' (depended on by '%s')" %
                              (self.NAME, pkg.NAME))
      remove_file(self.get_install_stamp())

      root = util.get_install_root(self.config)
      for filename in self.files():
        fullname = os.path.join(root, filename)
        if not os.path.lexists(fullname):
          util.warn('File not found while uninstalling: %s' % fullname)
          continue
        util.log_verbose('uninstall: %s' % filename)
        remove_file(fullname)

      if os.path.exists(self.get_list_file()):
        remove_file(self.get_list_file())

  def reverse_dependencies(self):
    """Yields the set of packages that depend directly on this one"""
    for pkg in installed_package_iterator(self.config):
      if self.NAME in pkg.DEPENDS:
        yield pkg


def installed_package_iterator(config):
  stamp_root = util.get_install_stamp_root(config)
  if not os.path.exists(stamp_root):
    return

  for filename in os.listdir(stamp_root):
    if os.path.splitext(filename)[1] != '.info':
      continue
    info_file = os.path.join(stamp_root, filename)
    if os.path.exists(info_file):
      yield InstalledPackage(info_file)


def create_installed_package(package_name, config=None):
  stamp_root = util.get_install_stamp_root(config)
  info_file = os.path.join(stamp_root, package_name + '.info')
  if not os.path.exists(info_file):
    raise error.Error('package not installed: %s [%s]' % (package_name, config))
  return InstalledPackage(info_file)
