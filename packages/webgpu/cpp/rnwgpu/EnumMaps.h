//
//  EnumMaps.h
//  Pods
//
//  Created by Ritesh Shukla on 05/10/26.
//

#pragma once

#include <stdexcept>

#include "GPUCompilationMessageType.hpp"

#include "webgpu/webgpu_cpp.h"

namespace rnwgpu {

inline margelo::nitro::webgpu::GPUCompilationMessageType
fromWGPU(wgpu::CompilationMessageType type) {
  using margelo::nitro::webgpu::GPUCompilationMessageType;
  switch (type) {
  case wgpu::CompilationMessageType::Error:
    return GPUCompilationMessageType::ERROR;
  case wgpu::CompilationMessageType::Warning:
    return GPUCompilationMessageType::WARNING;
  case wgpu::CompilationMessageType::Info:
    return GPUCompilationMessageType::INFO;
  }
  throw std::invalid_argument("Unknown wgpu::CompilationMessageType");
}

} // namespace rnwgpu
