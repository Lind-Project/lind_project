#!/usr/bin/env python
# Copyright (c) 2013 The Native Client Authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.
"""Manage partitioning of port builds.

Download historical data from the webports builders, and use it to
partition all of the projects onto the builder shards so each shard builds in
about the same amount of time.

Example use:

    $ ./partition.py -b linux-clang-

    builder 0 (total: 2786)
      bzip2
      zlib
      boost
      glibc-compat
      openssl
      libogg
      ...
    builder 1 (total: 2822)
      zlib
      libpng
      Regal
      glibc-compat
      ncurses
      ...
    builder 2 (total: 2790)
      zlib
      libpng
      bzip2
      jpeg
      ImageMagick
      glibc-compat
      ...
    Difference between total time of builders: 36


Pipe the results above (with appropriate use of -n and -p) into partition*.txt
so the partition can be used in the future.

The script is also used by the buildbot to read canned partitions.

Example use:

    $ ./partition.py -t <index> -n <number_of_shards>
"""

from __future__ import print_function

import argparse
import json
import os
import sys
import urllib2

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
ROOT_DIR = os.path.dirname(SCRIPT_DIR)
TOOLCHAINS = ('clang-newlib', 'glibc', 'pnacl')

sys.path.append(os.path.join(ROOT_DIR, 'lib'))

import webports
import webports.source_package
from webports.util import log_verbose

# Packages that the partitioned builders should never build.  The 'pnacl'
# toolchain package takes so long it has a dedicated builder.
EXCLUDED_PACKAGES = ['pnacl']


class Error(webports.Error):
  pass


def get_build_order(projects):
  rtn = []
  packages = [webports.source_package.create_package(p) for p in projects]
  for package in packages:
    for dep in package.DEPENDS:
      for ordered_dep in get_build_order([dep]):
        if ordered_dep not in rtn:
          rtn.append(ordered_dep)
    if package.NAME not in rtn:
      rtn.append(package.NAME)
  return rtn


def get_dependencies(projects):
  deps = get_build_order(projects)
  return set(deps) - set(projects)


def download_data_from_builder(builder, build):
  max_tries = 30

  for _ in xrange(max_tries):
    url = 'http://build.chromium.org/p/client.nacl.ports/json'
    url += '/builders/%s/builds/%d' % (builder, build)
    log_verbose('Downloading %s' % url)
    f = urllib2.urlopen(url)
    try:
      data = json.loads(f.read())
      text = data['text']
      if text == ['build', 'successful']:
        log_verbose('  Success!')
        return data
      log_verbose('  Not successful, trying previous build.')
    finally:
      f.close()
    build -= 1

  raise Error('Unable to find a successful build:\nBuilder: %s\nRange: [%d, %d]'
              % (builder, build - max_tries, build))


class Project(object):

  def __init__(self, name):
    self.name = name
    self.time = 0
    self.dep_names = get_dependencies([name])
    self.dep_times = [0] * len(self.dep_names)

  def update_dep_times(self, project_map):
    for i, dep_name in enumerate(self.dep_names):
      dep = project_map[dep_name]
      self.dep_times[i] = dep.time

  def get_time(self, used_dep_names):
    time = self.time
    for i, dep_name in enumerate(self.dep_names):
      if dep_name not in used_dep_names:
        time += self.dep_times[i]
    return time


class Projects(object):

  def __init__(self):
    self.projects = []
    self.project_map = {}
    self.dependencies = set()

  def add_project(self, name):
    if name not in self.project_map:
      project = Project(name)
      self.projects.append(project)
      self.project_map[name] = project
    return self.project_map[name]

  def add_data_from_builder(self, builder, build):
    data = download_data_from_builder(builder, build)
    for step in data['steps']:
      text = step['text'][0]
      text_tuple = text.split()
      if len(text_tuple) != 2 or text_tuple[0] not in TOOLCHAINS:
        continue
      _, name = text_tuple
      project = self.add_project(name)
      project.time = step['times'][1] - step['times'][0]

  def post_process_deps(self):
    for project in self.projects:
      project.update_dep_times(self.project_map)
      for dep_name in project.dep_names:
        self.dependencies.add(dep_name)

  def __getitem__(self, name):
    return self.project_map[name]


class ProjectTimes(object):

  def __init__(self):
    self.project_names = set()
    self.projects = []
    self.total_time = 0

  def get_total_time_with_project(self, project):
    return self.total_time + project.get_time(self.project_names)

  def add_project(self, projects, project):
    self.add_dependencies(projects, project)
    self.project_names.add(project.name)
    self.projects.append(project)
    self.total_time = self.get_total_time_with_project(project)

  def add_dependencies(self, projects, project):
    for dep_name in project.dep_names:
      if dep_name not in self.project_names:
        self.add_project(projects, projects[dep_name])

  def has_project(self, project):
    return project.name in self.project_names

  def topologically_sorted_project_names(self, projects):
    sorted_project_names = []

    def helper(project):
      for dep_name in project.dep_names:
        if dep_name not in sorted_project_names:
          helper(projects[dep_name])
      sorted_project_names.append(project.name)

    for project in self.projects:
      helper(project)

    return sorted_project_names


