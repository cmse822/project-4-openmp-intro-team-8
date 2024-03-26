#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
// #include <omp.h>
#include <stdlib.h>
#include <stdbool.h>

int main()
{
	int N[3] = {20,100,1000};
    int a[20][20] = {{0}};
    int b[20][20] = {{0}};
    int c[20][20] = {{0}};
    for(int j = 0; j < 20; j++) {
        for(int k = 0; k < 20; k++) {
            a[j][k] = k+1;
            b[j][k] = 20-(k);
        }
    }
    for(int j = 0; j < 20; j++) {
        for(int k = 0; k < 20; k++) {
            printf("%d ", b[j][k]);
        }
        printf("\n");
    }

    #define NUM_THREADS 16
    #define totalIterations 1

    for(int thread_num = 1; thread_num < NUM_THREADS + 1; thread_num*=2) {
        omp_set_num_threads(thread_num);
        int c[20][20] = {{0}};
        for(int iter = 0; iter < totalIterations + 1; iter++) {
            int actual_n_threads;
            #pragma omp parallel
            {
                int threadnum = omp_get_thread_num(),
                numthreads = omp_get_num_threads();
                actual_n_threads = numthreads;
                #pragma omp for collapse(2)
                for(int idx = 0; idx < N; idx++) {
                    for(int idy = 0; idy < N; idy++) {
                        for(int idz = 0; idz < N; idz++) {
                            c[idx][idy] += a[idx][idz] * b[idz][idy];
                        }
                    }
                }
            }
        }
        printf("NumThreads: %d\n", thread_num);
        for(int i = 0; i < N; i++) {
            for(int j = 0; j < N; j++) {
                printf("%d ", c[i][j]);
            }
            printf("\n");
        }
    }
}
