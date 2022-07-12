
#include "system_includes.h"
#include "check_mpi_error.h"
#include "print_string.h"

#ifndef _SETUP_MPI_NODES_H_
#define _SETUP_MPI_NODES_H_ 1

int
setup_mpi_nodes
    ( FILE* my_lfp 
    , int n_mpi_ranks
    );

#endif