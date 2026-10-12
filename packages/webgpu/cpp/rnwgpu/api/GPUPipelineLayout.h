#pragma once

#include <string>
#include <utility>

#include "HybridGPUPipelineLayoutSpec.hpp"
#include "WebGPUObject.hpp"

#include "webgpu/webgpu_cpp.h"

namespace rnwgpu {

class GPUPipelineLayout
    : public WebGPUObject<margelo::nitro::webgpu::HybridGPUPipelineLayoutSpec> {
public:
  GPUPipelineLayout(wgpu::PipelineLayout instance, std::string label)
      : HybridObject(TAG), _instance(std::move(instance)),
        _label(std::move(label)) {}

  std::string getLabel() override { return _label; }
  void setLabel(const std::string &label) override {
    _label = label;
    _instance.SetLabel(_label.c_str());
  }

  const wgpu::PipelineLayout get() { return _instance; }

private:
  wgpu::PipelineLayout _instance;
  std::string _label;
};

} // namespace rnwgpu
