import matplotlib.pyplot as plt
import pandas as pd
import seaborn as sns

# Load the data
data = pd.read_csv('performance_data.csv')

def plot_time_vs_mpi_ranks_by_matrix_size(data):
    '''
    Plot time to solution vs. MPI ranks for each matrix size in separate subplots.
    '''
    matrix_sizes = data['Matrix_Size'].unique()
    fig, axes = plt.subplots(nrows=len(matrix_sizes), ncols=1, figsize=(12, 8), sharex=True, sharey=True)
    
    for ax, matrix_size in zip(axes, matrix_sizes):
        for threads_per_rank in data['Threads_Per_Rank'].unique():
            subset = data[(data['Matrix_Size'] == matrix_size) & (data['Threads_Per_Rank'] == threads_per_rank)]
            ax.plot(subset['MPI_Ranks'], subset['Time'], marker='o', linestyle='-', label=f'Threads {threads_per_rank}')
        ax.set_title(f'Matrix Size: {matrix_size}')
        ax.grid(True)
        ax.set_xlabel('MPI Ranks')
        ax.set_ylabel('Time to Solution (s)')
        if ax == axes[-1]:
            ax.legend()

    plt.tight_layout()
    plt.show()

def plot_time_vs_matrix_size_by_mpi_rank(data):
    '''
    Plot time to solution vs. matrix size for each MPI rank in separate subplots.
    '''
    mpi_ranks = data['MPI_Ranks'].unique()
    fig, axes = plt.subplots(nrows=len(mpi_ranks), ncols=1, figsize=(12, 8), sharex=True, sharey=True)
    
    for ax, mpi_rank in zip(axes, mpi_ranks):
        for threads_per_rank in data['Threads_Per_Rank'].unique():
            subset = data[(data['MPI_Ranks'] == mpi_rank) & (data['Threads_Per_Rank'] == threads_per_rank)]
            ax.plot(subset['Matrix_Size'], subset['Time'], marker='o', linestyle='-', label=f'Threads {threads_per_rank}')
        ax.set_title(f'MPI Ranks: {mpi_rank}')
        ax.grid(True)
        ax.set_xlabel('Matrix Size')
        ax.set_ylabel('Time to Solution (s)')
        if ax == axes[-1]:
            ax.legend()

    plt.tight_layout()
    plt.show()
    
def plot_heatmap_for_matrix_size(data, matrix_size):
    '''
    Plot a heatmap showing time to solution for different configurations of MPI ranks and threads per rank for a given matrix size.
    '''
    plt.figure(figsize=(10, 6))
    subset = data[data['Matrix_Size'] == matrix_size]
    pivot_table = subset.pivot("MPI_Ranks", "Threads_Per_Rank", "Time")
    sns.heatmap(pivot_table, annot=True, fmt=".2f", cmap="YlGnBu")
    plt.xlabel('Threads Per Rank')
    plt.ylabel('MPI Ranks')
    plt.title(f'Time to Solution Heatmap (Matrix Size: {matrix_size})')
    plt.show()

if __name__ == '__main__':
    plot_time_vs_mpi_ranks_by_matrix_size(data)
    plot_time_vs_matrix_size_by_mpi_rank(data)


    matrix_sizes = [20, 100, 500]
    for matrix_size in matrix_sizes:
        plot_heatmap_for_matrix_size(data, matrix_size)
        

