import timeit
import subprocess
import json

dataset = dict()

def execute_scripts(size):
    process = subprocess.call(['/bin/bash', 'pipescriptvar-native', str(size)])

for size in range(2,17):
    dataset[size] = list()
    for j in range(10):
        print size
        t = timeit.Timer("execute_scripts("+str(size)+")", setup="from __main__ import execute_scripts")
        dataset[size].append(int(t.timeit(1) * 1000))


with open('nativedata.json', 'w') as fp:
    json.dump(dataset, fp)
