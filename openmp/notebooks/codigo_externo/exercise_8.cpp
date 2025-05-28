#include "openmp_config.h"
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

#define VECLEN 500

float a[VECLEN], b[VECLEN];

int main()
{
    int i;
    float sum = 0.0;
    double start_time, end_time;
    omp_set_num_threads(8); 

    for (i = 0; i < VECLEN; i++)
    {
        a[i] = b[i] = 1.0 * i;
    }

    start_time = omp_get_wtime();
#pragma omp parallel for reduction(+ : sum)
    for (i = 0; i < VECLEN; i++)
    {
        sum += a[i] * b[i];
    }

    end_time = omp_get_wtime();
    printf("Time taken: %f seconds\n", end_time - start_time);
    printf("Sum = %f\n", sum);

    return 0;
}
