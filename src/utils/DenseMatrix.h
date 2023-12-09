#ifndef _DENSE_MATRIX_H_
#define _DENSE_Matrix_H_


#include <iostream>
#include <fstream>
#include <cmath>
#include <mpi.h>
#include <vector>

#include "CombBLAS/CombBLAS.h"
#include "CombBLAS/SpParMat.h"
#include "CombBLAS/SpParHelper.h"
#include "CombBLAS/SpDCCols.h"


namespace combblas{

template<class NT>
class DenseMatrix 
{
  public:
    std::vector<NT> *getValues() {return values;}
    int getLocalRows() {return localRows;}
    int getLocalCols() {return localCols;}
    std::shared_ptr<CommGrid> getCommGrid() {return commGrid;}

    DenseMatrix<NT>(int rows, int cols, std::vector<NT> *values, std::shared_ptr<CommGrid> grid): values(values), localRows(rows), localCols(cols)
    {
      commGrid = grid;
    }

    DenseMatrix<NT>(int rows, int cols, std::vector<NT> *values, MPI_Comm world): values(values), localRows(rows), localCols(cols)
    {
      commGrid.reset(new CommGrid(MPI_COMM_WORLD, rows, cols));
    }

    // ~DenseMatrix<NT>()
    // {

    //   delete values;
    // }

    

