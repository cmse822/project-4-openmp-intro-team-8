import matplotlib.pyplot as plt
import numpy as np
import pandas as pd

# Load the data
data = pd.read_csv('data.csv')  # Make sure to use the correct file name

# Plotting time to solution vs. matrix size for different configurations
def plot_time_vs_matrix_size(data, mpi_ranks, threads_per_rank):
    '''
        Plot time to solution vs. matrix size for different configurations of MPI ranks and threads per rank
        
        Parameters:
            data (DataFrame): The performance data
            mpi_ranks (int): The number of MPI ranks
            threads_per_rank (int): The number of threads per rank
            
        Returns:
            None
    '''
    filtered_data = data[(data['MPI_Ranks'] == mpi_ranks) & (data['Threads_Per_Rank'] == threads_per_rank)]
    plt.figure(figsize=(10, 6))
    for size in filtered_data['Matrix_Size'].unique():
        subset = filtered_data[filtered_data['Matrix_Size'] == size]
        plt.plot(subset['Matrix_Size'], subset['Time'], marker='o', label=f'Size {size}')

    plt.xlabel('Matrix Size')
    plt.ylabel('Time to Solution (s)')
    plt.title(f'Time to Solution vs. Matrix Size (MPI Ranks: {mpi_ranks}, Threads/Rank: {threads_per_rank})')
    plt.legend()
    plt.grid(True)
    plt.show()

# Example usage for MPI Ranks = 2, Threads/Rank = 4

# Plotting time to solution for different MPI ranks and threads per rank for a fixed matrix size
def plot_time_vs_configurations(data, matrix_size):
    '''
        Plot a heatmap of time to solution for different configurations of MPI ranks and threads per rank

        Parameters:
            data (DataFrame): The performance data
            matrix_size (int): The matrix size to filter the data on
        
        Returns:
            None
    '''
    filtered_data = data[data['Matrix_Size'] == matrix_size]
    pivot_table = filtered_data.pivot("MPI_Ranks", "Threads_Per_Rank", "Time")

    plt.figure(figsize=(10, 6))
    sns.heatmap(pivot_table, annot=True, fmt=".2f", cmap="YlGnBu")
    plt.xlabel('Threads Per Rank')
    plt.ylabel('MPI Ranks')
    plt.title(f'Time to Solution Heatmap (Matrix Size: {matrix_size})')
    plt.show()


if __name__ == '__main__':
    plot_time_vs_matrix_size(data, mpi_ranks=2, threads_per_rank=4)
    plot_time_vs_configurations(data, matrix_size=)
