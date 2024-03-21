#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#include <omp.h>
#include <stdlib.h>
#include <stdbool.h>

//#define N 20

static int rrand(float value)
{
    return ((float)value * (rand() / (RAND_MAX + 1.0)));
}

static float** randomize(int size)
{
    // TODO: Fix pointers to create randomized matrices.
    float** arr = (float**)malloc(size * sizeof(float*));

    for (int idx = 0; idx < size; idx++)
    {
        arr[idx] = (float*)malloc(size * sizeof(float));
        for (int idy = 0; idy < size; idy++) 
        { 
            arr[idx][idy] = (float)rand() / RAND_MAX;
        }
    }

    return arr;
}

int main()
{

    // Check if file exists to avoid overwriting headers
    const char *csv_file_name="openMP_mmm.csv";

    FILE *outputFile = fopen(csv_file_name, "a");

    // Check if the file is open
    if (outputFile == NULL) {
        // Failed to open the file
        fprintf(stderr, "Error: Failed to open file for appending.\n");
        return 1;
    }

    // Write headers if the file is newly created
    fseek(outputFile, 0, SEEK_END); // Move to the end of the file
    long fileSize = ftell(outputFile); // Get the current position (file size)
    if (fileSize == 0) { // Check if the file is empty
        fprintf(outputFile, "Matrix Size, Iterations, Threads, Runtime\n");
    }



    int matrix_size[3] = {20,100,1000};

    for (int i = 0; i < 3; i++) {
        int n = matrix_size[i];
        int N = n;
        float** c = randomize(n);
        float** a = randomize(n);
        float** b = randomize(n);
        

        #define NUM_THREADS 16
        #define totalIterations 10

        for (int thread_num = 1; thread_num < NUM_THREADS + 1; thread_num*=2) {
            omp_set_num_threads(thread_num);
            for (int iter = 0; iter < totalIterations + 1; iter++){
                double start_time = omp_get_wtime();

                #pragma omp parallel
                {
                    int threadnum = omp_get_thread_num(), 
                    numthreads = omp_get_num_threads();

                    #pragma omp for collapse(2)
                    for (int idx = 0; idx < n; idx++)
                    {
                        for (int idy = 0; idy < n; idy++)
                        {
                            for (int idz = 0; idz < n; idz++)
                            {
                                // TODO: Make sure c is updated accordingly.
                                c[idx][idy] += a[idx][idz] * b[idz][idy];
                            }
                        }
                    }
                }

                double end_time = omp_get_wtime();
                double run_time = end_time - start_time;
                printf("Runtime information %d, %d, %d, %f\n", N, iter, thread_num, run_time);
                // Writing the data
                fprintf(outputFile, "%d, %d, %d, %f\n", N, iter, thread_num, run_time);

            }
        }
    }
    


    fclose(outputFile);

    return 0;
}
