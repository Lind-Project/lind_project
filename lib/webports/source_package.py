# Copyright (c) 2014 The Native Client Authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.

import contextlib
import fnmatch
import os
import re
import subprocess
import sys
import tempfile
import time
import urlparse

from webports import binary_package
from webports import configuration
from webports import package
from webports import package_index
from webports import installed_package
from webports import util
from webports import paths
from webports import bsd_pkg
from webports.util import log, trace, log_verbose
from webports.error import Error, DisabledError, PkgFormatError


class PkgConflictError(Error):
  pass


@contextlib.contextmanager
def redirect_stdout_stderr(filename):
  """Context manager that replaces stdout and stderr streams."""
  if filename is None:
    yield
    return

  with open(filename, 'a') as stream:
    old_stdout = sys.stdout
    old_stderr = sys.stderr
    sys.stdout = stream
    sys.stderr = stream
    util.check_stdout_for_color_support()
    try:
      yield
    finally:
      sys.stdout = old_stdout
      sys.stderr = old_stderr
      util.check_stdout_for_color_support()


def format_time_delta(delta):
  """Converts a duration in seconds to a human readable string.

  Args:
    delta: the amount of time in seconds.

  Returns: A string describing the amount of time passed in.
  """
  rtn = ''
  if delta >= 60:
    mins = delta / 60
    rtn += '%dm' % mins
    delta -= mins * 60

  if delta:
    rtn += '%.0fs' % delta
  return rtn


def extract_archive(archive, destination):
  ext = os.path.splitext(archive)[1]
  if ext in ('.gz', '.tgz', '.bz2', '.xz'):
    cmd = ['tar', 'xf', archive, '-C', destination]
  elif ext in ('.zip',):
    cmd = ['unzip', '-q', '-d', destination, archive]
  else:
    raise Error('unhandled extension: %s' % ext)
  log_verbose(cmd)
  subprocess.check_call(cmd)


def run_git_cmd(directory, cmd, error_ok=False):
  cmd = ['git'] + cmd
  log_verbose('%s' % ' '.join(cmd))
  p = subprocess.Popen(cmd, cwd=directory, stderr=subprocess.PIPE,
                       stdout=subprocess.PIPE)
  stdout, stderr = p.communicate()
  if not error_ok and p.returncode != 0:
    if stdout:
      log(stdout)
    if stderr:
      log(stderr)
    raise Error('git command failed: %s' % cmd)
  trace('git exited with %d' % p.returncode)
  return p.returncode


def init_git_repo(directory):
  """Initialize the source git repository for a given package directory.

  This function works for unpacked tar files as well as cloned git
  repositories.  It sets up an 'upstream' branch pointing and the
  pristine upstream sources and a 'master' branch will contain changes
  specific to webports (normally the result of applying nacl.patch).

  Args:
    directory: Directory containing unpacked package sources.
  """
  git_dir = os.path.join(directory, '.git')

  # If the upstream ref exists then we've already initialized this repo
  if os.path.exists(os.path.join(git_dir, 'refs', 'heads', 'upstream')):
    return

  if os.path.exists(git_dir):
    log('Init existing git repo: %s' % directory)
    run_git_cmd(directory, ['checkout', '-b', 'placeholder'])
    run_git_cmd(directory, ['branch', '-D', 'upstream'], error_ok=True)
    run_git_cmd(directory, ['branch', '-D', 'master'], error_ok=True)
    run_git_cmd(directory, ['checkout', '-b', 'upstream'])
    run_git_cmd(directory, ['checkout', '-b', 'master'])
    run_git_cmd(directory, ['branch', '-D', 'placeholder'])
  else:
    log('Init new git repo: %s' % directory)
    run_git_cmd(directory, ['init'])
    try:
      # Setup a bogus identity on the buildbots.
      if os.environ.get('BUILDBOT_BUILDERNAME'):
        run_git_cmd(directory, ['config', 'user.name', 'Naclports'])
        run_git_cmd(directory, ['config', 'user.email', 'nobody@example.com'])
      run_git_cmd(directory, ['add', '-f', '.'])
      run_git_cmd(directory, ['commit', '-m', 'Upstream version'])
      run_git_cmd(directory, ['checkout', '-b', 'upstream'])
      run_git_cmd(directory, ['checkout', 'master'])
    except:  # pylint: disable=bare-except
      # If git setup fails or is interrupted then remove the partially
      # initialized repository.
      util.remove_tree(os.path.join(git_dir))


