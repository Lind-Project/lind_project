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
import resource


TEST_FOLDER = "bash-pipelines"


def setup():
    return

def parse_native(test_result):
    parsed_time = test_result
    return parsed_time

def run_native():

    results = []
    files = os.listdir(TEST_FOLDER)
    print(files)
    for filename in files:
        usage_start = resource.getrusage(resource.RUSAGE_CHILDREN)
        test_sub = subprocess.Popen(["/bin/bash", TEST_FOLDER + filename], stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        usage_end = resource.getrusage(resource.RUSAGE_CHILDREN)
        test_result = testsub.stdout.read().decode().strip().split('\n')
        cpu_time = usage_end.ru_utime - usage_start.ru_utime
        print(test_result)
        print(cpu_time)
        parsed_time = parse_native(test_result)
        results.append((filename, parsed_time))

    return results

def parse_lind(test_result):
    parsed_time = test_result
    return parsed_time

def run_lind():
    
    results = []

    for filename in os.listdir(TEST_FOLDER):
        testsub = subprocess.Popen(["lind -t /bin/bash", filename], stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        test_result = testsub.stdout.read().decode().strip().split('\n')

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

