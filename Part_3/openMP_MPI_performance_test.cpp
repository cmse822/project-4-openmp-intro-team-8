#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <omp.h>

int main(int argc, char *argv[])
{
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    FILE *fp;
    if (rank == 0)
    {
        char filename[256];
        sprintf(filename, "performance_data_%d.csv", size);
        fp = fopen(filename, "w");
        fprintf(fp, "MPI_Ranks,Threads_Per_Rank,Matrix_Size,Time\n");
    }

    int matrix_sizes[] = {20, 100, 500}; 
    int num_threads_options[] = {1, 2, 4, 8, 16};
    int num_matrix_sizes = sizeof(matrix_sizes) / sizeof(matrix_sizes[0]);
    int num_thread_options = sizeof(num_threads_options) / sizeof(num_threads_options[0]);

    for (int matrix_index = 0; matrix_index < num_matrix_sizes; matrix_index++)
    {
        int N = matrix_sizes[matrix_index];
        int a[N][N], b[N][N], c[N][N];

        // Initialize matrices only on rank 0
        if (rank == 0)
        {
            for (int i = 0; i < N; i++)
            {
                for (int j = 0; j < N; j++)
                {
                    a[i][j] = i + j;
                    b[i][j] = i - j;
                }
            }
        }

        MPI_Bcast(a, N * N, MPI_INT, 0, MPI_COMM_WORLD);

        for (int thread_option_index = 0; thread_option_index < num_thread_options; thread_option_index++)
        {
            int threads_per_rank = num_threads_options[thread_option_index];
            omp_set_num_threads(threads_per_rank);

            int rows_per_rank = N / size;
            int local_b[rows_per_rank][N];
            MPI_Scatter(b, rows_per_rank * N, MPI_INT, local_b, rows_per_rank * N, MPI_INT, 0, MPI_COMM_WORLD);

            double start_time = MPI_Wtime();

            #pragma omp parallel for collapse(2)
            for (int i = 0; i < rows_per_rank; i++)
            {
                for (int j = 0; j < N; j++)
                {
                    c[i][j] = 0;
                    for (int k = 0; k < N; k++)
                    {
                        c[i][j] += local_b[i][k] * a[k][j];
                    }
                }
            }

            // Gather the partial results back to rank 0
            MPI_Gather(c, rows_per_rank * N, MPI_INT, b, rows_per_rank * N, MPI_INT, 0, MPI_COMM_WORLD);

            double end_time = MPI_Wtime();
            double time_to_solve = end_time - start_time;

            if (rank == 0)
            {
                fprintf(fp, "%d,%d,%d,%f\n", size, threads_per_rank, N, time_to_solve);
            }
        }
    }

    if (rank == 0)
    {
        fclose(fp);
    }

    MPI_Finalize();
    return 0;
}
