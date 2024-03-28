import numpy as np
import pandas as pd
import matplotlib
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


# dataset["relative_time"] = [100 * (1 - t) for t in dataset["relative_time"]]
df = pd.DataFrame(data=dataset)
pd.set_option("display.max_rows", None, "display.max_columns", None)
plt.figure(figsize=(8, 5))
sns.set(style="darkgrid")
sns.set_palette("bright")
fig = sns.barplot(x="bufsize", y="relative_time", hue="platform", data=df)
sns.move_legend(
    fig,
    "lower center",
    bbox_to_anchor=(0.5, -0.2),
    ncol=3,
    title="Platform",
    frameon=False,
)
fig.legend_.set_title(None)
# sns.lineplot(x="bufsize", y="time", hue="platform", data=df)
# plt.yscale("log")
plt.xlabel("# of cat stages", fontsize=10)
# plt.ylabel("Performance Improvement over Native Linux")
plt.ylabel("Relative runtime w.r.t Native runtime", fontsize=10)
plt.title("Pipeline Performance of N-Consecutive 'cat' Applications for a 2GB File")
plt.tight_layout(pad=0.25)

plt.savefig(sys.argv[3], dpi=800)
