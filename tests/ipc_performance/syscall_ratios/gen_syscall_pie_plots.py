import pandas as pd
import matplotlib.cm as cm
import numpy as np
import matplotlib.pyplot as plt
import seaborn as sns
import json
import sys


with open(sys.argv[1], "r") as fp:
    alldata = json.load(fp)
raw_nativedata = alldata["native"]
raw_linddata = alldata["lind"]

pd.set_option("display.max_rows", None, "display.max_columns", None)
sns.set(style="darkgrid")
sns.set_palette("bright")

for i in range(len(raw_nativedata["index"])):

    try:
        config, r_or_w, lind_time = raw_linddata['index'][i].split()
        config, r_or_w, native_time = raw_nativedata['index'][i].split()
        r_or_w = r_or_w[1:-1].capitalize()
        r, w = config.split('-')

        fig, axes = plt.subplots(1, 2, figsize=(7, 4))
        fig.suptitle(f"{r_or_w} Syscall {config}\n$2^{'{' + r + '}' if r_or_w == 'Read' else '{' + w + '}'}$ Total Calls")
        
        axes[0].pie(
            raw_nativedata["data"][i][:4],
            labels=None,
            autopct="%1.1f%%",
            pctdistance=1.25,
        )
        axes[0].set_title(f"Average call time: {native_time}")
        axes[1].pie(
            raw_linddata["data"][i][:4],
            labels=None,
            autopct="%1.1f%%",
            radius=int(lind_time[:-2]) / int(native_time[:-2]),
            pctdistance=1.4,
        )
        axes[1].set_title(f"Average call time: {lind_time}")
        fig.legend(labels=["Switch", "Syscall", "Pipe", "Copy"], loc='upper center')

        sns.move_legend(
            fig,
            "lower center",
            title="Syscall",
            frameon=True,
        )

        plt.tight_layout()

        plt.savefig(f"plots/syscall_pie/{sys.argv[2]}/{raw_nativedata['index'][i].split()[0]}.png")
    except Exception as e:
        print(f"Failed to generate: {sys.argv[2]}/{raw_nativedata['index'][i].split()[0]}.png")
