#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#include <omp.h>
#include "get_walltime.c"

#define N 50

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

    
    double start_time;
    get_walltime(&start_time);

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

    double end_time;
    get_walltime(&end_time);
    printf("Time for MMM: %f seconds\n", end_time - start_time);

    return 0;
}