# Imports built modules and flask.

import compileall
import os
import __builtin__
import imp
import marshal
import os
import sys
import traceback
import collections
import time
import math
import binascii
import cStringIO
import _random
import _ssl
import _hashlib
import cPickle
import _functools
import _struct
import _io
import datetime
import select
import array
import zlib
import unicodedata
import psycopg2
from psycopg2 import connect

print "Hello world!\nInstalled modules:"
print (dir())

conn = psycopg2.connect("dbname=test user=postgres")
cur = conn.cursor()
cur.execute("SELECT * FROM my_data")
records = cur.fetchall()
