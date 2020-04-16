"""
<Program Name>
  test_pipelines.py

<Started>
  April 15th, 2020.

<Last Modified>
  April 15th, 2020.

<Author>
  Nicholas Renner <nrenner@nyu.edu>

<Copyright>
  See LICENSE for licensing information.

<Purpose>
  Run bash pipeline scripts in Lind and compare their runtime with native bash runs.
"""


#!/usr/bin/env python3

import os
import sys
import subprocess


TEST_FOLDER = "bash-pipelines"


def setup():
    return

def parse_native(test_result):
    return parsed_time

def run_native():

    results = []

    for filename in os.listdir(TEST_FOLDER):
        test_result = subprocess.Popen(["/bin/bash", "time", filename], stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        print(test_result)
        parsed_time = parse_native(test_result)
        results.append((filename, parsed_time))

    return results

def parse_lind(test_result):
    return parsed_time

def run_lind():
    
    results = []

    for filename in os.listdir(TEST_FOLDER):
        test_result = subprocess.Popen(["lind -t /bin/bash", filename], stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        print(test_result)
        parsed_time = parse_native(test_result)
        results.append((filename, parsed_time))

    return results

def report_statistics(native_results, lind_results):
    return

def generate_plot():
    return


def main():
    setup()
    native_results = run_native()
    lind_results = run_lind()
    report_statistics(native_results, lind_results)
    generate_plot()




if __name__ == "__main__":
  main()

