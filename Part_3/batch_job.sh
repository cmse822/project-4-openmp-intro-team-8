#!/bin/bash --login
########## SBATCH Lines for Resource Request ##########

#SBATCH --time=1:00:00                 # Limit of wall clock time - how long the job will run
#SBATCH --nodes=1                     # Number of nodes requested
#SBATCH --ntasks-per-node=2           # Number of MPI ranks per node
#SBATCH --cpus-per-task=4             # Number of OpenMP threads per MPI rank (or CPUs per task)
#SBATCH --mem=32G                     # Total memory per node
#SBATCH --job-name=matrix_mult        # Job name for easier identification
#SBATCH --output=%x-%j.out            # Standard output file name, %x is job name, %j is job id
#SBATCH --error=%x-%j.err             # Standard error file name, %x is job name, %j is job id

########## Module and Environment Setup ##########
module purge                          # Clear any inherited modules
module load gcc/7.3.0-2.30 openmpi hdf5 python git  # Load necessary modules

echo "Job Information:"
scontrol show job $SLURM_JOB_ID       # Write job information to output file

########## Compilation ##########
mpic++ -fopenmp openMP_MPI_matrix_mult.cpp -o openMP_MPI_matrix_mult  # Compile the program with MPI and OpenMP support

########## Set Environment Variables ##########
export OMP_NUM_THREADS=$SLURM_CPUS_PER_TASK  # Set the number of OpenMP threads per MPI rank

########## Execution ##########
mpirun -np $SLURM_NTASKS ./openMP_MPI_matrix_mult      # Run the program with MPI, number of ranks as requested

