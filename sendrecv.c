// Question: Demonstrate point-to-point communication using MPI_Send and MPI_Recv.

#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
    int rank, data;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank == 0) {
        data = 100;
        MPI_Send(&data, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
        printf("Process 0 sent: %d\n", data);
    } else if (rank == 1) {
        MPI_Recv(&data, 1, MPI_INT, 0, 0,
                 MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Process 1 received: %d\n", data);
    }

    MPI_Finalize();
    return 0;
}

mpicc send_recv.c -o send_recv
mpirun -np 2 ./send_recv