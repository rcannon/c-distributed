
#include "init_mpi.h"

/*
    Setup basic MPI communication environment.
*/

int
init_mpi
    ( int* argc
    , char*** argv
    , int* my_mpi_rank_p
    , int* n_mpi_ranks_p
    )
{
    MPI_Comm comm;
    int mpi_error;
    int success;
    int my_mpi_rank;
    int n_mpi_ranks;

    success = 1;

    mpi_error = MPI_Init(argc, argv);
    comm = MPI_COMM_WORLD;
    success = check_mpi_error(stderr, "MPI_Init failed", comm,  mpi_error);

    if (success) {
        mpi_error = MPI_Comm_set_errhandler(comm, MPI_ERRORS_RETURN);
        success = check_mpi_error(stderr, "MPI_Comm_set_errhandler failed", comm, mpi_error);
    }

    if (success){
        mpi_error = MPI_Comm_rank(comm, &my_mpi_rank);
        success = check_mpi_error(stderr, "MPI_Comm_rank failed", comm, mpi_error);
    }

    if (success){
        mpi_error = MPI_Comm_size(comm, &n_mpi_ranks);
        success = check_mpi_error(stderr, "MPI_Comm_size failed", comm, mpi_error);
    }

    *my_mpi_rank_p = my_mpi_rank;
    *n_mpi_ranks_p = n_mpi_ranks;

    return success;
}