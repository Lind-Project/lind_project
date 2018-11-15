/*
 * Copyright (c) 2014 The Native Client Authors. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

/* globals TEST_F, ASSERT_EQ, ASSERT_TRUE, chrometest, DevEnvTest */

'use strict';

// Install the default packages.
// This test must be run before any tests that use these packages.
TEST_F(DevEnvTest, 'testDefaultPackageInstall', function() {
  var self = this;
  return Promise.resolve().then(function() {
    return self.installDefaultPackages();
  });
});

// Test of the Google I/O 2014 tutorial at:
// https://developer.chrome.com/native-client/io2014
TEST_F(DevEnvTest, 'testIO2014', function() {
  var self = this;
  var pid;
  var bashrc = 'git config --global user.name "John Doe"\n' +
               'git config --global user.email johndoe@example.com\n';
  return Promise.resolve().then(function() {
    return self.initFileSystem();
  }).then(function() {
    return self.writeFile('/home/user/.bashrc', bashrc);
  }).then(function() {
    return self.checkCommand('source ~/.bashrc');
  }).then(function() {
    return self.checkCommand('mkdir work');
  }).then(function() {
    return self.checkCommand(
        'cd work && ' +
        'curl http://nacltools.storage.googleapis.com/io2014/voronoi.zip -O');
  }).then(function() {
    return self.checkCommand('cd work && ls', 0, 'voronoi.zip\n');
  }).then(function() {
    return self.checkCommand('cd work && unzip voronoi.zip');
  }).then(function() {
    return self.checkCommand('cd work/voronoi && ls Makefile', 0, 'Makefile\n');
  }).then(function() {
    return self.checkCommand('cd work/voronoi && git init');
  }).then(function() {
    return self.checkCommand('cd work/voronoi && git add .');
  }).then(function() {
    return self.checkCommand(
        'cd work/voronoi && git commit -m "imported voronoi demo"');
  }).then(function() {
    if (self.params['TOOLCHAIN'] === 'glibc' &&
        self.params['SYS_ARCH'] === 'x86_64') {
      return Promise.resolve().then(function() {
        return self.checkCommand('cd work/voronoi && make voronoi.nexe');
      }).then(function() {
        chrometest.info('spawn voronoi');
        return self.spawnCommand('cd work/voronoi && make voronoi');
      }).then(function(msg) {
        pid = msg.pid;
        chrometest.info('got pid ' + pid);
        return chrometest.sleep(3000);
      }).then(function(msg) {
        chrometest.info('killing');
        self.sigint();
        return self.waitCommand(pid);
      }).then(function(msg) {
        chrometest.info('done killing');
        ASSERT_EQ(2, msg.status, 'Expect 2 from make');
      });
    } else {
      // TODO(bradnelson): Fix other combinations.
      chrometest.info('skipping unsupported toolchain / arch to build on');
    }
  });
});

// Test of the Chrome Dev Summit cpp tutorial at:
// https://developer.chrome.com/native-client/cds2014/cpp
TEST_F(DevEnvTest, 'testCDS2014', function() {
  var self = this;
  var pid;
  var bashrc = 'git config --global user.name "John Doe"\n' +
               'git config --global user.email johndoe@example.com\n';
  return Promise.resolve().then(function() {
    return self.initFileSystem();
  }).then(function() {
    return self.writeFile('/home/user/.bashrc', bashrc);
  }).then(function() {
    return self.checkCommand('source ~/.bashrc');
  }).then(function() {
    return self.checkCommand('mkdir work2');
  }).then(function() {
    return self.checkCommand(
        'cd work2 && ' +
        'curl https://nacltools.storage.googleapis.com/' +
        'cds2014/cds2014_cpp.zip -O');
  }).then(function() {
    return self.checkCommand('cd work2 && ls', 0, 'cds2014_cpp.zip\n');
  }).then(function() {
    return self.checkCommand('cd work2 && unzip cds2014_cpp.zip');
  }).then(function() {
    return self.checkCommand(
        'cd work2/cds2014_cpp && ls Makefile', 0, 'Makefile\n');
  }).then(function() {
    return self.checkCommand('cd work2/cds2014_cpp && git init');
  }).then(function() {
    return self.checkCommand('cd work2/cds2014_cpp && git add .');
  }).then(function() {
    return self.checkCommand(
        'cd work2/cds2014_cpp && git commit -m "imported cds2014_cpp demo"');
  }).then(function() {
    if (self.params['TOOLCHAIN'] === 'glibc' &&
        self.params['SYS_ARCH'] === 'x86_64') {
      return Promise.resolve().then(function() {
        return self.checkCommand('cd work2/cds2014_cpp && make');
      }).then(function() {
        chrometest.info('spawn fire');
        return self.spawnCommand('cd work2/cds2014_cpp && make fire');
      }).then(function(msg) {
        pid = msg.pid;
        chrometest.info('got pid ' + pid);
        return chrometest.sleep(3000);
      }).then(function(msg) {
        chrometest.info('killing');
        self.sigint();
        return self.waitCommand(pid);
      }).then(function(msg) {
        chrometest.info('done killing');
        ASSERT_EQ(2, msg.status, 'Expect 2 from make');
      });
    } else {
      // TODO(bradnelson): Fix other combinations.
      chrometest.info('skipping unsupported toolchain / arch to build on');
    }
  });
});
