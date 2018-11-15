# Copyright (c) 2014 The Native Client Authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.
"""Test harness for testing chrome apps / extensions."""

import argparse
import cStringIO
import contextlib
import hashlib
import logging
import os
import shutil
import subprocess
import sys
import tempfile
import threading
import urllib
import urllib2
import urlparse

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
SRC_DIR = os.path.dirname(SCRIPT_DIR)
sys.path.insert(0, os.path.join(SRC_DIR, 'build_tools'))
sys.path.insert(0, os.path.join(SRC_DIR, 'lib'))

import httpd
import download_chrome

# Pinned chrome revision. Update this to pull in a new chrome.
# Try to select a version that exists on all platforms.
CHROME_REVISION = '344999'

TESTING_LIB = os.path.join(SCRIPT_DIR, 'chrome_test.js')
TESTING_EXTENSION = os.path.join(SCRIPT_DIR, 'extension')
TESTING_TCP_APP = os.path.join(SCRIPT_DIR, 'tcpapp')

RETURNCODE_KILL = -9

LOG_LEVEL_MAP = {
    'ERROR': logging.ERROR,
    'WARNING': logging.WARNING,
    'INFO': logging.INFO,
    'DEBUG': logging.DEBUG,
}


def chrome_run_path(chrome_dir, arch):
  """Get the path to the chrome exectuable.

  Args:
    chrome_dir: Root directory of chrome installation
    arch: Chrome architecture to select i686/x86_64.
  Returns:
    Path to the chrome executable.
  """
  if sys.platform == 'win32':
    path = 'chrome.exe'
  elif sys.platform == 'darwin':
    path = 'Chromium.app/Contents/MacOS/Chromium'
  elif sys.platform.startswith('linux'):
    path = 'chrome-wrapper'
  else:
    logging.error('Unknown platform: %s' % sys.platform)
    sys.exit(1)
  return os.path.join(chrome_dir, path)


def kill_subprocess_and_children(proc):
  """Kill a subprocess and all children.

  While this is trivial on Posix platforms, on Windows this requires some
  method for walking the process tree. Relying on this functionality in
  the taskkill.exe utility for now.

  Args:
    proc: A subprocess.Popen process.
  """
  if sys.platform == 'win32':
    # Do subprocess call as the process may terminate before we manage
    # to invoke taskkill.
    subprocess.call(
        [os.path.join(os.environ['SYSTEMROOT'], 'System32', 'taskkill.exe'),
         '/F', '/T', '/PID', str(proc.pid)])
  else:
    # Send SIGKILL=9 to the entire process group associated with the child.
    os.kill(-proc.pid, 9)


def communicate_with_timeout(proc, timeout):
  """Wait for a subprocess.Popen to end, capturing output, with a timeout.

  Args:
    proc: A subprocess.Popen.
    timeout: A timeout in seconds.
  Returns:
    (stdout, stderr, returncode).
  """
  if timeout == 0:
    timeout = None

  result = []

  def target():
    result.append(list(proc.communicate()))

  thread = threading.Thread(target=target)
  thread.start()
  try:
    thread.join(timeout)
    if thread.is_alive():
      logging.error('Attempting to kill test due to timeout of %.1f seconds!' %
                    timeout)
      # This will kill the process which should force communicate to return with
      # any partial output.
      kill_subprocess_and_children(proc)
      # Thus result should ALWAYS contain something after this join.
      thread.join()
      logging.error('Killed test due to timeout of %.1f seconds!' % timeout)
      # Also append to stderr (or stdout).
      msg = '\n\nKilled test due to timeout of %.1f seconds!\n' % timeout
      if result[0][1] is not None:
        result[0][1] += msg
      else:
        result[0][0] += msg
      returncode = RETURNCODE_KILL
    else:
      returncode = proc.returncode
  finally:
    # In case something else goes wrong, be sure to bring down the child.
    if thread.is_alive():
      kill_subprocess_and_children(proc)
  assert len(result) == 1
  return tuple(result[0]) + (returncode,)


class ChromeTestServer(httpd.QuittableHTTPServer):
  """An HTTP server that keeps a count of test results."""

  def __init__(self, server_address, handler):
    self.tests = set()
    self.test_results = 0
    self.result = 0
    self.failed_tests = set()
    self.last_test = None
    self.expected_test_count = None
    self.roots = []
    self.filter_string = '*'
    httpd.QuittableHTTPServer.__init__(self, server_address, handler)

  def add_root(self, path):
    self.roots.append(os.path.abspath(path))

  def set_filter_string(self, filter_string):
    self.filter_string = filter_string


