
#include "system_includes.h"
#include "check_mpi_error.h"
#include "print_string.h"
#include "init_mpi.h"

int
main(int argc, char** argv)
{
    // mpi stuff
    MPI_Comm comm;
    int mpi_error;
    int my_mpi_rank;
    int mpi_size;
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
    comm = MPI_COMM_WORLD;
    success =  init_mpi(&argc, &argv, &my_mpi_rank, &mpi_size);

    if (success) {

        // open unique output file for each process
        my_lfp = NULL;
        offset = snprintf(my_lfp_name, base_filename_length, base_filename);
        file_threadname_start = offset - base_filename_length;
        snprintf(my_lfp_name + offset, file_threadname_start, "%d", my_mpi_rank);
        my_lfp = fopen(my_lfp_name, "a");

        fprintf(my_lfp, "\nHi from rank %d of %d!\n", my_mpi_rank, mpi_size);
        fflush(my_lfp);
    }

    //
    // main
    //

    if (success){

        if (my_mpi_rank == 0){

            // send argc
            buffer = argc;
            buffer_size = 1;
            mpi_error = MPI_Bcast(&buffer, buffer_size, MPI_INT, root, comm);
            success = check_mpi_error(my_lfp, "MPI_Bcast failed", comm, mpi_error);

            fprintf(my_lfp, "\nThe argc value is %d\n", argc);
            fflush(my_lfp);

            if (success) {

                // recieve sum of mpi_ranks
                buffer = 0;
                buffer_size = 1;
                mpi_error = MPI_Reduce(&my_mpi_rank, &buffer, buffer_size, MPI_INT, MPI_SUM, root, comm);
                success = check_mpi_error(my_lfp, "MPI_Reduce failed", comm, mpi_error);

                if (success) {

                    fprintf(my_lfp, "\nSum of MPI ranks: %d\n", buffer);
                    fflush(my_lfp);
                }
            }

        }
        else {

            // recieve argc
            buffer = 0;
            buffer_size = 1;
            mpi_error = MPI_Bcast(&buffer, buffer_size, MPI_INT, root, comm);
            success = check_mpi_error(my_lfp, "MPI_Bcast failed", comm, mpi_error);

            if (success) {

                fprintf(my_lfp, "\nI got an argc value of %d\n", buffer);
                fflush(my_lfp);
            }

            if (success) {

                // send my_mpi_rank for sum
                buffer = 0;
                buffer_size = 1;
                mpi_error = MPI_Reduce(&my_mpi_rank, &buffer, buffer_size, MPI_INT, MPI_SUM, root, comm);
                success = check_mpi_error(my_lfp, "MPI_Reduce failed", comm, mpi_error);
            }
        }
    }

    if (success) {
        // clean up MPI
        mpi_error = MPI_Finalize();
        check_mpi_error(my_lfp, "MPI_Finaize failed", comm, mpi_error);
    }

    return 0;
}
