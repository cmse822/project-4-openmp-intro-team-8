#include "mpi.h"
#include <omp.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) 
{
    int numtasks, rank, provided;
    int required = MPI_THREAD_FUNNELED;

    MPI_Init_thread(&argc, &argv, required, &provided);
    MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int name_length = MPI_MAX_PROCESSOR_NAME;
    char proc_name[name_length];
    MPI_Get_processor_name(proc_name, &name_length);

    #pragma omp parallel
    {
        int thread_id = omp_get_thread_num();
        printf("MPI Rank: %d, Thread: %d, on node: %s\n", rank, thread_id, proc_name);
    }

    MPI_Finalize();
    return 0;
}
