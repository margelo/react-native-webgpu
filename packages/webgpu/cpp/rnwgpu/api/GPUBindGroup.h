#pragma once

#include <string>
#include <utility>

#include "HybridGPUBindGroupSpec.hpp"
#include "WebGPUObject.hpp"

#include "webgpu/webgpu_cpp.h"

namespace rnwgpu {

class GPUBindGroup
    : public WebGPUObject<margelo::nitro::webgpu::HybridGPUBindGroupSpec> {
public:
  GPUBindGroup(wgpu::BindGroup instance, std::string label)
      : HybridObject(TAG), _instance(std::move(instance)),
        _label(std::move(label)) {}

  std::string getLabel() override { return _label; }
  void setLabel(const std::string &label) override {
    _label = label;
    _instance.SetLabel(_label.c_str());
  }

  const wgpu::BindGroup get() { return _instance; }

private:
  wgpu::BindGroup _instance;
  std::string _label;
};

} // namespace rnwgpu
