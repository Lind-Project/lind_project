# Copyright (c) 2013 The Native Client Authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.
"""Tool for manipulating webports packages in python.

This tool can be used to for working with webports packages.
It can also be incorporated into other tools that need to
work with packages (e.g. 'update_mirror.py' uses it to iterate
through all packages and mirror them on Google Cloud Storage).
"""

from __future__ import print_function
import os
import subprocess
import sys
import tempfile

if sys.version_info < (2, 7, 0):
  sys.stderr.write("python 2.7 or later is required run this script\n")
  sys.exit(1)

import argparse

sys.path.append(os.path.dirname(os.path.dirname(__file__)))

from webports import configuration, error, source_package, util, paths
from webports import installed_package


def print_error(msg):
  sys.stderr.write('webports: %s\n' % util.colorize(str(msg), 'red'))


def cmd_list(config, options, args):
  """List installed packages"""
  if len(args):
    raise error.Error('list command takes no arguments')
  if options.all:
    iterator = source_package.source_package_iterator()
  else:
    iterator = installed_package.installed_package_iterator(config)
  for package in iterator:
    if options.verbosity:
      sys.stdout.write('%-15s %s\n' % (package.NAME, package.VERSION))
    else:
      sys.stdout.write(package.NAME + '\n')
  return 0


def cmd_info(config, options, args):
  """Print infomation on installed package(s)"""
  if len(args) != 1:
    raise error.Error('info command takes a single package name')
  package_name = args[0]
  pkg = installed_package.create_installed_package(package_name, config)
  info_file = pkg.get_install_stamp()
  print('Install receipt: %s' % info_file)
  with open(info_file) as f:
    sys.stdout.write(f.read())


def cmd_pkg_list_deps(package, options):
  """Print complete list of package dependencies."""
  for pkg in package.transitive_dependencies():
    print(pkg.NAME)


def cmd_pkg_contents(package, options):
  """List contents of an installed package"""
  install_root = util.get_install_root(package.config)
  for filename in package.files():
    if util.log_level > util.LOG_INFO:
      filename = os.path.join(install_root, filename)
    if options.all:
      filename = package.NAME + ': ' + filename
    sys.stdout.write(filename + '\n')


def cmd_pkg_download(package, options):
  """Download sources for given package(s)"""
  package.download()


def cmd_pkg_uscan(package, options):
  """Use Debian's 'uscan' to check for upstream versions."""
  if not package.URL:
    return 0

  if package.VERSION not in package.URL:
    print_error('%s: uscan only works if VERSION is embedded in URL' %
                package.NAME)
    return 0

  temp_fd, temp_file = tempfile.mkstemp('webports_watchfile')
  try:
    with os.fdopen(temp_fd, 'w') as f:
      uscan_url = package.URL.replace(package.VERSION, '(.+)')
      uscan_url = uscan_url.replace('download.sf.net', 'sf.net')
      util.log_verbose('uscan pattern: %s' % uscan_url)
      f.write("version = 3\n")
      f.write("%s\n" % uscan_url)

    cmd = ['uscan', '--upstream-version', package.VERSION, '--package',
           package.NAME, '--watchfile', temp_file]
    util.log_verbose(' '.join(cmd))
    rtn = subprocess.call(cmd)
  finally:
    os.remove(temp_file)

  return rtn


def cmd_check(config, options, args):
  """Verify the dependecies of all install packages are also installed."""
  if len(args):
    raise error.Error('check command takes no arguments')

  installed_packages = installed_package.installed_package_iterator(config)
  installed_map = {pkg.NAME: pkg for pkg in installed_packages}

  checked = set()

  def check_deps(pkg_name, required_by):
    if pkg_name in checked:
      return
    checked.add(pkg_name)
    pkg = installed_map.get(pkg_name)
    if not pkg:
      raise error.Error("missing package '%s' required by '%s'" % (pkg_name,
                                                                   required_by))
    for dep in pkg.DEPENDS:
      check_deps(dep, pkg.NAME)

  for pkg in installed_map.itervalues():
    check_deps(pkg.NAME, None)


