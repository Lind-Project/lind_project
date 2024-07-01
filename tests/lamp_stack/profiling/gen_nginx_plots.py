import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns
import json
import sys


dataset = dict()
dataset["platform"] = list()
dataset["req/sec"] = list()
dataset["relative"] = list()
dataset["bytes"] = list()

nativeavgs = dict()

with open(sys.argv[1], "r") as fp:
    nativedata = json.load(fp)
with open(sys.argv[2], "r") as fp:
    linddata = json.load(fp)
with open(sys.argv[3], "r") as fp:
    rawdata = json.load(fp)

for key in linddata:
    dataset["req/sec"].append(linddata[key])
    dataset["relative"].append(linddata[key] / nativedata[key])
    dataset["platform"].append("Lind")
    dataset["bytes"].append(key)

for key in rawdata:
    dataset["req/sec"].append(rawdata[key])
    dataset["relative"].append(rawdata[key] / nativedata[key])
    dataset["platform"].append("RawPOSIX")
    dataset["bytes"].append(key)

for key in nativedata:
    dataset["req/sec"].append(nativedata[key])
    dataset["relative"].append(nativedata[key] / nativedata[key])
    dataset["platform"].append("Native")
    dataset["bytes"].append(key)


df = pd.DataFrame(data=dataset)
pd.set_option("display.max_rows", None, "display.max_columns", None)
plt.figure(figsize=(8, 4))
sns.set(style="darkgrid")
sns.set_palette("bright")
fig = sns.barplot(x="bytes", y="relative", hue="platform", data=df, width=0.7)
sns.move_legend(
    fig,
    "lower center",
    bbox_to_anchor=(0.5, 1),
    ncol=3,
    title="Platform",
    frameon=False,
)

plt.xlabel("Filesize", fontsize=15)
plt.ylabel("Normalized Request Rate", fontsize=15)
plt.xticks(df["bytes"])
plt.tight_layout()
plt.savefig(sys.argv[4])