def get_partition(projects, dims):
  # Greedy algorithm: sort the projects by slowest to fastest, then add the
  # projects, in order, to the shard that has the least work on it.
  #
  # Note that this takes into account the additional time necessary to build a
  # projects dependencies, if those dependencies have not already been built.
  parts = [ProjectTimes() for _ in xrange(dims)]
  sorted_projects = sorted(projects.projects, key=lambda p: -p.time)
  for project in sorted_projects:
    if any(part.has_project(project) for part in parts):
      continue

    key = lambda p: p[1].get_total_time_with_project(project)
    index, _ = min(enumerate(parts), key=key)
    parts[index].add_project(projects, project)
  return parts


def load_canned(parts):
  # Return an empty partition for the no-sharding case.
  if parts == 1:
    return [[]]
  partitions = []
  partition = []
  input_file = os.path.join(SCRIPT_DIR, 'partition%d.txt' % parts)
  log_verbose("LoadCanned: %s" % input_file)
  with open(input_file) as fh:
    for line in fh:
      if line.strip()[0] == '#':
        continue
      if line.startswith('  '):
        partition.append(line[2:].strip())
      else:
        if partition:
          partitions.append(partition)
          partition = []
  assert not partition
  assert len(partitions) == parts, partitions
  # Return a small set of packages for testing.
  if os.environ.get('TEST_BUILDBOT'):
    partitions[0] = [
        'corelibs',
        'glibc-compat',
        'nacl-spawn',
        'ncurses',
        'readline',
        'libtar',
        'zlib',
        'lua',
    ]
  return partitions


def fixup_canned(partitions):
  all_projects = [p for p in webports.source_package.source_package_iterator()]
  all_names = [p.NAME for p in all_projects if not p.DISABLED]
  disabled_names = [p.NAME for p in all_projects if p.DISABLED]

  # Blank the last partition and fill it with anything not in the first two.
  partitions[-1] = []
  covered = set()
  for partition in partitions[:-1]:
    for item in partition:
      covered.add(item)

  for item in all_names:
    if item not in covered and item not in EXCLUDED_PACKAGES:
      partitions[-1].append(item)

  # Order by dependencies.
  partitions[-1] = get_build_order(partitions[-1])

  # Check that all the items still exist.
  for i, partition in enumerate(partitions):
    for item in partition:
      if item not in all_names and item not in disabled_names:
        raise Error('non-existent package in partition %d: %s' % (i, item))

  # Check that partitions include all of their dependencies.
  for i, partition in enumerate(partitions):
    deps = get_dependencies(partition)
    for dep in deps:
      if not dep in partition:
        raise Error('dependency missing from partition %d: %s' % (i, dep))

  return partitions


def print_canned(index, parts):
  canned = get_canned(index, parts)
  print(' '.join(canned))


def get_canned(index, parts):
  assert index >= 0 and index < parts, [index, parts]
  partitions = load_canned(parts)
  partitions = fixup_canned(partitions)
  log_verbose("Found %d packages for shard %d" % (len(partitions[index]),
                                                  index))
  return partitions[index]


def main(args):
  parser = argparse.ArgumentParser()
  parser.add_argument('--check', action='store_true',
                      help='check canned partition information is up-to-date.')
  parser.add_argument('-v', '--verbose', action='store_true',
                      help='Output extra information.')
  parser.add_argument('-t', '--print-canned', type=int,
                      help='Print a the canned partition list and exit.')
  parser.add_argument('-b', '--bot-prefix', help='builder name prefix.',
                      default='linux-clang-')
  parser.add_argument('-n', '--num-bots',
                      help='Number of builders on the waterfall to collect '
                      'data from or to print a canned partition for.',
                      type=int, default=5)
  parser.add_argument('-p', '--num-parts',
                      help='Number of parts to partition things into '
                      '(this will differ from --num-bots when changing the '
                      'number of shards).',
                      type=int, default=5)
  parser.add_argument('--build-number', help='Builder number to look at for '
                      'historical data on build times.', type=int, default=-1)
  options = parser.parse_args(args)
  webports.set_verbose(options.verbose)

  if options.check:
    for num_bots in xrange(1, 7):
      print('Checking partioning with %d bot(s)' % (num_bots))
      # GetCanned with raise an Error if the canned partition information is
      # bad, which in turn will trigger a non-zero return from this script.
      get_canned(0, num_bots)
    return

  if options.print_canned is not None:
    print_canned(options.print_canned, options.num_bots)
    return

  projects = Projects()
  for bot in range(options.num_bots):
    bot_name = '%s%d' % (options.bot_prefix, bot)
    log_verbose('Attempting to add data from "%s"' % bot_name)
    projects.add_data_from_builder(bot_name, options.build_number)
  projects.post_process_deps()

  parts = get_partition(projects, options.num_parts)
  for i, project_times in enumerate(parts):
    print('builder %d (total: %d)' % (i, project_times.total_time))
    project_names = project_times.topologically_sorted_project_names(projects)
    print('  %s' % '\n  '.join(project_names))

  times = list(sorted(part.total_time for part in parts))
  difference = 0
  for i in range(1, len(times)):
    difference += times[i] - times[i - 1]
  print('Difference between total time of builders: %d' % difference)


if __name__ == '__main__':
  try:
    sys.exit(main(sys.argv[1:]))
  except Error as e:
    sys.stderr.write("%s\n" % e)
    sys.exit(1)
