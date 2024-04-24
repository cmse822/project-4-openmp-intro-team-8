#!/bin/bash --login
########## SBATCH Lines for Resource Request ##########

#SBATCH --time=1:00:00       # limit of wall clock time - how long the job will run (same as -t)
#SBATCH -A dicksonlab       # Do not remove!
#SBATCH --nodes=1                     # the number of node requested.
#SBATCH --ntasks=2                    # the number of task to run
#SBATCH --cpus-per-task=1      # the number of CPUs (or cores) per task (same as -c)
#SBATCH --mem=32G                  # total memory per node
#SBATCH --job-name 822_p4     # you can give your job a name for easier identification (same as -J)
#SBATCH --output=%x.out
#SBATCH --error=%x.err
########## Command Lines to Run ##########
module purge
module load gcc/7.3.0-2.30 openmpi hdf5 python git
 
scontrol show job $SLURM_JOB_ID     ### write job information to output file

mpic++ -fopenmp hello.cpp -o hello

export OMP_NUM_THREADS=4

mpirun -np 2 ./hello


