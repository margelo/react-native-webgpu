//
//  GPUExtent3D.hpp
//  Pods
//
//  Created by Dave Mkpa-Eke on 06/10/26.
//

#pragma once

#include <stdexcept>

#include <NitroModules/JSIConverter.hpp>

namespace margelo::nitro::webgpu {

struct GPUExtent3D {
  double width;
  double height = 1;
  double depthOrArrayLayers = 1;
};

} // namespace margelo::nitro::webgpu

namespace margelo::nitro {

template <> struct JSIConverter<webgpu::GPUExtent3D> final {
  static inline webgpu::GPUExtent3D fromJSI(jsi::Runtime &runtime,
                                            const jsi::Value &arg) {
    webgpu::GPUExtent3D result{};
    jsi::Object object = arg.asObject(runtime);
    if (object.isArray(runtime)) {
      jsi::Array array = object.getArray(runtime);
      size_t size = array.size(runtime);
      if (size == 0) {
        throw std::runtime_error("GPUExtent3D needs at least 1 item");
      }
      result.width = array.getValueAtIndex(runtime, 0).asNumber();
      if (size > 1) {
        result.height = array.getValueAtIndex(runtime, 1).asNumber();
      }
      if (size > 2) {
        result.depthOrArrayLayers =
            array.getValueAtIndex(runtime, 2).asNumber();
      }
    } else {
      if (!object.hasProperty(runtime, "width")) {
        throw std::runtime_error("GPUExtent3D.width is required");
      }
      result.width = object.getProperty(runtime, "width").asNumber();
      if (object.hasProperty(runtime, "height")) {
        result.height = object.getProperty(runtime, "height").asNumber();
      }
      if (object.hasProperty(runtime, "depthOrArrayLayers")) {
        result.depthOrArrayLayers =
            object.getProperty(runtime, "depthOrArrayLayers").asNumber();
      }
    }
    return result;
  }
  static inline jsi::Value toJSI(jsi::Runtime &, const webgpu::GPUExtent3D &) {
    throw std::runtime_error("GPUExtent3D cannot be converted to JS");
  }
  static inline bool canConvert(jsi::Runtime &, const jsi::Value &value) {
    return value.isObject();
  }
};

} // namespace margelo::nitro
