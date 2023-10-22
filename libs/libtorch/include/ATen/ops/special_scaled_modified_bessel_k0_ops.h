#pragma once

// @generated by torchgen/gen.py from Operator.h

#include <tuple>
#include <vector>

// Forward declarations of any types needed in the operator signatures.
// We can't directly include these classes because it will cause circular include dependencies.
// This file is included by TensorBody.h, which defines the Tensor class.
#include <ATen/core/ATen_fwd.h>

namespace at {
namespace _ops {


struct TORCH_API special_scaled_modified_bessel_k0 {
  using schema = at::Tensor (const at::Tensor &);
  using ptr_schema = schema*;
  // See Note [static constexpr char* members for windows NVCC]
  STATIC_CONSTEXPR_STR_INL_EXCEPT_WIN_CUDA(name, "aten::special_scaled_modified_bessel_k0")
  STATIC_CONSTEXPR_STR_INL_EXCEPT_WIN_CUDA(overload_name, "")
  STATIC_CONSTEXPR_STR_INL_EXCEPT_WIN_CUDA(schema_str, "special_scaled_modified_bessel_k0(Tensor x) -> Tensor")
  static at::Tensor call(const at::Tensor & x);
  static at::Tensor redispatch(c10::DispatchKeySet dispatchKeySet, const at::Tensor & x);
};

struct TORCH_API special_scaled_modified_bessel_k0_out {
  using schema = at::Tensor & (const at::Tensor &, at::Tensor &);
  using ptr_schema = schema*;
  // See Note [static constexpr char* members for windows NVCC]
  STATIC_CONSTEXPR_STR_INL_EXCEPT_WIN_CUDA(name, "aten::special_scaled_modified_bessel_k0")
  STATIC_CONSTEXPR_STR_INL_EXCEPT_WIN_CUDA(overload_name, "out")
  STATIC_CONSTEXPR_STR_INL_EXCEPT_WIN_CUDA(schema_str, "special_scaled_modified_bessel_k0.out(Tensor x, *, Tensor(a!) out) -> Tensor(a!)")
  static at::Tensor & call(const at::Tensor & x, at::Tensor & out);
  static at::Tensor & redispatch(c10::DispatchKeySet dispatchKeySet, const at::Tensor & x, at::Tensor & out);
};

}} // namespace at::_ops
