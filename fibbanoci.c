// Question: Calculate Fibonacci numbers using OpenMP tasks and compare execution times.

#include <stdio.h>
#include <omp.h>

long long fib_serial(int n) {
    if (n <= 1) return n;
    return fib_serial(n - 1) + fib_serial(n - 2);
}

long long fib_task(int n) {
    if (n <= 1) return n;

    long long x, y;

    #pragma omp task shared(x)
    x = fib_task(n - 1);

    #pragma omp task shared(y)
    y = fib_task(n - 2);

    #pragma omp taskwait
    return x + y;
}

int main() {
    int n;
    printf("Enter number of Fibonacci terms: ");
    scanf("%d", &n);

    double start = omp_get_wtime();
    printf("Serial Fibonacci Series:\n");
    for (int i = 0; i < n; i++)
        printf("%lld ", fib_serial(i));
    double st = omp_get_wtime() - start;
    printf("\nSerial Time = %f seconds\n", st);

    start = omp_get_wtime();
    printf("Parallel Fibonacci Series:\n");

    #pragma omp parallel
    {
        #pragma omp single
        for (int i = 0; i < n; i++)
            printf("%lld ", fib_task(i));
    }

    printf("\nParallel Time = %f seconds\n", omp_get_wtime() - start);
    return 0;
}

gcc -fopenmp fibonacci.c -o fibonacci
./fibonacci