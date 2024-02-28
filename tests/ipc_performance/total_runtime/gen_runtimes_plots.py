import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns
import json
import sys


dataset = dict()
dataset["relative_time"] = list()
dataset["platform"] = list()
dataset["time"] = list()
dataset["bufsize"] = list()

nativeavgs = dict()

with open(sys.argv[1], "r") as fp:
    nativedata = json.load(fp)
with open(sys.argv[2], "r") as fp:
    linddata = json.load(fp)
with open(sys.argv[3], "r") as fp:
    userdata = json.load(fp)

for key in userdata:
    dataset["relative_time"].append(userdata[key] / nativedata[key])
    dataset["time"].append(userdata[key])
    dataset["platform"].append("User (unsafe)")
    dataset["bufsize"].append(int(key))

for key in linddata:
    dataset["relative_time"].append(linddata[key] / nativedata[key])
    dataset["time"].append(linddata[key])
    dataset["platform"].append("Lind")
    dataset["bufsize"].append(int(key))

for key in nativedata:
    dataset["relative_time"].append(nativedata[key] / nativedata[key])
    dataset["time"].append(nativedata[key])
    dataset["platform"].append("Native")
    dataset["bufsize"].append(int(key))


df = pd.DataFrame(data=dataset)
pd.set_option("display.max_rows", None, "display.max_columns", None)
plt.figure(figsize=(5, 4))
sns.set(style="darkgrid")
sns.set_palette("bright")
fig = sns.barplot(x="bufsize", y="relative_time", hue="platform", data=df)
sns.move_legend(
    fig,
    "lower center",
    bbox_to_anchor=(0.5, 1),
    ncol=3,
    title="Platform",
    fontsize=10, 
    frameon=False,
)

plt.xlabel("log(buffersize)", fontsize=10)
plt.ylabel("Relative runtime w.r.t Native runtime", fontsize=10)
plt.title("Piping 32GB Varying Buffersize: " + sys.argv[4], y = -0.275, fontsize=12)
plt.tight_layout(pad=0.25)

plt.savefig(sys.argv[5], dpi=400)
