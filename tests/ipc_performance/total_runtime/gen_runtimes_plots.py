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
dataset["std"] = list()

nativeavgs = dict()

with open(sys.argv[1], "r") as fp:
    nativedata = json.load(fp)
with open(sys.argv[2], "r") as fp:
    linddata = json.load(fp)
with open(sys.argv[3], "r") as fp:
    userdata = json.load(fp)


for key in range(4, 21, 2):
    key = str(key)
    dataset["relative_time"].append(np.mean(userdata[key]) / np.mean(nativedata[key]))
    dataset["time"].append(np.mean(userdata[key]))
    dataset["platform"].append("Unsafe")
    dataset["bufsize"].append(int(key))
    dataset["std"].append(
        np.std(
            [
                userdata[key][i] / np.mean(nativedata[key])
                for i in range(len(userdata[key]))
            ]
        )
    )

for key in range(4, 21, 2):
    key = str(key)
    dataset["relative_time"].append(np.mean(linddata[key]) / np.mean(nativedata[key]))
    dataset["time"].append(np.mean(linddata[key]))
    dataset["platform"].append("Lind")
    dataset["bufsize"].append(int(key))
    dataset["std"].append(
        np.std(
            [
                linddata[key][i] / np.mean(nativedata[key])
                for i in range(len(linddata[key]))
            ]
        )
    )

for key in range(4, 21, 2):
    key = str(key)
    dataset["relative_time"].append(np.mean(nativedata[key]) / np.mean(nativedata[key]))
    dataset["time"].append(np.mean(nativedata[key]))
    dataset["platform"].append("Native")
    dataset["bufsize"].append(int(key))
    dataset["std"].append(
        np.std(
            [
                nativedata[key][i] / np.mean(nativedata[key])
                for i in range(len(nativedata[key]))
            ]
        )
    )


plt.rcParams["errorbar.capsize"] = 10
df = pd.DataFrame(data=dataset)
df["ymin"] = df["relative_time"] - df["std"]
df["ymax"] = df["relative_time"] + df["std"]
yerr = df[["ymin", "ymax"]].T.to_numpy()

pd.set_option("display.max_rows", None, "display.max_columns", None)
plt.figure(figsize=(10, 6))
sns.set(style="darkgrid")
sns.set_palette("bright")
fig = sns.barplot(x="bufsize", y="relative_time", hue="platform", data=df, palette=["C3", "C0", "C1"])
sns.move_legend(
    fig,
    "lower center",
    bbox_to_anchor=(0.5, -0.2),
    ncol=3,
    title="",
    fontsize=10,
    frameon=False,
)

for i, p in enumerate(fig.patches):
    if i >= len(df["ymin"]):
        break
    x = p.get_x()  # get the bottom left x corner of the bar
    w = p.get_width()  # get width of bar
    h = p.get_height()  # get height of bar
    min_y = df["ymin"][i]  # use h to get min from dict z
    max_y = df["ymax"][i]  # use h to get max from dict z
    plt.vlines(x + w / 2, min_y, max_y, color="k")

plt.xlabel("$log_2 (buffersize)$", fontsize=10)
plt.ylabel("Normalized Runtime", fontsize=10)
plt.tight_layout(pad=2)
plt.title(f"Normalized Total Runtime {sys.argv[4]}")
plt.savefig(sys.argv[5], dpi=400)
