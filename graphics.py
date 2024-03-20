import pandas as pd
import matplotlib.pyplot as plt
import numpy as np


def main(): 
    openMP_MMM_csv = 'nopenMP_mmm.csv'

    
    df = pd.read_csv(openMP_MMM_csv, low_memory=False)

    df_20 = pd.DataFrame(columns=['iterations', 'threads', 'runtime'])
    df_100 = pd.DataFrame(columns=['iterations', 'threads', 'runtime'])
    df_1000 = pd.DataFrame(columns=['iterations', 'threads', 'runtime'])

    for index, row in df.iterrows():
        if df[index][1] == 20:
            df_20.append(row)
        elif df[index][1] == 100:
            df_100.append(row)
        else:
            df_1000.append(row)


    # Create a plot for df_20
    plt.figure(figsize = (10,5))
    plt.scatter(df_20['threads'], df_20['runtime'], label='Number of threads vs runtime', linestyle='-', linewidth=1, color='blue')
    plt.xlabel('Number of Threads')
    plt.ylabel('Runtime (seconds)')
    plt.title("Num Threads vs Runtime for N=20")
    plt.savefig("NumThreadsVsRuntimeN=20.png")
    plt.legend(loc='upper left',)
    plt.grid(True)


    # Create a plot for df_100
    plt.figure(figsize = (10,5))
    plt.scatter(df_20['threads'], df_20['runtime'], label='Number of threads vs runtime', linestyle='-', linewidth=1, color='blue')
    plt.xlabel('Number of Threads')
    plt.ylabel('Runtime (seconds)')
    plt.title("Num Threads vs Runtime for N=20")
    plt.savefig("NumThreadsVsRuntimeN=20.png")
    plt.legend(loc='upper left',)
    plt.grid(True)

    # Create a plot for df_1000
    plt.figure(figsize = (10,5))
    plt.scatter(df_1000['threads'], df_1000['runtime'], label='Number of threads vs runtime', linestyle='-', linewidth=1, color='blue')
    plt.xlabel('Number of Threads')
    plt.ylabel('Runtime (seconds)')
    plt.title("Num Threads vs Runtime for N=1000")
    plt.savefig("NumThreadsVsRuntimeN=1000.png")
    plt.legend(loc='upper left',)
    plt.grid(True)


main()