#pragma once

// @generated by torchgen/gen.py from NativeFunction.h

#include <c10/core/Scalar.h>
#include <c10/core/Storage.h>
#include <c10/core/TensorOptions.h>
#include <c10/util/Deprecated.h>
#include <c10/util/Optional.h>
#include <c10/core/QScheme.h>
#include <ATen/core/Reduction.h>
#include <ATen/core/Tensor.h>
#include <tuple>
#include <vector>
#include <ATen/ops/addmm_meta.h>

namespace at {
namespace native {
struct TORCH_API structured_addmm_out_cpu : public at::meta::structured_addmm {
void impl(const at::Tensor & self, const at::Tensor & mat1, const at::Tensor & mat2, const at::Scalar & beta, const at::Scalar & alpha, const at::Tensor & out);
};
struct TORCH_API structured_addmm_out_cuda : public at::meta::structured_addmm {
void impl(const at::Tensor & self, const at::Tensor & mat1, const at::Tensor & mat2, const at::Scalar & beta, const at::Scalar & alpha, const at::Tensor & out);
};
TORCH_API at::Tensor addmm_sparse_dense_cpu(const at::Tensor & self, const at::Tensor & mat1, const at::Tensor & mat2, const at::Scalar & beta=1, const at::Scalar & alpha=1);
TORCH_API at::Tensor & addmm_out_sparse_dense_cpu(const at::Tensor & self, const at::Tensor & mat1, const at::Tensor & mat2, const at::Scalar & beta, const at::Scalar & alpha, at::Tensor & out);
TORCH_API at::Tensor & s_addmm_sparse_dense_cpu_(at::Tensor & self, const at::Tensor & mat1, const at::Tensor & mat2, const at::Scalar & beta=1, const at::Scalar & alpha=1);
TORCH_API at::Tensor addmm_sparse_dense_cuda(const at::Tensor & self, const at::Tensor & mat1, const at::Tensor & mat2, const at::Scalar & beta=1, const at::Scalar & alpha=1);
TORCH_API at::Tensor & addmm_out_sparse_dense_cuda(const at::Tensor & self, const at::Tensor & mat1, const at::Tensor & mat2, const at::Scalar & beta, const at::Scalar & alpha, at::Tensor & out);
TORCH_API at::Tensor & s_addmm_sparse_dense_cuda_(at::Tensor & self, const at::Tensor & mat1, const at::Tensor & mat2, const at::Scalar & beta=1, const at::Scalar & alpha=1);
TORCH_API at::Tensor addmm_sparse_compressed_dense(const at::Tensor & self, const at::Tensor & mat1, const at::Tensor & mat2, const at::Scalar & beta=1, const at::Scalar & alpha=1);
TORCH_API at::Tensor & addmm_out_sparse_compressed_cpu(const at::Tensor & self, const at::Tensor & mat1, const at::Tensor & mat2, const at::Scalar & beta, const at::Scalar & alpha, at::Tensor & out);
TORCH_API at::Tensor & addmm_out_sparse_compressed_cuda(const at::Tensor & self, const at::Tensor & mat1, const at::Tensor & mat2, const at::Scalar & beta, const at::Scalar & alpha, at::Tensor & out);
} // namespace native
} // namespace at
