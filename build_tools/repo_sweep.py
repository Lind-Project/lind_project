#!/usr/bin/env python
# Copyright (c) 2015 The Native Client Authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.

"""Generate repos for completed webports builds.

Scan the GSD bucket associated with webports for builds which have
been around for move than a few hours and which lack pkg repository
metadata. Run build_repo.sh on each of them.
"""

import datetime
import os
import subprocess
import sys


SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
AGE_LIMIT = 8 * 60 * 60  # 8 hours


def get_pepper_versions():
  output = subprocess.check_output(['gsutil', 'ls', 'gs://webports/builds'])
  names = [i.split('/')[-2] for i in output.splitlines()]
  picked = [i for i in names if int(i.split('_')[1]) >= 48]
  return picked


def get_version_revisions(version):
  output = subprocess.check_output(
      ['gsutil', 'ls', 'gs://webports/builds/%s' % version])
  return [i.split('/')[-2] for i in output.splitlines()]


def get_existing_version_revisions(version):
  try:
    output = subprocess.check_output(
        ['gsutil', 'ls',
         'gs://webports/builds/%s/*/publish/pkg_pnacl/meta.*' % version],
        stderr=open(os.devnull, 'w'))
    return set([i.split('/')[-4] for i in output.splitlines()])
  except subprocess.CalledProcessError:
    return set()


def get_existing_revisions():
  revisions = []
  for version in get_pepper_versions():
    for revision in get_existing_version_revisions(version):
      revisions.append((version, revision))
  return revisions


def get_all_missing_revisions():
  picked = []
  for version in get_pepper_versions():
    revisions = get_version_revisions(version)
    existing = get_existing_version_revisions(version)
    picked.extend((version, i) for i in revisions if i not in existing)
  return picked


def get_age(version, revision):
  try:
    output = subprocess.check_output(
        ['gsutil', 'ls', '-l',
         'gs://webports/builds/%s/%s/packages/devenv_*_pnacl.*' %
         (version, revision)], stderr=open(os.devnull, 'w'))
    stamp = output.splitlines()[0].split()[1]
    tm = datetime.datetime.strptime(stamp, '%Y-%m-%dT%H:%M:%SZ')
    return (datetime.datetime.utcnow() - tm).total_seconds()
  except subprocess.CalledProcessError:
    return None


def build_repo(version, revision):
  age = get_age(version, revision)
  if age is None:
    print 'Skipping %s/%s as it is a bad version' % (version, revision)
    return
  if age < AGE_LIMIT:
    print 'Skipping %s/%s as it is only %.1f hours old' % (version, revision,
                                                           age / 60 / 60)
    return
  env = os.environ.copy()
  env['SDK_VERSION'] = version
  cmd = ['bash', os.path.join(SCRIPT_DIR, 'build_repo.sh'), '-r', revision]
  print 'Building %s/%s...' % (version, revision)
  subprocess.check_call(cmd, env=env)


def main():
  missing = get_all_missing_revisions()
  for version, revision in missing:
    build_repo(version, revision)
  return 0


if __name__ == '__main__':
  sys.exit(main())
