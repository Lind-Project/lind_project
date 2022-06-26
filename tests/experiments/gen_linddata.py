from subprocess import Popen, PIPE
import os
import json

dataset = dict()

for size in range(2,17):
    dataset[size] = list()  
    count = 0
    while count < 10:
        with open(os.devnull, 'w') as devnull:
            output = Popen(['lind', '-t', '/bin/bash', 'pipescriptvar', str(size)], stdout=PIPE, stderr=PIPE)
        # dataset[size].append(int(float(output.rstrip("\n")) * 1000))
        stdout, stderr = output.communicate()
        print size
        try:
            timeval = int((float(stderr.split()[-1])) * 1000)
        except ValueError:
            continue
        dataset[size].append(timeval)
        count = count + 1

with open('linddata.json', 'w') as fp:
    json.dump(dataset, fp)

