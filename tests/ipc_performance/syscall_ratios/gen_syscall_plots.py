import pandas as pd
import matplotlib.cm as cm
import numpy as np
import matplotlib.pyplot as plt
import seaborn as sns
import json
import sys


def plot_clustered_stacked(dfall, labels=None, H="/", **kwargs):
    """Given a list of dataframes, with identical columns and index, create a clustered stacked bar plot.
    labels is a list of the names of the dataframe, used for the legend
    title is a string for the title of the plot
    H is the hatch used for identification of the different dataframe"""

    n_df = len(dfall)
    n_col = len(dfall[0].columns)
    n_ind = len(dfall[0].index)
    axe = plt.subplot(111)

    for df in dfall:  # for each data frame
        axe = df.plot(
            kind="bar",
            linewidth=0,
            stacked=True,
            ax=axe,
            legend=False,
            grid=True,
            **kwargs,
        )  # make bar plots

    h, l = axe.get_legend_handles_labels()  # get the handles we want to modify
    for i in range(0, n_df * n_col, n_col):  # len(h) = n_col * n_df
        for j, pa in enumerate(h[i : i + n_col]):
            for rect in pa.patches:  # for each index
                rect.set_x(rect.get_x() + 1 / float(n_df + 1) * i / float(n_col))
                rect.set_hatch(H * int(i / n_col) * 2)  # edited part
                rect.set_width(1 / float(n_df + 1))

    axe.set_xticks((np.arange(0, 2 * n_ind, 2) + 1 / float(n_df + 1)) / 2.0)
    axe.set_xticklabels(dfall[0].index, rotation=0)

    # Add invisible data to add another legend
    n = []
    for i in range(n_df):
        n.append(axe.bar(0, 0, color="gray", hatch=H * i * 5))
    if labels is not None:
        l2 = plt.legend(n, labels, loc=[0.85, 1.025])

    l1 = axe.legend(h[:n_col], l[:n_col])
    axe.add_artist(l1)
    axe.add_artist(l2)
    return axe


with open(sys.argv[1], "r") as fp:
    alldata = json.load(fp)
raw_nativedata = alldata["native"]
raw_linddata = alldata["lind"]

nativedata = {"data": [], "index": []}
linddata = {"data": [], "index": []}
for i in range(0, len(raw_nativedata["index"]), 4):
    nativedata["data"].extend(raw_nativedata["data"][i : i + 2])
    nativedata["index"].extend(raw_nativedata["index"][i : i + 2])
    linddata["data"].extend(raw_linddata["data"][i : i + 2])
    linddata["index"].extend(raw_linddata["index"][i : i + 2])

nativedf = pd.DataFrame(
    nativedata["data"],
    index=nativedata["index"],
    columns=["base_func", "kernel_func", "pipe_func", "copy_func"],
)
linddf = pd.DataFrame(
    linddata["data"],
    index=linddata["index"],
    columns=["base_func", "kernel_func", "pipe_func", "copy_func"],
)

plt.figure(figsize=(7, 5))
pd.set_option("display.max_rows", None, "display.max_columns", None)
sns.set(style="darkgrid")
sns.set_palette("muted")
fig = plot_clustered_stacked([nativedf, linddf], ["native", "lind"])
sns.move_legend(
    fig,
    "lower center",
    bbox_to_anchor=(0.425, 1),
    columnspacing=0.75,
    ncol=4,
    title="Syscall",
    frameon=False,
)

plt.xlabel("Buffer Exponents (r/w call)\nNative Time")
plt.ylabel("Lind/Native Time Ratio")
# plt.title(f"Stacked Syscall Ratios for Buffers: {sys.argv[2]}", y=-0.175, fontsize=16)
plt.tight_layout(pad=0.25)

plt.savefig(sys.argv[3], dpi=200)
