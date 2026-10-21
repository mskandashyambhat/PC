// Question: Demonstrate MPI_Reduce and MPI_Allreduce using MAX, MIN, SUM and PROD.

#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
    int rank, size, value, result;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    value = rank + 1;
    printf("Process %d has value %d\n", rank, value);

    MPI_Reduce(&value, &result, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    if (rank == 0) printf("Reduce SUM = %d\n", result);

    MPI_Reduce(&value, &result, 1, MPI_INT, MPI_PROD, 0, MPI_COMM_WORLD);
    if (rank == 0) printf("Reduce PRODUCT = %d\n", result);

    MPI_Reduce(&value, &result, 1, MPI_INT, MPI_MAX, 0, MPI_COMM_WORLD);
    if (rank == 0) printf("Reduce MAX = %d\n", result);

    MPI_Reduce(&value, &result, 1, MPI_INT, MPI_MIN, 0, MPI_COMM_WORLD);
    if (rank == 0) printf("Reduce MIN = %d\n", result);

    MPI_Allreduce(&value, &result, 1, MPI_INT, MPI_SUM, MPI_COMM_WORLD);
    printf("Process %d: Allreduce SUM = %d\n", rank, result);

    MPI_Allreduce(&value, &result, 1, MPI_INT, MPI_PROD, MPI_COMM_WORLD);
    printf("Process %d: Allreduce PRODUCT = %d\n", rank, result);

    MPI_Allreduce(&value, &result, 1, MPI_INT, MPI_MAX, MPI_COMM_WORLD);
    printf("Process %d: Allreduce MAX = %d\n", rank, result);

    MPI_Allreduce(&value, &result, 1, MPI_INT, MPI_MIN, MPI_COMM_WORLD);
    printf("Process %d: Allreduce MIN = %d\n", rank, result);

    MPI_Finalize();
    return 0;
}

mpicc reduce.c -o reduce
mpirun -np 4 ./reduce