import matplotlib
import pandas as pd
import seaborn as sns
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.ticker as ticker


labels = {
    "app" : "Benchmark",
    "l1_tlb_miss_rate": "Average L1-TLB Miss Rate (%)"
}

#xtick_labels = ["backprop", "bfs", "dwt2d", "gaussian", "hotspot", "hybridsort", "lavaMD", "lud", "nw", "particlefilter"]
#ordered_list = [9, 0, 3, 6, 2, 7, 5, 1, 4, 8]
ordered_list = ["particlefilter","backprop","gaussian","lud","hybridsort","hotspot","nw"]
fig, ax1 = plt.subplots(figsize=(50, 20))

df = pd.read_csv("stats-comparison.csv")
print(df)
list = list(df['benchmark'].unique())
print(list)


plt.style.use('seaborn-whitegrid')
plt.grid()
# charts = sns.barplot(
#      data=df,
#      x="benchmark", y="miss_rate", size=10
#  )

g = sns.catplot(
    data=df, kind="bar",
    x="benchmark", y="miss_rate", hue="run", alpha=.9, height=6
)
#
g.despine(left=True)
g.set_axis_labels(labels["app"], labels["l1_tlb_miss_rate"])
g.legend.set_title("")
#charts = sns.barplot(data=df, x="benchmark", y="miss_rate", dodge=False)
#ax1.set_axisbelow(True)
ax1.set_title("Average L1-TLB Miss Rates for gem5 GPU in SE Mode running Rodinia", size=50)
ax1.set_xticklabels(ordered_list, size=50)
ax1.set_yticklabels(ax1.get_yticks(), size=50)
ax1.set_xlabel(labels["app"], fontsize=50, fontweight=600,labelpad=20)
ax1.set_ylabel(labels["l1_tlb_miss_rate"], fontsize=50, fontweight=600,labelpad=20)
plt.savefig('./l1-tlb-miss-rate-comparison.png', bbox_inches='tight', dpi=300)
plt.close()
