#pragma once

#include <string>
#include <utility>

#include "EnumMaps.h"
#include "HybridGPUDeviceLostInfoSpec.hpp"
#include "WebGPUObject.hpp"

#include "webgpu/webgpu_cpp.h"

namespace rnwgpu {

class GPUDeviceLostInfo
    : public WebGPUObject<margelo::nitro::webgpu::HybridGPUDeviceLostInfoSpec> {
public:
  GPUDeviceLostInfo(wgpu::DeviceLostReason reason, std::string message)
      : HybridObject(TAG), _reason(reason), _message(std::move(message)) {}

  margelo::nitro::webgpu::GPUDeviceLostReason getReason() override {
    return fromWGPU(_reason);
  }
  std::string getMessage() override { return _message; }

private:
  wgpu::DeviceLostReason _reason;
  std::string _message;
};

} // namespace rnwgpu
