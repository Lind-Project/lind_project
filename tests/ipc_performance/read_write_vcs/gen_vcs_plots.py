import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns
import json
import sys


dataset = dict()
dataset["platform"] = list()
dataset["vcs/sec"] = list()
dataset["bufsize"] = list()

nativeavgs = dict()

with open(sys.argv[1], "r") as fp:
    nativedata = json.load(fp)
with open(sys.argv[2], "r") as fp:
    linddata = json.load(fp)
with open(sys.argv[3], "r") as fp:
    userdata = json.load(fp)


for key in linddata:
    dataset["vcs/sec"].append(
        linddata[key]["switches/time"] / nativedata[key]["switches/time"]
    )
    dataset["platform"].append("User (unsafe)")
    dataset["bufsize"].append(int(key))

df = pd.DataFrame(data=dataset)

pd.set_option("display.max_rows", None, "display.max_columns", None)
plt.figure(figsize=(10, 6))
sns.set(style="darkgrid")
sns.set_palette("bright")
fig = sns.lineplot(x="bufsize", y="vcs/sec", data=df)

plt.xlabel("$log_2 (buffersize)$", fontsize=10)
plt.ylabel("Lind/native ratio of context switches per sec", fontsize=10)
plt.title("Piping 32GB Varying Buffersize: " + sys.argv[4], y=-0.15, fontsize=12)
plt.tight_layout(pad=1)

plt.savefig(sys.argv[5], dpi=400)
