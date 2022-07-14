
#include "setup_mpi_nodes.h"

int
setup_mpi_nodes
    ( FILE* my_lfp 
	, struct mpi_comm_struct * my_mpi_struct
    )
{
    int success;
    int mpi_error;

	int save_errno;

    int my_processor_name_length;
    my_processor_name_length = 64;
    char my_processor_name[my_processor_name_length];
    int max_proc_name_length_buffer;
    int proc_names_length;
	size_t proc_names_array_length;
	int64_t one_l;
	size_t ask_for;
	char* proc_names_list;
	int* displacements;
	int* gatherv_recieve_counts;
	int* mpi_rank_order_list;
	int i;

    root = 0;

    // get my processor name
    mpi_error = MPI_Get_processor_name(my_processor_name, &my_processor_name_length);
    success = check_mpi_error(my_lfp, "MPI_Get_processor_name failed",my_mpi_struct->comm, mpi_error);
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
            , 1 /* since max_proc_name_length_buffer is integer */
            , MPI_INT
            , MPI_MAX
            , root
            , my_mpi_struct->comm
            );
        success = check_mpi_error(my_lfp, "MPI_Reduce failed", my_mpi_struct->comm, mpi_error);
        fprintf(my_lfp, "\nMaximum processor name length is %d\n", max_proc_name_length_buffer);
        fflush(my_lfp);
    }
	
	if (success) {

		// find next power of two greater than max_prox_name_length
		proc_name_length = 1;
		while (proc_names_length < max_proc_name_length_buffer) {
			proc_name_length << 1;
		}
	}

	if (my_mpi_struct->mpi_rank == 0){

		if (success){

			// allocate array for processor names
			proc_names_array_length = proc_name_length * my_mpi_struct->n_mpi_ranks;
			one_l = (int64_t) 1;
			ask_for proc_names_array_length * sizeof(char);
			proc_names_list = (char *) calloc(one_1, ask_for);
			save_errno = errno;
			if (!(proc_names_list)) {
				success = 0;
				fprintf
					( my_lfp
					, "calloc: allocate proc_names_list failed with errno = %d, %s\n"
					, save_errno
					, strerror(save_errno)
					);
				fflush(my_lfp);
			}
		}

		// allocate array of displacements
		if (success) {

			ask_for = sizeof(int) * my_mpi_struct->n_mpi_ranks;
			displacements = (int*) calloc(one_l, ask_for);
			save_errno = errno;
			if (!(proc_names_list)) {
				success = 0;
				fprintf
					( my_lfp
					, "calloc: allocate displacements failed with errno = %d, %s\n"
					, save_errno
					, strerror(save_errno)
					);
				fflush(my_lfp);
			}
		}

		// allocate gatherv recieve counts vector
		if (success) {

			ask_for = sizeof(int) * my_mpi_struct->n_mpi_ranks;
			gatherv_recieve_counts = (int*) calloc(one_l, ask_for);
			save_errno = errno;
			if (!(proc_names_list)) {
				success = 0;
				fprintf
					( my_lfp
					, "calloc: allocate gatherv_recieve_counts failed with errno = %d, %s\n"
					, save_errno
					, strerror(save_errno)
					);
				fflush(my_lfp);
			}
		}	

		// fill displacement array and recieve counts array
		if (success) {

			for (i = 0; i < n_mpi_ranks; i++) {
				displacements[i] = proc_name_length * i;
				gatherv_recieve_counts[i] = 1;
			}
		}
	}

	if (success) {

		// gather processor names from all ranks
		mpi_error = MPI_Gatherv
			( my_processor_name
			, proc_name_length
			, MPI_BYTE
			, proc_name_list
			, gatherv_recv_counts
			, displacements
			, MPI_BYTE
			, root
			, my_mpi_struct->comm
			);
		success = check_mpi_error(my_lfp, "\nMPI_Gatherv proc names failed\n", comm, mpi_error);
	}

	if (my_mpi_struct->mpi_rank == 0) {

		if (success) {

			// sort proc names and mpi ranks
			for (i = 0; i < n_mpi_ranks; i++){
				mpi_rank_list[i] = i;
			}
			sort_mpi_nodes_ranks(proc_name_list, &mpi_rank_order_list);

		}
	}

	if (success) {

		// send everyone their root rank
	}

    return success;
}
