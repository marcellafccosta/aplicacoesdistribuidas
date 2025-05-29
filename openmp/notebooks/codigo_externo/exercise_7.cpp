#include "openmp_config.h"
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main () 
{
	const int N=4192;
	int nthreads, tid, i, j;

	double start_time, end_time;

	double **a = (double **) malloc(N * sizeof(double *));
	for (i = 0; i < N; i++)
		a[i] = (double *) malloc(N * sizeof(double));

	
	start_time = omp_get_wtime();
	/* Fork a team of threads with explicit variable scoping */
	#pragma omp parallel shared(nthreads, a) private(i, j, tid)
	{
		/* Obtain/print thread info */
		tid = omp_get_thread_num();
		if(tid == 0) 
		{
			nthreads = omp_get_num_threads();
			printf("Number of threads = %d\n", nthreads);
		}
		printf("Thread %d starting...\n", tid);

		
		/* Each thread works on its own private copy of the array */
		#pragma omp for
		for (i=0; i<N; i++){
			for (j=0; j<N; j++){
			  a[i][j] = tid + i + j;
			}
		}

		/* For confirmation */
		printf("Thread %d done. Last element= %f\n",tid,a[N-1][N-1]);

	}  /* All threads join master thread and disband */

	for (i = 0; i < N; i++)
		free(a[i]);
	free(a);

	end_time = omp_get_wtime();
	printf("Time taken: %f seconds\n", end_time - start_time);

}