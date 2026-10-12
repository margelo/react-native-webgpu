#pragma once

#include <string>
#include <utility>

#include "HybridGPUBindGroupLayoutSpec.hpp"
#include "WebGPUObject.hpp"

#include "webgpu/webgpu_cpp.h"

namespace rnwgpu {

class GPUBindGroupLayout
    : public WebGPUObject<
          margelo::nitro::webgpu::HybridGPUBindGroupLayoutSpec> {
public:
  GPUBindGroupLayout(wgpu::BindGroupLayout instance, std::string label)
      : HybridObject(TAG), _instance(std::move(instance)),
        _label(std::move(label)) {}

  std::string getLabel() override { return _label; }
  void setLabel(const std::string &label) override {
    _label = label;
    _instance.SetLabel(_label.c_str());
  }

  const wgpu::BindGroupLayout get() { return _instance; }

protected:
  size_t getExternalMemorySize() noexcept override { return 512; }

private:
  wgpu::BindGroupLayout _instance;
  std::string _label;
};

} // namespace rnwgpu