def cmd_pkg_check(package, options):
  """Verify dependency information for given package(s)"""
  # The fact that we got this far means the pkg_info is basically valid.
  # This final check verifies the dependencies are valid.
  # Cache the list of all packages names since this function could be called
  # a lot in the case of "webports check --all".
  packages = source_package.source_package_iterator()
  if cmd_pkg_check.all_pkg_names is None:
    cmd_pkg_check.all_pkg_names = [os.path.basename(p.root) for p in packages]
  util.log("Checking deps for %s .." % package.NAME)
  package.check_deps(cmd_pkg_check.all_package_names)


cmd_pkg_check.all_pkg_names = None


def cmd_pkg_build(package, options):
  """Build package(s)"""
  package.build(options.build_deps, force=options.force)


def perform_uninstall(package):
  for dep in package.reverse_dependencies():
    perform_uninstall(dep)
  package.uninstall()


def cmd_pkg_install(package, options):
  """Install package(s)"""
  if options.all:
    for conflict in package.transitive_conflicts():
      if conflict.is_installed():
        perform_uninstall(conflict)

  package.install(options.build_deps, force=options.force,
                  from_source=options.from_source)


def cmd_pkg_uninstall(package, options):
  """Uninstall package(s)"""
  for dep in package.reverse_dependencies():
    if options.force or options.all:
      perform_uninstall(dep)
    else:
      raise error.Error("unable to uninstall '%s'. another package is "
                        "installed which depends on it: '%s'" %
                        (package.NAME, dep.NAME))

  package.uninstall()


def cmd_pkg_clean(package, options):
  """Clean package build artifacts."""
  package.clean()


def cmd_pkg_update_patch(package, options):
  """Update patch file for package(s)"""
  package.update_patch()


def cmd_pkg_extract(package, options):
  """Extact source archive for package(s)"""
  package.download()
  package.extract()


def cmd_pkg_patch(package, options):
  """Apply webports patch for package(s)"""
  package.patch()


def clean_all(config):
  """Remove all build directories and all pre-built packages as well
  as all installed packages for the given configuration."""

  def rmtree(path):
    util.log('removing %s' % path)
    util.remove_tree(path)

  rmtree(paths.STAMP_DIR)
  rmtree(paths.BUILD_ROOT)
  rmtree(paths.PUBLISH_ROOT)
  rmtree(paths.PACKAGES_ROOT)
  rmtree(util.get_install_stamp_root(config))
  rmtree(util.get_install_root(config))


