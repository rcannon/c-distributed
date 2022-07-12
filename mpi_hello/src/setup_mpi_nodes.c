
#include "setup_mpi_nodes.h"

int
setup_mpi_nodes
    ( FILE* my_lfp 
    , int n_mpi_ranks
    )
{
    MPI_Comm comm;
    int success;
    int mpi_error;
    int root;

    int my_processor_name_length;
    my_processor_name_length = 64;
    char my_processor_name[my_processor_name_length];
    int max_proc_name_length_buffer;
    int max_proc_name_length_buffer_length;
    //int proc_names_array_length;

    comm = MPI_COMM_WORLD;
    root = 0;

    // get my processor name
    mpi_error = MPI_Get_processor_name(my_processor_name, &my_processor_name_length);
    success = check_mpi_error(my_lfp, "MPI_Get_processor_name failed", comm, mpi_error);
    print_string(my_lfp,"\nMy processor is");
    print_string(my_lfp, my_processor_name);
    fprintf(my_lfp, "proc name length: %d\n", my_processor_name_length);
    fflush(my_lfp);

    // find/ share maximum proceesor name length
    if (success) {
        max_proc_name_length_buffer_length = 1;
        mpi_error = MPI_Reduce
            ( &my_processor_name_length
            , &max_proc_name_length_buffer
            , max_proc_name_length_buffer_length
            , MPI_INT
            , MPI_MAX
            , root
            , comm
            );
        success = check_mpi_error(my_lfp, "MPI_Reduce failed", comm, mpi_error);

        fprintf(my_lfp, "\nMaximum processor name length is %d\n", max_proc_name_length_buffer);
        fflush(my_lfp);
    }

    //proc_names_array_length = max_proc_name_length * n_mpi_ranks;


    return success;
}
