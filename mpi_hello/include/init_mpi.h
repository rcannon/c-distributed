
#include "system_includes.h"
#include "check_mpi_error.h"
#include "print_string.h"

#ifndef _INIT_MPI_H_
#define _INIT_MPI_H_ 1

int
init_mpi
    ( int* argc
    , char*** argv
    , int* my_mpi_rank_p
    , int* n_mpi_ranks_p
    );

#endif

