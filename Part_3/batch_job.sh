#!/bin/bash --login

# Check if we are in the submission phase or the execution phase
if [ -z "$SLURM_JOB_ID" ]; then
    # Submission phase
    # Define the ranges for your variables
    mpi_ranks=(1 2 4)  # Example MPI ranks
    threads_per_rank=(1 2 4 8)  # Example OpenMP threads per rank

    # Loop over the configurations and submit jobs
    for ranks in "${mpi_ranks[@]}"; do
        for threads in "${threads_per_rank[@]}"; do
                sbatch --ntasks-per-node="$ranks" --cpus-per-task="$threads" $0 "$ranks" "$threads"
        done
    done
else
    # Execution phase

    ########## SBATCH Lines for Resource Request ##########
    #SBATCH --time=1:00:00                 # Limit of wall clock time
    #SBATCH --nodes=1                     # Number of nodes requested
    #SBATCH --mem=32G                     # Total memory per node
    #SBATCH --job-name=matrix_mult        # Job name for easier identification
    #SBATCH --output=%x-%j.out            # Standard output file name
    #SBATCH --error=%x-%j.err             # Standard error file name

    ########## Module and Environment Setup ##########
    module purge
    module load gcc/7.3.0-2.30 openmpi   # Load necessary modules

    # Read variables passed from the submission phase
    MPI_RANKS=$1
    THREADS_PER_RANK=$2

    mpic++ -fopenmp openMP_MPI_performance_test.cpp -o openMP_MPI_performance_test

    ########## Set Environment Variables ##########
    export OMP_NUM_THREADS=$THREADS_PER_RANK

    ########## Execution ##########
    mpirun -np $MPI_RANKS ./openMP_MPI_performance_test
fi
