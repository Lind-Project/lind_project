#!/usr/bin/env python
# Copyright 2015 The Native Client Authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.
"""Scan online pkg packages and download all files

This script is intended to be run periodically and is called
by build_repo.sh script to build repository.
"""

from __future__ import print_function

import argparse
import os
import re
import subprocess
import sys

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
sys.path.append(os.path.join(os.path.dirname(SCRIPT_DIR), 'lib'))

import webports

from scan_packages import find_gsutil, parse_gs_util_output, \
  format_size, check_hash, get_hash
from webports.util import log, log_verbose


def download_files(pkg_dir, files, check_hashes=True, parallel=False):
  """Download one of more files to the local disk.

  Args:
    files: List of FileInfo objects to download.
    check_hashes: When False assume local files have the correct
    hash otherwise always check the hashes match the onces in the
    FileInfo ojects.

  Returns:
    List of (filename, url) tuples.
  """
  files_to_download = []
  filenames = []
  download_dir = os.path.join(webports.package_index.PREBUILT_ROOT, 'pkg',
                              pkg_dir)
  if not os.path.exists(download_dir):
    os.makedirs(download_dir)

  for file_info in files:
    basename = os.path.basename(file_info.url)
    # TODO(bradnelson): The pnacl package is >2GB, which confuses pkg.
    #                   Figure out why and re-enable this.
    if basename == 'pnacl-0.0.1.tbz':
      continue
    file_info.name = os.path.join(download_dir, basename)
    file_info.rel_name = file_info.name[len(webports.paths.NACLPORTS_ROOT) + 1:]
    filenames.append((file_info.name, file_info.url))
    if os.path.exists(file_info.name):
      if not check_hashes or check_hash(file_info.name, file_info.md5):
        log('Up-to-date: %s' % file_info.rel_name)
        continue
    files_to_download.append(file_info)

  def check(file_info):
    if check_hashes and not check_hash(file_info.name, file_info.md5):
      raise webports.Error(
          'Checksum failed: %s\nExpected=%s\nActual=%s' %
          (file_info.rel_name, file_info.md5, get_hash(file_info.name)))

  if not files_to_download:
    log('All files up-to-date')
  else:
    total_size = sum(f.size for f in files_to_download)
    log('Need to download %d/%d files [%s]' %
        (len(files_to_download), len(files), format_size(total_size)))

    gsutil = find_gsutil()
    if parallel:
      remaining_files = files_to_download
      num_files = 20
      while remaining_files:
        files = remaining_files[:num_files]
        remaining_files = remaining_files[num_files:]
        cmd = gsutil + ['-m', 'cp'] + [f.gsurl for f in files] + [download_dir]
        log_verbose(cmd)
        subprocess.check_call(cmd)
        for file_info in files:
          check(file_info)
    else:
      for file_info in files_to_download:
        webports.download_file(file_info.name, file_info.url)
        check(file_info)

  return filenames


def main(args):
  parser = argparse.ArgumentParser(description=__doc__)
  parser.add_argument('revision', metavar='REVISION',
                      help='webports revision to to scan for.')
  parser.add_argument('-v', '--verbose', action='store_true',
                      help='Output extra information.')
  parser.add_argument('-p', '--parallel', action='store_true',
                      help='Download packages in parallel.')
  parser.add_argument('-l', '--cache-listing', action='store_true',
                      help='Cached output of gsutil -L (for testing).')
  parser.add_argument('--skip-md5', action='store_true',
                      help='Assume on-disk files are up-to-date (for testing).')
  args = parser.parse_args(args)
  if args.verbose:
    webports.set_verbose(True)

  sdk_version = webports.util.get_sdk_version()
  log('Scanning packages built for pepper_%s at revsion %s' %
      (sdk_version, args.revision))
  base_path = '%s/builds/pepper_%s/%s/publish' % (webports.GS_BUCKET,
                                                  sdk_version, args.revision)
  gs_base_url = 'gs://' + base_path
  cmd = find_gsutil() + ['ls', gs_base_url]
  log_verbose('Running: %s' % str(cmd))
  try:
    all_published = subprocess.check_output(cmd)
  except subprocess.CalledProcessError as e:
    raise webports.Error("Command '%s' failed: %s" % (cmd, e))

  pkg_dir = re.findall(r'pkg_[\w-]+', all_published)
  for pkg in pkg_dir:
    listing_file = os.path.join(webports.NACLPORTS_ROOT, 'lib',
                                pkg + '_' + 'listing.txt')
    if args.cache_listing and os.path.exists(listing_file):
      log('Using pre-cached gs listing: %s' % listing_file)
      with open(listing_file) as f:
        listing = f.read()
    else:
      gs_url = gs_base_url + '/' + pkg + '/*'
      log('Searching for packages at: %s' % gs_url)
      cmd = find_gsutil() + ['stat', gs_url]
      log_verbose('Running: %s' % str(cmd))
      try:
        listing = subprocess.check_output(cmd)
      except subprocess.CalledProcessError as e:
        raise webports.Error("Command '%s' failed: %s" % (cmd, e))
      if args.cache_listing:
        with open(listing_file, 'w') as f:
          f.write(listing)
    all_files = parse_gs_util_output(listing)
    log('Found %d packages [%s] for %s' %
        (len(all_files), format_size(sum(f.size for f in all_files)), pkg))
    download_files(pkg, all_files, not args.skip_md5, args.parallel)
  log('Done')
  return 0


if __name__ == '__main__':
  try:
    sys.exit(main(sys.argv[1:]))
  except webports.Error as e:
    sys.stderr.write('%s\n' % e)
    sys.exit(-1)
