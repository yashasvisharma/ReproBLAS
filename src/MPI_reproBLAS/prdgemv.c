/*
 *  Created   13/10/25   H.D. Nguyen
 */

//#include <mpi.h>
#include <stdlib.h>
#include <stdio.h>

#include "MPI_indexed.h"
#include "../MPI_indexed/MPI_dindexed.h"
#include "MPI_reproBLAS.h"
#include "indexedBLAS.h"
#include "reproBLAS.h"


void prdgemv(int rank, int nprocs, rblas_order_t Order, rblas_transpose_t TransA, int M, int N, double *myA, int lda, double *myX, int incX, double *Y, int incY){
    Idouble *myYI;
    Idouble *YI;
    int i;

    RMPI_Init();
    myYI = (Idouble*)malloc(M * sizeof(Idouble));
    for(i = 0; i < M; i++){
      sISetZero(myYI[i]);
    }
    dgemvI(Order, TransA, M, N/nprocs, myA, N/nprocs, myX, 1, YI, 1, DEFAULT_FOLD);

    if(rank == 0){
      YI = (Idouble*)malloc(M * sizeof(Idouble));
      for(i = 0; i < M; i++){
        sISetZero(YI[i]);
      }
    }

    MPI_Reduce(myYI, YI, M, MPI_IDOUBLE, MPI_RSUM, 0, MPI_COMM_WORLD);

    if(rank == 0){
      for(i = 0; i < M; i++){
        Y[i] = ddiconv(YI + i, DEFAULT_FOLD);
      }
    }
}
