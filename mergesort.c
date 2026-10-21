// Question: Write an OpenMP program for sequential and parallel merge sort using sections.

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

void merge(int a[], int l, int m, int r) {
    int n1 = m - l + 1, n2 = r - m;
    int *L = malloc(n1 * sizeof(int)), *R = malloc(n2 * sizeof(int));

    for (int i = 0; i < n1; i++) L[i] = a[l + i];
    for (int j = 0; j < n2; j++) R[j] = a[m + 1 + j];

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2)
        a[k++] = (L[i] <= R[j]) ? L[i++] : R[j++];

    while (i < n1) a[k++] = L[i++];
    while (j < n2) a[k++] = R[j++];

    free(L);
    free(R);
}

void serial(int a[], int l, int r) {
    if (l < r) {
        int m = (l + r) / 2;
        serial(a, l, m);
        serial(a, m + 1, r);
        merge(a, l, m, r);
    }
}

void parallel(int a[], int l, int r, int depth) {
    if (l < r) {
        int m = (l + r) / 2;

        if (depth <= 3) {
            #pragma omp parallel sections
            {
                #pragma omp section
                parallel(a, l, m, depth + 1);

                #pragma omp section
                parallel(a, m + 1, r, depth + 1);
            }
        } else {
            serial(a, l, m);
            serial(a, m + 1, r);
        }
        merge(a, l, m, r);
    }
}

int main() {
    int n;
    printf("Enter number of elements: ");
    scanf("%d", &n);

    int *a = malloc(n * sizeof(int));
    int *b = malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) a[i] = b[i] = rand() % 10000;

    double start = omp_get_wtime();
    serial(a, 0, n - 1);
    double st = omp_get_wtime() - start;

    start = omp_get_wtime();
    parallel(b, 0, n - 1, 1);
    double pt = omp_get_wtime() - start;

    printf("Sequential time: %f seconds\n", st);
    printf("Parallel time: %f seconds\n", pt);
    printf("Speedup: %.2fx\n", st / pt);

    free(a);
    free(b);
    return 0;
}


gcc -fopenmp merge.c -o merge
./merge