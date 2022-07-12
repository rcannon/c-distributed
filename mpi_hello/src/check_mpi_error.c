
#include "check_mpi_error.h"

int
check_mpi_error
    ( FILE* fp
    , char* message
    , MPI_Comm comm
    , int mpi_error
    )
{
    int success = 1;

    if (mpi_error != MPI_SUCCESS){
        success = 0;
        fprintf(fp, "%s\n", message);
        fprintf(fp, "Error was %d\n", mpi_error);
        fflush(fp);
        mpi_error = MPI_Abort(comm, 0);
    }
    return success;
}