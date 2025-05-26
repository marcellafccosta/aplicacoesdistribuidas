#include "openmp_config.h"
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>


int main() 
{
	int n= 50;
	int i, nthreads, tid;
	float a[n], b[n], c[n], d[n];

    double start_time, end_time;
    omp_set_num_threads(4);
    
	/* Some initializations */
	for(i=0; i<n; i++){
		a[i] = i * 1.5;
		b[i] = i + 22.35;
		c[i] = d[i] = 0.0;
	}

    start_time = omp_get_wtime();
	
	/*1 - O QUE ESTÁ ACONCENDO AQUI?*/
	#pragma omp parallel shared(a,b,c,d,nthreads) private(i,tid)
	{
		tid = omp_get_thread_num();
		if (tid == 0)			
		{
			nthreads = omp_get_num_threads();
			printf("Number of threads = %d\n", nthreads);
		}
		printf("Thread %d starting...\n",tid);
		
		/*2 - O QUE ESTÁ ACONCENDO AQUI?*/
		#pragma omp sections nowait
		{
			/*3 - O QUE ESTÁ ACONCENDO AQUI?*/
			#pragma omp section
			{
				printf("Thread %d doing section 1\n",tid);
				for(i=0; i<n; i++){
				  c[i] = a[i] + b[i];
					printf("Thread %d: c[%d]= %f\n",tid,i,c[i]);
				}
			}

			/*4 - O QUE ESTÁ ACONCENDO AQUI?*/
			#pragma omp section
			{
				printf("Thread %d doing section 2\n",tid);
				for(i=0; i<n; i++){
					d[i] = a[i] * b[i];
					printf("Thread %d: d[%d]= %f\n",tid,i,d[i]);
				}
			}

		}  

		printf("Thread %d done.\n",tid); 

	  }  

    end_time = omp_get_wtime();
    printf("Tempo total: %f segundos\n", end_time - start_time);
}