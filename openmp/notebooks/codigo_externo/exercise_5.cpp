#include "openmp_config.h"
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
    const int N = 50;
    const int CHUNKSIZE = 5;

    int i, chunk, tid;
    float a[N], b[N], c[N];

    double start_time, end_time;

    /* Some initializations */
    for (i = 0; i < N; i++)
    {
        a[i] = b[i] = i * 1.0;
    }

    chunk = CHUNKSIZE;

    omp_set_num_threads(8);
    start_time = omp_get_wtime();

#pragma omp parallel for shared(a, b, c, chunk) private(i, tid) schedule(static, chunk)
    for (i = 0; i < N; i++)
    {
        tid = omp_get_thread_num();
        c[i] = a[i] + b[i];
        printf("tid= %d i= %d c[i]= %f\n", tid, i, c[i]);
    }
    /* end of parallel for construct */

    end_time = omp_get_wtime();
    printf("Time: %f seconds\n", end_time - start_time);

    return 0;
}