  private:
    int localRows;
    int localCols;
    std::vector<NT> *values;
    std::shared_ptr<CommGrid> commGrid; 
};

int getSendingRankInRow(int rank, int diagOffset, int cols){
  int rowPos = rank / cols;
  return rowPos * cols + (rowPos + diagOffset) % cols;
}


int getRecvRank(int rank, int round, int cols, int size){
  int RecvRank = rank - (round * cols);
  if (RecvRank < 0){
    RecvRank = size + rank - (round * cols);
  }
  return RecvRank;
}

// template<typename IT, typename NT, typename DER>	
// static void SendAndReceive(MPI_Comm & comm1d, , std::vector<IT> * essentials, int dest, int source)
// {
//   int myrank;
//   MPI_Comm_rank(comm1d, &myrank);

//   if(myrank != root)
// 	{
// 		Matrix.Create(essentials);		// allocate memory for arrays		
// 	}

// 	Arr<IT,NT> arrinfo = Matrix.GetArrays();
// 	for(unsigned int i=0; i< arrinfo.indarrs.size(); ++i)	// get index arrays
// 	{
// 		MPI_Bcast(arrinfo.indarrs[i].addr, arrinfo.indarrs[i].count, MPIType<IT>(), root, comm1d);
// 	}
// 	for(unsigned int i=0; i< arrinfo.numarrs.size(); ++i)	// get numerical arrays
// 	{
// 		MPI_Bcast(arrinfo.numarrs[i].addr, arrinfo.numarrs[i].count, MPIType<NT>(), root, comm1d);
// 	}
// }


template<typename IT, typename NT>	
static void BCastMatrixDense(MPI_Comm & comm1d, std::vector<NT> * values, std::vector<IT> essentials, int sendingRank)
{
  int myrank;
  MPI_Comm_rank(comm1d, &myrank);


  MPI_Bcast(essentials.data(), essentials.size(), MPIType<IT>(), sendingRank, comm1d);

  if (myrank != sendingRank){
    values->resize(essentials[0]);
  }

  MPI_Bcast(values->data(), essentials[0], MPIType<NT>(), sendingRank, comm1d); 
}

template<typename SR, typename IT, typename NT, typename DER>
void localMatrixMult(size_t dense_rows, size_t dense_cols, std::vector<NT>* dense_A, DER* sparse_B, std::vector<NT> * outValues){
  int myrank;
  MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
  
  IT nnz = sparse_B->getnnz();
  IT cols_spars = sparse_B->getncol();
  IT rows_spars = sparse_B->getnrow();

  if (dense_cols != rows_spars) {
    throw std::invalid_argument( "DIMENSIONS DON'T MATCH" );        
  }

  if (nnz == 0){
    return;
  }

  Dcsc<IT, NT>* Bdcsc = sparse_B->GetDCSC();
  for(size_t i = 0; i < dense_rows; i++){
    for (size_t j = 0; j < Bdcsc->nzc; j++){
      IT col = Bdcsc->jc[j];
      size_t nnzInCol = Bdcsc->cp[j+1] - Bdcsc->cp[j];
      for(size_t k =0; k < nnzInCol; k++){
        IT sparseRow = Bdcsc->ir[Bdcsc->cp[j]+ k];
        NT elem = Bdcsc->numx[Bdcsc->cp[j]+ k];
        outValues->at(i * cols_spars + col) += SR::multiply(dense_A->at(i * dense_cols + sparseRow), elem);
      }

    }
  }
}


template<typename SR, typename IT, typename NT, typename DER>
DenseMatrix<NT> fox(DenseMatrix<NT> &A, SpParMat<IT, NT, DER> &B)
{
  MPI_Comm commi = A.getCommGrid().GetWorld();
  int size, myrank;
  MPI_Comm_size(commi, &size);
  MPI_Comm_rank(commi, &myrank);

  int rowDense = A.getCommGrid().GetGridRows();
  int colDense = A.getCommGrid().GetGridCols();

  int rowSparse = B.getCommGrid().GetGridRows();
  int colSparse = B.getCommGrid().GetGridCols();

  if (myrank == 0){
    if (rowDense != rowSparse || colDense != colSparse || rowDense != colDense){
      MPI_Abort(commi, 1);
    }
  }

  DER * B_elems = B.getSpSeq();
  std::vector<DenseMatrix<NT>*> results;

  // Round 0:
  std::vector<NT> bufferA;
  int size_vec;
  int sendingRank = getSendingRankInRow(myrank, 0, colDense);
  if (myrank == sendingRank){
    size_vec = A.getValues().size_vec();
    bufferA = *A.getValues();
  }
  MPI_Bcast(&size_vec, 1, MPI_INT, sendingRank, A.getCommGrid().GetRowWorld);

  bufferA.resize(size_vec);
  
  if (std::is_same<NT, double>::value){
      MPI_Bcast(bufferA.data(), size_vec, MPI_DOUBLE, sendingRank, A.getCommGrid().GetRowWorld);
  }

  DenseMatrix<NT> A_tmp = DenseMatrix<NT>(rowDense, colDense, &bufferA, A.getCommGrid);

  results.push_back(localMatrixMult(A_tmp, B));

  // other Rounds:
  std::vector<std::tuple<IT,IT,NT>> bufferB;
  for (size_t round = 1; round < colDense; round++){
    // BroadCasting A
    sendingRank = getSendingRankInRow(myrank, round, colDense);

    if (myrank == sendingRank){
      size_vec = A.getValues().size_vec();
      bufferA = *A.getValues();
    }

    MPI_Bcast(&size_vec, 1, MPI_INT, sendingRank, A.getCommGrid().GetRowWorld);
    bufferA.resize(size_vec);

    if (std::is_same<NT, double>::value){
      MPI_Bcast(bufferA.data(), size_vec, MPI_DOUBLE, sendingRank, A.getCommGrid().GetRowWorld);
    }
    
    MPI_Request send_request, recv_request;
    MPI_Status status;
    // Sending the correct B block
    int RecvRank = getRecvRank(myrank, round, colDense, size);
    // int Send_rank = 
    int sizeSparse = B_elems->getnnz();

    MPI_Isend(&sizeSparse, 1, MPI_INT, RecvRank, 0, MPI_COMM_WORLD, &send_request);
    

  }
    

}

template<typename SR, typename IT, typename NT, typename DER>
DenseMatrix<NT> fox2(DenseMatrix<NT> &A, SpParMat<IT, NT, DER> &B){
    int myrank;
    MPI_Comm_rank(MPI_COMM_WORLD,&myrank);
    int rowDense = A.getCommGrid()->GetGridRows();
    int colDense = A.getCommGrid()->GetGridCols();

    int stages, dummy;
    std::shared_ptr<CommGrid> GridC = ProductGrid((A.getCommGrid()).get(), (B.getcommgrid()).get(), stages, dummy, dummy);		
    

    IT ** BRecvSizes = SpHelper::allocate2D<IT>(DER::esscount, stages);
    SpParHelper::GetSetSizes( *(B.getSpSeq()), BRecvSizes, (B.getcommgrid())->GetColWorld());


    std::vector<NT> * bufferA = new std::vector<NT>();
    std::vector<IT> essentialsA(3); // saves rows, cols and total number of elements of block
    std::vector<IT> ess = std::vector<IT>();
    std::vector<NT> * out;
    DER * bufferB;
    // MPI_Comm RowWorldA = A.getCommGrid()->GetRowWorld;
    int rankAinRow = A.getCommGrid()->GetRankInProcRow();
    int rankAinCol = A.getCommGrid()->GetRankInProcCol();
    int rankBinCol = B.getcommgrid()->GetRankInProcCol();

    int denseLocalRows = A.getLocalRows();
    int denseLocalCols = A.getLocalCols();

    int sparseLocalRows = B.getlocalrows();
    int sparseLocalCols = B.getlocalcols();

    std::vector<NT> * localOut = new std::vector<NT>(denseLocalRows * sparseLocalCols);
    
    //First Iteration: Matrix B already in Place
    // int sendingRank = rankAinCol;	SpParHelper::GetSetSizes( *(B.spSeq), BRecvSizes, (B.commGrid)->GetColWorld());


    // if (rankAinRow == sendingRank){
    //   bufferA = A.getValues();
    //   essentialsA[1] = A.getLocalRows();
    //   essentialsA[2] = A.getLocalCols();
    //   essentialsA[0] = essentialsA[1] * essentialsA[2];
    // }

    // BCastMatrixDense(RowWorldA, bufferA, essentialsA, sendingRank);
    // out.push(localMatrixMult(bufferA, B));

    //other stages:
    for (int i = 0; i < stages; i++){
      int sendingRank = i;

      // cout << "this is the sending rank " << sendingRank << endl;
      
      if (rankAinRow == sendingRank){
        bufferA = A.getValues();

        // for (int i = 0; i < denseLocalRows; i++){
        //     for (int j = 0; j < denseLocalCols; j++){
        //         std::cout << (*bufferA)[i*denseLocalCols + j] << " ";
        //     }
        //     std::cout << std::endl;
        // }
        essentialsA[1] = A.getLocalRows();
        essentialsA[2] = A.getLocalCols();
        essentialsA[0] = essentialsA[1] * essentialsA[2];
      }

      BCastMatrixDense(GridC->GetRowWorld(), bufferA, essentialsA, sendingRank);

      if (rankAinRow != sendingRank){
        std::cout << "from rank " << myrank << std::endl;
        for (int i = 0; i < denseLocalRows; i++){
            for (int j = 0; j < denseLocalCols; j++){
                std::cout << (*bufferA)[i*denseLocalCols + j] << " ";
            }
            std::cout << std::endl;
        }
      }

      if(rankBinCol == sendingRank)
      {
        bufferB = B.getSpSeq();

        for(auto colit = bufferB->begcol(); colit != bufferB->endcol(); ++colit)	// iterate over columns
	      {
            for(auto nzit = bufferB->begnz(colit); nzit != bufferB->endnz(colit); ++nzit)
            {	
                // std::cout << "before: " << nzit.rowid() << '\t' << colit.colid() << '\t' << nzit.value() << '\n';

            }
	      }
      }
      else
      {
        ess.resize(DER::esscount);		
        for(int j=0; j< DER::esscount; ++j)	
        {
          ess[j] = BRecvSizes[j][i];
        }	
        bufferB = new DER();
      }
      int rankOfColWorld;
      MPI_Comm_rank(GridC->GetColWorld(),&rankOfColWorld);
      // std::cout << "rank in col comm: " << rankOfColWorld << endl;
      SpParHelper::BCastMatrix<IT, NT, DER>(GridC->GetColWorld(), *bufferB, ess, sendingRank);

      // std::cout << "hello from rank " << myrank << std::endl;
      // std::cout << "stage: " << i << endl;

      localMatrixMult<SR, IT, NT, DER>(denseLocalRows, denseLocalCols, bufferA, bufferB, localOut);

    }

    return DenseMatrix<NT>(denseLocalRows, sparseLocalCols, localOut, GridC);
}

}


#endif