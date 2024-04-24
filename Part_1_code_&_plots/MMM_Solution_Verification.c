#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#include <omp.h>
#include <stdlib.h>
#include <stdbool.h>

int main()
{
	int N = 5;
	int a[5][5] = {{1, 2, 3, 4, 5}, {1, 2, 3, 4, 5}, {1, 2, 3, 4, 5}, {1, 2, 3, 4, 5}, {1, 2, 3, 4, 5}};
	int b[5][5] = {{5, 4, 3, 2, 1}, {5, 4, 3, 2, 1}, {5, 4, 3, 2, 1}, {5, 4, 3, 2, 1}, {5, 4, 3, 2, 1}};
	int c[5][5] = {{0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}};

	#define NUM_THREADS 16
	#define totalIterations 1

	for(int thread_num = 1; thread_num < NUM_THREADS + 1; thread_num*=2) {
		omp_set_num_threads(thread_num);
		int c[5][5] = {{0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}};
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
