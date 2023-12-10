#ifndef DIST_MODEL_H
#define DIST_MODEL_H

#include <torch/torch.h>
#include <vector>
#include <iostream>

#include "CombBLAS/CombBLAS.h"
#include "CombBLAS/CommGrid3D.h"
#include "CombBLAS/SpParMat3D.h"
#include "CombBLAS/DenseParMat.h"
#include "CombBLAS/FullyDistVec.h"
#include "CombBLAS/ParFriends.h"

#include "../utils/DenseMatrix.h"
#include "../utils/configParse.h"

using namespace std;
using namespace combblas;

typedef SpDCCols <int64_t, double> DCCols;
typedef SpParMat <int64_t, double, DCCols> MPI_DCCols;
typedef SpParMat<int64_t, double, SpDCCols<int64_t, double>> SPMAT_DOUBLE;
typedef DenseParMat<int64_t, double> DPMAT_DOUBLE;
typedef FullyDistVec <int64_t, double> DPVEC_DOUBLE;

class DistConv
{
    private:
        DPMAT_DOUBLE weights;
        DPVEC_DOUBLE bias;

    public:
        DPMAT_DOUBLE G_2;
        DPMAT_DOUBLE G_3;

        DistConv(int in_dim, int out_dim, bool withBias);

        DPMAT_DOUBLE forward(DPMAT_DOUBLE &input);
};

class DistModel
{
    private:
        int input_dim;
        std::vector<int>* layer_dim;
        int output_dim;
        int number_of_hid_layers;
        double dropout;
        std::vector<DistConv> layers;
        SPMAT_DOUBLE dvh;
        SPMAT_DOUBLE invde_ht_dvh;
        vector<double> w;
        SPMAT_DOUBLE G_1;

    public:
        DistModel(ConfigProperties &config, int in_dim);

        // forward function of the Model, it takes the features X (called input) and the constant leftSide of the expression 10 of the paper 
        // Hypergraph Neural Networks (called leftSide)
        DenseMatrix forward(const DenseMatrix &input);


};
#endif