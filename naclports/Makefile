# Copyright (c) 2012 The Native Client Authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.
#
# Makefile
#
# usage: 'make [package]'
#
# This makefile can by used to perform common actions such as building
# all ports, building a give port, running a webserver to test the ports.
# Each port has a dependency on its own sentinel file, which can be found
# at out/sentinels/*

PYLINT = build_tools/python_wrapper -m pylint
NODE ?= nodejs
JSHINT := $(NODE) node_modules/.bin/jshint
JSLINT := $(NODE) node_modules/.bin/jslint
COVERAGE := bin/coverage
COVERAGE_ARGS := --fail-under=60
COVERAGE_VER := $(shell $(COVERAGE) --version 2>/dev/null)

ifeq ($(V),1)
VERBOSE ?= 1
endif

ifeq ($(F),1)
FORCE ?= 1
endif

ifeq ($(V),2)
VERBOSE ?= 1
VERBOSE_BUILD ?= 1
endif

ifeq ($(VERBOSE),1)
BUILD_FLAGS += -v
endif

ifeq ($(VERBOSE_BUILD),1)
BUILD_FLAGS += --verbose-build
endif

ifeq ($(FORCE),1)
BUILD_FLAGS += -f
endif

ifeq ($(FROM_SOURCE),1)
BUILD_FLAGS += --from-source
endif

export NACL_ARCH
export TOOLCHAIN

all:
	bin/webports --all install $(BUILD_FLAGS)

run:
	./build_tools/httpd.py

clean:
	bin/webports --all clean

reallyclean: clean
	rm -rf $(NACL_OUT)

check: test

JS_FILES := $(shell git ls-files "*.js")

lint: pylint jshint jslint

pylint:
	$(PYLINT) --rcfile=.pylintrc lib/webports lib/webports/tests/*.py

jshint:
	$(JSHINT) $(JS_FILES)

jslint:
	$(JSLINT) build_tools/naclprocess.js build_tools/naclterm.js

test:
	$(COVERAGE) run --include=lib/webports/*,build_tools/* -m nose \
		--rednose build_tools lib
	@rm -rf out/coverage_html
	$(COVERAGE) html
	$(COVERAGE) report $(COVERAGE_ARGS)

%:
	bin/webports install $* $(BUILD_FLAGS)

.PHONY: all run clean sdklibs sdklibs_list reallyclean check test
.PHONY: lint pylint jshint jslint
