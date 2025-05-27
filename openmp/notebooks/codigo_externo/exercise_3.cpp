#include "openmp_config.h"
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#define VECLEN 10000

float a[VECLEN], b[VECLEN], sum;

float dotprod()
{
	
	int i, tid;
	tid = omp_get_thread_num();

	/*1 - O QUE ESTÁ ACONCENDO AQUI?*/
	#pragma omp for reduction(+:sum)
	for(i=0; i < VECLEN; i++){
		sum = sum + (a[i]*b[i]);
		printf("  tid= %d i=%d\n",tid,i);
	}

	return sum;
}


int main(){
	int i;
	double start_time, end_time;
	
	for(i=0; i < VECLEN; i++){
	  a[i] = b[i] = 1.0 * i;
	}

	sum = 0.0;
	omp_set_num_threads(8); 

	start_time = omp_get_wtime();
	/*2 - O QUE ESTÁ ACONCENDO AQUI?*/
	#pragma omp parallel
	{
		dotprod();
	}

	end_time = omp_get_wtime();
	printf("Time = %f seconds\n", end_time - start_time);
	printf("Sum = %f\n",sum);

	return 0;

}