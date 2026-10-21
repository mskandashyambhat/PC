// Question: Demonstrate MPI_Bcast operation in MPI.

#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
    int rank, value;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank == 0) {
        value = 100;
        printf("Root broadcasting value = %d\n", value);
    }

    MPI_Bcast(&value, 1, MPI_INT, 0, MPI_COMM_WORLD);

    printf("Process %d received value = %d\n", rank, value);

    MPI_Finalize();
    return 0;
}

mpicc broadcast.c -o broadcast
mpirun -np 4 ./broadcast