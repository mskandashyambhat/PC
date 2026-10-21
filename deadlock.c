// Question: Avoid MPI deadlock by altering the send and receive sequence.

#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
    int rank, data = 10, buf;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank == 0) {
        MPI_Send(&data, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
        MPI_Recv(&buf, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    } else if (rank == 1) {
        MPI_Recv(&buf, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Send(&data, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }

    printf("Process %d completed communication\n", rank);
    MPI_Finalize();
    return 0;
}

mpicc deadlock.c -o deadlock
mpirun -np 2 ./deadlock