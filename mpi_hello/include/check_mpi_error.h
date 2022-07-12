
#include "system_includes.h"
#include "mpi.h"

#ifndef _CHECK_MPI_ERROR_H_
#define _CHECK_MPI_ERROR_H_ 1

int
check_mpi_error
    ( FILE* my_lfp
    , char* message
    , MPI_Comm comm
    , int mpi_error
    );

#endif