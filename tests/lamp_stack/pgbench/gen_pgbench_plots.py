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
dataset["transactions"] = list()

nativeavgs = dict()

with open(sys.argv[1], "r") as fp:
    nativedata = json.load(fp)
with open(sys.argv[2], "r") as fp:
    linddata = json.load(fp)

for key in linddata:
    dataset["relative_time"].append(linddata[key][1] / nativedata[key][1])
    dataset["time"].append(linddata[key][1])
    dataset["platform"].append("Lind")
    dataset["transactions"].append(int(key))

for key in nativedata:
    dataset["relative_time"].append(nativedata[key][1] / nativedata[key][1])
    dataset["time"].append(nativedata[key][1])
    dataset["platform"].append("Native")
    dataset["transactions"].append(int(key))


df = pd.DataFrame(data=dataset)
pd.set_option("display.max_rows", None, "display.max_columns", None)
plt.figure(figsize=(8, 4))
sns.set(style="darkgrid")
sns.set_palette("bright")
fig = sns.barplot(x="transactions", y="time", hue="platform", data=df, width=0.7)
sns.move_legend(
    fig,
    "lower center",
    bbox_to_anchor=(0.5, 1),
    ncol=3,
    title="Platform",
    frameon=False,
)

plt.xlabel("Number of transactions", fontsize=15)
plt.ylabel("Transactions per second", fontsize=15)
plt.tight_layout()
plt.savefig(sys.argv[3])
