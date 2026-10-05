//
//  GPUSize64.hpp
//  Pods
//
//  Created by Dave Mkpa-Eke on 06/10/26.
//

#pragma once

#include <cstdint>

#include <NitroModules/JSIConverter.hpp>

#include "EnforceRange.h"

namespace margelo::nitro::webgpu {

struct GPUSize64 {
  uint64_t value;
};

} // namespace margelo::nitro::webgpu

namespace margelo::nitro {

template <> struct JSIConverter<webgpu::GPUSize64> final {
  static inline webgpu::GPUSize64 fromJSI(jsi::Runtime &,
                                          const jsi::Value &arg) {
    return webgpu::GPUSize64(
        rnwgpu::enforceRange<uint64_t>(arg.asNumber(), "GPUSize64"));
  }
  static inline jsi::Value toJSI(jsi::Runtime &, const webgpu::GPUSize64 &arg) {
    return jsi::Value(static_cast<double>(arg.value));
  }
  static inline bool canConvert(jsi::Runtime &, const jsi::Value &value) {
    return value.isNumber();
  }
};

} // namespace margelo::nitro
