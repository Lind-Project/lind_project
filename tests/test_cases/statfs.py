#!/bin/python2
# Checks if the outputs of fstatfs and statfs are the same

import os
import subprocess

def parse_output(output):
    # Split output by newlines
    lines = output.split('\n')

    # Dictionary to store the parsed values
    parsed = {}

    # Parse each line
    for line in lines:
        # Split line by colon
        parts = line.split(':')

        # If line is not empty
        if len(parts) >= 2:
            # Use the first part as key and the second part as value
            key = parts[0].strip()
            value = parts[1].strip()

            # Add to dictionary
            parsed[key] = value
    
    return parsed


# Use 'subprocess.check_output' to run the commands and get their output
fstatfs_output = subprocess.check_output("fstatfs filename", shell=True).decode('utf-8')
statfs_output = subprocess.check_output("statfs filename", shell=True).decode('utf-8')

# Parse the outputs
fstatfs_parsed = parse_output(fstatfs_output)
statfs_parsed = parse_output(statfs_output)

# Compare and print result
if fstatfs_parsed == statfs_parsed:
    print("The outputs of fstatfs and statfs are the same.")
else:
    print("The outputs of fstatfs and statfs are different.")
