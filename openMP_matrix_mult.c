#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#include <omp.h>

#define N 20

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
    int n = N;
    float** c = randomize(n);
    float** a = randomize(n);
    float** b = randomize(n);
    // TODO: Check if the matrices updated.

    // TODO: Add timers for the performance meajurements

    #define NUM_THREADS 4
    omp_set_num_threads(NUM_THREADS);

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
    printf("Time for MMM: %f seconds\n", end_time - start_time);

    return 0;
}