class ChromeTestHandler(httpd.QuittableHTTPHandler):
  """An HTTP request handler that gathers test results."""

  def send_empty_reply(self):
    self.send_response(200, 'OK')
    self.send_header('Content-type', 'text/html')
    self.send_header('Content-length', '0')
    self.end_headers()

  def translate_path(self, path):
    cwd = os.getcwd()
    tpath = httpd.QuittableHTTPHandler.translate_path(self, path)
    rpath = os.path.relpath(tpath, cwd)
    hit = []
    for root in self.server.roots:
      npath = os.path.join(root, rpath)
      if os.path.exists(npath):
        hit.append(npath)
    if len(hit) == 0:
      # Use first root if there is not match, to allow usual favicon.ico
      # handling.
      return os.path.join(self.server.roots[0], rpath)
    if len(hit) > 1:
      raise Exception('Duplicate resource at path: %s' % rpath)
    return hit[0]

  def do_GET(self):
    parts = self.path.rsplit('?')
    # Provide a js test library at a fixed location.
    if parts[0] == '/_chrome_test.js':
      test_lib = open(TESTING_LIB).read()
      self.send_response(200, 'OK')
      self.send_header('Content-type', 'text/html')
      self.send_header('Content-length', str(len(test_lib)))
      self.end_headers()
      self.wfile.write(test_lib)
      return
    # Check for a set of special command from the running tests.
    if len(parts) == 2 and parts[0] == '/_command':
      params = urlparse.parse_qs(parts[1])
      # Allow the tests to send out log messages.
      if ('log' in params and len(params['log']) == 1 and
          'level' in params and len(params['level']) == 1):
        level = LOG_LEVEL_MAP.get(params['level'][0], logging.ERROR)
        message = params['log'][0]
        if message[-1] == '\n':
          message = message[:-1]
        logging.log(level, message)
        self.send_empty_reply()
        return
      # Allow the tests to request the current test filter string.
      elif ('filter' in params and len(params['filter']) == 1 and
            params['filter'][0] == '1'):
        self.send_response(200, 'OK')
        self.send_header('Content-type', 'text/html')
        self.send_header('Content-length', str(len(self.server.filter_string)))
        self.end_headers()
        self.wfile.write(self.server.filter_string)
        return
      # Allow the tests to declare their name on start.
      elif ('start' in params and len(params['start']) == 1 and
            params['start'][0] == '1' and 'name' in params and
            len(params['name']) == 1):
        name = params['name'][0]
        if name in self.server.tests:
          result = 1
          print '[ DUP!!!   ] Duplicate test: %s' % name
        else:
          self.server.tests.add(name)
          print '[ RUN      ] %s' % name
        self.server.last_test = name
        self.send_empty_reply()
        return
      # Allow the tests to post (pass/fail) results.
      elif ('result' in params and len(params['result']) == 1 and
            'name' in params and len(params['name']) == 1 and
            'duration' in params and len(params['duration']) == 1):
        name = params['name'][0]
        result = params['result'][0]
        duration = params['duration'][0]
        if self.server.last_test != name:
          self.server.result = 1
          print '[ ERR!!!   ] Return from unexpected test: %s' % name
        if result == '1':
          print '[       OK ] %s (%s)' % (name, duration)
        else:
          self.server.result = 1
          self.server.failed_tests.add(name)
          print '[  FAILED  ] %s (%s)' % (name, duration)
        self.server.last_test = None
        self.server.test_results += 1
        self.send_empty_reply()
        return
      # Allow the test set to announce the number of tests it will run.
      elif 'test_count' in params and len(params['test_count']) == 1:
        assert self.server.expected_test_count is None
        self.server.expected_test_count = int(params['test_count'][0])
        self.send_empty_reply()
        return
    # Fall back to a providing normal HTTP access.
    httpd.QuittableHTTPHandler.do_GET(self)

  def log_message(self, fmt, *args):
    if logging.getLogger().isEnabledFor(logging.DEBUG):
      httpd.QuittableHTTPHandler.log_message(self, fmt, *args)


def hex_to_alpha(ch):
  """Convert a hexadecimal digit from 0-9 / a-f to a-p.

  Args:
    ch: a character in 0-9 / a-f.
  Returns:
    A character in a-p.
  """
  if ch >= '0' and ch <= '9':
    return chr(ord(ch) - ord('0') + ord('a'))
  else:
    return chr(ord(ch) + 10)


def chrome_app_id_from_path(path):
  """Converts a path to the corresponding chrome app id.

  A stable but semi-undocumented property of unpacked chrome extensions is
  that they are assigned an app-id based on the first 32 characters of the
  sha256 digest of the absolute symlink expanded path of the extension.
  Instead of hexadecimal digits, characters a-p.
  From discussion with webstore team + inspection of extensions code.
  Args:
    path: Path to an unpacked extension.
  Returns:
    A 32 character chrome extension app id.
  """
  hasher = hashlib.sha256(os.path.realpath(path))
  hexhash = hasher.hexdigest()[:32]
  return ''.join([hex_to_alpha(ch) for ch in hexhash])


