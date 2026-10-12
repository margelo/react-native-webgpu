#pragma once

#include <string>
#include <utility>

#include "HybridGPUCommandBufferSpec.hpp"
#include "WebGPUObject.hpp"

#include "webgpu/webgpu_cpp.h"

namespace rnwgpu {

class GPUCommandBuffer
    : public WebGPUObject<margelo::nitro::webgpu::HybridGPUCommandBufferSpec> {
public:
  GPUCommandBuffer(wgpu::CommandBuffer instance, std::string label)
      : HybridObject(TAG), _instance(std::move(instance)),
        _label(std::move(label)) {}

  std::string getLabel() override { return _label; }
  void setLabel(const std::string &label) override {
    _label = label;
    _instance.SetLabel(_label.c_str());
  }

  const wgpu::CommandBuffer get() { return _instance; }

private:
  wgpu::CommandBuffer _instance;
  std::string _label;
};

} // namespace rnwgpu
