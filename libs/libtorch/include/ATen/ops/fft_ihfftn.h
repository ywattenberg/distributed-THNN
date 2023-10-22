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



#include <ATen/ops/fft_ihfftn_ops.h>

namespace at {


// aten::fft_ihfftn(Tensor self, SymInt[1]? s=None, int[1]? dim=None, str? norm=None) -> Tensor
inline at::Tensor fft_ihfftn(const at::Tensor & self, at::OptionalIntArrayRef s=c10::nullopt, at::OptionalIntArrayRef dim=c10::nullopt, c10::optional<c10::string_view> norm=c10::nullopt) {
    return at::_ops::fft_ihfftn::call(self, s.has_value() ? c10::make_optional(c10::fromIntArrayRefSlow(*s)) : c10::nullopt, dim, norm);
}
namespace symint {
  template <typename T, typename = std::enable_if_t<std::is_same<T, int64_t>::value>>
  at::Tensor fft_ihfftn(const at::Tensor & self, at::OptionalIntArrayRef s=c10::nullopt, at::OptionalIntArrayRef dim=c10::nullopt, c10::optional<c10::string_view> norm=c10::nullopt) {
    return at::_ops::fft_ihfftn::call(self, s.has_value() ? c10::make_optional(c10::fromIntArrayRefSlow(*s)) : c10::nullopt, dim, norm);
  }
}

// aten::fft_ihfftn(Tensor self, SymInt[1]? s=None, int[1]? dim=None, str? norm=None) -> Tensor
inline at::Tensor fft_ihfftn_symint(const at::Tensor & self, at::OptionalSymIntArrayRef s=c10::nullopt, at::OptionalIntArrayRef dim=c10::nullopt, c10::optional<c10::string_view> norm=c10::nullopt) {
    return at::_ops::fft_ihfftn::call(self, s, dim, norm);
}
namespace symint {
  template <typename T, typename = std::enable_if_t<std::is_same<T, c10::SymInt>::value>>
  at::Tensor fft_ihfftn(const at::Tensor & self, at::OptionalSymIntArrayRef s=c10::nullopt, at::OptionalIntArrayRef dim=c10::nullopt, c10::optional<c10::string_view> norm=c10::nullopt) {
    return at::_ops::fft_ihfftn::call(self, s, dim, norm);
  }
}

// aten::fft_ihfftn.out(Tensor self, SymInt[1]? s=None, int[1]? dim=None, str? norm=None, *, Tensor(a!) out) -> Tensor(a!)
inline const at::Tensor & fft_ihfftn_out(const at::Tensor & out, const at::Tensor & self, at::OptionalIntArrayRef s=c10::nullopt, at::OptionalIntArrayRef dim=c10::nullopt, c10::optional<c10::string_view> norm=c10::nullopt) {
    return at::_ops::fft_ihfftn_out::call(self, s.has_value() ? c10::make_optional(c10::fromIntArrayRefSlow(*s)) : c10::nullopt, dim, norm, out);
}
namespace symint {
  template <typename T, typename = std::enable_if_t<std::is_same<T, int64_t>::value>>
  const at::Tensor & fft_ihfftn_out(const at::Tensor & out, const at::Tensor & self, at::OptionalIntArrayRef s=c10::nullopt, at::OptionalIntArrayRef dim=c10::nullopt, c10::optional<c10::string_view> norm=c10::nullopt) {
    return at::_ops::fft_ihfftn_out::call(self, s.has_value() ? c10::make_optional(c10::fromIntArrayRefSlow(*s)) : c10::nullopt, dim, norm, out);
  }
}

// aten::fft_ihfftn.out(Tensor self, SymInt[1]? s=None, int[1]? dim=None, str? norm=None, *, Tensor(a!) out) -> Tensor(a!)
inline const at::Tensor & fft_ihfftn_outf(const at::Tensor & self, at::OptionalIntArrayRef s, at::OptionalIntArrayRef dim, c10::optional<c10::string_view> norm, const at::Tensor & out) {
    return at::_ops::fft_ihfftn_out::call(self, s.has_value() ? c10::make_optional(c10::fromIntArrayRefSlow(*s)) : c10::nullopt, dim, norm, out);
}
namespace symint {
  template <typename T, typename = std::enable_if_t<std::is_same<T, int64_t>::value>>
  const at::Tensor & fft_ihfftn_outf(const at::Tensor & self, at::OptionalIntArrayRef s, at::OptionalIntArrayRef dim, c10::optional<c10::string_view> norm, const at::Tensor & out) {
    return at::_ops::fft_ihfftn_out::call(self, s.has_value() ? c10::make_optional(c10::fromIntArrayRefSlow(*s)) : c10::nullopt, dim, norm, out);
  }
}

// aten::fft_ihfftn.out(Tensor self, SymInt[1]? s=None, int[1]? dim=None, str? norm=None, *, Tensor(a!) out) -> Tensor(a!)
inline const at::Tensor & fft_ihfftn_symint_out(const at::Tensor & out, const at::Tensor & self, at::OptionalSymIntArrayRef s=c10::nullopt, at::OptionalIntArrayRef dim=c10::nullopt, c10::optional<c10::string_view> norm=c10::nullopt) {
    return at::_ops::fft_ihfftn_out::call(self, s, dim, norm, out);
}
namespace symint {
  template <typename T, typename = std::enable_if_t<std::is_same<T, c10::SymInt>::value>>
  const at::Tensor & fft_ihfftn_out(const at::Tensor & out, const at::Tensor & self, at::OptionalSymIntArrayRef s=c10::nullopt, at::OptionalIntArrayRef dim=c10::nullopt, c10::optional<c10::string_view> norm=c10::nullopt) {
    return at::_ops::fft_ihfftn_out::call(self, s, dim, norm, out);
  }
}

// aten::fft_ihfftn.out(Tensor self, SymInt[1]? s=None, int[1]? dim=None, str? norm=None, *, Tensor(a!) out) -> Tensor(a!)
inline const at::Tensor & fft_ihfftn_symint_outf(const at::Tensor & self, at::OptionalSymIntArrayRef s, at::OptionalIntArrayRef dim, c10::optional<c10::string_view> norm, const at::Tensor & out) {
    return at::_ops::fft_ihfftn_out::call(self, s, dim, norm, out);
}
namespace symint {
  template <typename T, typename = std::enable_if_t<std::is_same<T, c10::SymInt>::value>>
  const at::Tensor & fft_ihfftn_outf(const at::Tensor & self, at::OptionalSymIntArrayRef s, at::OptionalIntArrayRef dim, c10::optional<c10::string_view> norm, const at::Tensor & out) {
    return at::_ops::fft_ihfftn_out::call(self, s, dim, norm, out);
  }
}

}