def run_chrome(chrome_path, timeout, filter_string, roots, use_xvfb,
               unlimited_storage, enable_nacl, enable_nacl_debug,
               load_extensions, load_apps, start_path):
  """Run Chrome with a timeout and several options.

  Args:
    chrome_path: Path to the chrome executable.
    timeout: Timeout in seconds.
    filter_string: Filter string to select which tests to run.
    roots: Directories to serve test from.
    use_xvfb: Boolean indicating if xvfb should be used.
    unlimited_storage: Boolean indicating if chrome should be run with
                       unlimited storage.
    enable_nacl: Boolean indicating that NaCl should be enabled on regular
                 pages.
    enable_nacl_debug: Boolean indicating that NaCl debugging should be
                       enabled.
    load_extensions: A list of unpacked extensions paths to load on start.
    load_apps: A list of unpacked apps to load on start.
    start_path: The path relative to the current directory to point the browser
                at on startup.
  """
  # Ensure all extension / app paths are absolute.
  load_extensions = [os.path.abspath(os.path.expanduser(i))
                     for i in load_extensions]
  load_apps = [os.path.abspath(os.path.expanduser(i)) for i in load_apps]

  # Add in the chrome_test extension and compute its id.
  load_extensions += [TESTING_EXTENSION, TESTING_TCP_APP]
  testing_id = chrome_app_id_from_path(TESTING_EXTENSION)

  s = ChromeTestServer(('', 0), ChromeTestHandler)
  for root in roots:
    s.add_root(root)
  s.set_filter_string(filter_string)

  def target():
    s.serve_forever(poll_interval=0.1)

  base_url = 'http://%s:%d' % (s.server_address[0], s.server_address[1])
  quit_url = '%s/?quit=1' % base_url
  start_url = '%s/%s' % (base_url, start_path)

  logging.info('Started web server at %s' % base_url)

  returncode = RETURNCODE_KILL
  try:
    work_dir = tempfile.mkdtemp(prefix='chrome_test_', suffix='.tmp')
    work_dir = os.path.abspath(work_dir)
    logging.info('Created work area in %s' % work_dir)
    try:
      thread = threading.Thread(target=target)
      thread.start()

      cmd = []
      if sys.platform.startswith('linux') and use_xvfb:
        cmd += ['xvfb-run', '--auto-servernum', '-s',
                '-screen 0 1024x768x24 -ac']
      cmd += [chrome_path]
      cmd += ['--user-data-dir=' + work_dir]
      # We want to pin the pnacl component to the one that we downloaded.
      # This allows us to test features of the pnacl translator that are
      # not yet in the public component.
      cmd += ['--disable-component-update']
      # Pass testing extension id in user agent to make it widely available.
      # TODO(bradnelson): Drop this when hterm is fixed.
      # Hterm currently expects "Chrome/[0-9][0-9]" in the User Agent and
      # faults without it. Using "Chrome/34" so that it goes down one of the
      # more sensible of its version based code paths.
      cmd += ['--user-agent=ChromeTestAgent/' + testing_id + ' Chrome/34']
      if unlimited_storage:
        cmd += ['--unlimited-storage']
      if enable_nacl:
        cmd += ['--enable-nacl']
      if enable_nacl_debug:
        cmd += ['--enable-nacl-debug']
      if len(load_extensions) != 0:
        cmd += ['--load-extension=' + ','.join(load_extensions)]
      if len(load_apps) != 0:
        cmd += ['--load-and-launch-app=' + ','.join(load_apps)]
      cmd += [start_url]

      def process_group():
        if sys.platform != 'win32':
          # On non-windows platforms, start a new process group so that we can
          # be certain we bring down Chrome on a timeout.
          os.setpgid(0, 0)

      p = subprocess.Popen(cmd, stdout=subprocess.PIPE,
                           stderr=subprocess.STDOUT, preexec_fn=process_group)
      logging.info('Started chrome with command line: %s' % (' '.join(cmd)))
      stdout, _, returncode = communicate_with_timeout(p, timeout=timeout)
      if logging.getLogger().isEnabledFor(logging.DEBUG):
        sys.stdout.write('\n[[[ STDOUT ]]]\n')
        sys.stdout.write('-' * 70 + '\n')
        sys.stdout.write(stdout)
        sys.stdout.write('\n' + '-' * 70 + '\n')
      logging.info('Chrome exited with return code %d' % returncode)
    finally:
      try:
        with contextlib.closing(urllib2.urlopen(quit_url)) as stream:
          stream.read()
      except Exception:
        pass
    thread.join()
    logging.info('Shutdown web server.')
  finally:
    shutil.rmtree(work_dir)
    logging.info('Removed %s' % work_dir)
  logging.info('Done.')

  if returncode == RETURNCODE_KILL:
    print '[ TIMEOUT   ] Timed out, ran %d tests, %d failed.' % (
        len(s.tests), len(s.failed_tests))
    sys.exit(1)
  elif s.expected_test_count is None:
    print('[ XXXXXXXX ] Expected test count never emitted.')
    sys.exit(1)
  elif s.test_results != s.expected_test_count:
    print('[ XXXXXXXX ] '
          'Expected %d tests, but only %d had results, with %d failures.' % (
              s.expected_test_count, s.test_results, len(s.failed_tests)))
    sys.exit(1)
  elif s.result != 0:
    print '[ Failures ] Ran %d tests, %d failed.' % (len(s.tests),
                                                     len(s.failed_tests))
    sys.exit(1)
  else:
    print '[ Success! ] Ran %d tests.' % len(s.tests)


