#include "openmp_config.h"
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#define VECLEN 10000

float a[VECLEN], b[VECLEN];

int main() {
    int i;
    float total_sum = 0.0;
    double start_time, end_time;

    for (i = 0; i < VECLEN; i++) {
        a[i] = b[i] = 1.0 * i;
    }

    start_time = omp_get_wtime();

    #pragma omp parallel for reduction(+:total_sum)
    for (i = 0; i < VECLEN; i++) {
        int tid = omp_get_thread_num();
        total_sum += a[i] * b[i];
        printf("  tid= %d i=%d\n", tid, i);
    }

    end_time = omp_get_wtime();

    printf("Sum = %f\n", total_sum);
    printf("Time taken: %f seconds\n", end_time - start_time);

    return 0;
}
