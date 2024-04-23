import json
import sys

native_stats = {}
lind_stats = {}

# process native linux stats
num_stats = 8
native_data = {}
native_times = []
with open(sys.argv[1], "r") as native_file:
    lines = native_file.readlines()
    native_report = [line.strip() for line in lines]

for i in range(0, len(native_report), num_stats):
    index = native_report[i]
    run_time = float(native_report[i + 1])
    native_times.append(run_time)

    if not native_data.get(index):
        native_data[index] = []

    base_func = float(native_report[i + 2])
    kern_func = float(native_report[i + 3])
    pipe_func = float(native_report[i + 4])
    copy_func = (
        float(native_report[i + 5])
        + float(native_report[i + 6])
        + float(native_report[i + 7])
    )

    copy_percent = copy_func / base_func
    pipe_percent = (pipe_func / base_func) - copy_percent
    kern_percent = (kern_func / base_func) - pipe_percent - copy_percent
    base_percent = 1 - kern_percent - pipe_percent - copy_percent

    native_data[index].append(
        (
            run_time,
            base_percent,
            kern_percent,
            pipe_percent,
            copy_percent,
        )
    )

native_stats = {"index": [], "data": []}
for key in native_data:
    data = [
        [native_data[key][i][j] for i in range(len(native_data[key]))]
        for j in range(len(native_data[key][0]))
    ]
    data = [sum(stat) / len(stat) for stat in data]
    native_stats["index"].append(f"{key}\n{data[0]}ns")
    native_stats["data"].append(data[1:])

# process lind stats
num_stats = 6
lind_data = {}
with open(sys.argv[2], "r") as lind_file:
    lines = lind_file.readlines()
    lind_report = [line.strip() for line in lines]

for i in range(0, len(lind_report), num_stats):
    index = lind_report[i]
    run_time = float(lind_report[i + 1])

    if not lind_data.get(index):
        lind_data[index] = []

    base_func = float(lind_report[i + 2])
    kern_func = min(base_func, float(lind_report[i + 3]))
    pipe_func = min(kern_func, float(lind_report[i + 4]))
    copy_func = min(pipe_func, float(lind_report[i + 5]))

    copy_percent = copy_func / base_func
    pipe_percent = (pipe_func / base_func) - copy_percent
    kern_percent = (kern_func / base_func) - pipe_percent - copy_percent
    base_percent = 1 - kern_percent - pipe_percent - copy_percent

    lind_ratio = float(run_time) / native_times[i // num_stats]
    lind_data[index].append(
        (
            run_time,
            lind_ratio * base_percent,
            lind_ratio * kern_percent,
            lind_ratio * pipe_percent,
            lind_ratio * copy_percent,
        )
    )

lind_stats = {"index": [], "data": []}
for key in lind_data:
    data = [
        [lind_data[key][i][j] for i in range(len(lind_data[key]))]
        for j in range(len(lind_data[key][0]))
    ]
    data = [sum(stat) / len(stat) for stat in data]
    lind_stats["index"].append(f"{key}\n{data[0]}ns")
    lind_stats["data"].append(data[1:])

stats = {"lind": lind_stats, "native": native_stats}
with open(sys.argv[3], "w") as f:
    json.dump(stats, f)
