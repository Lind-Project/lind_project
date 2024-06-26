#!/bin/python2
import sys
lindoutput = sys.argv[1].split('\n')
hostoutput = sys.argv[2].split('\n')

def parse_output(lines):
    # Extract the parts of interest
    server_status = lines[0]
    server_connection = lines[1]
    client_status = lines[2]
    client_ip_port = lines[3].rsplit(',', 1)[0]  # Remove the port part
    
    return server_status, server_connection, client_status, client_ip_port

def compare_outputs(output1, output2):
    # Parse both outputs
    parsed_output1 = parse_output(output1)
    parsed_output2 = parse_output(output2)
    
    # Compare the parsed outputs
    return parsed_output1 == parsed_output2

print(lindoutput)
# Compare the outputs
if compare_outputs(lindoutput, hostoutput) == False:
    print("The outputs are different.")
    exit(1)

