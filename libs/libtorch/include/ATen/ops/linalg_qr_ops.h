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


struct TORCH_API linalg_qr {
  using schema = ::std::tuple<at::Tensor,at::Tensor> (const at::Tensor &, c10::string_view);
  using ptr_schema = schema*;
  // See Note [static constexpr char* members for windows NVCC]
  STATIC_CONSTEXPR_STR_INL_EXCEPT_WIN_CUDA(name, "aten::linalg_qr")
  STATIC_CONSTEXPR_STR_INL_EXCEPT_WIN_CUDA(overload_name, "")
  STATIC_CONSTEXPR_STR_INL_EXCEPT_WIN_CUDA(schema_str, "linalg_qr(Tensor A, str mode='reduced') -> (Tensor Q, Tensor R)")
  static ::std::tuple<at::Tensor,at::Tensor> call(const at::Tensor & A, c10::string_view mode);
  static ::std::tuple<at::Tensor,at::Tensor> redispatch(c10::DispatchKeySet dispatchKeySet, const at::Tensor & A, c10::string_view mode);
};

struct TORCH_API linalg_qr_out {
  using schema = ::std::tuple<at::Tensor &,at::Tensor &> (const at::Tensor &, c10::string_view, at::Tensor &, at::Tensor &);
  using ptr_schema = schema*;
  // See Note [static constexpr char* members for windows NVCC]
  STATIC_CONSTEXPR_STR_INL_EXCEPT_WIN_CUDA(name, "aten::linalg_qr")
  STATIC_CONSTEXPR_STR_INL_EXCEPT_WIN_CUDA(overload_name, "out")
  STATIC_CONSTEXPR_STR_INL_EXCEPT_WIN_CUDA(schema_str, "linalg_qr.out(Tensor A, str mode='reduced', *, Tensor(a!) Q, Tensor(b!) R) -> (Tensor(a!) Q, Tensor(b!) R)")
  static ::std::tuple<at::Tensor &,at::Tensor &> call(const at::Tensor & A, c10::string_view mode, at::Tensor & Q, at::Tensor & R);
  static ::std::tuple<at::Tensor &,at::Tensor &> redispatch(c10::DispatchKeySet dispatchKeySet, const at::Tensor & A, c10::string_view mode, at::Tensor & Q, at::Tensor & R);
};

}} // namespace at::_ops