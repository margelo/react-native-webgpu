//
//  GPUOrigin2D.hpp
//  Pods
//
//  Created by Dave Mkpa-Eke on 06/10/26.
//

#pragma once

#include <stdexcept>

#include <NitroModules/JSIConverter.hpp>

namespace margelo::nitro::webgpu {

struct GPUOrigin2D {
  double x = 0;
  double y = 0;
};

} // namespace margelo::nitro::webgpu

namespace margelo::nitro {

template <> struct JSIConverter<webgpu::GPUOrigin2D> final {
  static inline webgpu::GPUOrigin2D fromJSI(jsi::Runtime &runtime,
                                            const jsi::Value &arg) {
    webgpu::GPUOrigin2D result{};
    jsi::Object object = arg.asObject(runtime);
    if (object.isArray(runtime)) {
      jsi::Array array = object.getArray(runtime);
      size_t size = array.size(runtime);
      if (size == 0) {
        throw std::runtime_error("GPUOrigin2D needs at least 1 item");
      }
      result.x = array.getValueAtIndex(runtime, 0).asNumber();
      if (size > 1) {
        result.y = array.getValueAtIndex(runtime, 1).asNumber();
      }
    } else {
      if (object.hasProperty(runtime, "x")) {
        result.x = object.getProperty(runtime, "x").asNumber();
      }
      if (object.hasProperty(runtime, "y")) {
        result.y = object.getProperty(runtime, "y").asNumber();
      }
    }
    return result;
  }
  static inline jsi::Value toJSI(jsi::Runtime &, const webgpu::GPUOrigin2D &) {
    throw std::runtime_error("GPUOrigin2D cannot be converted to JS");
  }
  static inline bool canConvert(jsi::Runtime &, const jsi::Value &value) {
    return value.isObject();
  }
};

} // namespace margelo::nitro
