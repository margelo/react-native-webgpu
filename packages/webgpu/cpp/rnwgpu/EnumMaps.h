//
//  EnumMaps.h
//  Pods
//
//  Created by Ritesh Shukla on 05/10/26.
//

#pragma once

#include <stdexcept>

#include "GPUCompilationMessageType.hpp"
#include "GPUDeviceLostReason.hpp"
#include "GPUQueryType.hpp"

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

inline margelo::nitro::webgpu::GPUQueryType fromWGPU(wgpu::QueryType type) {
  using margelo::nitro::webgpu::GPUQueryType;
  switch (type) {
  case wgpu::QueryType::Occlusion:
    return GPUQueryType::OCCLUSION;
  case wgpu::QueryType::Timestamp:
    return GPUQueryType::TIMESTAMP;
  }
  throw std::invalid_argument("Unknown wgpu::QueryType");
}

inline margelo::nitro::webgpu::GPUDeviceLostReason
fromWGPU(wgpu::DeviceLostReason reason) {
  using margelo::nitro::webgpu::GPUDeviceLostReason;
  switch (reason) {
  case wgpu::DeviceLostReason::Destroyed:
    return GPUDeviceLostReason::DESTROYED;
  case wgpu::DeviceLostReason::Unknown:
  case wgpu::DeviceLostReason::CallbackCancelled:
  case wgpu::DeviceLostReason::FailedCreation:
    return GPUDeviceLostReason::UNKNOWN;
  }
  throw std::invalid_argument("Unknown wgpu::DeviceLostReason");
}

} // namespace rnwgpu
