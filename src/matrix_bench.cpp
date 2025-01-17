#include <mpi.h>
#include <cblas.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <chrono>

#include "CombBLAS/CombBLAS.h"
#include "CombBLAS/CommGrid3D.h"
#include "CombBLAS/SpParMat3D.h"
#include "CombBLAS/DenseParMat.h"
#include "CombBLAS/ParFriends.h"
#include "CombBLAS/FullyDistVec.h"
#include "CombBLAS/SpParMat.h"

#include "utils/parDenseGEMM.h"
#include "DenseMatrix/DenseMatrix.h"
#include "DenseMatrix/DenseMatrixAlgorithms.h"

using namespace std;
using namespace combblas;

typedef PlusTimesSRing<double, double> PTFF;

int main(int argc, char* argv[]) {
    int opt;
    std::string tmp_dir;
    int run_id = -1;
    int iterations = 10;
    while((opt = getopt(argc, argv, "t:i:")) != -1){
      switch(opt){
        case 't':
          tmp_dir = optarg;
          break;
        case 'i':
          run_id = atoi(optarg);
          break;
        default:
          std::cerr << "Invalid command line argument" << std::endl;
          exit(1);
      }
    }

    MPI_Init(&argc, &argv);

    int size, rank;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    {
      shared_ptr<CommGrid> fullWorld;
      fullWorld.reset( new CommGrid(MPI_COMM_WORLD, 0, 0) );

      for (int scale = 1; scale <= 1; scale*=2) {
        // create dense matrix
        std::string filename = tmp_dir + "/data/random/scale_" + std::to_string(scale) + "/features.mtx";
        std::cout << "Reading " << filename << std::endl;
        DenseMatrix<double> A(0, 0, fullWorld);
        A.ParallelReadDMM(filename, false);

        DenseMatrix<double> B(0, 0, fullWorld);
        B.ParallelReadDMM(filename, false);

        using std::chrono::high_resolution_clock;
        using std::chrono::duration_cast;
        using std::chrono::duration;
        using std::chrono::milliseconds;

        for (int i = 0; i < iterations; i++) {
          MPI_Barrier(MPI_COMM_WORLD);
          auto t1 = high_resolution_clock::now();

          DenseMatrix<double> C = DenseDenseMult<PTFF, double>(A, B);

          if (rank == 0){
            std::cout << "C: " << C.getnrow() << " " << C.getncol() << std::endl;
          }

          MPI_Barrier(MPI_COMM_WORLD);

          if (rank == 0) {
            auto t2 = high_resolution_clock::now();
            /* Getting number of milliseconds as an integer. */
            auto ms_int = duration_cast<milliseconds>(t2 - t1);
            /* Getting number of milliseconds as a double. */
            duration<double, std::milli> ms_double = t2 - t1;

            std::cout <<"Forward took " << ms_int.count() << "ms\n";

            std::ofstream outfile;
            outfile.open("../data/timing/mm_bench.csv", std::ios_base::app);
            outfile << run_id << "," << scale << "," << i << "," << ms_int.count() << "\n";
          }
        }

        delete A.getValues();
        delete B.getValues();
      }
    }

    MPI_Finalize();
}