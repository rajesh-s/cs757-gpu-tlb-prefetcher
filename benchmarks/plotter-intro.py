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
ordered_list = [9, 0, 3, 6, 2, 7, 5, 1, 4, 8]
#ordered_list = ["particlefilter", "backprop",  "lavaMD", "gaussian","dwt2d" , "lud", "hybridsort", "bfs", "hotspot" , "nw"]
ordered_list = ["particlefilter", "b+tree", "backprop", "gaussian", "lavaMD","dwt2d" , "lud", "pathfinder","hybridsort", "bfs", "hotspot" , "nw"]
fig, ax1 = plt.subplots(figsize=(50, 20))

df = pd.read_csv("stats-baseline.csv")
print(df)
list = list(df['benchmark'].unique())
print(list)


plt.style.use('seaborn-whitegrid')
plt.grid()

charts = sns.barplot(data=df, x="benchmark", y="miss_rate", dodge=False)
ax1.set_axisbelow(True)
ax1.set_title("Average L1-TLB Miss Rates for gem5 GPU in SE Mode running Rodinia", size=50)
ax1.set_xticklabels(ordered_list, size=50)
ax1.set_yticklabels(ax1.get_yticks(), size=50)
ax1.set_xlabel(labels["app"], fontsize=50, fontweight=600,labelpad=20)
ax1.set_ylabel(labels["l1_tlb_miss_rate"], fontsize=50, fontweight=600,labelpad=20)
plt.savefig('./l1-tlb-miss-rate-baseline.jpg', bbox_inches='tight', dpi=300)
plt.close()
