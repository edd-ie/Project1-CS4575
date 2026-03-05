#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>
#include <mpi.h>

int main(int argc, char **argv)
{
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (argc < 3)
    {
        if (rank == 0)
            printf("Usage: mpirun -np {processors} ./main {mode} {threads}\n");
        MPI_Finalize();
        return 1;
    }

    const int mode = atoi(argv[1]);
    const int threads = atoi(argv[2]);

    MPI_Finalize();
    return 0;
}