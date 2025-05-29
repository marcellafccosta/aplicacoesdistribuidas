#include "openmp_config.h"
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main () 
{
	int nthreads, i, tid;
	float total = 0.0;
	double start_time, end_time;
    int n = 100000000;
	start_time = omp_get_wtime();
	/*** Spawn parallel region ***/
	#pragma omp parallel private(tid) shared(nthreads) reduction(+:total)
	{
		/* Obtain thread number */
		tid = omp_get_thread_num();
		/* Only master thread does this */
		if (tid == 0){
			nthreads = omp_get_num_threads();
			printf("Number of threads = %d\n", nthreads);
		}

		printf("Thread %d is starting...\n",tid);

		#pragma omp barrier
		/* do some work */
		
		#pragma omp for schedule(dynamic,10)
		
		for (i=0; i<n; i++){
			total += i * 1.0;
		}

		printf ("Thread %d is done! \n", tid);

	  } /*** End of parallel region ***/
	  end_time = omp_get_wtime();
	  printf("Time taken = %f seconds\n", end_time - start_time);
	  printf("Total = %f\n", total);


	  return 0;

}