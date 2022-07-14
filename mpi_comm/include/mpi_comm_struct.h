
#include "system_includes.h"

#ifndef _MPI_COMM_STRUCT_H_
#define _MPI_COMM_STRUCT_H_ 1

struct mpi_comm_struct {
	int64_t children[20];
	int64_t num_children;
	int64_t parent;
	int64_t mpi_rank;
	int64_t n_mpi_ranks;
	MPI_Comm comm;	
};

#endif
