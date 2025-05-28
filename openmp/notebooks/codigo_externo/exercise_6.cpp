#include "openmp_config.h"
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main () 
{
	int nthreads, i, tid;
	double total;

    double start_time, end_time;

    omp_set_num_threads(8); 


    start_time = omp_get_wtime();
	/*** Spawn parallel region ***/
	#pragma omp parallel private(tid)
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
        double local_total = 0.0;

        int n = 10000000;
		#pragma omp for schedule(dynamic,10) reduction(+:total)
		for (i=0; i<n; i++){
			total += i*1.0;
		}

		printf ("Thread %d is done!\n", tid);

	  } /*** End of parallel region ***/

      end_time = omp_get_wtime();
      printf("Time taken: %f seconds\n", end_time - start_time);
      printf("Total sum = %f\n", total);

      return 0;
}

