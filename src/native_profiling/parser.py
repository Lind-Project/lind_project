import re
import sys

report_file = sys.argv[1]

with open(report_file, "r") as f:
    perf_report = f.read()

lamp_stack_apps = ["nginx", "postgres", "python"]
syscalls = ["__x64_sys_recvfrom", "__x64_sys_sendto", "__x64_sys_poll"]
app_runtime_stats = []
syscall_stats = {}

print("Runtime stats")
print("Application\t|\t% of runtime")
print("-"*32)
total_runtime_percent = 0
for app in lamp_stack_apps:
    search_str = f".*{app}.*"
    matches = re.findall(search_str, perf_report, re.MULTILINE)
    if len(matches) == 0:
        print(f"No stats found for {app}")
        continue
    stat = matches[0].split()
    stat = (float(stat[0][:-1]), stat[2], stat[-1])
    app_runtime_stats.append(stat)
    print(f"{stat[1]:<11}\t|\t{stat[0]}%")
    total_runtime_percent += stat[0]
print(f"{'Total':<11}\t|\t{total_runtime_percent}%")

print("\n\nsyscall stats\n")
for syscall in syscalls:
    print(syscall)
    syscall_stats[syscall] = []
    print("Application\t|\tPerf %")
    print("-"*32)
    total_syscall_percent = 0
    for app in lamp_stack_apps:
        search_str = f".*{app}.*{syscall}"
        matches = re.findall(search_str, perf_report, re.MULTILINE)
        if len(matches) == 0:
            continue
        stat = matches[0].split()
        stat = (float(stat[0][:-1]), stat[2])
        syscall_stats[syscall].append(stat)
        print(f"{stat[1]:<11}\t|\t{stat[0]}%")
        total_syscall_percent += stat[0]
    print(f"{'Total':<11}\t|\t{total_syscall_percent}%")
    print(f"\nsyscall/LAMP -> {(total_syscall_percent / total_runtime_percent) * 100: .5f}%\n")
