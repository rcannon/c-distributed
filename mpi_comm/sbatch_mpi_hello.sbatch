#!/bin/bash

#SBATCH -A ops
#SBATCH -p all
##SBATCH --ntasks-per-node=64
#SBATCH -N 1
#SBATCH -t 60
#SBATCH -o out%J.out
#SBATCH -e err%J.out
#SBATCH -J mvp

source /etc/profile.d/modules.sh
source ../env.sh

ulimit -s

echo module list output
echo
module list > ml.lis 2>&1
cat ml.lis
/bin/rm -f ml.lis

echo
echo printenv output
echo
printenv

echo
echo limit output
echo
ulimit -a

echo 
echo "Building."
echo 

make clean
make

echo
echo ldd output
echo 
ldd bin/mpi_hello
echo 
echo program output
echo 

echo 
echo "Remove old thread files."
echo 

rm thread_files/*

echo 
echo "Running program."
echo 

mpirun -n 16 bin/mpi_hello

echo
echo "clean up"
echo

make clean

echo
echo "done"
echo