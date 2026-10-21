// Question: Divide loop iterations into static chunks of size 2 using OpenMP.

#include <stdio.h>
#include <omp.h>

int main() {
    int n;
    printf("Enter number of iterations: ");
    scanf("%d", &n);

    omp_set_schedule(omp_sched_static, 2);

    #pragma omp parallel
    {
        int tid = omp_get_thread_num();

        #pragma omp for schedule(runtime)
        for (int i = 0; i < n; i++)
            printf("Thread %d : Iteration %d\n", tid, i);
    }

    return 0;
}

gcc -fopenmp static.c -o static
OMP_NUM_THREADS=2 ./static