#pragma once

// @generated by torchgen/gen.py from Function.h

#include <ATen/Context.h>
#include <ATen/DeviceGuard.h>
#include <ATen/TensorUtils.h>
#include <ATen/TracerMode.h>
#include <ATen/core/Generator.h>
#include <ATen/core/Reduction.h>
#include <ATen/core/Tensor.h>
#include <c10/core/Scalar.h>
#include <c10/core/Storage.h>
#include <c10/core/TensorOptions.h>
#include <c10/util/Deprecated.h>
#include <c10/util/Optional.h>



#include <ATen/ops/tanh_backward_ops.h>

namespace at {


// aten::tanh_backward.grad_input(Tensor grad_output, Tensor output, *, Tensor(a!) grad_input) -> Tensor(a!)
inline at::Tensor & tanh_backward_out(at::Tensor & grad_input, const at::Tensor & grad_output, const at::Tensor & output) {
    return at::_ops::tanh_backward_grad_input::call(grad_output, output, grad_input);
}
// aten::tanh_backward.grad_input(Tensor grad_output, Tensor output, *, Tensor(a!) grad_input) -> Tensor(a!)
inline at::Tensor & tanh_backward_outf(const at::Tensor & grad_output, const at::Tensor & output, at::Tensor & grad_input) {
    return at::_ops::tanh_backward_grad_input::call(grad_output, output, grad_input);
}

// aten::tanh_backward(Tensor grad_output, Tensor output) -> Tensor
inline at::Tensor tanh_backward(const at::Tensor & grad_output, const at::Tensor & output) {
    return at::_ops::tanh_backward::call(grad_output, output);
}

}
