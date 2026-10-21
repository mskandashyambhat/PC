// Question: Demonstrate MPI_Scatter and MPI_Gather operations.

#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
    int rank, size, send[4] = {10, 20, 30, 40}, recv;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    MPI_Scatter(send, 1, MPI_INT, &recv, 1, MPI_INT, 0, MPI_COMM_WORLD);
    printf("Process %d received: %d\n", rank, recv);

    recv *= 10;

    MPI_Gather(&recv, 1, MPI_INT, send, 1, MPI_INT, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        printf("Gathered data: ");
        for (int i = 0; i < size; i++)
            printf("%d ", send[i]);
        printf("\n");
    }

    MPI_Finalize();
    return 0;
}

mpicc scatter_gather.c -o scatter_gather
mpirun -np 4 ./scatter_gather