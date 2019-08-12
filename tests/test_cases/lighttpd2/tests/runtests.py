#!/usr/bin/env python
# -*- coding: utf-8 -*-

import os
import sys
from logfile import LogFile, RemoveEscapeSeq

from base import Env, Tests

from optparse import OptionParser

from tempfile import mkdtemp


def which(program):
	def is_exe(fpath):
		return os.path.exists(fpath) and os.access(fpath, os.X_OK)

	fpath, fname = os.path.split(program)
	if fpath:
		if is_exe(program):
			return program
	else:
		for path in os.environ["PATH"].split(os.pathsep):
			exe_file = os.path.join(path, program)
			if is_exe(exe_file):
				return exe_file

	return None

def find_port(port):
	if port >= 1024 and port < (65536-8):
		return port

	from random import Random
	r = Random(os.getpid())
	return r.randint(1024, 65536-8)

class ArgumentError(Exception):
	def __init__(self, value): self.value = value
	def __str__(self): return repr(self.value)

parser = OptionParser()
parser.add_option("--angel", help = "Path to angel binary (required)")
parser.add_option("--worker", help = "Path to worker binary (required)")
parser.add_option("--plugindir", help = "Path to plugin directory (required)")
parser.add_option("-k", "--no-cleanup", help = "Keep temporary files, no cleanup", action = "store_true", default = False)
parser.add_option("-p", "--port", help = "Use [port,port+7] as tcp ports on 127.0.0.2 (default: 8088; use 0 for random port)", default = 8088, type = "int")
parser.add_option("-t", "--test", help = "Run specific test", action = "append", dest = "tests", default = [])
parser.add_option("-c", "--force-cleanup", help = "Keep no temporary files (overwrites -k)", action = "store_true", default = False)
parser.add_option("--strace", help = "Strace services", action = "store_true", default = False)
parser.add_option("--truss", help = "Truss services", action = "store_true", default = False)
parser.add_option("--debug-requests", help = "Dump requests", action = "store_true", default = False)
parser.add_option("--no-angel", help = "Spawn lighttpd worker directly", action = "store_true", default = False)
parser.add_option("--debug", help = "Show service logs on console", action = "store_true", default = False)
parser.add_option("--wait", help = "Wait for services to exit on first signal", action = "store_true", default = False)
parser.add_option("--valgrind", help = "Run worker with valgrind from angel", action = "store_true", default = False)
parser.add_option("--valgrind-leak", help = "Run valgrind with memory leak check; takes an empty string or a valgrind suppression file", action="store", default = False)

(options, args) = parser.parse_args()

if not options.angel or not options.worker or not options.plugindir:
	raise ArgumentError("Missing required arguments")

if options.force_cleanup: options.no_cleanup = False

Env.angel = os.path.abspath(options.angel)
Env.worker = os.path.abspath(options.worker)
Env.plugindir = os.path.abspath(options.plugindir)
Env.no_cleanup = options.no_cleanup
Env.force_cleanup = options.force_cleanup
Env.port = find_port(options.port)
Env.tests = options.tests
Env.sourcedir = os.path.dirname(os.path.abspath(os.path.dirname(__file__)))
Env.contribdir = os.path.join(Env.sourcedir, "contrib")
Env.debugRequests = options.debug_requests
Env.strace = options.strace
Env.truss = options.truss
Env.no_angel = options.no_angel
Env.debug = options.debug
Env.wait = options.wait
Env.valgrind = options.valgrind
Env.valgrind_leak = options.valgrind_leak
if Env.valgrind or Env.valgrind_leak:
	Env.valgrind = which('valgrind')

Env.color = sys.stdin.isatty()
Env.COLOR_RESET = Env.color and "\033[0m" or ""
Env.COLOR_BLUE = Env.color and "\033[1;34m" or ""
Env.COLOR_GREEN = Env.color and "\033[1;32m" or ""
Env.COLOR_YELLOW = Env.color and "\033[1;33m" or ""
Env.COLOR_RED = Env.color and "\033[1;31m" or ""
Env.COLOR_CYAN = Env.color and "\033[1;36m" or ""

Env.fcgi_cgi = which('fcgi-cgi')

Env.dir = mkdtemp(suffix='-l2-tests')
Env.defaultwww = os.path.join(Env.dir, "www", "default")

Env.log = open(os.path.join(Env.dir, "tests.log"), "w")
if Env.color: Env.log = RemoveEscapeSeq(Env.log)
if Env.debug:
	logfile = Env.log
	Env.log = LogFile(sys.stdout, **{ "[log]": logfile })
	sys.stderr = LogFile(sys.stderr, **{ "[stderr]": logfile })
	sys.stdout = LogFile(sys.stdout, **{ "[stdout]": logfile })
else:
	Env.log = LogFile(Env.log)
	sys.stderr = LogFile(sys.stderr, **{ "[stderr]": Env.log })
	sys.stdout = LogFile(sys.stdout, **{ "[stdout]": Env.log })

failed = False

try:
	# run tests
	tests = Tests()
	tests.LoadTests()
	failed = True
	try:
		tests.Prepare()
	except:
		import traceback
		print >> sys.stderr, traceback.format_exc()
	else:
		if tests.Run():
			failed = False
	finally:
		tests.Cleanup()
		if not Env.no_cleanup and not failed:
			os.remove(os.path.join(Env.dir, "tests.log"))
except:
	import traceback
	print >> sys.stderr, traceback.format_exc()
	failed = True
finally:
	try:
		if Env.force_cleanup:
			import shutil
			shutil.rmtree(Env.dir)
		elif not Env.no_cleanup and not failed:
			os.rmdir(Env.dir)
	except OSError:
		print >> sys.stderr, "Couldn't delete temporary directory '%s', probably not empty (perhaps due to some errors)" % Env.dir

Env.log.close()

if failed:
	sys.exit(1)
else:
	sys.exit(0)
