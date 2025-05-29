#include "openmp_config.h"

#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
	const int NRA = 248; /* number of rows in matrix A */
	const int NCA = 60;	 /* number of columns in matrix A */
	const int NCB = 28;	 /* number of columns in matrix B */

	int tid, nthreads, i, j, k, chunk;
	double a[NRA][NCA], /* matrix A to be multiplied */
		b[NCA][NCB],	/* matrix B to be multiplied */
		c[NRA][NCB];	/* result matrix C */

	double start_time, end_time;

	chunk = 10;

	start_time = omp_get_wtime();
/*1 - O QUE ESTÁ ACONCENDO AQUI?*/
#pragma omp parallel shared(a, b, c, nthreads, chunk) private(tid, i, j, k)
	{

		tid = omp_get_thread_num();
		if (tid == 0)
		{
			nthreads = omp_get_num_threads();
			printf("Starting matrix multiple example with %d threads\n", nthreads);
			printf("Initializing matrices...\n");
		}

/*2 - O QUE ESTÁ ACONCENDO AQUI?*/
#pragma omp for schedule(static, chunk)
		for (i = 0; i < NRA; i++)
		{
			for (j = 0; j < NCA; j++)
			{
				a[i][j] = i + j;
			}
		}
/*3 - O QUE ESTÁ ACONCENDO AQUI?*/
#pragma omp for schedule(static, chunk)
		for (i = 0; i < NCA; i++)
		{
			for (j = 0; j < NCB; j++)
			{
				b[i][j] = i * j;
			}
		}
/*4 - O QUE ESTÁ ACONCENDO AQUI?*/
#pragma omp for schedule(static, chunk)
		for (i = 0; i < NRA; i++)
		{
			for (j = 0; j < NCB; j++)
			{
				c[i][j] = 0;
			}
		}

		/*5 - O QUE ESTÁ ACONCENDO AQUI?*/
		printf("Thread %d starting matrix multiply...\n", tid);
#pragma omp for schedule(static, chunk)
		for (i = 0; i < NRA; i++)
		{
			printf("Thread=%d did row=%d\n", tid, i);
			for (j = 0; j < NCB; j++)
			{
				for (k = 0; k < NCA; k++)
				{
					c[i][j] += a[i][k] * b[k][j];
				}
			}
		}

	} /*** End of parallel region ***/

	end_time = omp_get_wtime();

	/*** Print results ***/
	printf("******************************************************\n");
	printf("Result Matrix:\n");
	for (i = 0; i < NRA; i++)
	{
		for (j = 0; j < NCB; j++)
		{
			printf("%6.2f   ", c[i][j]);
		}
		printf("\n");
	}
	printf("******************************************************\n");
	printf("Done.\n");
	printf("Time taken: %f seconds\n", end_time - start_time);
}