def main(argv):
  """Main method to invoke in test harness programs.
  Args:
    argv: Command line options controlling what to run.
          See --help.
  NOTE: Ends the process with sys.exit(1) on failure.
  """
  parser = argparse.ArgumentParser(description=__doc__)
  parser.add_argument('start_path', metavar='START_PATH',
                      help='location in which to run tests')
  parser.add_argument('-x', '--xvfb', action='store_true',
                      help='Run Chrome thru xvfb on Linux.')
  parser.add_argument('-a', '--arch', default='x86_64',
                      choices=['x86_64', 'i686'], help='Chrome architecture.')
  parser.add_argument('-v', '--verbose', default=0, action='count',
                      help='Emit verbose output, use twice for more.')
  parser.add_argument('-t', '--timeout', default=30, type=float,
                      help='Timeout for all tests (in seconds).')
  parser.add_argument('-C', '--chdir', default=[], action='append',
                      help='Add a root directory.')
  parser.add_argument('--load-extension', default=[], action='append',
                      help='Add an extension to load on start.')
  parser.add_argument('--load-and-launch-app', default=[], action='append',
                      help='Add an app to load on start.')
  parser.add_argument('--unlimited-storage', default=False, action='store_true',
                      help='Allow unlimited storage.')
  parser.add_argument('--enable-nacl', default=False, action='store_true',
                      help='Enable NaCl generally.')
  parser.add_argument('--enable-nacl-debug', default=False, action='store_true',
                      help='Enable NaCl debugging.')
  parser.add_argument('-f', '--filter', default='*', help='Filter on tests.')
  parser.add_argument(
      '-p', '--param', default=[], action='append',
      help='Add a parameter to the end of the url, = separated.')
  options = parser.parse_args(argv)

  if options.param:
    params = {}
    params['SYS_ARCH'] = options.arch
    for param in options.param:
      key, value = param.split('=', 1)
      params[key] = value
    options.start_path += '?' + urllib.urlencode(params)

  if options.verbose > 1:
    logging.getLogger().setLevel(logging.DEBUG)
  elif options.verbose > 0:
    logging.getLogger().setLevel(logging.INFO)
  else:
    logging.getLogger().setLevel(logging.WARNING)
  logging.basicConfig(format='%(asctime)-15s %(levelname)s: %(message)s',
                      datefmt='%Y-%m-%d %H:%M:%S')
  if not options.chdir:
    options.chdir.append('.')

  if sys.platform.startswith('linux'):
    default_sandbox_locations = [
      '/usr/local/sbin/chrome-devel-sandbox',
      '/opt/chromium/chrome_sandbox',
      '/opt/google/chrome-beta/chrome-sandbox'
    ]
    if 'CHROME_DEVEL_SANDBOX' not in os.environ:
      for filename in default_sandbox_locations:
        if os.path.exists(filename):
          os.environ['CHROME_DEVEL_SANDBOX'] = filename
          break
      else:
        logging.error('chrome_test on linux requires CHROME_DEVEL_SANDBOX')
        sys.exit(1)
    if not os.path.exists(os.environ['CHROME_DEVEL_SANDBOX']):
      logging.error('chrome sandbox specified by CHROME_DEVEL_SANDBOX is '
                    'missing: %s' % os.environ['CHROME_DEVEL_SANDBOX'])
      sys.exit(1)

  chrome_dir = download_chrome.download_chrome(options.arch, CHROME_REVISION)
  run_chrome(chrome_path=chrome_run_path(chrome_dir, options.arch),
             timeout=options.timeout, filter_string=options.filter,
             roots=options.chdir, use_xvfb=options.xvfb,
             unlimited_storage=options.unlimited_storage,
             enable_nacl=options.enable_nacl,
             enable_nacl_debug=options.enable_nacl_debug,
             load_extensions=options.load_extension,
             load_apps=options.load_and_launch_app,
             start_path=options.start_path)
  sys.exit(0)