def run_main(args):
  base_commands = {
      'list': cmd_list,
      'info': cmd_info,
      'check': cmd_check,
  }

  pkg_commands = {
      'download': cmd_pkg_download,
      'uscan': cmd_pkg_uscan,
      'check': cmd_pkg_check,
      'build': cmd_pkg_build,
      'install': cmd_pkg_install,
      'clean': cmd_pkg_clean,
      'uninstall': cmd_pkg_uninstall,
      'contents': cmd_pkg_contents,
      'depends': cmd_pkg_list_deps,
      'updatepatch': cmd_pkg_update_patch,
      'extract': cmd_pkg_extract,
      'patch': cmd_pkg_patch
  }

  installed_pkg_commands = ['contents', 'uninstall']

  all_commands = dict(base_commands.items() + pkg_commands.items())

  epilog = "The following commands are available:\n"
  for name, function in all_commands.iteritems():
    epilog += '  %-12s - %s\n' % (name, function.__doc__)

  parser = argparse.ArgumentParser(prog='webports', description=__doc__,
      formatter_class=argparse.RawDescriptionHelpFormatter, epilog=epilog)
  parser.add_argument('-v', '--verbose', dest='verbosity', action='count',
                      default=0, help='Output extra information.')
  parser.add_argument('-V', '--verbose-build', action='store_true',
                      help='Make builds verbose (e.g. pass V=1 to make')
  parser.add_argument('--skip-sdk-version-check', action='store_true',
                      help="Disable the NaCl SDK version check on startup.")
  parser.add_argument('--all', action='store_true',
                      help='Perform action on all known ports.')
  parser.add_argument('--color', choices=('always', 'never', 'auto'),
                      help='Enabled color terminal output', default='auto')
  parser.add_argument('-f', '--force', action='store_const', const='build',
                      help='Force building specified targets, '
                      'even if timestamps would otherwise skip it.')
  parser.add_argument('--from-source', action='store_true',
                      help='Always build from source rather than downloading '
                      'prebuilt packages.')
  parser.add_argument('-F', '--force-all', action='store_const', const='all',
                      dest='force', help='Force building target and all '
                      'dependencies, even if timestamps would otherwise skip '
                      'them.')
  parser.add_argument('--no-deps', dest='build_deps', action='store_false',
                      default=True,
                      help='Disable automatic building of dependencies.')
  parser.add_argument('--ignore-disabled', action='store_true',
                      help='Ignore attempts to build disabled packages.\n'
                      'Normally attempts to build such packages will result\n'
                      'in an error being returned.')
  parser.add_argument('-t', '--toolchain',
                      help='Set toolchain to use when building (newlib, glibc, '
                      'or pnacl)')
  # use store_const rather than store_true since we want to default for
  # debug to be None (which then falls back to checking the NACL_DEBUG
  # environment variable.
  parser.add_argument('-d', '--debug', action='store_const', const=True,
                      help='Build debug configuration (release is the default)')
  parser.add_argument('-a', '--arch',
                      help='Set architecture to use when building (x86_64,'
                      ' x86_32, arm, pnacl)')
  parser.add_argument('command', help="sub-command to run")
  parser.add_argument('pkg', nargs='*', help="package name or directory")
  args = parser.parse_args(args)

  if not args.verbosity and os.environ.get('VERBOSE') == '1':
    args.verbosity = 1

  util.set_log_level(util.LOG_INFO + args.verbosity)

  if args.verbose_build:
    os.environ['VERBOSE'] = '1'
  else:
    if 'VERBOSE' in os.environ:
      del os.environ['VERBOSE']
    if 'V' in os.environ:
      del os.environ['V']

  if args.skip_sdk_version_check:
    util.MIN_SDK_VERSION = -1

  util.check_sdk_root()
  config = configuration.Configuration(args.arch, args.toolchain, args.debug)
  util.color_mode = args.color
  if args.color == 'never':
    util.colorize.enabled = False
  elif args.color == 'always':
    util.colorize.enabled = True

  if args.command in base_commands:
    base_commands[args.command](config, args, args.pkg)
    return 0

  if args.command not in pkg_commands:
    parser.error("Unknown subcommand: '%s'\n"
                 'See --help for available commands.' % args.command)

  if len(args.pkg) and args.all:
    parser.error('Package name(s) and --all cannot be specified together')

  if args.pkg:
    package_names = args.pkg
  else:
    package_names = [os.getcwd()]

  def do_cmd(package):
    try:
      pkg_commands[args.command](package, args)
    except error.DisabledError as e:
      if args.ignore_disabled:
        util.log('webports: %s' % e)
      else:
        raise e

  if args.all:
    args.ignore_disabled = True
    if args.command == 'clean':
      clean_all(config)
    else:
      if args.command in installed_pkg_commands:
        package_iterator = installed_package.installed_package_iterator(config)
      else:
        package_iterator = source_package.source_package_iterator()
      for p in package_iterator:
        do_cmd(p)
  else:
    for package_name in package_names:
      if args.command in installed_pkg_commands:
        p = installed_package.create_installed_package(package_name, config)
      else:
        p = source_package.create_package(package_name, config)
      do_cmd(p)


def main(args):
  try:
    run_main(args)
  except KeyboardInterrupt:
    print_error('interrupted')
    return 1
  except error.Error as e:
    if os.environ.get('DEBUG'):
      raise
    print_error(str(e))
    return 1

  return 0


if __name__ == '__main__':
  sys.exit(main(sys.argv[1:]))
