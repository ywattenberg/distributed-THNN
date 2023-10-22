#pragma once
// @generated by torchgen/gen.py from DispatchKeyFunction.h

// NB: The implementing C++ file is RegisterDispatchKey.cpp

// The only #includes we need are for custom classes that have defaults in the C++ API
#include <c10/core/MemoryFormat.h>
#include <c10/core/Scalar.h>
#include <ATen/core/Reduction.h>

// Forward declarations of any types needed in the operator signatures.
// We can't directly include these classes because it will cause circular include dependencies.
// This file is included by TensorBody.h, which defines the Tensor class.
#include <ATen/core/ATen_fwd.h>

namespace at {

namespace compositeimplicitautograd {

TORCH_API at::Tensor conv_transpose1d(const at::Tensor & input, const at::Tensor & weight, const c10::optional<at::Tensor> & bias={}, at::IntArrayRef stride=1, at::IntArrayRef padding=0, at::IntArrayRef output_padding=0, int64_t groups=1, at::IntArrayRef dilation=1);
TORCH_API at::Tensor conv_transpose1d_symint(const at::Tensor & input, const at::Tensor & weight, const c10::optional<at::Tensor> & bias={}, at::IntArrayRef stride=1, c10::SymIntArrayRef padding=c10::SymInt(0), c10::SymIntArrayRef output_padding=c10::SymInt(0), int64_t groups=1, at::IntArrayRef dilation=1);

} // namespace compositeimplicitautograd
} // namespace at
