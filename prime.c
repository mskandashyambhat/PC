// Question: Find prime numbers from 1 to n using OpenMP parallel for and compare times.

#include <stdio.h>
#include <omp.h>

int is_prime(int n) {
    if (n <= 1) return 0;

    for (int i = 2; i * i <= n; i++)
        if (n % i == 0) return 0;

    return 1;
}

int main() {
    int n;
    printf("Enter the value of n: ");
    scanf("%d", &n);

    double start = omp_get_wtime();
    printf("Serial Prime Numbers:\n");

    for (int i = 1; i <= n; i++)
        if (is_prime(i)) printf("%d ", i);

    double st = omp_get_wtime() - start;

    start = omp_get_wtime();
    printf("\nParallel Prime Numbers:\n");

    #pragma omp parallel for schedule(dynamic)
    for (int i = 1; i <= n; i++) {
        if (is_prime(i)) {
            #pragma omp critical
            printf("%d ", i);
        }
    }

    double pt = omp_get_wtime() - start;

    printf("\nSerial Execution Time: %f seconds\n", st);
    printf("Parallel Execution Time: %f seconds\n", pt);
    return 0;
}

gcc -fopenmp prime.c -o prime
./prime