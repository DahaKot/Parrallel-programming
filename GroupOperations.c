#include <mpi.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    MPI_Init(&argc, &argv);
    const int Data_size = 1000000;

    int N = 0;
    MPI_Comm_size(MPI_COMM_WORLD, &N);

    if (N < 1) {
        printf("Try more processes\n");
        return -1;
    }

    int Rank = -1;
    MPI_Comm_rank(MPI_COMM_WORLD, &Rank);

    int buf[Data_size];
    if (Rank == 0) {
        for (int i = 0; i < Data_size; i++) {
            buf[i] = i;
        }
        printf("Wtick is: %lg\n", MPI_Wtick());
    }

    MPI_Barrier(MPI_COMM_WORLD);

    double start = MPI_Wtime();

    MPI_Bcast(buf, Data_size, MPI_INT, 0, MPI_COMM_WORLD);

    double end = MPI_Wtime();

    printf("%d Broadcast time: %lg\n", Rank, end - start);

    MPI_Finalize();

    return 0;
}