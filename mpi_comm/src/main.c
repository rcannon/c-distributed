
#include "system_includes.h"
#include "check_mpi_error.h"
#include "print_string.h"
#include "init_mpi.h"
#include "mpi_comm_struct.h"

int
main(int argc, char** argv)
{
    // mpi stuff
	struct mpi_comm_struct my_mpi_struct;
    int mpi_error;
    int success;

    // rank output file stuff
    FILE* my_lfp;
    int offset;
    int file_threadname_start;
    char my_lfp_name[4096]; // max linux filename length
    int base_filename_length = 18;
    char* base_filename = "thread_files/out_";

    // problem
    int buffer;
    int buffer_size;
    int root;
    
    root = 0;

    // setup MPI
    my_comm_struct.comm = MPI_COMM_WORLD;
    success =  init_mpi(&argc, &argv, &my_mpi_struct);

    if (success) {

        // open unique output file for each process
        my_lfp = NULL;
        offset = snprintf(my_lfp_name, base_filename_length, base_filename);
        file_threadname_start = offset - base_filename_length;
        snprintf(my_lfp_name + offset, file_threadname_start, "%d", my_mpi_struct.mpi_rank);
        my_lfp = fopen(my_lfp_name, "a");

        fprintf(my_lfp, "\nHi from rank %d of %d!\n", my_mpi_struct.mpi_rank, my_mpi_struct.n_mpi_ranks);
        fflush(my_lfp);

		// setup MPI communication structure
		success = setup_mpi_nodes(my_lfp, &my_mpi_struct);
    }

    //
    // main
    //

    if (success) {
        // clean up MPI
        mpi_error = MPI_Finalize();
        check_mpi_error(my_lfp, "MPI_Finaize failed", my_mpi_struct.comm, mpi_error);
    }

    return 0;
}
