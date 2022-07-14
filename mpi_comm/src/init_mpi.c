
#include "init_mpi.h"

/*
    Setup basic MPI communication environment.
*/

int
init_mpi
    ( int* argc
    , char*** argv
 	, struct mpi_comm_struct * my_comm_struct
	)
{
    MPI_Comm comm;
    int mpi_error;
    int success;
    int my_mpi_rank;
    int n_mpi_ranks;

    success = 1;

    mpi_error = MPI_Init(argc, argv);
    comm = my_mpi_struct->comm;
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

    my_mpi_struct->mpi_rank = my_mpi_rank;
    my_mpi_struct->n_mpi_ranks = n_mpi_ranks;

    return success;
}