def write_stamp(stamp_file, stamp_contents):
  """Write a stamp file to disk with the given file contents."""
  stamp_dir = os.path.dirname(stamp_file)
  util.makedirs(stamp_dir)

  with open(stamp_file, 'w') as f:
    f.write(stamp_contents)
  log('Wrote stamp: %s' % stamp_file)


def stamp_contents_match(stamp_file, stamp_contents):
  """Return True is stamp_file exists and contains the given contents."""
  if not os.path.exists(stamp_file):
    return False
  with open(stamp_file) as f:
    return f.read() == stamp_contents


class SourcePackage(package.Package):
  """Representation of a single webports source package.

  Package objects correspond to folders on disk which
  contain a 'pkg_info' file.
  """

  def __init__(self, pkg_root, config=None):
    super(SourcePackage, self).__init__()
    if config is None:
      config = configuration.Configuration()
    self.config = config

    self.root = os.path.abspath(pkg_root)
    info_file = os.path.join(self.root, 'pkg_info')
    if not os.path.isdir(self.root) or not os.path.exists(info_file):
      raise Error('Invalid package folder: %s' % pkg_root)

    super(SourcePackage, self).__init__(info_file)
    if self.NAME != os.path.basename(self.root):
      raise Error('%s: package NAME must match directory name' % self.info)

  def get_install_location(self):
    install_dir = 'install_%s' % util.arch_to_pkgarch[self.config.arch]
    if self.config.arch != self.config.toolchain:
      install_dir += '_' + self.config.toolchain
    if self.config.config_name == 'debug':
      install_dir += '_debug'
    return os.path.join(paths.BUILD_ROOT, self.NAME, install_dir, 'payload')

  def get_build_location(self):
    package_dir = self.ARCHIVE_ROOT or '%s-%s' % (self.NAME, self.VERSION)
    return os.path.join(paths.BUILD_ROOT, self.NAME, package_dir)

  def get_patch_file(self):
    patch_name = self.PATCH_NAME or 'nacl.patch'
    return os.path.join(self.root, patch_name)

  def get_archive_filename(self):
    if self.URL_FILENAME:
      return self.URL_FILENAME

    if self.is_git_upstream() or self.URL is None:
      return None

    return os.path.basename(urlparse.urlparse(self.URL)[2])

  def download_location(self):
    archive = self.get_archive_filename()
    if not archive:
      return
    return os.path.join(paths.CACHE_ROOT, archive)

  def is_installed(self):
    return util.is_installed(self.NAME, self.config,
                             self.installed_info_contents())

  def is_git_upstream(self):
    return self.URL and self.URL.split('@')[0].endswith('.git')

  def install_deps(self, force, from_source=False):
    for dep in self.dependencies():
      if not dep.is_any_version_installed() or force == 'all':
        dep.install(True, force, from_source)

  def package_file(self):
    fullname = [os.path.join(paths.PACKAGES_ROOT, self.NAME)]
    fullname.append(self.VERSION)
    fullname.append(util.arch_to_pkgarch[self.config.arch])
    # for pnacl toolchain and arch are the same
    if self.config.toolchain != self.config.arch:
      fullname.append(self.config.toolchain)
    if self.config.debug:
      fullname.append('debug')
    return '_'.join(fullname) + '.tar.bz2'

  def installed_info_contents(self):
    """Generate content of the .info file to install based on source
    pkg_info file and current build configuration."""
    with open(self.info) as f:
      info_content = f.read()
    info_content += 'BUILD_CONFIG=%s\n' % self.config.config_name
    info_content += 'BUILD_ARCH=%s\n' % self.config.arch
    info_content += 'BUILD_TOOLCHAIN=%s\n' % self.config.toolchain
    info_content += 'BUILD_SDK_VERSION=%s\n' % util.get_sdk_version()
    return info_content

  def is_built(self):
    package_file = self.package_file()
    if not os.path.exists(package_file):
      return False
    try:
      pkg = binary_package.BinaryPackage(package_file)
    except PkgFormatError:
      # If the package is malformed in some way or in some old format
      # then treat it as not built.
      return False
    return pkg.is_installable()

  def install(self, build_deps, force=None, from_source=False):
    self.check_installable()

    if force is None and self.is_installed():
      self.log_status('Already installed')
      return

    if build_deps:
      self.install_deps(force, from_source)

    if force:
      from_source = True

    package_file = self.package_file()
    if not self.is_built() and not from_source:
      index = package_index.get_current_index()
      if index.installable(self.NAME, self.config):
        package_file = index.download(self.NAME, self.config)
      else:
        from_source = True

    if from_source:
      self.build(build_deps, force)

    if self.is_any_version_installed():
      installed_pkg = self.get_installed_package()
      installed_pkg.log_status('Uninstalling existing')
      installed_pkg.do_uninstall(force=True)

    binary_package.BinaryPackage(package_file).install(force)

  def get_installed_package(self):
    return installed_package.create_installed_package(self.NAME, self.config)

  def create_pkg_file(self):
    """Create and pkg file for use with the FreeBSD pkg tool.

    Create a package from the result of the package's InstallStep.
    """
    install_dir = self.get_install_location()
    if not os.path.exists(install_dir):
      log('Skiping pkg creation. Install dir not found: %s' % install_dir)
      return

    # Strip all elf or pexe files in the install directory (except .o files
    # since we don't want to strip, for example, crt1.o)
    if not self.config.debug and self.config.toolchain != 'emscripten':
      strip = util.get_strip(self.config)
      for root, _, files in os.walk(install_dir):
        for filename in files:
          fullname = os.path.join(root, filename)
          if (os.path.isfile(fullname) and util.is_elf_file(fullname) and
              os.path.splitext(fullname)[1] != '.o'):
            log('stripping: %s %s' % (strip, fullname))
            subprocess.check_call([strip, fullname])

    abi = 'pkg_' + self.config.toolchain
    if self.config.arch != self.config.toolchain:
      abi += "_" + util.arch_to_pkgarch[self.config.arch]
    abi_dir = os.path.join(paths.PUBLISH_ROOT, abi)
    pkg_file = os.path.join(abi_dir, '%s-%s.tbz' % (self.NAME, self.VERSION))
    util.makedirs(abi_dir)
    deps = self.DEPENDS
    if self.config.toolchain != 'glibc':
      deps = []
    bsd_pkg.create_pkg_file(self.NAME, self.VERSION, self.config.arch,
                            self.get_install_location(), pkg_file, deps)

  def build(self, build_deps, force=None):
    self.check_buildable()

    if build_deps:
      self.install_deps(force)

    if not force and self.is_built():
      self.log_status('Already built')
      return

    log_root = os.path.join(paths.OUT_DIR, 'logs')
    util.makedirs(log_root)

    self.log_status('Building')

    if util.log_level > util.LOG_INFO:
      log_filename = None
    else:
      log_filename = os.path.join(log_root, '%s_%s.log' %
                                  (self.NAME,
                                   str(self.config).replace('/', '_')))
      if os.path.exists(log_filename):
        os.remove(log_filename)

    start = time.time()
    with util.DirLock(self.root):
      try:
        with redirect_stdout_stderr(log_filename):
          old_log_level = util.log_level
          util.log_level = util.LOG_VERBOSE
          try:
            self.download()
            self.extract()
            self.patch()
            self.run_build_sh()
            self.create_pkg_file()
          finally:
            util.log_level = old_log_level
      except KeyboardInterrupt:
        # Treat KeyboardInterrupt as special, and not an actual failure.  This
        # avoid log spew to stdout when they user interupts a quit build.
        raise
      except:
        if log_filename:
          with open(log_filename) as log_file:
            sys.stdout.write(log_file.read())
        raise

    duration = format_time_delta(time.time() - start)
    util.log_heading('Build complete', ' [took %s]' % duration)

  def run_build_sh(self):
    build_port = os.path.join(paths.TOOLS_DIR, 'build_port.sh')
    cmd = [build_port]

    if self.config.toolchain == 'emscripten':
      util.setup_emscripten()
    env = os.environ.copy()
    env['TOOLCHAIN'] = self.config.toolchain
    env['NACL_ARCH'] = self.config.arch
    env['NACL_DEBUG'] = self.config.debug and '1' or '0'
    env['NACL_SDK_ROOT'] = util.get_sdk_root()
    rtn = subprocess.call(cmd, stdout=sys.stdout, stderr=sys.stderr,
                          cwd=self.root, env=env)
    if rtn != 0:
      raise Error('Build failed: %s' % self.info_string())

  def download(self, force_mirror=None):
    """Download upstream sources and verify integrity."""
    if self.is_git_upstream():
      self.git_clone_to_mirror()
      return

    archive = self.download_location()
    if not archive:
      return

    if force_mirror is None:
      force_mirror = os.environ.get('FORCE_MIRROR', False)
    self.download_archive(force_mirror=force_mirror)

    if self.SHA1 is None:
      raise PkgFormatError('missing SHA1 attribute: %s' % self.info)

    util.verify_hash(archive, self.SHA1)
    log('verified: %s' % util.rel_path(archive))

  def clean(self):
    pkg = self.package_file()
    log('removing %s' % pkg)
    if os.path.exists(pkg):
      os.remove(pkg)

    stamp_dir = os.path.join(paths.STAMP_DIR, self.NAME)
    log('removing %s' % stamp_dir)
    util.remove_tree(stamp_dir)

  def extract(self):
    """Extract the package archive into its build location.

    This method assumes the package has already been downloaded.
    """
    if self.is_git_upstream():
      self.git_clone()
      return

    archive = self.download_location()
    if not archive:
      self.log('Skipping extract; No upstream archive')
      return

    dest = self.get_build_location()
    output_path, new_foldername = os.path.split(dest)
    util.makedirs(output_path)

    # Check existing stamp file contents
    stamp_file = self.get_extract_stamp()
    stamp_contents = self.get_extract_stamp_content()
    if os.path.exists(dest):
      if stamp_contents_match(stamp_file, stamp_contents):
        log('Already up-to-date: %s' % util.rel_path(dest))
        return

      raise Error("Upstream archive or patch has changed.\n" +
                  "Please remove existing checkout and try again: '%s'" % dest)

    util.log_heading('Extracting')
    util.makedirs(paths.OUT_DIR)
    tmp_output_path = tempfile.mkdtemp(dir=paths.OUT_DIR)
    try:
      extract_archive(archive, tmp_output_path)
      src = os.path.join(tmp_output_path, new_foldername)
      if not os.path.isdir(src):
        raise Error('Archive contents not found: %s' % src)
      log_verbose("renaming '%s' -> '%s'" % (src, dest))
      os.rename(src, dest)
    finally:
      util.remove_tree(tmp_output_path)

    self.remove_stamps()
    write_stamp(stamp_file, stamp_contents)

  def run_cmd(self, cmd, **args):
    try:
      subprocess.check_call(cmd, stdout=sys.stdout, stderr=sys.stderr,
                            cwd=self.get_build_location(), **args)
    except subprocess.CalledProcessError as e:
      raise Error(e)

  def log(self, message):
    log('%s: %s' % (message, self.info_string()))

  def get_stamp_dir(self):
    return os.path.join(paths.STAMP_DIR, self.NAME)

  def remove_stamps(self):
    util.remove_tree(self.get_stamp_dir())

  def patch(self):
    stamp_file = os.path.join(self.get_stamp_dir(), 'nacl_patch')
    src_dir = self.get_build_location()
    if self.URL is None:
      return

    if os.path.exists(stamp_file):
      self.log('Skipping patch step (cleaning source tree)')
      cmd = ['git', 'clean', '-f', '-d']
      if not util.log_level > util.LOG_INFO:
        cmd.append('-q')
      self.run_cmd(cmd)
      return

    util.log_heading('Patching')
    init_git_repo(src_dir)
    if os.path.exists(self.get_patch_file()):
      log_verbose('applying patch to: %s' % src_dir)
      cmd = ['patch', '-p1', '-g0', '--no-backup-if-mismatch']
      with open(self.get_patch_file()) as f:
        self.run_cmd(cmd, stdin=f)
      self.run_cmd(['git', 'add', '.'])
      self.run_cmd(['git', 'commit', '-m', 'Apply webports patch'])

    write_stamp(stamp_file, '')

  def get_extract_stamp(self):
    return os.path.join(self.get_stamp_dir(), 'extract')

  def get_extract_stamp_content(self):
    patch_file = self.get_patch_file()
    if os.path.exists(patch_file):
      patch_sha = util.hash_file(self.get_patch_file())
      return 'ARCHIVE_SHA1=%s PATCH_SHA1=%s\n' % (self.SHA1, patch_sha)
    else:
      return 'ARCHIVE_SHA1=%s\n' % self.SHA1

  def get_mirror_url(self):
    return util.GS_MIRROR_URL + '/' + self.get_archive_filename()

  def check_installable(self):
    if self.DISABLED:
      raise DisabledError('%s: package is disabled' % self.NAME)

    if self.config.libc in self.DISABLED_LIBC:
      raise DisabledError('%s: cannot be built with %s' %
                          (self.NAME, self.config.libc))

    for disabled_toolchain in self.DISABLED_TOOLCHAIN:
      if '/' in disabled_toolchain:
        disabled_toolchain, arch = disabled_toolchain.split('/')
        if (self.config.arch == arch and
            self.config.toolchain == disabled_toolchain):
          raise DisabledError('%s: cannot be built with %s for %s' %
                              (self.NAME, self.config.toolchain, arch))
      else:
        if self.config.toolchain == disabled_toolchain:
          raise DisabledError('%s: cannot be built with %s' %
                              (self.NAME, self.config.toolchain))

    if self.config.arch in self.DISABLED_ARCH:
      raise DisabledError('%s: disabled for architecture: %s' %
                          (self.NAME, self.config.arch))

    if self.MIN_SDK_VERSION is not None:
      if not util.check_sdk_version(self.MIN_SDK_VERSION):
        raise DisabledError('%s: requires SDK version %s or above' %
                            (self.NAME, self.MIN_SDK_VERSION))

    if self.ARCH is not None:
      if self.config.arch not in self.ARCH:
        raise DisabledError('%s: disabled for architecture: %s' %
                            (self.NAME, self.config.arch))

    for conflicting_package in self.CONFLICTS:
      if util.is_installed(conflicting_package, self.config):
        raise PkgConflictError("%s: conflicts with installed package: %s" %
                               (self.NAME, conflicting_package))

    for dep in self.dependencies():
      try:
        dep.check_installable()
      except DisabledError as e:
        raise DisabledError('%s depends on %s; %s' % (self.NAME, dep.NAME, e))

  def conflicts(self):
    """Yields the set of SourcePackages that directly conflict with this one"""
    for dep_name in self.CONFLICTS:
      yield create_package(dep_name, self.config)

  def transitive_conflicts(self):
    rtn = set(self.conflicts())
    for dep in self.transitive_dependencies():
      rtn |= set(dep.conflicts())
    return rtn

  def dependencies(self):
    """Yields the set of SourcePackages that this package directly depends on"""
    for dep_name in self.DEPENDS:
      yield create_package(dep_name, self.config)

  def reverse_dependencies(self):
    """Yields the set of packages that depend directly on this one"""
    for pkg in source_package_iterator():
      if self.NAME in pkg.DEPENDS:
        yield pkg

  def transitive_dependencies(self):
    """Yields the set of packages that this package transitively depends on"""
    deps = []
    for dep in self.dependencies():
      for d in dep.transitive_dependencies():
        if d not in deps:
          deps.append(d)
      if dep not in deps:
        deps.append(dep)
    return deps

  def check_buildable(self):
    self.check_installable()

    if self.BUILD_OS is not None:
      if util.get_platform() != self.BUILD_OS:
        raise DisabledError('%s: can only be built on %s' %
                            (self.NAME, self.BUILD_OS))

  def git_clone_to_mirror(self):
    """Clone the upstream git repo into a local mirror. """
    git_url, git_commit = self.URL.split('@', 2)

    # Clone upstream git repo into local mirror, or update the existing
    # mirror.
    git_mirror = git_url.split('://', 2)[1]
    git_mirror = git_mirror.replace('/', '_')
    mirror_dir = os.path.join(paths.CACHE_ROOT, git_mirror)
    if os.path.exists(mirror_dir):
      if run_git_cmd(mirror_dir, ['rev-parse', git_commit + '^{commit}'],
                     error_ok=True) != 0:
        log('Updating git mirror: %s' % util.rel_path(mirror_dir))
        run_git_cmd(mirror_dir, ['remote', 'update', '--prune'])
    else:
      log('Mirroring upstream git repo: %s' % self.URL)
      run_git_cmd(paths.CACHE_ROOT, ['clone', '--mirror', git_url, git_mirror])
    log('git mirror up-to-date: %s' % util.rel_path(mirror_dir))
    return mirror_dir, git_commit

  def git_clone(self):
    """Create a clone of the upstream repo in the build directory.

    This operation will only require a network connection if the
    local git mirror is out-of-date."""
    stamp_file = self.get_extract_stamp()
    stamp_content = 'GITURL=%s' % self.URL
    patch_file = self.get_patch_file()
    if os.path.exists(patch_file):
      patch_checksum = util.hash_file(patch_file)
      stamp_content += ' PATCH=%s' % patch_checksum

    stamp_content += '\n'

    dest = self.get_build_location()
    if os.path.exists(self.get_build_location()):
      if stamp_contents_match(stamp_file, stamp_content):
        return

      raise Error('Upstream archive or patch has changed.\n' +
                  "Please remove existing checkout and try again: '%s'" % dest)

    util.log_heading('Cloning')
    # Ensure local mirror is up-to-date
    git_mirror, git_commit = self.git_clone_to_mirror()
    # Clone from the local mirror.
    run_git_cmd(None, ['clone', git_mirror, dest])
    run_git_cmd(dest, ['reset', '--hard', git_commit])

    # Set the origing to the original URL so it is possible to push directly
    # from the build tree.
    run_git_cmd(dest, ['remote', 'set-url', 'origin', self.URL.split('@')[0]])

    self.remove_stamps()
    write_stamp(stamp_file, stamp_content)

  def download_archive(self, force_mirror):
    """Download the archive to the local cache directory.

    Args:
      force_mirror: force downloading from mirror only.
    """
    filename = self.download_location()
    if not filename or os.path.exists(filename):
      return
    util.makedirs(os.path.dirname(filename))

    # Always try the mirror URL first
    mirror_url = self.get_mirror_url()
    try:
      util.download_file(filename, mirror_url)
    except Error as e:
      if not force_mirror:
        # Fall back to the original upstream URL
        util.download_file(filename, self.URL)
      else:
        raise e

  def update_patch(self):
    if self.URL is None:
      return

    git_dir = self.get_build_location()
    if not os.path.exists(git_dir):
      raise Error('Source directory not found: %s' % git_dir)

    try:
      diff = subprocess.check_output(
          ['git', 'diff', 'upstream', '--no-ext-diff'], cwd=git_dir)
    except subprocess.CalledProcessError as e:
      raise Error('error running git in %s: %s' % (git_dir, str(e)))

    # Drop index lines for a more stable diff.
    diff = re.sub('\nindex [^\n]+\n', '\n', diff)

    # Drop binary files, as they don't work anyhow.
    diff = re.sub('diff [^\n]+\n'
                  '(new file [^\n]+\n)?'
                  '(deleted file mode [^\n]+\n)?'
                  'Binary files [^\n]+ differ\n', '', diff)

    # Always filter out config.sub changes
    diff_skip = ['*config.sub']

    # Add optional per-port skip list.
    diff_skip_file = os.path.join(self.root, 'diff_skip.txt')
    if os.path.exists(diff_skip_file):
      with open(diff_skip_file) as f:
        diff_skip += f.read().splitlines()

    new_diff = ''
    skipping = False
    for line in diff.splitlines():
      if line.startswith('diff --git a/'):
        filename = line[len('diff --git a/'):].split()[0]
        skipping = False
        for skip in diff_skip:
          if fnmatch.fnmatch(filename, skip):
            skipping = True
            break
      if not skipping:
        new_diff += line + '\n'
    diff = new_diff

    # Write back out the diff.
    patch_path = self.get_patch_file()
    preexisting = os.path.exists(patch_path)

    if not diff:
      if preexisting:
        log('removing patch file: %s' % util.rel_path(patch_path))
        os.remove(patch_path)
      else:
        log('no patch required: %s' % util.rel_path(git_dir))
      return

    if preexisting:
      with open(patch_path) as f:
        if diff == f.read():
          log('patch unchanged: %s' % util.rel_path(patch_path))
          return

    with open(patch_path, 'w') as f:
      f.write(diff)

    if preexisting:
      log('created patch: %s' % util.rel_path(patch_path))
    else:
      log('updated patch: %s' % util.rel_path(patch_path))


def source_package_iterator():
  """Iterator which yields a Package object for each webports package."""
  ports_root = os.path.join(paths.NACLPORTS_ROOT, 'ports')
  for root, dirs, files in os.walk(ports_root):
    # Sort files and dirs so that the iterator reports packages in a
    # consistent order.
    dirs.sort()
    files.sort()
    if 'pkg_info' in files:
      yield SourcePackage(root)


DEFAULT_LOCATIONS = ('ports', 'ports/python_modules')


def create_package(package_name, config=None):
  """Create a Package object given a package name or path.

  Returns:
    Package object
  """
  if os.path.isdir(package_name):
    return SourcePackage(package_name, config)

  for subdir in DEFAULT_LOCATIONS:
    pkg_root = os.path.join(paths.NACLPORTS_ROOT, subdir, package_name)
    info = os.path.join(pkg_root, 'pkg_info')
    if os.path.exists(info):
      return SourcePackage(pkg_root, config)

  raise Error("Package not found: %s" % package_name)
