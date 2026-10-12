//
//  GPUColor.hpp
//  Pods
//
//  Created by Dave Mkpa-Eke on 06/10/26.
//

#pragma once

#include <stdexcept>

#include <NitroModules/JSIConverter.hpp>

namespace margelo::nitro::webgpu {

struct GPUColor {
  double r;
  double g;
  double b;
  double a;
};

} // namespace margelo::nitro::webgpu

namespace margelo::nitro {

template <> struct JSIConverter<webgpu::GPUColor> final {
  static inline webgpu::GPUColor fromJSI(jsi::Runtime &runtime,
                                         const jsi::Value &arg) {
    webgpu::GPUColor result{};
    jsi::Object object = arg.asObject(runtime);
    if (object.isArray(runtime)) {
      jsi::Array array = object.getArray(runtime);
      if (array.size(runtime) >= 4) {
        result.r = array.getValueAtIndex(runtime, 0).asNumber();
        result.g = array.getValueAtIndex(runtime, 1).asNumber();
        result.b = array.getValueAtIndex(runtime, 2).asNumber();
        result.a = array.getValueAtIndex(runtime, 3).asNumber();
      }
    } else {
      if (object.hasProperty(runtime, "r")) {
        result.r = object.getProperty(runtime, "r").asNumber();
      }
      if (object.hasProperty(runtime, "g")) {
        result.g = object.getProperty(runtime, "g").asNumber();
      }
      if (object.hasProperty(runtime, "b")) {
        result.b = object.getProperty(runtime, "b").asNumber();
      }
      if (object.hasProperty(runtime, "a")) {
        result.a = object.getProperty(runtime, "a").asNumber();
      }
    }
    return result;
  }
  static inline jsi::Value toJSI(jsi::Runtime &, const webgpu::GPUColor &) {
    throw std::runtime_error("GPUColor cannot be converted to JS");
  }
  static inline bool canConvert(jsi::Runtime &, const jsi::Value &value) {
    return value.isObject();
  }
};

} // namespace margelo::nitro
