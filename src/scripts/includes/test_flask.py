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
import _functools
import cPickle
import _struct
import select
import array
import unicodedata
import _ssl
import _hashlib
import _io
import datetime
import zlib


import flask

print "Hello world!\nInstalled modules:"
print (dir())

from flask import Flask

app = Flask(__name__)

@app.route("/")
def hello_world():
    return "<p>Hello Flask!</p>"
