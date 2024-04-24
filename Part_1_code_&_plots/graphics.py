import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
import warnings

warnings.filterwarnings("ignore")

def main(): 
    openMP_MMM_csv = 'openMP_mmm.csv'

    
    df = pd.read_csv(openMP_MMM_csv, low_memory=False)

    print(df)

    df_20 = pd.DataFrame(columns=df.columns)
    df_100 = pd.DataFrame(columns=df.columns)
    df_1000 = pd.DataFrame(columns=df.columns)

    for index, row in df.iterrows():
        if row[0] == 20:
            row

            df_20 = pd.concat([df_20, pd.DataFrame([row])], ignore_index = True)
        elif row[0] == 100:
            df_100 = pd.concat([df_100, pd.DataFrame([row])], ignore_index = True)
        else:
            df_1000 = pd.concat([df_1000, pd.DataFrame([row])], ignore_index = True)

    print(df_20)
    print(df_100)
    print(df_1000)




    # Create a plot for df_20
    plt.figure(figsize = (10,5))
    plt.scatter(df_20[' Threads'], df_20[' Runtime'], label='Number of threads vs runtime', linestyle='-', linewidth=1, color='blue')
    plt.xlabel('Number of Threads')
    plt.ylabel('Runtime (seconds)')
    plt.title("Num Threads vs Runtime for N=20")
    plt.savefig("NumThreadsVsRuntimeN=20.png")
    plt.legend(loc='upper right',)
    plt.ylim(min(df_20[' Runtime']), max(df_20[' Runtime']))
    plt.grid(True)
    plt.show()


    # Create a plot for df_100
    plt.figure(figsize = (10,5))
    plt.scatter(df_100[' Threads'], df_100[' Runtime'], label='Number of threads vs runtime', linestyle='-', linewidth=1, color='blue')
    plt.xlabel('Number of Threads')
    plt.ylabel('Runtime (seconds)')
    plt.title("Num Threads vs Runtime for N=100")
    plt.savefig("NumThreadsVsRuntimeN=100.png")
    plt.legend(loc='upper right',)
    plt.grid(True)
    plt.show()

    # Create a plot for df_1000
    plt.figure(figsize = (10,5))
    plt.scatter(df_1000[' Threads'], df_1000[' Runtime'], label='Number of threads vs runtime', linestyle='-', linewidth=1, color='blue')
    plt.xlabel('Number of Threads')
    plt.ylabel('Runtime (seconds)')
    plt.title("Num Threads vs Runtime for N=1000")
    plt.savefig("NumThreadsVsRuntimeN=1000.png")
    plt.legend(loc='upper right',)
    plt.grid(True)
    plt.show()


main()
