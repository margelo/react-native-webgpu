#pragma once

#include <memory>
#include <string>
#include <utility>

#include "GPUInternalError.h"
#include "GPUOutOfMemoryError.h"
#include "GPUValidationError.h"
#include "HybridGPUUncapturedErrorEventSpec.hpp"
#include "WebGPUObject.hpp"

namespace rnwgpu {

class GPUUncapturedErrorEvent
    : public WebGPUObject<
          margelo::nitro::webgpu::HybridGPUUncapturedErrorEventSpec> {
public:
  explicit GPUUncapturedErrorEvent(
      std::shared_ptr<margelo::nitro::webgpu::HybridGPUErrorSpec> error)
      : HybridObject(TAG), _error(std::move(error)) {}

  std::string getType() override { return "uncapturederror"; }
  std::shared_ptr<margelo::nitro::webgpu::HybridGPUErrorSpec>
  getError() override {
    return _error;
  }

private:
  std::shared_ptr<margelo::nitro::webgpu::HybridGPUErrorSpec> _error;
};

} // namespace rnwgpu
