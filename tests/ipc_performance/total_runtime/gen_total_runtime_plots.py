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

configs = ["x_16", "x_x", "16_x"]
nativedata = {}
userdata = {}
linddata = {}
for config in configs:
    with open(f"data/total_runtimes/nat_{config}.json", "r") as fp:
        nativedata[config] = json.load(fp)
    with open(f"data/total_runtimes/lind_{config}.json", "r") as fp:
        linddata[config] = json.load(fp)
    with open(f"data/total_runtimes/user_{config}.json", "r") as fp:
        userdata[config] = json.load(fp)


for i, config in enumerate(configs):
    for key in range(4, 21, 2):
        key = str(key)
        dataset["relative_time"].append(
            np.mean(userdata[config][key]) / np.mean(nativedata[config][key])
        )
        dataset["time"].append(np.mean(userdata[config][key]))
        dataset["platform"].append("Unsafe")
        if key != "16":
            dataset["bufsize"].append(config.replace("_", "-").replace("x", key))
        else:
            dataset["bufsize"].append("16-16" + " " * i)
        dataset["std"].append(
            np.std(
                [
                    userdata[config][key][i] / np.mean(nativedata[config][key])
                    for i in range(len(userdata[config][key]))
                ]
            )
        )

for i, config in enumerate(configs):
    for key in range(4, 21, 2):
        key = str(key)
        dataset["relative_time"].append(
            np.mean(linddata[config][key]) / np.mean(nativedata[config][key])
        )
        dataset["time"].append(np.mean(linddata[config][key]))
        dataset["platform"].append("Lind")
        if key != "16":
            dataset["bufsize"].append(config.replace("_", "-").replace("x", key))
        else:
            dataset["bufsize"].append("16-16" + " " * i)
        dataset["std"].append(
            np.std(
                [
                    linddata[config][key][i] / np.mean(nativedata[config][key])
                    for i in range(len(linddata[config][key]))
                ]
            )
        )


for i, config in enumerate(configs):
    for key in range(4, 21, 2):
        key = str(key)
        dataset["relative_time"].append(
            np.mean(nativedata[config][key]) / np.mean(nativedata[config][key])
        )
        dataset["time"].append(np.mean(nativedata[config][key]))
        dataset["platform"].append("Native")
        if key != "16":
            dataset["bufsize"].append(config.replace("_", "-").replace("x", key))
        else:
            dataset["bufsize"].append("16-16" + " " * i)
        dataset["std"].append(
            np.std(
                [
                    nativedata[config][key][i] / np.mean(nativedata[config][key])
                    for i in range(len(nativedata[config][key]))
                ]
            )
        )

plt.rcParams["errorbar.capsize"] = 10
df = pd.DataFrame(data=dataset)
df["ymin"] = df["relative_time"] - df["std"]
df["ymax"] = df["relative_time"] + df["std"]
yerr = df[["ymin", "ymax"]].T.to_numpy()

print(df)

pd.set_option("display.max_rows", None, "display.max_columns", None)
plt.figure(figsize=(18, 6))
sns.set(style="darkgrid")
sns.set_palette("bright")
fig = sns.barplot(
    x="bufsize", y="relative_time", hue="platform", data=df, palette=["C3", "C0", "C1"], width=0.6
)
sns.move_legend(
    fig,
    "lower center",
    bbox_to_anchor=(0.5, 1),
    ncol=3,
    title="Platform",
    fontsize=15,
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

# multiple lines all full height
plt.vlines(x=[8.5, 17.5], ymin=0, ymax=1.1, color="black", ls='--', lw=1)

plt.xticks(rotation=45)
plt.xlabel("Read-Write buffersize $log_2 (N)$ - $log_2 (M)$", fontsize=15)
plt.ylabel("Normalized Runtime", fontsize=15)
plt.tight_layout()
plt.savefig("plots/runtime.png")