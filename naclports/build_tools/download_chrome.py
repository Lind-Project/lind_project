#!/usr/bin/env python
# Copyright 2015 The Native Client Authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.
"""Download the a build of chrome from Google Clound Storage."""

import argparse
import logging
import os
import shutil
import sys
import zipfile

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
SRC_DIR = os.path.dirname(SCRIPT_DIR)
sys.path.insert(0, os.path.join(SRC_DIR, 'lib'))

import webports

GS_URL = 'http://storage.googleapis.com'
CHROME_URL_FORMAT = GS_URL + '/chromium-browser-continuous/%s/%s/%s'
CHROME_DOWNLOAD_DIR = os.path.join(webports.paths.OUT_DIR, 'downloaded_chrome')


def chrome_dir(arch):
  """Get the directory to download chrome to."""
  return os.path.join(CHROME_DOWNLOAD_DIR, arch)


def chrome_archive_root():
  if sys.platform == 'win32':
    return 'chrome-win32'
  elif sys.platform == 'darwin':
    return 'chrome-mac'
  elif sys.platform.startswith('linux'):
    return 'chrome-linux'
  else:
    raise webports.error.Error('Unknown platform: %s' % sys.platform)


def chrome_url(arch, revision):
  """Get the URL to download chrome from.

  Args:
    arch: Chrome architecture to select i686/x86_64/pnacl.
  Returns:
    URL to download a zip file from.
  """
  if sys.platform == 'win32':
    filename = 'chrome-win32.zip'
    target = 'Win_x64'
  elif sys.platform == 'darwin':
    filename = 'chrome-mac.zip'
    target = 'Mac'
  elif sys.platform.startswith('linux'):
    filename = 'chrome-linux.zip'
    if arch == 'i686':
      target = 'Linux'
    elif arch == 'x86_64' or arch == 'pnacl':
      # Arbitrarily decide we will use 64-bit Linux for PNaCl.
      target = 'Linux_x64'
    else:
      logging.error('Bad architecture %s' % arch)
      sys.exit(1)
  else:
    logging.error('Unsupported platform %s' % sys.platform)
    sys.exit(1)
  return CHROME_URL_FORMAT % (target, revision, filename)


def do_download(url, destination):
  """Download chrome.

  Download chrome to a particular destination, leaving a stamp containing the
  download URL. Download is skipped if the stamp matches the URL.
  Args:
    url: URL to download chrome from.
    destination: A directory to download chrome to.
  """
  stamp_filename = os.path.join(destination, 'STAMP')
  # Change this line each time the mods we make to the chrome checkout change
  # otherwise the modding code will be skipped.
  stamp_content = 'mods_v2:' + url
  if os.path.exists(stamp_filename):
    with open(stamp_filename) as f:
      if f.read() == stamp_content:
        logging.info('Skipping chrome download, '
                     'chrome in %s is up to date' % destination)
        return
  if os.path.exists(destination):
    logging.info('Deleting old chrome...')
    shutil.rmtree(destination)

  logging.info('Creating %s' % destination)
  os.makedirs(destination)

  logging.info('Downloading chrome from %s to %s...' % (url, destination))
  chrome_zip = os.path.join(webports.paths.CACHE_ROOT, os.path.basename(url))
  webports.util.makedirs(os.path.dirname(chrome_zip))
  try:
    webports.util.download_file(chrome_zip, url)
  except webports.error.Error as e:
    logging.error('Unable to download chrome: %s' % str(e))
    sys.exit(1)

  pnacl_url = os.path.join(os.path.dirname(url), 'pnacl.zip')
  pnacl_zip = os.path.join(webports.paths.CACHE_ROOT, 'pnacl.zip')
  logging.info('Downloading pnacl component from %s ...' % url)
  try:
    webports.util.download_file(pnacl_zip, pnacl_url)
  except webports.error.Error as e:
    logging.error('Unable to download chrome: %s' % str(e))
    sys.exit(1)

  logging.info('Extracting %s' % chrome_zip)
  with zipfile.ZipFile(chrome_zip) as zip_archive:
    zip_archive.extractall(destination)
    # Change the executables to be executable.
    for root, _, files in os.walk(destination):
      for filename in files:
        if (filename.startswith('Chromium') or
            filename in ('chrome-wrapper', 'chrome', 'nacl_helper',
                         'nacl_helper_bootstrap')):
          path = os.path.join(root, filename)
          os.chmod(path, 0755)

    if sys.platform.startswith('linux'):
      if '64' in url:
        libudev0 = '/lib/x86_64-linux-gnu/libudev.so.0'
        libudev1 = '/lib/x86_64-linux-gnu/libudev.so.1'
      else:
        libudev0 = '/lib/i386-linux-gnu/libudev.so.0'
        libudev1 = '/lib/i386-linux-gnu/libudev.so.1'
      if os.path.exists(libudev1) and not os.path.exists(libudev0):
        link = os.path.join(destination, 'chrome-linux', 'libudev.so.0')
        logging.info('creating link %s' % link)
        os.symlink(libudev1, link)

  logging.info('Extracting %s' % pnacl_zip)
  with zipfile.ZipFile(pnacl_zip) as zip_archive:
    zip_archive.extractall(destination)

  chrome_root = os.path.join(destination, chrome_archive_root())
  pnacl_root = os.path.join(destination, 'pnacl', 'pnacl')
  logging.info('Renaming pnacl directory %s -> %s' % (pnacl_root, chrome_root))
  os.rename(pnacl_root, os.path.join(chrome_root, 'pnacl'))

  logging.info('Writing stamp...')
  with open(stamp_filename, 'w') as fh:
    fh.write(stamp_content)
  logging.info('Done.')


def download_chrome(arch, revision):
  target_dir = chrome_dir(arch)
  do_download(chrome_url(arch, revision), target_dir)
  return os.path.join(target_dir, chrome_archive_root())


def run_main(argv):
  parser = argparse.ArgumentParser(prog='download_chrome', description=__doc__)
  parser.add_argument('-a', '--arch', default='x86_64',
                      choices=['x86_64', 'i686'], help='Chrome architecture.')
  logging.basicConfig(format='%(message)s', level=logging.INFO)
  parser.add_argument('revision')
  options = parser.parse_args(argv)
  dirname = download_chrome(options.arch, options.revision)
  logging.info('Chrome %s downloaded to: %s' % (options.revision, dirname))
  return 0


def main(argv):
  try:
    return run_main(argv)
  except KeyboardInterrupt:
    sys.stderr.write('interrupted\n')
    return 1
  except webports.error.Error as e:
    if os.environ.get('DEBUG'):
      raise
    sys.stderr.write(str(e) + '\n')
    return 1


if __name__ == '__main__':
  sys.exit(main(sys.argv[1:]))
