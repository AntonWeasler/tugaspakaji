#include <mpi.h>
#include <stdio.h>
int main(int argc, char **argv)
{
int rank, size;
MPI_Init(&argc, &argv);
MPI_Comm_rank(MPI_COMM_WORLD, &rank);
MPI_Comm_size(MPI_COMM_WORLD, &size);
double local = rank + 1.0;
double max = 0.0;
MPI_Allreduce(&local, &max, 1, MPI_DOUBLE,

MPI_MAX, MPI_COMM_WORLD);
printf("rank=%d max=%.1f\n",
rank, max);
MPI_Finalize();
return 0;
}
