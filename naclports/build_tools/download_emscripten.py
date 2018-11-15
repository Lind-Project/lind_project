#!/usr/bin/env python
# Copyright 2015 The Native Client Authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.
"""Download the Emscripten SDK for the current platform.

This script downloads the emscripten tarball and expands it.
It requires gsutil to be in the bin PATH and is currently
supported on Linux and Mac OSX and not windows.
"""

import os
import subprocess
import sys
import tarfile

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
NACLPORTS_ROOT = os.path.dirname(SCRIPT_DIR)
sys.path.append(os.path.join(NACLPORTS_ROOT, 'lib'))

import webports
import webports.source_package
import webports.util

MIRROR_URL = '%s%s/prebuilt/emscripten' % (webports.util.GS_URL,
                                           webports.util.GS_BUCKET)

EMSDK_SHA1 = '89c962d5f06c874f63b06917913e2071d45e3c2e'
EMSDK_URL = MIRROR_URL + '/emsdk-20150817.tar.gz'

NODE_SHA1 = '79880ff2bc95a674bd0701a6dd4ed38f8366db27'
NODE_URL = MIRROR_URL + '/node-v0.12.1-linux-x64.tar.gz'

SCRIPT_DIR = os.path.abspath(os.path.dirname(__file__))
SRC_DIR = os.path.dirname(SCRIPT_DIR)
OUT_DIR = os.path.join(SRC_DIR, 'out')
TARGET_DIR = os.path.join(OUT_DIR, 'emscripten_sdk')


def download_to_cache(url, sha1):
  filename = os.path.basename(url)
  download_dir = webports.paths.CACHE_ROOT
  if not os.path.exists(download_dir):
    os.makedirs(download_dir)
  full_name = os.path.join(download_dir, filename)
  if os.path.exists(full_name):
    try:
      webports.util.verify_hash(full_name, sha1)
      webports.log("Verified cached file: %s" % filename)
      return full_name
    except webports.util.HashVerificationError:
      webports.log("Hash mistmatch on cached download: %s" % filename)

  webports.download_file(full_name, url)
  webports.util.verify_hash(full_name, sha1)
  return full_name


def download_and_extract(url, sha1, target_dir, link_name=None):
  tar_file = download_to_cache(url, sha1)

  if not os.path.exists(OUT_DIR):
    os.makedirs(OUT_DIR)

  os.chdir(OUT_DIR)

  # Remove previously extracted archive
  if os.path.exists(target_dir):
    webports.log('Cleaning up existing %s...' % target_dir)
    cmd = ['rm', '-rf']
    cmd.append(target_dir)
    subprocess.check_call(cmd)

  # Extract archive
  webports.log('Exctacting %s...' % os.path.basename(tar_file))
  if subprocess.call(['tar', 'xf', tar_file]):
    raise webports.Error('Error unpacking Emscripten SDK')

  if link_name:
    if os.path.exists(link_name):
      os.remove(link_name)
    os.symlink(target_dir, link_name)


def build_optimizer():
  emsdk_root = os.path.join(OUT_DIR, 'emsdk')
  node_bin = os.path.join(OUT_DIR, 'node', 'bin')
  emscripten_root = os.path.join(emsdk_root, 'emscripten')
  os.environ['EMSDK_ROOT'] = emscripten_root
  os.environ['EM_CONFIG'] = os.path.join(emsdk_root, '.emscripten')
  os.environ['PATH'] += ':' + node_bin
  os.environ['PATH'] += ':' + emscripten_root

  # Run using -O2 to compile the native js-optimizer
  open('test.c', 'w').close()
  subprocess.check_call(['emcc', '-O2', '-o', 'test.js', 'test.c'])
  os.remove('test.js')
  os.remove('test.c')
  return 0


def main(argv):
  if sys.platform in ['win32', 'cygwin']:
    webports.Error('Emscripten support is currently not available on Windows.')
    return 1

  download_and_extract(EMSDK_URL, EMSDK_SHA1, 'emsdk')
  download_and_extract(NODE_URL, NODE_SHA1, 'node-v0.12.1-linux-x64', 'node')
  build_optimizer()

  webports.log('Emscripten SDK Install complete')
  return 0


if __name__ == '__main__':
  try:
    rtn = main(sys.argv[1:])
  except webports.Error as e:
    sys.stderr.write('error: %s\n' % str(e))
    rtn = 1
  sys.exit(rtn)
