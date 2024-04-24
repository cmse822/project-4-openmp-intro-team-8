#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#include <omp.h>
#include <mpi.h>
#include <stdlib.h>
#include <stdbool.h>

int main(int argc, char *argv[])
{
	//int N[3] = {20,100,1000};
    int a[20][20] = {{0}};
    int b[20][20] = {{0}};
    int c[20][20] = {{0}};
    
    // for(int j = 0; j < 20; j++) {
    //     for(int k = 0; k < 20; k++) {
    //         printf("%d ", b[j][k]);
    //     }
    //     printf("\n");
    // }

    int rank, size; 
    
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);



    if (rank == 0)
    {
        for (int j = 0; j < 20; j++)
        {
            for (int k = 0; k < 20; k++)
            {
                a[j][k] = k + 1;
                b[j][k] = 20 - (k);
            }
        }
    }

    // Broadcast matrix a to all ranks
    MPI_Bcast(a, 20 * 20, MPI_INT, 0, MPI_COMM_WORLD);

    // Scatter rows of matrix b among the ranks
    int rows_per_rank = 20 / size; // Assuming the number of ranks divides 20 evenly
    int local_b[rows_per_rank][20];
    MPI_Scatter(b, rows_per_rank * 20, MPI_INT, local_b, rows_per_rank * 20, MPI_INT, 0, MPI_COMM_WORLD);

    #define NUM_THREADS 16
    #define totalIterations 1
    int N = 20;

    for(int thread_num = 1; thread_num < NUM_THREADS + 1; thread_num*=2) {
        omp_set_num_threads(thread_num);
        int c[20][20] = {{0}};
        for(int iter = 0; iter < totalIterations + 1; iter++) {
            // int actual_n_threads;
            // int message_size = 2;
            // int processA,processB;
            // processA = 0; processB = 1;
            int c_local[20][20] = {{0}}; // Each thread will have its local result matrix

            #pragma omp parallel
            {
                // int threadnum = omp_get_thread_num(),
                // numthreads = omp_get_num_threads();
                // actual_n_threads = numthreads;
                // char *buffer = (char *)malloc(message_size * sizeof(char));
                #pragma omp for collapse(2)

                    for(int idx = 0; idx < N; idx++) {
                        for(int idy = 0; idy < N; idy++) {
                            for(int idz = 0; idz < N; idz++) {
                                c_local[idx][idy] += a[idx][idz] * b[idz][idy];
                            }
                        }
                }
            
            }
            // Accumulate local results into global result matrix c
            MPI_Reduce(c_local, c, 20 * 20, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
            
        }
        printf("NumThreads: %d\n", thread_num);
        for(int i = 0; i < N; i++) {
            for(int j = 0; j < N; j++) {
                printf("%d ", c[i][j]);
            }
            printf("\n");
        }
    }

    MPI_Finalize();
    return 0;
}
